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

void TextureCreator::addUniformInstaller(UniformInstaller *ui) {
  uniformInstallers.push_back(std::unique_ptr<UniformInstaller>(ui));
}

bool TextureCreator::needsDepthTest() { return needsDepthTest_; }

void TextureCreator::render(const UniformHolder *holder) {
  GLuint program = shaderProgram->getProgramId();
  glUseProgram(program);
  //glDisable(GL_CULL_FACE);
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
        if (!(holder && holder->setupUniform(name, location)))
          std::cerr << "Target " << targets[0] << " has no uniform " << name
                    << "\n";
      }
    }
    geometry->render();
  }
  geometry->unsetBuffers();
}

void TextureCreator::cleanFramebuffer(GLuint fb) {
  if (useBlending) {
    glDisable(GL_BLEND);
  }
  for (int ix = 0; ix < targets.size(); ++ix)
    glFramebufferTexture(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0 + ix, 0, 0);

  glBindFramebuffer(GL_FRAMEBUFFER, 0);
  glEnable(GL_DEPTH_TEST);
}

void TextureCreator::prepareFramebuffer(GLuint framebuffer,
                                        UniformHolder *holder) {
  glBindFramebuffer(GL_FRAMEBUFFER, framebuffer);

  GLenum buffers[targets.size()];
  GLuint textures[targets.size()];
  int ix = 0;
  glGenTextures(targets.size(), textures);
  for (std::string &target : targets) {
    std::cout << target << " render target\n";
    if (depth == 1) {
      std::cout << " ---- bind 2d texture\n";
      auto uptr = (*holder)[target];
      if (uptr) {
        std::cout << " ----- holder already has uniform \n";
        auto tu = dynamic_cast<const FB2DTexture *>(uptr);

        //deleting freshly created texture
        glDeleteTextures(1, textures + ix);
        textures[ix] = tu->getTextureId();
        std::cout << " puttin it to binded textures \n";
      } else {
        std::cout << "===== bind and setup texture and uniform\n";

        glBindTexture(GL_TEXTURE_2D, textures[ix]);
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA32F, width, height, 0, GL_RGBA,
                     GL_FLOAT, 0);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
        holder->setUniformValue(targets[ix], new FB2DTexture(textures[ix]));
      }
    } else {
      auto uptr = (*holder)[target];
      if (uptr) {
        auto tu = dynamic_cast<const FB3DTexture *>(uptr);
        glDeleteTextures(1, textures + ix);
        textures[ix] = tu->getTextureId();
      } else {
        glBindTexture(GL_TEXTURE_3D, textures[ix]);
        glTexParameteri(GL_TEXTURE_3D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
        glTexParameteri(GL_TEXTURE_3D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
        glTexParameteri(GL_TEXTURE_3D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
        glTexParameteri(GL_TEXTURE_3D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
        glTexParameteri(GL_TEXTURE_3D, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);
        glTexImage3D(GL_TEXTURE_3D, 0, GL_RGBA32F, width, height, depth, 0,
                     GL_RGBA, GL_FLOAT, NULL);
        holder->setUniformValue(targets[ix], new FB3DTexture(textures[ix]));
      }
    }

    glFramebufferTexture(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0 + ix,
                         textures[ix], 0);
    std::cout << "bind texture " << textures[ix] << "\n";
    buffers[ix] = GL_COLOR_ATTACHMENT0 + ix;
    ++ix;
  }
  std::cout << "draw buffers " << targets.size() << "\n";
  glDrawBuffers(targets.size(), buffers);
  auto res = glCheckFramebufferStatus(GL_FRAMEBUFFER);
  if (res != GL_FRAMEBUFFER_COMPLETE) {
    std::cerr << "Was unable to setup framebuffer with target " << targets[0]
              << "\n";
    std::cerr << std::hex << "RESULT " << res << "\n";
    std::cerr << std::dec;
    glBindFramebuffer(GL_FRAMEBUFFER, 0);
    return;
  }
  std::cout << "WxH" << width << "x "<< height << "\n";
  glViewport(0, 0, width, height);
  glClearColor(0.0, 0.0, 0.0, 1.0);
  glDisable(GL_DEPTH_TEST);
  if (useBlending) {
    glEnable(GL_BLEND);
    glBlendEquationSeparate(blendSrc, blengDst);
    glBlendFuncSeparate(blendFuncSep.x, blendFuncSep.y, blendFuncSep.z,
                        blendFuncSep.w);
  }
}

void TextureCreator::blend() { useBlending = true; }
void TextureCreator::setBlending(GLenum s, GLenum d) {
  blendSrc = s;
  blengDst = d;
}
void TextureCreator::setBlendFunc(glm::ivec4 bf) { blendFuncSep = bf; }

TextureCreator::FB2DTexture::FB2DTexture(GLuint i) : TextureOwnerUniform(i) {}
GLuint TextureCreator::FB2DTexture::getTextureId() const { return textureId; }
TextureCreator::FB3DTexture::FB3DTexture(GLuint i) : Texture3DOwnerUniform(i) {}
GLuint TextureCreator::FB3DTexture::getTextureId() const { return textureId; }
Uniform *TextureCreator::FB2DTexture::clone() {
  return new TextureUniform(textureId);
}
Uniform *TextureCreator::FB3DTexture::clone() {
  return new Texture3DUniform(textureId);
}
}
}
