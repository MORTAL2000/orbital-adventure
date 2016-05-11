#include <boost/algorithm/string.hpp>
#include <fstream>
#include <iostream>
#include <sstream>
#include "ShaderProgam.hpp"
namespace oa {
namespace render {
void ShaderProgram::setupUniformLocations() {
  for (auto &p : uniformTypes) {
    uniformLocations[p.first] =
        glGetUniformLocation(programId, p.first.c_str());
  }
}
std::map<std::string, GLuint> &ShaderProgram::getUniformLocations() {
  return uniformLocations;
}
std::regex ShaderProgram::getUniformRegex(int) {
  return std::regex("^uniform (\\w+) (\\w+);");
}

std::regex ShaderProgram::getAttributeRegex(int version) {
  if (version >= 330)
    return std::regex("^layout(.*)\\s+in\\s+(\\w+)\\s+(\\w+);");
  return std::regex("^attribute\\s+(\\w+)\\s+(\\w+);");
}

void ShaderProgram::parseShader(std::string shader) {
  std::vector<std::string> lines;
  boost::split(lines, shader, boost::is_any_of("\n"));
  std::string firstLine = lines[0];
  std::smatch m;
  std::regex r("\\d+");
  std::regex_search(firstLine, m, r);
  int version;
  std::stringstream(m[0]) >> version;
  std::regex uniformRegex = getUniformRegex(version),
             attributeRegex = getAttributeRegex(version);

  for (auto &line : lines) {
    std::smatch umatch;
    std::regex_match(line, umatch, uniformRegex);
    if (umatch.size() > 0)
      uniformTypes.insert(std::make_pair(umatch[2], umatch[1]));
    std::smatch amatch;
    std::regex_match(line, amatch, attributeRegex);
    if (amatch.size() > 0)
      attributeTypes.insert(std::make_pair(amatch[3], amatch[2]));
  }
}

GLuint ShaderProgram::getProgramId() { return programId; }
void ShaderProgram::free() { glDeleteProgram(programId); }
void ShaderProgram::compile(std::string vs, std::string fs) {
  std::ifstream vsf(vs);
  std::ifstream fsf(fs);
  std::string vshader((std::istreambuf_iterator<char>(vsf)),
                      std::istreambuf_iterator<char>());
  std::string fshader((std::istreambuf_iterator<char>(fsf)),
                      std::istreambuf_iterator<char>());
  GLuint vShaderId, fShaderId;
  vShaderId = glCreateShader(GL_VERTEX_SHADER);
  fShaderId = glCreateShader(GL_FRAGMENT_SHADER);
  GLint result = GL_FALSE;
  int infoLogLength;

  parseShader(vshader);
  parseShader(fshader);

  // vertex
  char const *VertexSourcePointer = vshader.c_str();
  glShaderSource(vShaderId, 1, &VertexSourcePointer, NULL);
  glCompileShader(vShaderId);
  glGetShaderiv(vShaderId, GL_COMPILE_STATUS, &result);
  glGetShaderiv(vShaderId, GL_INFO_LOG_LENGTH, &infoLogLength);
  if (infoLogLength > 0) {
    std::vector<char> VertexShaderErrorMessage(infoLogLength + 1);
    glGetShaderInfoLog(vShaderId, infoLogLength, NULL,
                       &VertexShaderErrorMessage[0]);
    printf("%s\n", &VertexShaderErrorMessage[0]);
  }

  // fragment

  char const *FragmentSourcePointer = fshader.c_str();
  glShaderSource(fShaderId, 1, &FragmentSourcePointer, NULL);
  glCompileShader(fShaderId);
  glGetShaderiv(fShaderId, GL_COMPILE_STATUS, &result);
  glGetShaderiv(fShaderId, GL_INFO_LOG_LENGTH, &infoLogLength);
  if (infoLogLength > 0) {
    std::vector<char> FragmentShaderErrorMessage(infoLogLength + 1);
    glGetShaderInfoLog(fShaderId, infoLogLength, NULL,
                       &FragmentShaderErrorMessage[0]);
    printf("%s\n", &FragmentShaderErrorMessage[0]);
  }

  programId = glCreateProgram();
  glAttachShader(programId, vShaderId);
  glAttachShader(programId, fShaderId);
  glLinkProgram(programId);
  glGetProgramiv(programId, GL_LINK_STATUS, &result);
  glGetProgramiv(programId, GL_INFO_LOG_LENGTH, &infoLogLength);
  if (infoLogLength > 0) {
    std::vector<char> ProgramErrorMessage(infoLogLength + 1);
    glGetProgramInfoLog(programId, infoLogLength, NULL,
                        &ProgramErrorMessage[0]);
    printf("%s\n", &ProgramErrorMessage[0]);
  }
  glDeleteShader(fShaderId);
  glDeleteShader(vShaderId);
  setupUniformLocations();
}

void ShaderProgram::compile(std::string vs, std::string fs, std::string gs) {
  std::ifstream vsf(vs);
  std::ifstream fsf(fs);
  std::ifstream gsf(gs);
  std::string vshader((std::istreambuf_iterator<char>(vsf)),
                      std::istreambuf_iterator<char>());
  std::string fshader((std::istreambuf_iterator<char>(fsf)),
                      std::istreambuf_iterator<char>());
  std::string gshader((std::istreambuf_iterator<char>(gsf)),
                      std::istreambuf_iterator<char>());
  GLuint vShaderId, fShaderId, gShaderId;
  vShaderId = glCreateShader(GL_VERTEX_SHADER);
  fShaderId = glCreateShader(GL_FRAGMENT_SHADER);
  gShaderId = glCreateShader(GL_GEOMETRY_SHADER);
  GLint result = GL_FALSE;
  int infoLogLength;

  parseShader(vshader);
  parseShader(fshader);
  parseShader(gshader);

  // vertex
  char const *VertexSourcePointer = vshader.c_str();
  glShaderSource(vShaderId, 1, &VertexSourcePointer, NULL);
  glCompileShader(vShaderId);
  glGetShaderiv(vShaderId, GL_COMPILE_STATUS, &result);
  glGetShaderiv(vShaderId, GL_INFO_LOG_LENGTH, &infoLogLength);
  if (infoLogLength > 0) {
    std::vector<char> VertexShaderErrorMessage(infoLogLength + 1);
    glGetShaderInfoLog(vShaderId, infoLogLength, NULL,
                       &VertexShaderErrorMessage[0]);
    printf("%s\n", &VertexShaderErrorMessage[0]);
  }

  // geometry
  char const *GeometrySourcePointer = gshader.c_str();
  glShaderSource(gShaderId, 1, &GeometrySourcePointer, NULL);
  glCompileShader(gShaderId);
  glGetShaderiv(gShaderId, GL_COMPILE_STATUS, &result);
  glGetShaderiv(gShaderId, GL_INFO_LOG_LENGTH, &infoLogLength);
  if (infoLogLength > 0) {
    std::vector<char> GeometryShaderErrorMessage(infoLogLength + 1);
    glGetShaderInfoLog(gShaderId, infoLogLength, NULL,
                       &GeometryShaderErrorMessage[0]);
    printf("%s\n", &GeometryShaderErrorMessage[0]);
  }

  // fragment

  char const *FragmentSourcePointer = fshader.c_str();
  glShaderSource(fShaderId, 1, &FragmentSourcePointer, NULL);
  glCompileShader(fShaderId);
  glGetShaderiv(fShaderId, GL_COMPILE_STATUS, &result);
  glGetShaderiv(fShaderId, GL_INFO_LOG_LENGTH, &infoLogLength);
  if (infoLogLength > 0) {
    std::vector<char> FragmentShaderErrorMessage(infoLogLength + 1);
    glGetShaderInfoLog(fShaderId, infoLogLength, NULL,
                       &FragmentShaderErrorMessage[0]);
    printf("%s\n", &FragmentShaderErrorMessage[0]);
  }

  programId = glCreateProgram();
  glAttachShader(programId, vShaderId);
  glAttachShader(programId, fShaderId);
  glAttachShader(programId, gShaderId);
  glLinkProgram(programId);
  glGetProgramiv(programId, GL_LINK_STATUS, &result);
  glGetProgramiv(programId, GL_INFO_LOG_LENGTH, &infoLogLength);
  if (infoLogLength > 0) {
    std::vector<char> ProgramErrorMessage(infoLogLength + 1);
    glGetProgramInfoLog(programId, infoLogLength, NULL,
                        &ProgramErrorMessage[0]);
    printf("%s\n", &ProgramErrorMessage[0]);
  }
  glDeleteShader(fShaderId);
  glDeleteShader(vShaderId);
  setupUniformLocations();
}
}
}
