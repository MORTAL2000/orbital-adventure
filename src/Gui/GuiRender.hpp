#pragma once
#include <Rocket/Core.h>
#include "../engine/Renderer.hpp"
#include "../engine/ShaderProgam.hpp"

namespace oa {
namespace gui {
class GuiRenderer : public Rocket::Core::RenderInterface {
  struct geom {
    geometry::Geometry *geometry;
    GLuint texture;
  };

  render::Renderer *renderer;
  render::ShaderProgram *shader;
  glm::vec2 translation;
  GLuint currentTexture;
  std::map<std::string, std::unique_ptr<render::Uniform>> uniforms;
  glm::vec2 dimentions;

  void RenderGeometry(Rocket::Core::Vertex *vertices, int num_verticies,
                      int *indices, int num_indices,
                      Rocket::Core::TextureHandle texture,
                      const Rocket::Core::Vector2f &translation) override;
  Rocket::Core::CompiledGeometryHandle CompileGeometry(
      Rocket::Core::Vertex *vertices, int num_vertices, int *indices,
      int num_indices, Rocket::Core::TextureHandle texture) override;

  /// Called by Rocket when it wants to render application-compiled geometry.
  void RenderCompiledGeometry(
      Rocket::Core::CompiledGeometryHandle geometry,
      const Rocket::Core::Vector2f &translation) override;
  //    /// Called by Rocket when it wants to release application-compiled
  //    geometry.
  void ReleaseCompiledGeometry(
      Rocket::Core::CompiledGeometryHandle geometry) override;
  //
  //        /// Called by Rocket when it wants to enable or disable scissoring
  //        to clip content.
  void EnableScissorRegion(bool enable) override;
  /// Called by Rocket when it wants to change the scissor region.
  void SetScissorRegion(int x, int y, int width, int height) override;

  bool LoadTexture(Rocket::Core::TextureHandle &texture_handle,
                   Rocket::Core::Vector2i &texture_dimensions,
                   const Rocket::Core::String &source) override;
  /// Called by Rocket when a texture is required to be built from an
  /// internally-generated sequence of pixels.
  bool GenerateTexture(
      Rocket::Core::TextureHandle &texture_handle,
      const Rocket::Core::byte *source,
      const Rocket::Core::Vector2i &source_dimensions) override;
  //    /// Called by Rocket when a loaded texture is no longer required.
  void ReleaseTexture(Rocket::Core::TextureHandle texture_handle) override;

  void initProgram();

 public:
  void setRenderer(render::Renderer *);
  void setDimentions(int w, int h);
};
}
}
