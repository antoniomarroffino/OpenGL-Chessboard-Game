# ♟️ OpenGL Chessboard Game - 3D Graphics Engine + Interactive Scene

## 🧩 Description

This project consists of two distinct components:

1. A **3D Graphics Engine** developed as a dynamic library (`.dll` / `.so`)
2. A **Chessboard Application** (`.exe`) that leverages the engine to render and interact with a real-time 3D scene

The project was developed entirely in **C/C++**, following professional engineering standards, and is documented with **Doxygen**.  
It was built as part of the university curriculum, specifically within the **Computer Graphics** and **Software Engineering II** courses, and runs on both **Windows** and **Linux** systems.

## 🧱 Architecture

### 🧠 3D Graphics Engine

Packaged as a shared library with a clean API, this engine offers:

- High-level classes to manage 3D models, light sources, materials, cameras
- A scene graph structure to organize and transform objects
- Abstractions over OpenGL and internal rendering systems
- Model loading from 3D-specific file formats
- Texture mapping and image loading
- Real-time rendering performance (targeting > 24 FPS)

### 🎮 Chessboard Application

A standalone application that uses the engine to render and interact with a 3D chessboard. It features:

- A full chessboard with 3D models for all white and black pieces
- A textured environment and optional surrounding elements
- Object selection via keyboard (select piece/square and move destination)
- Undo/Redo and Reset functionality
- **No game logic or rules validation** (free movement only)
- Support for multiple camera angles, including a dynamic camera
- Lighting setup with at least one static and one dynamic light source
- Realistic shadows or reflections for pieces and board

## 🎯 Main Features

- ✅ Modular architecture: separate engine and application
- 📦 Dynamic linking and reusable engine API
- 🧱 Scene graph for hierarchical object management
- 💡 Lighting system with static and dynamic sources
- 🔄 Viewpoint cycling through predefined cameras
- ⏱️ Maintains a framerate above 24 FPS
- 🧪 Runs on both Windows (Visual Studio) and Linux (Code::Blocks or similar)
- 📚 Full documentation generated with Doxygen

## 🛠️ Technologies Used

- **Language:** C, C++
- **Graphics API:** OpenGL
- **Build Tools:** Visual Studio 2022 (Windows), GCC/Make (Linux)
- **Documentation:** Doxygen
- **IDE Support:** Code::Blocks (Linux), Visual Studio (Windows)
- **Modeling Tools:** 3D Studio Max 2025 (recommended for asset creation)

## 🚀 How to Build and Run

### ▶️ Demo Usage

Pre-built executables are available in the `demo/` folder for quick access:

#### 🪟 Windows

1. Navigate to:
   ```
   demo/Windows/Release
   ```
2. Run:
   ```
   client.exe
   ```

#### 🐧 Linux

1. Navigate to:
   ```
   demo/Linux
   ```
2. Run from a terminal:
   ```bash
   ./run_client.sh
   ```

### 🔧 Windows

1. Open the solution in **Visual Studio 2022**
2. Build both the graphics engine (DLL) and the application (EXE)
3. Run the application from the output directory

### 🐧 Linux

1. Open project in **Code::Blocks** or any preferred IDE
2. Make sure OpenGL and required libraries are installed
3. Build the dynamic library and link it to the main application
4. Run the executable

## 📚 Educational Goals

This project applied several advanced software development practices:

- Modular architecture and separation of concerns
- Scene graph and 3D graphics abstractions
- Advanced C++ design with reusable components
- Cross-platform compatibility
- OpenGL rendering pipeline
- Real-time performance constraints
- Automated documentation using Doxygen

The goal was not to implement chess rules, but to create an **interactive, performant, and visually rich 3D simulation**.

## ✅ Project Status

✔️ Completed in December 2024  
🔒 No further development planned

## 👤 Author

**Antonio Marroffino**
- GitHub: [github.com/antoniomarroffino](https://github.com/antoniomarroffino)
- LinkedIn: [linkedin.com/in/antonio-marroffino](https://www.linkedin.com/in/antoniomarroffino)

---

## 📜 License

This project was developed for educational purposes as part of the Bachelor's degree in Computer Engineering at SUPSI.
