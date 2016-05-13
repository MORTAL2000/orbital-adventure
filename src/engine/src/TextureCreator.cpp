#include <iostream>
#include "GeometryManager.hpp"
#include "TextureCreator.hpp"
namespace oa {
namespace render {
TextureCreator::TextureCreator(ShaderProgram *sp, std::vector<std::string> &t,
                               bool needsDepthTest, int width, int height,
                               int depth)
    : targets(t),
      needsDepthTest_(needsDepthTest),
      width(width),
      height(height),
      depth(depth),
      shaderProgram(sp) {
  geometry = GeometryManager::instance()->createPatchGeometry();
}
TextureCreator::TextureCreator(ShaderProgram *sp, std::string t,
                               bool needsDepthTest, int width, int height,
                               int depth)
    : targets({t}),
      needsDepthTest_(needsDepthTest),
      width(width),
      height(height),
      depth(depth),
      shaderProgram(sp) {
  geometry = GeometryManager::instance()->createPatchGeometry();
}
void TextureCreator::clearUniformInstallers() { uniformInstallers.clear(); }

TextureCreator::TextureCreator(ShaderProgram *sp, std::string target)
    : targets({target}), shaderProgram(sp) {}

std::vector<std::string> &TextureCreator::getTargets() { return targets; }

size_t TextureCreator::supposedDepth() { return depth; }
size_t TextureCreator::supposedWidth() { return width; }
size_t TextureCreator::supposedHeight() { return height; }

void TextureCreator::addUniformInstaller(UniformInstaller *ui) {
  uniformInstallers.push_back(std::unique_ptr<UniformInstaller>(ui));
}
bool TextureCreator::needsDepthTest() { return needsDepthTest_; }
void TextureCreator::render() {
  GLuint program = shaderProgram->getProgramId();
  glUseProgram(program);
  geometry->setBuffers();
  for (int layer = 0; layer < depth; ++layer) {
    this->setUniformValue("textureLayer", new render::IntOwnerUniform(layer));
    for (auto &ui : uniformInstallers) {
      ui->install(this, nullptr, 0);
    }
    for (auto &pair : shaderProgram->getUniformLocations()) {
      auto name = pair.first;
      auto location = pair.second;
      if (!setupUniform(name, location)) {
        std::cerr << "Target " << targets[0] << " has no uniform " << name
                  << "\n";
      }
    }
    geometry->render();
  }
  geometry->unsetBuffers();
}
}
}
