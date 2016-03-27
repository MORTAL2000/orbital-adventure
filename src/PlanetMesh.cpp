#include "PlanetMesh.hpp"
#include "ShaderManager.hpp"
#include "TextureManager.hpp"
#include "GeometryManager.hpp"
#include <iostream>
#include <glm/gtc/matrix_transform.hpp>

namespace oa {
namespace render {
uint32_t PlanetMesh::getProgramId() {
  // std::cout << "programid" << programId << "\n";
  return programId;
}
PlanetMesh::PlanetMesh() {
  geometry = GeometryManager::instance()->loadGeometry("SphereGeometry");

  programId = ShaderProgramManager::instance()->loadProgram(
      "../data/shaders/rockPlanetVertex.glsl",
      "../data/shaders/rockPlanetFragment.glsl");
  glUseProgram(programId);
  mvpLocation = glGetUniformLocation(programId, "modelViewMatrix");
  diffuseLocation = glGetUniformLocation(programId, "diffuseMap");
  normalLocation = glGetUniformLocation(programId, "normalMap");
  specularLocation = glGetUniformLocation(programId, "specularMap");
}
void PlanetMesh::setDiffuse(std::string fname) {
  diffuseMapId = TextureManager::instance()->loadTexture(fname);
}
void PlanetMesh::setSpecular(std::string fname) {
  specularMapId = TextureManager::instance()->loadTexture(fname);
}
void PlanetMesh::setNormal(std::string fname) {
  normalMapId = TextureManager::instance()->loadTexture(fname);
}

void PlanetMesh::setupUniforms(glm::mat4 projection, glm::mat4 view) {
  // std::cout << "setup uniforms\n";
  static float cx = 0;
  auto mm = this->getMatrix();
  auto m = projection * view * this->getMatrix();
  glUniformMatrix4fv(mvpLocation, 1, GL_FALSE, &m[0][0]);
}

void PlanetMesh::render() {
  // std::cout << "render\n";
  geometry->setBuffers();
  geometry->render();
  geometry->unsetBuffers();
}
}
}
