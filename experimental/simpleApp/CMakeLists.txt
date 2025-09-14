cmake_minimum_required(VERSION 3.20)
project(MyApp CXX)
set(CMAKE_CXX_STANDARD 17)

find_package(SDL2 REQUIRED)  # gives SDL2::SDL2 on modern FindSDL2

add_executable(MyApp MACOSX_BUNDLE src/main.cpp)

# 1) Ensure the binary has an rpath that points to the app’s Frameworks dir
set(CMAKE_MACOSX_RPATH ON)
set_target_properties(MyApp PROPERTIES
  INSTALL_RPATH "@executable_path/../Frameworks"
  BUILD_WITH_INSTALL_RPATH TRUE
)

# (Optional belt-and-suspenders; some toolchains like seeing the explicit link flag)
target_link_options(MyApp PRIVATE "-Wl,-rpath,@executable_path/../Frameworks")

target_link_libraries(MyApp PRIVATE SDL2::SDL2)

# 2) Bundle the SDL2 dylib into MyApp.app/Contents/Frameworks
add_custom_command(TARGET MyApp POST_BUILD
  COMMAND ${CMAKE_COMMAND} -E make_directory
          "$<TARGET_BUNDLE_DIR:MyApp>/Contents/Frameworks"
  COMMAND ${CMAKE_COMMAND} -E copy
          "$<TARGET_FILE:SDL2::SDL2>"
          "$<TARGET_BUNDLE_DIR:MyApp>/Contents/Frameworks/"
)
