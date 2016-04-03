#include "PlanetMesh.hpp"
#include "ShaderManager.hpp"
#include "TextureManager.hpp"
#include "GeometryManager.hpp"
#include <iostream>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

namespace oa {
namespace render {
uint32_t PlanetMesh::getProgramId() {
  // std::cout << "programid" << programId << "\n";
  return programId;
}
PlanetMesh::PlanetMesh() {
  // geometry = GeometryManager::instance()->loadGeometry("SphereGeometry");

  // programId = ShaderProgramManager::instance()->loadProgram(
  //"../data/shaders/rockPlanetVertex.glsl",
  //"../data/shaders/rockPlanetFragment.glsl");
  glUseProgram(programId);
  mvpLocation = glGetUniformLocation(programId, "modelViewMatrix");
  modelLocation = glGetUniformLocation(programId, "model");
  viewLocation = glGetUniformLocation(programId, "view");
  projectionlLocation = glGetUniformLocation(programId, "projection");
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
  static float cx = 0;
  // const glm::mat4 &mm = this->getMatrix();
  // auto m = projection * view * mm;
  // glUniformMatrix4fv(mvpLocation, 1, GL_FALSE, &m[0][0]);
  // glActiveTexture(GL_TEXTURE0);
  // glBindTexture(GL_TEXTURE_2D, diffuseMapId);
  // glUniform1i(diffuseLocation, 0);
}

void PlanetMesh::render() {
  geometry->setBuffers();
  geometry->render();
  geometry->unsetBuffers();
}
}
}
