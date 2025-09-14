## 🔧 Steps to Build IGL from Source

### 1. Clone the repo

```bash
git clone https://github.com/facebook/igl.git
cd igl
```

### 2. Deploy dependencies

IGL uses a **Python helper** to fetch and set up external dependencies. You need to run it before CMake:

```bash
python3 build/deploy_deps.py
```

This will pull in things like `glfw`, `glm`, shader tools, etc.
(If you skip this, the CMake step won’t find third-party libs.)

Optionally, you may also run:

```bash
python3 build/deploy_content.py
```

(for setting up demo assets like sample shaders/textures).

---

### 3. Configure with CMake

Now you can create a build directory:

```bash
mkdir build
cd build
```

For macOS + Xcode (no Vulkan):

```bash
cmake .. -G "Xcode" -DIGL_WITH_VULKAN=OFF
```

For Linux (using Makefiles):

```bash
cmake .. -DIGL_WITH_VULKAN=ON
```

For Windows (Visual Studio 2022):

```powershell
cmake .. -G "Visual Studio 17 2022" -A x64 -DIGL_WITH_VULKAN=ON
```

---

### 4. Build

* **macOS/Linux**:

  ```bash
  cmake --build . --config Release -j8
  ```
* **Windows**:
  Open the `.sln` in Visual Studio and build.

---

### 5. Run samples

After building, you should see sample apps under `build/shell/Release`.
For example:

open HelloWorldSession.app

These demo programs let you test IGL with OpenGL, Metal, or Vulkan (depending on your `-DIGL_WITH_...` flags).

---

## ⚙️ Useful CMake Options

* `-DIGL_WITH_VULKAN=ON` — enable Vulkan backend (requires Vulkan SDK).
* `-DIGL_WITH_OPENGL=ON` — enable OpenGL backend.
* `-DIGL_WITH_METAL=ON` — enable Metal backend (macOS/iOS only).
* `-DIGL_BUILD_SHELL=ON` — build sample apps.
* `-DIGL_BUILD_TESTS=ON` — build test suite (requires GoogleTest).

---

## 📝 Notes

* On **macOS**, if you want Vulkan: install [LunarG Vulkan SDK](https://vulkan.lunarg.com/sdk/home) and ensure `VULKAN_SDK` is set in your environment.
* On **Linux**, make sure you have `xorg-dev`, `libgl1-mesa-dev`, `vulkan-dev` etc. installed.
* On **Windows**, you need CMake ≥ 3.20, Visual Studio 2022, and optionally the Vulkan SDK.
