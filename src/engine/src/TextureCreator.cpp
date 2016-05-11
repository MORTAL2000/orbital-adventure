#include <iostream>
#include "GeometryManager.hpp"
#include "TextureCreator.hpp"
namespace oa {
namespace render {
TextureCreator::TextureCreator(ShaderProgram *sp, std::string t,
                               bool needsDepthTest, int width, int height)
    : target(t),
      needsDepthTest_(needsDepthTest),
      width(width),
      height(height),
      shaderProgram(sp) {
  geometry = GeometryManager::instance()->createPatchGeometry();
}

TextureCreator::TextureCreator(ShaderProgram *sp, std::string target)
    : target(target), shaderProgram(sp) {}

std::string TextureCreator::getTarget() { return target; }
size_t TextureCreator::supposedWidth() { return width; }
size_t TextureCreator::supposedHeight() { return height; }
void TextureCreator::addUniformInstaller(UniformInstaller *ui) {
  uniformInstallers.push_back(std::unique_ptr<UniformInstaller>(ui));
}
bool TextureCreator::needsDepthTest() { return needsDepthTest_; }
void TextureCreator::render() {
  GLuint program = shaderProgram->getProgramId();
  glUseProgram(program);
  for (auto &pair : shaderProgram->getUniformLocations()) {
    auto name = pair.first;
    auto location = pair.second;
    if (!setupUniform(name, location)) {
      std::cerr << "Target " << target << " has no uniform " << name << "\n";
    }
  }
  geometry->setBuffers();
  geometry->render();
  geometry->unsetBuffers();
}
}
}
