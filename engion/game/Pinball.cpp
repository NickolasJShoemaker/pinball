//#ident "$Id: Pinball.cpp,v 1.44 2003/06/18 10:43:44 henqvist Exp $"
/***************************************************************************
                          Pinball.cpp  -  description
                             -------------------
    begin                : Thu Mar 9 2000
    copyright            : (C) 2000 by Henrik Enqvist
    email                : henqvist@excite.com
***************************************************************************/

#include <fstream>
#include <string>
#include <iostream>

//#include <sstream>
#include <strstream> //TODO:

#include <sys/stat.h>
#include <sys/types.h>
#include <cstring>
#include <cstdlib>
#include <ctime>

#ifdef _MSC_VER //!+rzr : maybe we can use a portable IO lib such as physicfs
  #include <io.h> //find
  #include <direct.h> //getcwd
#else
  #include <dirent.h>
#endif
#include "Private.h" // macro flags defined here

#ifdef HAVE_UNISTD_H
  #include <unistd.h> // not in msvc (replaced by io.h)
#endif //!-rzr

#include "Pinball.h"
#include "Keyboard.h"
#include "Menu.h"
#include "Engine.h"
#include "Camera.h"
#include "Light.h"
#include "BigSphere.hpp"
#include "Cylinder.hpp"
#include "BounceBehavior.h"
#include "KeyBehavior.hpp"
#include "Grid.hpp"
#include "KeyRotBehavior.hpp"
#include "Polygon.h"
#include "TextureUtil.h"
#include "SoundUtil.h"
#include "Score.h"
#include "CollisionBounds.h"

//#include "EyeBehavior.h"
#include "Config.h"
#include "EmFont.h"
#include "Loader.h"
#include "BallGroup.h"
#include "Table.h"

#if EM_USE_SDL
  #include <SDL.h>
#endif

constexpr float AMBIENT = 0.05f;

void get_config(void);

float g_RatioArray[] = { 1./2. , 1./1.  , 5./4. , 4./3. , 3./2. , 16/10. , 16./9. , 9./5, 2./1. };
int g_WidthArray[] = { 320, 400, 512, 640, 800 , 864, 1024, 1280 , 1680 , 1920};

/*
* Main
*/
int main(int argc, char *argv[]){
  //cerr<<"+ Pinball::main"<<endl;
  try {
    // Create a engine and parse emilia arguments
    Config::getInstance()->loadConfig();
    Engine* engine = new Engine(argc, argv);

    float direct = 0.0f;
    float temp = Config::getInstance()->getBrightness();
    if(temp < 0.35f){
      direct = 0.3f;
    }else if(temp >= 0.35f && <= 0.75f){
      direct = temp - 0.5f;
    }else{
      direct = 0.8f;
    }
    engine->setLightning(direct, AMBIENT);

#if EM_USE_SDL
    string filename = Config::getInstance()->getDataDir() + string("/font_34.png");
#endif
#if EM_USE_ALLEGRO
    string filename = Config::getInstance()->getDataDir() + string("/font_35.pcx");
#endif

    EmFont::getInstance()->loadFont(filename.c_str());

    // Add a score board and a menu.
    MenuItem* menu = createMenus(engine);

    // Draw to the screen.
    int all = 0;

    engine->resetTick();

    //cout<<"catch close win"<<endl; //!rzr
    while (!(SDL_QuitRequested() || Keyboard::isKeyDown(SDLK_INSERT))){

#if EM_DEBUG
      if (Keyboard::isKeyDown(SDLK_p)){
        Keyboard::waitForKey();
        Keyboard::clear();
        engine->resetTick();
      }
#endif //EM_DEBUG

      if (Keyboard::isKeyDown(SDLK_ESCAPE) || all == 0){
        SoundUtil::getInstance()->pauseMusic();
        if (menu->perform() == EM_MENU_EXIT){
          break;
        }
        engine->resetTick();
        SoundUtil::getInstance()->resumeMusic();
      }

      if (Keyboard::isKeyDown(SDLK_r)){
        SignalSender::getInstance()->addSignal(PBL_SIG_RESET_ALL, 0, engine, NULL);
      }

      if (engine->nextTickFPS(200)){
        engine->tick();
      }else{
        engine->render();
        if (Table::getInstance()->getScore() != NULL){
          Table::getInstance()->getScore()->draw();
        }
        if (engine->getGroup(0) == NULL){
          EmFont::getInstance()->printRowCenter("no table loaded", 6);
          EmFont::getInstance()->printRowCenter("press esc", 8);
        }
        engine->swap();
      }

      all++;
      //engine->limitFPS(100);
    }

    Config::getInstance()->saveConfig();

    // Write high scores to disk - pnf
    Table::getInstance()->writeHighScoresFile();

    delete(engine);
  }catch(string str){
    cerr << "EXCEPTION: " << str << endl;
  }

  return EXIT_SUCCESS;
}

#if EM_USE_ALLEGRO
END_OF_MAIN();
#endif


/// entry point function (main) for w32 codewarrior
#if( (defined WIN32 ) && ( defined __MWERKS__ ) )
  extern "C" {
    /**
     * @author: www.Philippe.COVAL.free.FR - $rev: $author
     * Was need to convert win32 args to ansi way :
     * int argc; char** argv;
     * convertStringWords( GetCommandLine(), &argc, &argv);
     * TODO : check if quotes are wanted or not ?
     **/

    void convertStringWords( char * arg, int *argc, char*** argv);
    void convertStringWords( char * arg, int *argc, char*** argv){
      char *b, *e, *q;
      int i=0;
      int n;
      b = arg;
      q = e  = b ;
      //debug("+ convertStringWords");  debug(arg);
      *argc=0;
      *argv = (char**) malloc( sizeof(char*));

      do {
        while ( *b == ' ' ) b++;
        q=e=b-1;

        do { q = strchr( q + 1 , '"'); }
        while ( (q != NULL) && ( *(q-1) == '\\' ) );

        do { e = strchr( e + 1 , ' '); }
        while ( (e != NULL) && ( *(e-1) == '\\' ) );
        //debugf("%u<%u ?\n",&q,&e);

        if ( (q != NULL) && ( e != NULL) && ( q < e ) ){
          //debug("quoted");
          do { q = strchr( q + 1 , '"'); }
          while ( (q != NULL) && ( *(q-1) == '\\' ) );
          e = ++q;
        }

        if ( e != NULL) n = (e) - b; else n = strlen(b);
        //debugf("n=%d=%s;\n", n,b);


        *argv = (char**) realloc( *argv, ( (*argc) + 1 ) * sizeof(char*) );
        (*argv)[ *argc ] = (char*) malloc ( n +1);
        strncpy( (*argv)[ *argc ], b , n);
        *( (*argv)[ *argc ] + n ) = '\0';
        //debug( (*argv)[ *argc ] );

        b = e;
        (*argc)++;

      } while ( e != NULL );
      //debug("- convertStringWords");
    }

  } //extern "C"

  /*
  * Win32 Main
  */
  int WINAPI WinMain(HINSTANCE hInst,  HINSTANCE hPreInst, LPSTR lpszCmdLine,  int nCmdShow){
    int argc = 0; char** argv = 0;
    convertStringWords(GetCommandLine(), &argc, &argv);

    //int argc = 1;   char* argv[1] = { 0 };
    //argv[0] = GetCommandLine(); //cut on space
    return main(argc, argv);
  }
#endif //win32 Main
// EOF $Id: Pinball.cpp,v 1.44 2003/06/18 10:43:44 henqvist Exp $
