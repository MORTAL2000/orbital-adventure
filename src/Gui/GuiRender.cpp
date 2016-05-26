#include <iostream>
#include "GuiRender.hpp"
namespace oa {
namespace gui {
void GuiRenderer::setRenderer(render::Renderer *r) { renderer = r; }

void GuiRenderer::RenderGeometry(Rocket::Core::Vertex *vertices,
                                 int num_verticies, int *indices,
                                 int num_indices,
                                 Rocket::Core::TextureHandle texture,
                                 const Rocket::Core::Vector2f &translation) {
  std::cout << "render geometry\n";
};
Rocket::Core::CompiledGeometryHandle GuiRenderer::CompileGeometry(
    Rocket::Core::Vertex *vertices, int num_vertices, int *indices,
    int num_indices, Rocket::Core::TextureHandle texture) {
  std::cout << "compile gui geometry\n";
  return 0;
};

/// Called by Rocket when it wants to render application-compiled geometry.
void GuiRenderer::RenderCompiledGeometry(
    Rocket::Core::CompiledGeometryHandle geometry,
    const Rocket::Core::Vector2f &translation) {
  std::cout << "render compiled geometry\n";
};
//    /// Called by Rocket when it wants to release application-compiled
//    geometry.
void GuiRenderer::ReleaseCompiledGeometry(
    Rocket::Core::CompiledGeometryHandle geometry) {
  std::cout << "release compiled geometry\n";
};
//
//        /// Called by Rocket when it wants to enable or disable scissoring
//        to clip content.
void GuiRenderer::EnableScissorRegion(bool enable) {
  std::cout << "enable scissors geometry\n";
};
/// Called by Rocket when it wants to change the scissor region.
void GuiRenderer::SetScissorRegion(int x, int y, int width, int height) {
  std::cout << "set scissors geometry\n";
};

bool GuiRenderer::LoadTexture(Rocket::Core::TextureHandle &texture_handle,
                              Rocket::Core::Vector2i &texture_dimensions,
                              const Rocket::Core::String &source) {
  std::cout << "load texture\n";
  return false;
};
/// Called by Rocket when a texture is required to be built from an
/// internally-generated sequence of pixels.
bool GuiRenderer::GenerateTexture(
    Rocket::Core::TextureHandle &texture_handle,
    const Rocket::Core::byte *source,
    const Rocket::Core::Vector2i &source_dimensions) {
  std::cout << "GenerateTexture\n";
  return false;
};
//    /// Called by Rocket when a loaded texture is no longer required.
void GuiRenderer::ReleaseTexture(Rocket::Core::TextureHandle texture_handle) {
  std::cout << "ReleaseTexture\n ";
};
}
}
