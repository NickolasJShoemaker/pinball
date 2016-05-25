/***************************************************************************
                          Keyboard.h  -  description
                             -------------------
    begin                : Thu Feb 1 2001
    copyright            : (C) 2001 by Henrik Enqvist
    email                : henqvist@excite.com
 ***************************************************************************/


#ifndef KEYBOARD_H
#define KEYBOARD_H

#ifndef PRIVATE_H
  #error Must include Private.h before Keyboard.h
#endif

#include <SDL2/SDL.h>
//#include <SDL2/SDL_keyboard.h>
//#include <SDL2/SDL_keysym.h>
//#define EMKey int
#define EMKey SDL_Keycode

#ifndef KEY_MAX
  #define KEY_MAX 512
#endif

/** @author Henrik Enqvist */

class Keyboard {
 public:
  Keyboard();
  ~Keyboard()=default;
  static void clear();
  static void poll();
  static bool isKeyDown(int piKey);
  static EMKey waitForKey();
 private:
  static bool m_abKey[KEY_MAX];
};

#endif // KEYBOARD_H
