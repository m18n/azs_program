# 🚗 Fuel Station Management System - C/Ultralight Version

![Status](https://img.shields.io/badge/status-archived-yellow)
![Framework](https://img.shields.io/badge/framework-Ultralight-blue)
![Language](https://img.shields.io/badge/language-C-green)
![Platform](https://img.shields.io/badge/platform-Windows%20%7C%20Linux%20%7C%20macOS-lightgrey)

## 📋 Overview

This repository contains the original version of the Fuel Station Management System, developed in C using the Ultralight framework. This represents the first iteration of our solution - a desktop application that renders HTML/CSS/JavaScript content in a native window to create a modern user interface while maintaining tight integration with local hardware.

## 🔄 Project Evolution

This is the first part of a three-stage development journey:

1. **Current C/Ultralight Version**: Desktop application with embedded HTML viewer
2. **C++/Crow Version**: Evolution to a web server implementation using the Crow C++ framework
3. **Final Rust Version**: Complete rewrite in Rust with improved architecture

## 💡 Concept

This project was designed as a desktop application that would:
- Run directly on fuel station cashier and operator computers
- Render HTML-based interfaces in a native window
- Connect to proprietary fuel station hardware directly
- Operate in a standalone mode with local database storage

## 🛠️ Technology Stack

- **C**: Core programming language
- **Ultralight**: Lightweight HTML UI engine
- **AppCore**: Windowing and application framework by Ultralight
- **WebCore**: Web content rendering
- **SQLite**: Embedded database (via COREAZS library)
- **Custom COREAZS Library**: Core business logic for fuel station operations

## 🖥️ Architecture

The application uses a unique architecture that combines web technologies with native code:

- **HTML/CSS/JavaScript**: For the user interface
- **C Backend**: For hardware integration and business logic
- **Embedded UI Engine**: Ultralight renders web content in native windows
- **JavaScript Bridge**: `funjs.cpp` provides JavaScript-to-C bindings
- **View System**: `views.cpp` and `coreviews.cpp` manage UI components

## 🔌 Key Components

Based on the CMakeLists.txt, the project consists of:

- **main.cpp**: Application entry point
- **funjs.cpp**: JavaScript function bindings for interaction between UI and backend
- **views.cpp**: View management and rendering
- **coreviews.cpp**: Core view functionality
- **coreazs/**: Custom library for fuel station business logic
- **RESTART**: Utility application for restarting the main program

## 💻 Building and Running

### Prerequisites

- C/C++ compiler
- CMake 3.10+
- Platform-specific dependencies:
  - Windows: Visual Studio
  - Linux: Required development libraries
  - macOS: Xcode

### Build Instructions - Windows

```bash
# Clone the repository
git clone https://github.com/yourusername/AZS.git

# Create a build directory
mkdir build && cd build

# Generate Visual Studio project files
cmake ..

# Build the project
cmake --build . --config Debug

# Run the application
.\Debug\AZS.exe
```

### Build Instructions - Linux/macOS

```bash
# Clone the repository
git clone https://github.com/yourusername/AZS.git

# Create a build directory
mkdir build && cd build

# Generate build files
cmake ..

# Build the project
cmake --build .

# Run the application
./AZS
```
## 🌟 Features

- **Cross-Platform**: Supports Windows, Linux, and macOS
- **Modern UI**: HTML/CSS/JavaScript interface with native performance
- **Hardware Integration**: Direct access to fuel station equipment
- **Database Storage**: Local data persistence using SQLite
- **Restart Capability**: Includes a utility for application restart

## 🧪 Limitations That Led to Evolution

While this approach had several advantages, we eventually encountered limitations:

1. **Scalability Challenges**: The desktop application model limited multi-user scenarios
2. **Update Complexity**: Deploying updates to multiple stations was cumbersome
3. **Integration Limitations**: Direct hardware access required specific driver configurations
4. **Modern Web Features**: Some newer web technologies were not fully supported by the embedded engine

These limitations eventually led us to evolve the project into a web server-based approach using C++/Crow and ultimately Rust.

## 🔮 Historical Context

This project represents our initial approach to modernizing fuel station management systems. By embedding a web view into a native application, we aimed to combine the user-friendly nature of web interfaces with the hardware access capabilities of native code.

The experience gained from this project was invaluable for understanding:
- The balance between web and native technologies
- Cross-platform development challenges
- Integration with specialized hardware
- User experience considerations for operational systems

## 📝 Legacy and Evolution

While this project has been superseded by newer iterations, it represents an important step in our development journey. Many of the core concepts and business logic developed here were carried forward into subsequent versions, albeit with improved architectures and technologies.

---

*This project marks the beginning of our fuel station management system journey. Though we've since moved to more modern approaches, this initial version provided the foundation and insights that shaped all subsequent development.*
