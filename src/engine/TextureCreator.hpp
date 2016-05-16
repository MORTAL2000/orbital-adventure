#pragma once
#include <memory>
#include "Geometry.hpp"
#include "ShaderProgam.hpp"
#include "UniformHolder.hpp"
#include "UniformInstaller.hpp"
namespace oa {
namespace render {
class TextureCreator : public UniformOwner {
  std::vector<std::string> targets;
  bool useBlending = false;
  GLenum blendSrc, blengDst;
  glm::ivec4 blendFuncSep;
  bool needsDepthTest_;
  int width, height, depth;
  GLuint depthbuffer;
  ShaderProgram* shaderProgram;
  geometry::Geometry* geometry;
  virtual bool needsDepthTest();

  struct FB2DTexture : public TextureOwnerUniform {
    FB2DTexture(GLuint);
    GLuint getTextureId() const;
  };

  struct FB3DTexture : public Texture3DOwnerUniform {
    FB3DTexture(GLuint);
    GLuint getTextureId() const;
  };

 protected:
  std::vector<std::unique_ptr<UniformInstaller>> uniformInstallers;

 public:
  void blend();
  void setBlending(GLenum src, GLenum dst);
  void setBlendFunc(glm::ivec4);
  virtual void addUniformInstaller(UniformInstaller*);
  virtual void clearUniformInstallers();
  virtual void prepareFramebuffer(GLuint, UniformHolder* out);
  virtual void cleanFramebuffer(GLuint);

  TextureCreator(ShaderProgram*, std::string target);
  TextureCreator(ShaderProgram*, std::string target, bool needsDepthTest,
                 int width, int height, int depth);
  TextureCreator(ShaderProgram*, std::vector<std::string>& target,
                 bool needsDepthTest, int width, int height, int depth);
  virtual void render(const UniformHolder* h = nullptr);
};
}
}
