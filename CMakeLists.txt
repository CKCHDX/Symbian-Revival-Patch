cmake_minimum_required(VERSION 3.15)
project(SROS C CXX ASM)

# Set C/C++ standards
set(CMAKE_C_STANDARD 99)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_C_FLAGS_RELEASE "-O2 -fPIC")
set(CMAKE_CXX_FLAGS_RELEASE "-O2 -fPIC")

# Architecture detection
if(NOT DEFINED PLATFORM)
    # Try to detect platform
    if(CMAKE_SYSTEM_PROCESSOR MATCHES "x86_64|AMD64")
        set(PLATFORM "x86_64")
    elseif(CMAKE_SYSTEM_PROCESSOR MATCHES "i386|i686")
        set(PLATFORM "x86")
    elseif(CMAKE_SYSTEM_PROCESSOR MATCHES "arm|ARM")
        set(PLATFORM "arm-eabi")
    else()
        set(PLATFORM "x86_64")
    endif()
endif()

message(STATUS "==========================================")
message(STATUS "SROS Build System")
message(STATUS "==========================================")
message(STATUS "Platform: ${PLATFORM}")
message(STATUS "Build Type: ${CMAKE_BUILD_TYPE}")
message(STATUS "C Compiler: ${CMAKE_C_COMPILER}")
message(STATUS "C++ Compiler: ${CMAKE_CXX_COMPILER}")
message(STATUS "==========================================")

# Symbian source root
set(SYMBIAN_ROOT "${CMAKE_CURRENT_SOURCE_DIR}/Symbian-OS/symbian-os")

# Find packages
find_package(PkgConfig)
find_program(MAKE_EXECUTABLE make)

if(NOT MAKE_EXECUTABLE)
    message(WARNING "make not found - some components may not compile")
endif()

# Output directories
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

# Create build targets directory
set(BUILD_OUTPUT_DIR "${CMAKE_BINARY_DIR}/artifacts")
file(MAKE_DIRECTORY "${BUILD_OUTPUT_DIR}/kernel")
file(MAKE_DIRECTORY "${BUILD_OUTPUT_DIR}/drivers")
file(MAKE_DIRECTORY "${BUILD_OUTPUT_DIR}/system")

# ========================================
# HARDWARE DETECTION MODULE
# ========================================
message(STATUS "Adding hardware detection module...")

set(HW_DETECTION_SOURCES
    src/hw_detection/hw_probe.cpp
)

set(HW_DETECTION_HEADERS
    src/hw_detection/hw_probe.h
)

if(HW_DETECTION_SOURCES)
    add_library(hw_detection STATIC ${HW_DETECTION_SOURCES})
    target_include_directories(hw_detection PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}/src/hw_detection
    )
    target_compile_options(hw_detection PRIVATE
        -Wall -Wextra -Wno-deprecated-declarations
    )
    message(STATUS "  Hardware detection module added")
else()
    message(STATUS "  No hardware detection sources found")
endif()

# ========================================
# KERNEL BUILD TARGET
# ========================================
if(EXISTS "${SYMBIAN_ROOT}/kernel")
    message(STATUS "Adding kernel target...")
    
    # Kernel source files
    file(GLOB_RECURSE KERNEL_C_SOURCES
        "${SYMBIAN_ROOT}/kernel/eka/kernel/*.c"
        "${SYMBIAN_ROOT}/kernel/eka/nanokernel/*.c"
        "${SYMBIAN_ROOT}/kernel/hal/src/*.c"
    )
    
    file(GLOB_RECURSE KERNEL_CPP_SOURCES
        "${SYMBIAN_ROOT}/kernel/eka/kernel/*.cpp"
        "${SYMBIAN_ROOT}/kernel/eka/nanokernel/*.cpp"
    )
    
    set(KERNEL_SOURCES ${KERNEL_C_SOURCES} ${KERNEL_CPP_SOURCES})
    
    if(KERNEL_SOURCES)
        list(LENGTH KERNEL_SOURCES KERNEL_COUNT)
        message(STATUS "  Found ${KERNEL_COUNT} kernel source files")
        
        add_library(kernel_obj OBJECT ${KERNEL_SOURCES})
        target_include_directories(kernel_obj PUBLIC
            "${SYMBIAN_ROOT}/kernel/eka/include"
            "${SYMBIAN_ROOT}/kernel/eka/nanokernel"
            "${SYMBIAN_ROOT}/kernel/hal/include"
        )
        target_compile_options(kernel_obj PRIVATE
            -Wno-deprecated-declarations
        )
    else()
        message(STATUS "  No kernel sources found")
    endif()
else()
    message(WARNING "Symbian kernel directory not found at ${SYMBIAN_ROOT}/kernel")
    message(WARNING "  Please clone the Symbian OS source code:")
    message(WARNING "  cd ${SYMBIAN_ROOT}")
    message(WARNING "  git clone --depth=1 https://github.com/SymbianSource/oss.FCL.sf.os.kernelhwsrv.git kernel")
endif()

# ========================================
# GRAPHICS BUILD TARGET
# ========================================
if(EXISTS "${SYMBIAN_ROOT}/graphics")
    message(STATUS "Adding graphics target...")
    
    file(GLOB_RECURSE GRAPHICS_SOURCES
        "${SYMBIAN_ROOT}/graphics/graphicsdeviceinterface/gdi/src/*.cpp"
        "${SYMBIAN_ROOT}/graphics/windowing/windowserver/src/*.cpp"
    )
    
    if(GRAPHICS_SOURCES)
        list(LENGTH GRAPHICS_SOURCES GRAPHICS_COUNT)
        message(STATUS "  Found ${GRAPHICS_COUNT} graphics source files")
        
        add_library(graphics_obj OBJECT ${GRAPHICS_SOURCES})
        target_include_directories(graphics_obj PUBLIC
            "${SYMBIAN_ROOT}/graphics/graphicsdeviceinterface/gdi/include"
            "${SYMBIAN_ROOT}/graphics/windowing/windowserver/inc"
            "${SYMBIAN_ROOT}/kernel/eka/include"
        )
        target_compile_options(graphics_obj PRIVATE
            -Wno-deprecated-declarations
        )
    else()
        message(STATUS "  No graphics sources found")
    endif()
else()
    message(STATUS "Graphics directory not found (optional)")
endif()

# ========================================
# DEVICE SERVICES BUILD TARGET
# ========================================
if(EXISTS "${SYMBIAN_ROOT}/devicesrv")
    message(STATUS "Adding device services target...")
    
    file(GLOB_RECURSE DEVICESRV_SOURCES
        "${SYMBIAN_ROOT}/devicesrv/os/devicesrv/src/*.cpp"
    )
    
    if(DEVICESRV_SOURCES)
        list(LENGTH DEVICESRV_SOURCES DEVICESRV_COUNT)
        message(STATUS "  Found ${DEVICESRV_COUNT} device services source files")
        
        add_library(devicesrv_obj OBJECT ${DEVICESRV_SOURCES})
        target_include_directories(devicesrv_obj PUBLIC
            "${SYMBIAN_ROOT}/devicesrv/os/devicesrv/inc"
            "${SYMBIAN_ROOT}/kernel/eka/include"
        )
        target_compile_options(devicesrv_obj PRIVATE
            -Wno-deprecated-declarations
        )
    else()
        message(STATUS "  No device services sources found")
    endif()
else()
    message(STATUS "Device services directory not found (optional)")
endif()

# ========================================
# TESTS
# ========================================
if(TARGET hw_detection)
    message(STATUS "Adding hardware detection test...")
    
    add_executable(hw_detection_test tests/hw_detection_test.cpp)
    target_link_libraries(hw_detection_test hw_detection)
    target_include_directories(hw_detection_test PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/src/hw_detection
    )
    
    message(STATUS "  Test executable: hw_detection_test")
endif()

# ========================================
# BUILD SUMMARY
# ========================================
message(STATUS "")
message(STATUS "==========================================")
message(STATUS "SROS Build Configuration Summary")
message(STATUS "==========================================")
message(STATUS "Platform:       ${PLATFORM}")
message(STATUS "Build Type:     ${CMAKE_BUILD_TYPE}")
message(STATUS "Symbian Root:   ${SYMBIAN_ROOT}")
message(STATUS "Output Dir:     ${BUILD_OUTPUT_DIR}")
message(STATUS "")

if(EXISTS "${SYMBIAN_ROOT}/kernel")
    message(STATUS "✓ Symbian kernel found")
else()
    message(STATUS "✗ Symbian kernel NOT found")
endif()

if(EXISTS "${SYMBIAN_ROOT}/graphics")
    message(STATUS "✓ Graphics subsystem found")
else()
    message(STATUS "✗ Graphics subsystem NOT found")
endif()

if(TARGET hw_detection)
    message(STATUS "✓ Hardware detection module built")
endif()

if(TARGET hw_detection_test)
    message(STATUS "✓ Hardware detection test built")
endif()

message(STATUS "")
message(STATUS "To build: ninja or make")
message(STATUS "To test:  ./bin/hw_detection_test")
message(STATUS "==========================================")
