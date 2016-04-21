// clang-format off
#include <fcntl.h>
#include <png.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <unistd.h>
#include <boost/filesystem.hpp>
#include <fstream>
#include <iostream>
#include <jpeglib.h> // jpeglib include is order-dependent, It MUST be included after <stdio.h>
#include "TextureManager.hpp"
// clang-format on

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
  struct stat file_info;
  int rc = stat(filename.c_str(), &file_info);
  if (rc) {
    std::cerr << "FAILED to stat source jpg";
    exit(EXIT_FAILURE);
  }
  long jpg_size = file_info.st_size;
  char* jpg_buffer = new char[jpg_size + 100];
  int i = 0;

  std::ifstream infile;
  infile.open(filename.c_str(), std::ios::in | std::ios::binary);

  while (infile.read((char*)(jpg_buffer + i), jpg_size - i)) {
    i += infile.gcount();
    if (i == jpg_size) break;
  }

  cinfo.err = jpeg_std_error(&emgr);
  jpeg_create_decompress(&cinfo);
  jpeg_mem_src(&cinfo, (unsigned char*)jpg_buffer, jpg_size);

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
  glTexParameteri(GL_TEXTURE_2D, GL_GENERATE_MIPMAP, GL_TRUE);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
  glGenerateMipmap(GL_TEXTURE_2D);

  jpeg_finish_decompress(&cinfo);
  jpeg_destroy_decompress(&cinfo);
  return textureId;
}

GLuint TextureManager::loadPngTexture(std::string filename) {
  png_byte header[8];

  FILE* fp = fopen(filename.c_str(), "rb");
  if (fp == 0) {
    perror(filename.c_str());
    return 0;
  }

  // read the header
  fread(header, 1, 8, fp);

  if (png_sig_cmp(header, 0, 8)) {
    fprintf(stderr, "error: %s is not a PNG.\n", filename.c_str());
    fclose(fp);
    return 0;
  }

  png_structp png_ptr =
      png_create_read_struct(PNG_LIBPNG_VER_STRING, NULL, NULL, NULL);
  if (!png_ptr) {
    fprintf(stderr, "error: png_create_read_struct returned 0.\n");
    fclose(fp);
    return 0;
  }

  // create png info struct
  png_infop info_ptr = png_create_info_struct(png_ptr);
  if (!info_ptr) {
    fprintf(stderr, "error: png_create_info_struct returned 0.\n");
    png_destroy_read_struct(&png_ptr, (png_infopp)NULL, (png_infopp)NULL);
    fclose(fp);
    return 0;
  }

  // create png info struct
  png_infop end_info = png_create_info_struct(png_ptr);
  if (!end_info) {
    fprintf(stderr, "error: png_create_info_struct returned 0.\n");
    png_destroy_read_struct(&png_ptr, &info_ptr, (png_infopp)NULL);
    fclose(fp);
    return 0;
  }

  // the code in this if statement gets called if libpng encounters an error
  if (setjmp(png_jmpbuf(png_ptr))) {
    fprintf(stderr, "error from libpng\n");
    png_destroy_read_struct(&png_ptr, &info_ptr, &end_info);
    fclose(fp);
    return 0;
  }

  // init png reading
  png_init_io(png_ptr, fp);

  // let libpng know you already read the first 8 bytes
  png_set_sig_bytes(png_ptr, 8);

  // read all the info up to the image data
  png_read_info(png_ptr, info_ptr);

  // variables to pass to get info
  int bit_depth, color_type;
  png_uint_32 temp_width, temp_height;

  // get info about png
  png_get_IHDR(png_ptr, info_ptr, &temp_width, &temp_height, &bit_depth,
               &color_type, NULL, NULL, NULL);

  // if (width){ *width = temp_width; }
  // if (height){ *height = temp_height; }

  // Update the png info struct.
  png_read_update_info(png_ptr, info_ptr);

  // Row size in bytes.
  int rowbytes = png_get_rowbytes(png_ptr, info_ptr);

  // glTexImage2d requires rows to be 4-byte aligned
  rowbytes += 3 - ((rowbytes - 1) % 4);

  // Allocate the image_data as a big block, to be given to opengl
  png_byte* image_data;
  image_data =
      (unsigned char*)malloc(rowbytes * temp_height * sizeof(png_byte) + 15);
  if (image_data == NULL) {
    fprintf(stderr, "error: could not allocate memory for PNG image data\n");
    png_destroy_read_struct(&png_ptr, &info_ptr, &end_info);
    fclose(fp);
    return 0;
  }

  // row_pointers is for pointing to image_data for reading the png with libpng
  png_bytep* row_pointers = (png_bytep*)malloc(temp_height * sizeof(png_bytep));
  if (row_pointers == NULL) {
    fprintf(stderr, "error: could not allocate memory for PNG row pointers\n");
    png_destroy_read_struct(&png_ptr, &info_ptr, &end_info);
    free(image_data);
    fclose(fp);
    return 0;
  }

  // set the individual row_pointers to point at the correct offsets of
  // image_data
  int i;
  for (i = 0; i < temp_height; i++) {
    row_pointers[temp_height - 1 - i] = image_data + i * rowbytes;
  }

  // read the png into image_data through row_pointers
  png_read_image(png_ptr, row_pointers);

  // Generate the OpenGL texture object

  GLuint textureId;
  glGenTextures(1, &textureId);
  glBindTexture(GL_TEXTURE_2D, textureId);
  glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, temp_width, temp_height, 0, GL_RGB,
               GL_UNSIGNED_BYTE, image_data);
  glTexParameteri(GL_TEXTURE_2D, GL_GENERATE_MIPMAP, GL_TRUE);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
  glGenerateMipmap(GL_TEXTURE_2D);

  fclose(fp);
  return textureId;
}

bool TextureManager::isPng(std::string ext) {
  std::vector<std::string> exts({".png", ".PNG"});
  auto pos = std::find_if(exts.cbegin(), exts.cend(),
                          [&ext](std::string e) { return ext == e; });
  return pos != exts.cend();
}
bool TextureManager::isJpeg(std::string ext) {
  std::vector<std::string> exts({".jpeg", ".jpg", ".JPG", ".JPEG"});
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
