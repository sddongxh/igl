cmake_minimum_required(VERSION 3.20)
project(MyApp CXX)
set(CMAKE_CXX_STANDARD 17)

find_package(SDL2 REQUIRED)

add_executable(MyApp MACOSX_BUNDLE src/main.cpp)
target_link_libraries(MyApp PRIVATE SDL2::SDL2)

# 让可执行文件到 .app/Contents/Frameworks 下找依赖
set(CMAKE_MACOSX_RPATH ON)
set_target_properties(MyApp PROPERTIES
  INSTALL_RPATH "@executable_path/../Frameworks"
  BUILD_WITH_INSTALL_RPATH TRUE
)
target_link_options(MyApp PRIVATE "-Wl,-rpath,@executable_path/../Frameworks")

# 构建完成后把 SDL2 复制进 .app/Contents/Frameworks
add_custom_command(TARGET MyApp POST_BUILD
  COMMAND ${CMAKE_COMMAND} -E make_directory
          "$<TARGET_BUNDLE_DIR:MyApp>/Contents/Frameworks"
  COMMAND ${CMAKE_COMMAND} -E copy
          "$<TARGET_FILE:SDL2::SDL2>"
          "$<TARGET_BUNDLE_DIR:MyApp>/Contents/Frameworks/"
)

# 安装 .app（直接拷贝整个 bundle）
install(TARGETS MyApp
  BUNDLE DESTINATION .
  RUNTIME DESTINATION bin
)
