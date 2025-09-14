cmake_minimum_required(VERSION 3.20)
project(HelloWorldSessionOnly LANGUAGES CXX)

# ======= 配置项 =======
# 传入 facebook/igl 仓库根目录（包含 igl/、IGLU/、shell/ 等文件夹）
# 使用方式举例：
#   cmake -S . -B build -DIGL_SOURCE_DIR=/path/to/facebook/igl

set(IGL_SOURCE_DIR "../..")
message("IGL_SOURCE_DIR: "  ${IGL_SOURCE_DIR})

if(NOT IGL_SOURCE_DIR)
  message(FATAL_ERROR "Please pass -DIGL_SOURCE_DIR=/path/to/facebook/igl")
endif()

# 你当前工程的源文件布局建议如下（至少要满足这两个）：
#   ./shell/renderSessions/HelloWorldSession.h
#   ./shell/renderSessions/HelloWorldSession.cpp
# 如果你的路径不同，改这里的相对路径即可。
file(GLOB SESSION_SRC ${CMAKE_CURRENT_SOURCE_DIR}/*.cpp)
file(GLOB SESSION_HDR ${CMAKE_CURRENT_SOURCE_DIR}/*.h)

# include_directories(

# ======= 目标：仅编译 HelloWorldSession（不强制链接 IGL 库）=======
# 用 OBJECT/STATIC 都可；若你稍后要把它合并进别的目标，OBJECT 更方便。
add_library(helloworld_session OBJECT ${SESSION_SRC} ${SESSION_HDR})

# C++ 标准与常规编译设置
target_compile_features(helloworld_session PUBLIC cxx_std_17)
set_target_properties(helloworld_session PROPERTIES
  POSITION_INDEPENDENT_CODE ON
)
# target_compile_definitions(IGLLibrary PUBLIC "IGL_CMAKE_BUILD=1")
target_compile_definitions(helloworld_session PUBLIC IGL_CMAKE_BUILD=1)


# ======= 头文件搜索路径 =======
# IGL 源码树里头文件直接以 <igl/...>, <IGLU/...>, <shell/...> 形式包含
# 因此把仓库根目录本身也加进来（保证能从根找到这些前缀）。
target_include_directories(helloworld_session
  PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}       # 让本地相对路径也可包含
    ${IGL_SOURCE_DIR}                 # 提供 <igl/...>, <IGLU/...>, <shell/...>
    ${IGL_SOURCE_DIR}/src
)

# 如果你在非 Apple 平台还需要后续链接 IGL/平台库，可以在你的最终可执行目标里做，比如：
# target_link_libraries(my_app PRIVATE igl::igl igl::iglu ...)  # 取决于你的 IGL 构建输出

# ======= 可选：平台宏（根据需要启用）=======
# 下面这些开关一般由 IGL 的上层工程控制；如果你单独编译需要特定后端，可自行添加：
# target_compile_definitions(helloworld_session PUBLIC IGL_BACKEND_METAL=1)
# target_compile_definitions(helloworld_session PUBLIC IGL_BACKEND_VULKAN=1)
# target_compile_definitions(helloworld_session PUBLIC IGL_BACKEND_OPENGL=1)

# ======= 说明 =======
# 这个 CMakeLists 只负责把 HelloWorldSession 源码编译成一个可被复用的目标，
# 不创建可执行文件，也不强制链接 IGL 库（因为你的 shell/runner 一般已经链接好了）。
# 在你的最终 App/CMake 里，把 helloworld_session 作为对象库加进去即可，例如：
#
# add_executable(igl_shell_app ...)
# target_link_libraries(igl_shell_app PRIVATE $<TARGET_OBJECTS:helloworld_session>)
# # 或者如果你把它改成 STATIC：
# # target_link_libraries(igl_shell_app PRIVATE helloworld_session)
