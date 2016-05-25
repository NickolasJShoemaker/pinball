//#ident "$Id: TextureUtil.h,v 1.5 2003/06/13 13:39:46 rzr Exp $"
/***************************************************************************
                          TextureUtil.h  -  description
                             -------------------
    begin                : Mon Nov 27 2000
    copyright            : (C) 2000 by Henrik Enqvist
    email                : henqvist@excite.com
***************************************************************************/


#ifndef TEXTUREUTIL_H
#define TEXTUREUTIL_H

#ifndef PRIVATE_H
  #error "Must include Private.h before Config.h"
#endif

#include <SDL/SDL_opengl.h>

typedef struct {
  unsigned int width;
  unsigned int height;
  unsigned int channels;
  unsigned char* pixels;
} struct_image;

#define EmImage struct_image
#define EmTexture GLuint

constexpr float EM_RIGHT = 0.8f;
constexpr float EM_UP    = 0.6f;
constexpr float EM_NEAR  = 1.0f;
constexpr float EM_FAR   = 1000.0f;

#include <map>
#include <string>
#include <list>

#include "EMath.h"

/** Singleton class for initializing graphics and loading textures. */
class TextureUtil {
protected:
  TextureUtil();
public:
  ~TextureUtil() = default;
  static TextureUtil* getInstance();
  void initGrx();
  void stopGrx();
  /// just unload the textures from main mem (needed w32)
  void freeTextures(); 
  void reloadTextures();
  void resizeView(unsigned int w = 320 , unsigned int h = 240 );
  EmTexture* loadTexture(const char* file);
  EmImage* loadImage(const char* file);
  const char * getTextureName(EmTexture * tex);
  void setClearColor(float r = 1, float g = 1, float b = 1, float a = 1);
  void getFilename(list<string>& filenames);
private:
  /// load it also in openGL context
  int genTexture( char const * const filename, EmTexture * const texture);
  map<EmTexture*, string> m_hImageName;
  map<string, EmTexture*> m_hEmTexture;
  static TextureUtil* p_TextureUtil;
  Color m_colClear;
};

#endif // TEXTUREUTIL_H
//EOF: $Id: TextureUtil.h,v 1.5 2003/06/13 13:39:46 rzr Exp $
