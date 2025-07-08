# 🚗 Fuel Station Management System - Evolution Project

![Status](https://img.shields.io/badge/status-archived-yellow)
![Languages](https://img.shields.io/badge/languages-C%20%7C%20C++%20%7C%20Rust-blue)

## 📋 Project Overview

This repository documents the evolution of a Fuel Station Management System through three distinct technological iterations. The project was designed to provide software solutions for gas stations, supporting cashier and operator workflows with both local and networked components.

## 🔄 Project Evolution Timeline

### 1️⃣ Initial C Version with Ultralight (Desktop Application)

The project began as a desktop application built in C using the Ultralight framework to render HTML content in a native window.

**Key Technical Components (Confirmed from CMakeLists.txt):**
- Core Language: C
- UI Framework: Ultralight, AppCore, WebCore
- Key Files: main.cpp, funjs.cpp, views.cpp, coreviews.cpp
- Custom Core Library: COREAZS
- Database: SQLite integration
- Cross-platform: Windows, Linux, macOS support
- Restart Utility: Separate executable for application restart

**Architecture:**
- Desktop application with embedded HTML viewer
- Direct local hardware integration
- JavaScript-to-C bridging via funjs.cpp
- Custom view system (views.cpp, coreviews.cpp)

### 2️⃣ C++ Version with Crow Framework (Web Server)

The second iteration evolved to a web server approach using C++ and the Crow framework.

**Key Technical Components (Confirmed from CMakeLists.txt):**
- Core Language: C++
- Web Framework: Crow
- Key Files: 
  - controller.cpp, model.cpp, view.cpp
  - core.cpp, local_data.cpp, azs.cpp
  - web_tehnology.cpp, users_controller.cpp
- Databases: SQLite and MySQL (via MySQL Connector/C++)
- Security: OpenSSL, JWT authentication
- Cross-platform: Windows and Linux support
- Docker support for Linux deployment

**Architecture:**
- Web server deployed on each gas station
- MVC pattern implementation
- RESTful API endpoints
- Cross-platform compatibility
- Database flexibility (SQLite/MySQL)

### 3️⃣ Rust Version (Current)

The final evolution is a complete rewrite in Rust, focusing on performance, safety, and modern web server capabilities.

**Key Technical Notes:**
- This was my first Rust project, used to explore the language's capabilities
- Aimed to address limitations in previous C/C++ implementations
- Focus on memory safety and concurrent processing

## 💻 Building the Projects

### C/Ultralight Version Build

```bash
# Prerequisites: CMake 3.10+, C compiler, platform-specific dependencies

# Windows (Visual Studio)
mkdir build && cd build
cmake ..
cmake --build . --config Debug

# Linux/macOS
mkdir build && cd build
cmake ..
cmake --build .
```

### C++/Crow Version Build

```bash
# Prerequisites: CMake 3.1+, C++ compiler, OpenSSL, MySQL Connector/C++

# Windows
mkdir build && cd build
cmake -DCMAKE_BUILD_TYPE=Debug ..  # or Release
cmake --build . --config Debug  # or Release

# Linux
mkdir build && cd build
cmake -DCMAKE_BUILD_TYPE=Release ..
cmake --build .

# Docker (Linux)
cd build/bin
docker build -t azs_local_server .
docker run -p 8080:8080 azs_local_server
```

## 🧪 Project Context and Legacy

This repository documents my programming journey through three languages and architectural approaches. The project began as a real-world application intended for deployment at actual fuel stations, but wasn't completed for production use.

Each iteration represents significant learning and evolution in approach:

1. **C/Ultralight**: Explored embedding web UI in native applications, with direct hardware access
2. **C++/Crow**: Implemented proper web server architecture with database integration
3. **Rust**: My first Rust project, focusing on memory safety and modern web server implementation

While the project never reached production deployment, it served as an invaluable learning experience in cross-platform development, web technologies, and the evolution of a complex application across different programming paradigms.

---

*This repository captures a programming journey across three languages and architectural approaches, demonstrating the evolution of both the project and developer expertise.*
