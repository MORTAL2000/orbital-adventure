#include <iostream>
#include "../engine/CustomGeometry.hpp"
#include "../engine/LanguageUtils.hpp"
#include "../engine/PatchGeometry.hpp"
#include "../engine/ShaderManager.hpp"
#include "../engine/TextureManager.hpp"
#include "GuiRender.hpp"
namespace oa {
namespace gui {
using namespace utils;
void GuiRenderer::setRenderer(render::Renderer *r) {
  renderer = r;
  initProgram();
}

void GuiRenderer::setDimentions(int w, int h) {
  dimentions.x = w;
  dimentions.y = h;
}
void GuiRenderer::RenderGeometry(Rocket::Core::Vertex *vertices,
                                 int num_verticies, int *indices,
                                 int num_indices,
                                 Rocket::Core::TextureHandle texture,
                                 const Rocket::Core::Vector2f &translation) {
  std::cout << "GUI: render geometry\n";
  ROCKET_UNUSED(num_vertices);

  glPushMatrix();
  glTranslatef(translation.x, translation.y, 0);

  glVertexPointer(2, GL_FLOAT, sizeof(Rocket::Core::Vertex),
                  &vertices[0].position);
  glEnableClientState(GL_COLOR_ARRAY);
  glColorPointer(4, GL_UNSIGNED_BYTE, sizeof(Rocket::Core::Vertex),
                 &vertices[0].colour);

  if (!texture) {
    glDisable(GL_TEXTURE_2D);
    glDisableClientState(GL_TEXTURE_COORD_ARRAY);
  } else {
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, (GLuint)texture);
    glEnableClientState(GL_TEXTURE_COORD_ARRAY);
    glTexCoordPointer(2, GL_FLOAT, sizeof(Rocket::Core::Vertex),
                      &vertices[0].tex_coord);
  }

  glDrawElements(GL_TRIANGLES, num_indices, GL_UNSIGNED_INT, indices);

  glPopMatrix();
};
Rocket::Core::CompiledGeometryHandle GuiRenderer::CompileGeometry(
    Rocket::Core::Vertex *vertices, int num_vertices, int *indices,
    int num_indices, Rocket::Core::TextureHandle texture) {
  std::cout << "GUI: compile gui geometry\n";
  std::cout << "NUM : " << num_vertices << " " << num_indices << " texture "
            << texture << "\n";
  float verts[num_vertices * 2];
  float uvs[num_vertices * 2];
  float colors[num_vertices * 4];

  // float verts[] = {-1, -1, 0, -1, 1, 0,
  //
  // 1,  -1, 0, 1,  1, 0};
  // int inds[] = {0, 2, 3, 0, 3, 1};
  for (size_t i = 0; i < num_vertices; ++i) {
    Rocket::Core::Vertex v = vertices[i];
    // std::cout << "vv " << (v.position.x + 168) / 636 << "\n";

    verts[i * 2] = v.position.x;
    verts[i * 2 + 1] = v.position.y;
    uvs[i * 2] = v.tex_coord.x;
    uvs[i * 2 + 1] = v.tex_coord.y;
    glm::vec4 c(v.colour.red / 255., v.colour.green / 255.,
                v.colour.blue / 255., v.colour.alpha / 255);
    colors[i * 4] = v.colour.red / 255.;
    colors[i * 4 + 1] = v.colour.green / 255.;
    colors[i * 4 + 2] = v.colour.blue / 255.;
    colors[i * 4 + 3] = v.colour.alpha / 255.;
  }
  geometry::CustomGeometry *g = new geometry::CustomGeometry;
  g->addBuffer((char *)verts, num_vertices, 2, sizeof(float));
  g->addBuffer((char *)uvs, num_vertices, 2, sizeof(float));
  g->addBuffer((char *)colors, num_vertices, 4, sizeof(float));
  g->addIndex((char *)indices, num_indices, sizeof(int));

  geom *gg = new geom;
  gg->geometry = g;  // new geometry::PatchGeometry();
  gg->geometry->prepareOpenglBuffers();
  gg->texture = texture;

  // return (unsigned long)nullptr;
  return (unsigned long)gg;
};
void GuiRenderer::initProgram() {
  shader = render::ShaderProgramManager::instance()->loadProgram(
      "../data/shaders/gui/vertexShader.glsl",
      "../data/shaders/gui/fragmentShader.glsl");
  uniforms["transition"] =
      std::unique_ptr<render::Uniform>(new render::Vec2Uniform(&translation));
  uniforms["font"] = std::unique_ptr<render::Uniform>(
      new render::TexturePtrUniform(&currentTexture));
  uniforms["resolution"] =
      std::unique_ptr<render::Uniform>(new render::Vec2Uniform(&dimentions));
}

/// Called by Rocket when it wants to render application-compiled geometry.
void GuiRenderer::RenderCompiledGeometry(
    Rocket::Core::CompiledGeometryHandle geometry,
    const Rocket::Core::Vector2f &translation) {
  geom *g = reinterpret_cast<geom *>(geometry);
  this->translation = glm::vec2(translation.x, translation.y);
  this->currentTexture = g->texture;

  glUseProgram(shader->getProgramId());
  glDisable(GL_CULL_FACE);
  g->geometry->setBuffers();
  for (auto &p : shader->getUniformLocations()) {
    const std::string &n = p.first;
    // std::cout << n << " U \n";
    GLuint l = p.second;
    uniforms[n]->setup(l);
  }
  g->geometry->render();
  g->geometry->unsetBuffers();
  glEnable(GL_CULL_FACE);
  // std::cout << "GUI: render compiled geometry\n";
};
//    /// Called by Rocket when it wants to release application-compiled
//    geometry.
void GuiRenderer::ReleaseCompiledGeometry(
    Rocket::Core::CompiledGeometryHandle geometry) {
  std::cout << "GUI: release compiled geometry\n";
};
//
//        /// Called by Rocket when it wants to enable or disable scissoring
//        to clip content.
void GuiRenderer::EnableScissorRegion(bool enable){
    /*
    if (enable)
      glEnable(GL_SCISSOR_TEST);
    else
      glDisable(GL_SCISSOR_TEST);
      */
};
/// Called by Rocket when it wants to change the scissor region.
void GuiRenderer::SetScissorRegion(int x, int y, int width, int height) {
  // glScissor(x, y, width, height);
  glScissor(x, dimentions.y - (y + height), width, height);
};

bool GuiRenderer::LoadTexture(Rocket::Core::TextureHandle &texture_handle,
                              Rocket::Core::Vector2i &texture_dimensions,
                              const Rocket::Core::String &source) {
  std::cout << "GUI: load texture \n";
  return false;
};
/// Called by Rocket when a texture is required to be built from an
/// internally-generated sequence of pixels.
bool GuiRenderer::GenerateTexture(
    Rocket::Core::TextureHandle &texture_handle,
    const Rocket::Core::byte *source,
    const Rocket::Core::Vector2i &source_dimensions) {
  texture_handle = render::TextureManager::instance()->createTexture(
      source, source_dimensions.x, source_dimensions.y);
  std::cout << "Created texture with num " << texture_handle << "dim "
            << source_dimensions.x << " " << source_dimensions.y << " "
            << "\n";
  int t = 0;
  for (size_t i = 0; i < source_dimensions.y; ++i) {
    for (size_t j = 0; j < source_dimensions.x; ++j) {
      size_t ix = (i * source_dimensions.x + j) * 4;
      if (source[ix + 3] != 0) {
        // std::cout << std::hex << "C: " << int(source[ix]) << ", "
        //<< int(source[ix + 1]) << ", " << int(source[ix + 2]) << ", "
        //<< int(source[ix + 3]) << "   ";
        // if (++t > 5) {
        // t = 0;
        // std::cout << "\n";
        //}
      }
    }
  }
  if (texture_handle != -1) {
    return true;
  }
  return false;
};
//    /// Called by Rocket when a loaded texture is no longer required.
void GuiRenderer::ReleaseTexture(Rocket::Core::TextureHandle texture_handle) {
  std::cout << "GUI: ReleaseTexture\n ";
};
}
}
