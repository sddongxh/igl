## Build

rm -rf build
cmake -S . -B build -G "Unix Makefiles" -DCMAKE_BUILD_TYPE=Release
cmake --build build -j
# 用绝对路径作为安装前缀
cmake --install build --prefix "$(pwd)/build/install"

## Verification 

ls build/MyApp.app/Contents/Frameworks
ls build/install/MyApp.app/Contents/Frameworks
otool -l build/install/MyApp.app/Contents/MacOS/MyApp | grep -A3 LC_RPATH
otool -L build/install/MyApp.app/Contents/MacOS/MyApp
# 不应再出现 /opt/homebrew/... 的硬编码路径
