#include <memory>
#include <shell/shared/platform/glfw/PlatformGLFW.h>
#include <shell/shared/renderSession/RenderSession.h>
#include "HelloWorldSession.h"

using namespace igl::shell;

int main() {
  // 创建 GLFW 平台（默认 OpenGL 上下文）
  auto platform = std::make_shared<PlatformGLFW>();
  PlatformParams params;
  params.windowTitle = "IGL Hello Triangle";
  params.windowWidth = 800;
  params.windowHeight = 600;
  params.backendType = igl::BackendType::OpenGL; // 本例使用 OpenGL
  if (!platform->initialize(params)) {
    return -1;
  }

  // 构造你的 Session
  auto session = std::make_unique<HelloWorldSession>(platform);
  session->initialize();

  // 主循环
  while (!platform->shouldClose()) {
    platform->pollEvents();

    // 从 Platform 获取当帧 SurfaceTextures (color/depth)
    auto surfaceTextures = platform->acquireSurfaceTextures();
    session->update(surfaceTextures);

    platform->present(); // 交换前后缓冲
  }

  platform->shutdown();
  return 0;
}
