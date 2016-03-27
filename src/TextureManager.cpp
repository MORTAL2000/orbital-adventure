#include "TextureManager.hpp"
#include <boost/filesystem.hpp>
#include <jpeglib.h>
#include <png.h>
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <unistd.h>
#include <fcntl.h>

namespace oa {
namespace render {
TextureManager::TextureManager() {}
GLuint TextureManager::loadTexture(std::string filepath) {
  auto p = boost::filesystem::path(filepath);
  std::string extension = p.extension().string();
  if (isJpeg(extension)) {
    return loadJpegTexture(filepath);
  }
  if (isPng(extension)) {
    return loadPngTexture(filepath);
  }

  return 0;
}

GLuint TextureManager::loadJpegTexture(std::string filename) {
  struct jpeg_decompress_struct cinfo;
  struct jpeg_error_mgr emgr;
  // struct TextureManager::error_mgr errmgr;
  FILE* infile;
  if ((infile = fopen(filename.c_str(), "rb")) == NULL) {
    std::cerr << "can't open " << filename << " \n";
    return 0;
  }
  struct stat file_info;
  int rc = stat(filename.c_str(), &file_info);
  if (rc) {
    std::cerr << "FAILED to stat source jpg";
    exit(EXIT_FAILURE);
  }
  long jpg_size = file_info.st_size;
  unsigned char* jpg_buffer = new unsigned char[jpg_size + 100];
  int i = 0;

  while (i < jpg_size) {
    rc = fread(jpg_buffer + i, jpg_size - i, 1, infile);
    i += rc;
  }

  cinfo.err = jpeg_std_error(&emgr);
  // emgr.error_exit = TextureManager::jpeg_error_exit;
  jpeg_create_decompress(&cinfo);
  jpeg_mem_src(&cinfo, jpg_buffer, jpg_size);

  rc = jpeg_read_header(&cinfo, TRUE);

  if (rc != 1) {
    std::cerr << "File does not seem to be a normal JPEG\n";
  }

  jpeg_start_decompress(&cinfo);
  size_t dataLength =
      cinfo.output_width * cinfo.output_height * cinfo.output_components;
  unsigned char* data = new unsigned char[dataLength];
  int rowLength = cinfo.output_width * cinfo.output_components;
  while (cinfo.output_scanline < cinfo.output_height) {
    unsigned char* buffer[1];
    buffer[0] = data + cinfo.output_scanline * rowLength;
    jpeg_read_scanlines(&cinfo, buffer, 1);
  }

  int type = -1;
  if (cinfo.output_components == 3) type = GL_RGB;
  if (cinfo.output_components == 4) type = GL_RGBA;
  GLuint textureId;
  glGenTextures(1, &textureId);
  glBindTexture(GL_TEXTURE_2D, textureId);
  glTexImage2D(GL_TEXTURE_2D, 0, type, cinfo.output_width, cinfo.output_height,
               0, type, GL_UNSIGNED_BYTE, data);

  jpeg_finish_decompress(&cinfo);
  jpeg_destroy_decompress(&cinfo);
  return textureId;
}

GLuint TextureManager::loadPngTexture(std::string filename) {
  char header[8];  // 8 is the maximum size that can be checked
  png_byte color_type;
  png_byte bit_depth;
  png_structp png_ptr;
  png_infop info_ptr;

  /* open file and test for it being a png */
  FILE* fp = fopen(filename.c_str(), "rb");
  if (!fp)
    std::cerr << "[read_png_file] File  could not be opened for reading"
              << filename << "\n";
  fread(header, 1, 8, fp);
  // if (png_sig_cmp(header, 0, 8))
  // std::cerr << "[read_png_file] File %s is not recognized as a PNG file"
  //<< filename << "\n";

  /* initialize stuff */
  png_ptr = png_create_read_struct(PNG_LIBPNG_VER_STRING, NULL, NULL, NULL);

  if (!png_ptr)
    std::cerr << "[read_png_file] png_create_read_struct failed"
              << "\n";

  info_ptr = png_create_info_struct(png_ptr);
  if (!info_ptr) std::cerr << "[read_png_file] png_create_info_struct failed\n";

  if (setjmp(png_jmpbuf(png_ptr)))
    std::cerr << "[read_png_file] Error during init_io\n";

  png_init_io(png_ptr, fp);
  png_set_sig_bytes(png_ptr, 8);

  png_read_info(png_ptr, info_ptr);

  int width = png_get_image_width(png_ptr, info_ptr);
  int height = png_get_image_height(png_ptr, info_ptr);
  color_type = png_get_color_type(png_ptr, info_ptr);
  bit_depth = png_get_bit_depth(png_ptr, info_ptr);

  int number_of_passes = png_set_interlace_handling(png_ptr);
  png_read_update_info(png_ptr, info_ptr);

  /* read file */
  if (setjmp(png_jmpbuf(png_ptr)))
    std::cerr << "[read_png_file] Error during read_image\n";

  png_bytepp row_pointers = (png_bytep*)malloc(sizeof(png_bytep) * height);

  for (size_t y = 0; y < height; y++)
    row_pointers[y] = (png_byte*)malloc(png_get_rowbytes(png_ptr, info_ptr));

  png_read_image(png_ptr, row_pointers);

  GLuint textureId;
  glGenTextures(1, &textureId);
  glBindTexture(GL_TEXTURE_2D, textureId);
  glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA,
               GL_UNSIGNED_BYTE, row_pointers);

  fclose(fp);
  return textureId;
}

bool TextureManager::isPng(std::string ext) {
  std::vector<std::string> exts({"png", "PNG"});
  auto pos = std::find_if(exts.cbegin(), exts.cend(),
                          [&ext](std::string e) { return ext == e; });
  return pos != exts.cend();
}
bool TextureManager::isJpeg(std::string ext) {
  std::vector<std::string> exts({"jpeg", "jpg", "JPG", "JPEG"});
  auto pos = std::find_if(exts.cbegin(), exts.cend(),
                          [&ext](std::string e) { return ext == e; });
  return pos != exts.cend();
}

TextureManager* TextureManager::instance() {
  static TextureManager inst;
  return &inst;
}
}
}
