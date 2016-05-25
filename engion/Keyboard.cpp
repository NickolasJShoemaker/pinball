/***************************************************************************
                          Keyboard.cpp  -  description
                             -------------------
    begin                : Thu Feb 1 2001
    copyright            : (C) 2001 by Henrik Enqvist
    email                : henqvist@excite.com
 ***************************************************************************/

#include <cstring>
#include "Private.h"
#include "Keyboard.h"

#if EM_USE_SDL
bool Keyboard::m_abKey[KEY_MAX];
#endif

Keyboard::Keyboard(){
	this->clear();
}

void Keyboard::poll(){
  SDL_Event event;
  while(SDL_PollEvent(&event)){
    if (event.type == SDL_KEYDOWN){
      m_abKey[event.key.keysym.sym] = true;
    }
    if (event.type == SDL_KEYUP){
      m_abKey[event.key.keysym.sym] = false;
    }
  }
}

void Keyboard::clear(){
  memset(m_abKey, false, KEY_MAX*sizeof(bool));
}

EMKey Keyboard::waitForKey(){
  while(true){
    SDL_Event event;
    SDL_WaitEvent(&event);
    if (event.type == SDL_KEYDOWN && event.key.state == SDL_PRESSED){
      break;
    }
  }
  while (true){
    SDL_Event event;
    SDL_WaitEvent(&event);
    if (event.type == SDL_KEYUP && event.key.state == SDL_RELEASED){
      return event.key.keysym.sym;
    }
  }
}

bool Keyboard::isKeyDown(int piKey){
  if (piKey < 0 || piKey >= KEY_MAX) return false;
  return m_abKey[piKey];
}
