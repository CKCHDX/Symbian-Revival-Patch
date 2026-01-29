# Contributing to Symbian Revival OS

Thank you for your interest in contributing to SROS! This document provides guidelines for contributing to the project.

## Getting Started

1. **Fork the repository** on GitHub
2. **Clone your fork** locally:
   ```bash
   git clone https://github.com/YOUR-USERNAME/Symbian-Revival-Patch.git
   cd Symbian-Revival-Patch
   ```
3. **Set up the development environment**:
   ```bash
   ./tools/setup.sh
   ```
4. **Create a branch** for your changes:
   ```bash
   git checkout -b feature/your-feature-name
   ```

## Areas Where You Can Contribute

### 1. Hardware Porting
- Create device profiles for new hardware
- Test on different devices
- Document hardware-specific quirks
- Add device drivers

**Location**: `src/hw_detection/device_profiles/`

### 2. Driver Development
- Implement device drivers for touch, WiFi, Bluetooth, storage
- Port existing Linux drivers
- Test driver compatibility

**Location**: `src/drivers/`

### 3. Architecture Improvements
- Enhance the Hardware Abstraction Layer (HAL)
- Improve hardware detection algorithms
- Optimize driver loading

**Location**: `src/hal/`, `src/hw_detection/`

### 4. Build System
- Improve CMake configuration
- Add support for new toolchains
- Optimize build process

**Location**: `CMakeLists.txt`, `tools/`

### 5. Documentation
- Write guides and tutorials
- Improve API documentation
- Create examples

**Location**: `docs/`

### 6. Testing
- Write unit tests
- Create integration tests
- Test on real hardware

**Location**: `tests/`

## Code Style Guidelines

### C/C++ Code
- Follow the existing code style in the project
- Use meaningful variable and function names
- Comment complex logic
- Keep functions small and focused

### Python Scripts
- Follow PEP 8 style guide
- Use descriptive variable names
- Add docstrings to functions

### Shell Scripts
- Use `#!/bin/bash` shebang
- Add comments for complex commands
- Check exit codes with `set -e`

## Commit Message Guidelines

Use clear, descriptive commit messages:

```
component: Brief description of change

More detailed explanation if needed. Explain what changed
and why, not how (the code shows how).

Fixes #123
```

**Examples**:
- `hal: Add x86_64 CPU detection support`
- `drivers/touch: Implement Atmel AT88SC103 driver`
- `docs: Update build instructions for macOS`
- `hw_detection: Fix device profile loading on ARM`

## Pull Request Process

1. **Update documentation** if needed
2. **Add tests** for new functionality
3. **Ensure all tests pass**
4. **Update the README.md** if you add features
5. **Submit a pull request** with:
   - Clear title and description
   - Reference to related issues
   - Screenshots/logs if applicable

### PR Checklist
- [ ] Code follows project style guidelines
- [ ] Documentation is updated
- [ ] Tests pass locally
- [ ] Commit messages are clear
- [ ] No unnecessary files included (use .gitignore)

## Adding a New Device Profile

To add support for a new device:

1. Create a JSON profile in `src/hw_detection/device_profiles/`:
   ```json
   {
     "device_id": "your_device_id",
     "name": "Your Device Name",
     "arch": "arm",
     "soc": "device_soc",
     ...
   }
   ```

2. Test the profile on the target device

3. Document any special requirements

4. Submit a PR with:
   - The device profile
   - Testing results
   - Photos/logs if helpful

## Adding a New Driver

To add a new device driver:

1. Create driver files in appropriate directory:
   - Touch: `src/drivers/touch/`
   - WiFi: `src/drivers/wifi/`
   - Bluetooth: `src/drivers/bluetooth/`
   - Storage: `src/drivers/storage/`

2. Follow the existing driver structure (LDD/PDD pattern)

3. Add driver to CMakeLists.txt

4. Test thoroughly

5. Document the driver in comments and/or separate doc

## Reporting Bugs

When reporting bugs, include:
- **Description**: What happened vs. what you expected
- **Steps to reproduce**: Detailed steps
- **Environment**: OS, architecture, versions
- **Logs**: Relevant error messages or logs
- **Screenshots**: If applicable

Use the GitHub issue tracker: [Report a Bug](https://github.com/CKCHDX/Symbian-Revival-Patch/issues)

## Feature Requests

We welcome feature requests! When submitting:
- **Describe the feature** clearly
- **Explain the use case** - why is it needed?
- **Provide examples** if possible

## Development Workflow

1. Pick an issue from the [issue tracker](https://github.com/CKCHDX/Symbian-Revival-Patch/issues) or create your own
2. Assign yourself to the issue (or comment that you're working on it)
3. Create a branch: `git checkout -b feature/issue-123-description`
4. Make your changes
5. Test your changes
6. Commit: `git commit -m "component: description"`
7. Push: `git push origin feature/issue-123-description`
8. Open a pull request

## Questions?

- **GitHub Issues**: For bug reports and feature requests
- **GitHub Discussions**: For questions and general discussion
- **README.md**: For project overview and quick start

## Code of Conduct

- Be respectful and inclusive
- Welcome newcomers
- Focus on constructive feedback
- Help others learn and grow

## License

By contributing, you agree that your contributions will be licensed under the same license as the project (EPL v1.0 / LGPL v2.1 / MIT).

---

**Thank you for contributing to Symbian Revival OS!** 🚀

Every contribution, no matter how small, helps make this project better.
