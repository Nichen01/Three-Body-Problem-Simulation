# Gravity Lab: Three-Body Problem Simulation
2D gravitational N-body simulation using C++17, OpenGL 3.3 Core, GLFW, GLAD, GLM and (soon) Dear ImGui.

## Build (Windows, Visual Studio 2022)
1. File > Open > Folder and pick this folder. Visual Studio reads `CMakePresets.json`.
2. Choose the **Visual Studio 2022 (x64)** preset and wait for CMake to finish (it downloads GLFW and GLM the first time).
3. Select `GravityLab.exe` as the startup item and press F5.

Or from a terminal:
```
cmake --preset vs2022
cmake --build --preset debug
.\build\vs2022\Debug\GravityLab.exe
```

## Layout
- `src/` application code
- `external/glad/` OpenGL 3.3 Core loader, generated with glad2 (`glad --api gl:core=3.3 --extensions="" c`)
