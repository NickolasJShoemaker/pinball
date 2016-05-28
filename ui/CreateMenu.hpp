#ifndef MENU_HPP
#define MENU_HPP

/****************************************************************************
 * Menus
 ***************************************************************************/

constexpr float AMBIENT = 0.05f;
void get_config(void);

float g_RatioArray[] = { 1./2. , 1./1.  , 5./4. , 4./3. , 3./2. , 16/10. , 16./9. , 9./5, 2./1. };
int g_WidthArray[] = { 320, 400, 512, 640, 800 , 864, 1024, 1280 , 1680 , 1920};

MenuChoose* menusnd     = NULL;
MenuChoose* menumusic   = NULL;
MenuChoose* menubright  = NULL;
MenuChoose* menuscreen  = NULL;
MenuChoose* menusize    = NULL;
MenuChoose* menuratio   = NULL;
MenuChoose* menuview    = NULL;
MenuChoose* menufilter  = NULL;
MenuChoose* menufps     = NULL;
MenuChoose* menufire    = NULL;
MenuChoose* menulights  = NULL;

/****************************************************************************
 * Define some menu classes
 ***************************************************************************/

// Menu item to display high scores - pnf
class MyMenuHighScores : public MenuFct {
public:
  MyMenuHighScores(const char * name, int (*fct)(void), Engine *e) : MenuFct(name, fct, e){};
protected:
  int perform(){
    p_Engine->clearScreen();

    if (p_Texture != NULL)
      p_Engine->drawSplash(p_Texture);

    p_EmFont->printRowCenter("- High Scores -", 2);
    string sHeader = string("table: ") + Table::getInstance()->getTableName();
    p_EmFont->printRowCenter(sHeader.c_str(), 3);

    int nStartRow = 5;
    string sRow = "X";

    list<string> listHighScores;

    Table::getInstance()->getHighScoresData(listHighScores);

    if (listHighScores.size() > 0){
      list<string>::iterator iter = listHighScores.begin();
      list<string>::iterator end = listHighScores.end();
      for (int i=0; i<EM_MAX_HIGHSCORES && iter != end; ++i, ++iter){
        sRow = (*iter);
        p_EmFont->printRowCenter(sRow.c_str(), nStartRow + i);
      }
    }else{
      p_EmFont->printRowCenter("No Table Loaded!", 10);
    }

    p_EmFont->printRowCenter("Hit any key for main menu...", 20);

    p_Engine->swap();
    Keyboard::waitForKey();

    return EM_MENU_NOP;
  }
};

/** Menu item for changing a key binding. */
class MyMenuKey : public MenuFct {
public:
  MyMenuKey(const char * name, int (*fct)(void), Engine *e) : MenuFct(name, fct, e){};
protected:

  int perform (){
    p_Engine->clearScreen();
    if (p_Texture != NULL) p_Engine->drawSplash(p_Texture);
    p_EmFont->printRowCenter("press a key", 10);
    p_Engine->swap();
    EMKey key = Keyboard::waitForKey();
    string name(m_Name);
    Config::getInstance()->setKey(name, key);
    return EM_MENU_NOP;
  }

  const char * getText(){
    ostrstream stm; //TODO
    stm.clear();
    string name(m_Name);
    const char * keyname = Config::getInstance()->getKeyCommonName(Config::getInstance()->getKey(name));
    string key;
    if (keyname != NULL){
      key = string(keyname);
    }else{
      key = string("unknown");
    }
    name = name + ":";
    while (name.size() < 12){
      name = name + " ";
    }
    while (key.size() < 12){
      key = " " + key;
    }
    stm << name << key << '\0';
    string text = stm.str();
    return text.c_str();
  }
};


/** The apply meny item. */
class MyMenuApply : public MenuFct {
public:
  MyMenuApply(const char * name, int (*fct)(void), Engine *e) : MenuFct(name, fct, e){};
protected:
  int perform(){
    Config* config = Config::getInstance();
    TextureUtil* textureutil = TextureUtil::getInstance();
    // sound
    int temp = menusnd->getCurrent();
    if(temp >= 0 && temp <= 8){
      config->setSound(temp);
    }
    temp = menumusic->getCurrent();
    if(temp >= 0 && temp <= 8){
      config->setMusic(temp);
    }
    SoundUtil::getInstance()->applyConfigVolume();
    // fullscreen
    if(menuscreen->getCurrent() == 0){
      if(config->useFullScreen() == false){
        //SDL_WM_ToggleFullScreen(SDL_GetVideoSurface());
        SDL_SetWindowFullscreen(SDL_GL_GetCurrentWindow(), 0);
      }
      config->setFullScreen(true);
    }else{
      if(config->useFullScreen() == true){
        //SDL_WM_ToggleFullScreen(SDL_GetVideoSurface());
        SDL_SetWindowFullscreen(SDL_GL_GetCurrentWindow(), SDL_WINDOW_FULLSCREEN);
      }
      config->setFullScreen(false);
    }
    // brightness
    temp = menubright->getCurrent();
    if(temp >= 0 && temp <= 5){
      menubright->getEngine()->setLightning((temp/10)+0.3f, AMBIENT);
      Config::getInstance()->setBrightness((temp/10)+0.3f);
    }else{
      menubright->getEngine()->setLightning(0.5f, AMBIENT);
      Config::getInstance()->setBrightness(0.5f);
    }

    {
      // scren ratio
      float ratio=4./3.;
      {
        int index = menuratio->getCurrent();
        if( index < ( sizeof(g_RatioArray) / sizeof( g_RatioArray[0]) ) ){
          ratio = g_RatioArray[ index ];
        }
        config->setRatio( ratio );
      }
     
      // screen size
      int w=640, h=480;
      {
      
        int index = menusize->getCurrent();
        if( index < ( sizeof(g_WidthArray) / sizeof(g_WidthArray[0]) ) ){
          w = g_WidthArray[ index ];
        }
        h=w/ratio;
      }
      
      if((config->getWidth() != w)  || (config->getHeight() != h)){
        //SDL_SetVideoMode(w, h, config->getBpp(), SDL_OPENGL | (config->useFullScreen() ? SDL_FULLSCREEN : 0));
        TextureUtil::getInstance()->resizeView(w, h);

        #ifdef WIN32 //~rzr:{  //cout<<("Workround bug (for WIN32) + macosx etc");
        //TextureUtil::getInstance()->reloadTextures(); //TODO: fix the w32 bug
        TextureUtil::getInstance()->freeTextures(); // "hide" the w32 bug
        string filename = Config::getInstance()->getDataDir() + string("/font_34.png");
        EmFont::getInstance()->loadFont(filename.c_str());
        //cout<<"may not be  driver bug cos it also happends under wine"<<endl;
        // unload level and textures //TODO: Reload Splash Screen
        Table::getInstance()->clear(Engine::getCurrentEngine() );
        #endif //~rzr:} //cout<<"@w32 / resizing unreference textures (mipmaping?)"<<endl;
      }

      config->setSize(w, h);
    }

    switch (menuview->getCurrent()){
      case 1: config->setView(1); break;
      case 2: config->setView(2); break;
      case 3: config->setView(3); break;
      default: config->setView(0);
    }
    // texture filter
    if (menufilter->getCurrent() == 0){
      config->setGLFilter(EM_LINEAR);
    } else if (menufilter->getCurrent() == 1){
      config->setGLFilter(EM_NEAREST);
    }else{
      config->setGLFilter(-1);
    }
    // fps
    config->setShowFPS((menufps->getCurrent() == 0) ? false:true);
    // fire
    if (menufire->getCurrent() == 0){
      config->setFire(false);
      for (int a=0; a<MAX_BALL; ++a){
        BallGroup * bg = Table::getInstance()->getBall(a);
        if (bg != NULL){
          Behavior * beh = bg->getBehavior();
          EmAssert(beh != NULL, "MyMenuApply::perform behavior NULL");
          EmAssert(beh->getType() == PBL_TYPE_BOUNCEBEH,
                   "MyMenuApply::perform behavior not bouncebehavior");
          ((BounceBehavior*)beh)->setFire(false);
        }
      }
    }else{
      config->setFire(true);
      for (int a=0; a<MAX_BALL; ++a){
        BallGroup * bg = Table::getInstance()->getBall(a);
        if (bg != NULL){
          Behavior * beh = bg->getBehavior();
          EmAssert(beh != NULL, "MyMenuApply::perform behavior NULL");
          EmAssert(beh->getType() == PBL_TYPE_BOUNCEBEH, "MyMenuApply::perform behavior not bouncebehavior");
          ((BounceBehavior*)beh)->setFire(true);
        }
      }
    }
    // dynamic lights
    config->setLights((menulights->getCurrent() == 0) ? true:false);
    get_config();
    return EM_MENU_NOP;
  }
};

/** The back button. */
class MyMenuCancel : public MenuFct {
public:
  MyMenuCancel(const char * name, int (*fct)(void), Engine *e) : MenuFct(name, fct, e){};
protected:
  int perform (){
    get_config();
    return EM_MENU_BACK;
  }
};

/** Button for loading a table. */
class MyMenuLoad : public MenuFct {
public:
  MyMenuLoad(const char * name, int (*fct)(void), Engine *e) : MenuFct(name, fct, e){};
protected:
  int perform (){
    p_Engine->clearScreen();
    if (p_Texture != NULL) p_Engine->drawSplash(p_Texture);
    p_EmFont->printRowCenter("LOADING", 10);
    p_Engine->swap();

    // Save the high scores of current table, if any - pnf
    Table::getInstance()->writeHighScoresFile();

    if (Table::getInstance()->loadLevel(p_Engine, m_Name) == 0){
      // Load high scores for this table - pnf
      Table::getInstance()->readHighScoresFile();

      p_Engine->clearScreen();
      if (p_Texture != NULL) p_Engine->drawSplash(p_Texture);
      p_EmFont->printRowCenter("OK", 10);
      p_Engine->swap();
      p_Engine->delay(500);
    }else{
      p_Engine->clearScreen();
      if (p_Texture != NULL) p_Engine->drawSplash(p_Texture);
      p_EmFont->printRowCenter("ERROR", 10);
      p_Engine->swap();
      p_Engine->delay(1000);
    }
    return EM_MENU_BACK;
  }
};


/****************************************************************************
 * Menu functions
 ***************************************************************************/

/** Update the current menu with the configuration. */
void get_config(void){
  // sound
 
  menusnd->setCurrent( Config::getInstance()->getSound() );

  int temp = Config::getInstance()->getMusic();
  if(temp >= 0 && temp <= 8){
    menumusic->setCurrent(temp); 
  }

  menuscreen->setCurrent(Config::getInstance()->useFullScreen() ? 0:1);  // fullscreen

  // brightness
  float brightness = Config::getInstance()->getBrightness() - 0.35f;
  if(brightness >= 0.0f && brightness <= 0.4f){
    menubright->setCurrent((int)(brightness * 10));
  }else{
    menubright->setCurrent(5); 
  }

  { cerr<<"// screen ratio="<<Config::getInstance()->getRatio()<<endl;
    int array_size = sizeof( g_RatioArray ) / sizeof( g_RatioArray[0] );
    menuratio->setCurrent(3);
    for (int i=array_size-1; (i>=0) ; i-- ){
      if (Config::getInstance()->getRatio() == g_RatioArray[i]){
        menuratio->setCurrent(i);
        i=0;
      }
    }
  }

  { // screen size
    int array_size = sizeof( g_WidthArray ) / sizeof( g_WidthArray[0] );
    menusize->setCurrent(0);
    for (int i=array_size-1; (i>=0) ; i-- ){
      if (Config::getInstance()->getWidth() == g_WidthArray[i]){
        menusize->setCurrent(i);
        i=0;
      }    
    }
  }

  // view mode
  switch(Config::getInstance()->getView()){
    case 1: menuview->setCurrent(1); break;
    case 2: menuview->setCurrent(2); break;
    case 3: menuview->setCurrent(3); break;
    default: menuview->setCurrent(0);
  }
  // texture filter
  if (Config::getInstance()->getGLFilter() == EM_LINEAR){
    menufilter->setCurrent(0);
  } else if (Config::getInstance()->getGLFilter() == EM_NEAREST){
    menufilter->setCurrent(1);
  }else{
    menufilter->setCurrent(2);
  }
  menufps->setCurrent(Config::getInstance()->getShowFPS() ? 1:0);   // show fps
  menufire->setCurrent(Config::getInstance()->getFire() ? 1:0);     // fire
  menulights->setCurrent(Config::getInstance()->useLights() ? 0:1); // dynamic lights
}

/* Create some menus */
MenuItem* createMenus(Engine* engine){
  // Create the meny
  MenuSub* menu = new MenuSub("main menu", engine);
  menu->setBottomText("http://pinball.sourceforge.net");

  MenuSub* menuresume = new MenuSub("play", engine);
  menuresume->setAction(EM_MENU_RESUME);
  menu->addMenuItem(menuresume);

  MenuSub* menuload = new MenuSub("load table", engine);
  menu->addMenuItem(menuload);

  // Show high scores for current loadad table - pnf
  MyMenuHighScores* menuhighscores = new MyMenuHighScores("High Scores", NULL, engine);
  menu->addMenuItem(menuhighscores);

  MenuSub* menucfg = new MenuSub("config", engine);
  menu->addMenuItem(menucfg);

  MenuSub* menuexit = new MenuSub("exit", engine);
  menuexit->setAction(EM_MENU_EXIT);
  menu->addMenuItem(menuexit);

  MenuSub* menugfx = new MenuSub("graphics", engine);
  menucfg->addMenuItem(menugfx);

  MenuSub* menuaudio = new MenuSub("audio", engine);
  menucfg->addMenuItem(menuaudio);

  MenuSub* menukey = new MenuSub("keyboard", engine);
  menukey->setBottomText("shortcuts for view change F5-F8");
  menucfg->addMenuItem(menukey);

  string filename = string(Config::getInstance()->getDataSubDir()) + "/splash.png";
  EmTexture * tex = TextureUtil::getInstance()->loadTexture(filename.c_str());
  if (tex != NULL){
    menu->setBackground(tex);
    menuload->setBackground(tex);
    menucfg->setBackground(tex);
    menugfx->setBackground(tex);
    menuaudio->setBackground(tex);
    menukey->setBackground(tex);
    menuhighscores->setBackground(tex);
  }else{
    cerr << "Error loading data/splash.png" << endl;
  }

  // create one entry for each directory
  // TODO scrolling text if too many tables
#if ( HAVE_UNISTD_H ) // __GNUC__ //!+rzr
  DIR * datadir = opendir(Config::getInstance()->getDataDir());
  char cwd[256];
  if (datadir != NULL && getcwd(cwd, 256) != NULL){
    struct dirent * entry;
    struct stat statbuf;
    //cerr<<  Config::getInstance()->getDataDir() <<endl; //!+rzr
    int status = chdir(Config::getInstance()->getDataDir());
    if ( status == 0 ){
      while ((entry = readdir(datadir)) != NULL){
  lstat(entry->d_name, &statbuf);
  if (S_ISDIR(statbuf.st_mode) &&
      strcmp(".", entry->d_name) != 0 &&
      strcmp("..", entry->d_name) != 0){
    MenuFct * menufct = new MyMenuLoad(entry->d_name, NULL, engine);
    menuload->addMenuItem(menufct);
    if (tex != NULL){
      menufct->setBackground(tex);
    }
  }
      }
      chdir(cwd);
    }else{
      cerr<<"error: io: datadir "<<endl;
    }
    closedir(datadir);
  }
#else
#ifdef _MSC_VER //!+rzr : thanx to ramlaid ;)
  struct _finddata_t dirFile;
  long hFile=0;
  char cwd[256];
  if (getcwd(cwd,256) != NULL){
    chdir(Config::getInstance()->getDataDir());
    if( (hFile = _findfirst( "*", &dirFile )) != NULL ){
      do {
        if ((dirFile.attrib & _A_SUBDIR) != 0){
          if (strcmp(".", dirFile.name) != 0
              && strcmp("..", dirFile.name) != 0){
            MenuFct * menufct = new MyMenuLoad(dirFile.name, NULL, engine);
            menuload->addMenuItem(menufct);
            if (tex != NULL){
              menufct->setBackground(tex);
            }
          }
        }
      }
      while( _findnext( hFile, &dirFile ) == 0 );
      chdir(cwd);
      _findclose( hFile );
    }
  }
#else
#warning "check your compiler here"
#endif
#endif //!+rzr

  menuview = new MenuChoose(engine);
  menuview->addText(  "view:         classic");
  menuview->addText(  "view:   softly moving");
  menuview->addText(  "view:          moving");
  menuview->addText(  "view:             top");
  menugfx->addMenuItem(menuview);

  menuscreen = new MenuChoose(engine);
  menuscreen->addText("screen:    fullscreen");
  menuscreen->addText("screen:      windowed");
  menugfx->addMenuItem(menuscreen);

  menubright = new MenuChoose(engine);
  menubright->addText( "brightness:    =.....");
  menubright->addText( "brightness:    ==....");
  menubright->addText( "brightness:    ===...");
  menubright->addText( "brightness:    ====..");
  menubright->addText( "brightness:    =====.");
  menubright->addText( "brightness:    ======");
  menugfx->addMenuItem(menubright);

  {
    menusize = new MenuChoose(engine);
    menusize->addText(   "screen width:     340");
    menusize->addText(   "screen width:     400");
    menusize->addText(   "screen width:     512");
    menusize->addText(   "screen width:     640");
    menusize->addText(   "screen width:     800");
    menusize->addText(   "screen width:     864");
    menusize->addText(   "screen width:    1024");
    menusize->addText(   "screen width:    1280");
    menusize->addText(   "screen width:    1680");
    menusize->addText(   "screen width:    1920");
    menugfx->addMenuItem(menusize);
  }
  {
    menuratio = new MenuChoose(engine);
    menuratio->addText( "ratio:      0.5 (1/2)");
    menuratio->addText( "ratio:       1. (1/1)");
    menuratio->addText( "ratio:      1.2 (5/4)");
    menuratio->addText( "ratio:      1.3 (4/3)");
    menuratio->addText( "ratio:      1.5 (3/2)");
    menuratio->addText( "ratio:    1.6 (16/10)");
    menuratio->addText( "ratio:     1.7 (16/9)");
    menuratio->addText( "ratio:      1.8 (9/5)");
    menuratio->addText( "ratio:        2 (2/1)");
    menugfx->addMenuItem(menuratio);
  }

  menufilter = new MenuChoose(engine);
  menufilter->addText("texture:       nicest"); //was linear // gamers  //!rzr
  menufilter->addText("texture:      fastest"); //was nearest // vocabulary :)
  menufilter->addText("texture:         none");
  menugfx->addMenuItem(menufilter);

  menufps = new MenuChoose(engine);
  menufps->addText(   "show fps:          no");
  menufps->addText(   "show fps:         yes");
  menugfx->addMenuItem(menufps);

  menufire = new MenuChoose(engine);
  menufire->addText(  "fire effect:       no");
  menufire->addText(  "fire effect:      yes");
  menugfx->addMenuItem(menufire);

  menulights = new MenuChoose(engine);
  menulights->addText("dynamic lights:   yes");
  menulights->addText("dynamic lights:    no");
  menugfx->addMenuItem(menulights);

  //   menumaxfps = new MenuChoose(engine);
  //   menumaxfps->addText("max fps            50");
  //   menumaxfps->addText("max fps           100");
  //   menugfx->addMenuItem(menumaxfps);

  menusnd = new MenuChoose(engine);
  menusnd->addText(   "sound:            off");
  menusnd->addText(   "sound:       =.......");
  menusnd->addText(   "sound:       ==......");
  menusnd->addText(   "sound:       ===.....");
  menusnd->addText(   "sound:       ====....");
  menusnd->addText(   "sound:       =====...");
  menusnd->addText(   "sound:       ======..");
  menusnd->addText(   "sound:       =======.");
  menusnd->addText(   "sound:       ========");
  menuaudio->addMenuItem(menusnd);

  menumusic = new MenuChoose(engine);
  menumusic->addText( "music:            off");
  menumusic->addText( "music:       =.......");
  menumusic->addText( "music:       ==......");
  menumusic->addText( "music:       ===.....");
  menumusic->addText( "music:       ====....");
  menumusic->addText( "music:       =====...");
  menumusic->addText( "music:       ======..");
  menumusic->addText( "music:       =======.");
  menumusic->addText( "music:       ========");
  menuaudio->addMenuItem(menumusic);

  MyMenuKey * menuleftflip = new MyMenuKey("leftflip", NULL, engine);
  menukey->addMenuItem(menuleftflip);
  MyMenuKey * menurightflip = new MyMenuKey("rightflip", NULL, engine);
  menukey->addMenuItem(menurightflip);
  MyMenuKey * menuleftnudge = new MyMenuKey("leftnudge", NULL, engine);
  menukey->addMenuItem(menuleftnudge);
  MyMenuKey * menurightnudge = new MyMenuKey("rightnudge", NULL, engine);
  menukey->addMenuItem(menurightnudge);
  MyMenuKey * menubottomnudge = new MyMenuKey("bottomnudge", NULL, engine);
  menukey->addMenuItem(menubottomnudge);
  MyMenuKey * menulaunch = new MyMenuKey("launch", NULL, engine);
  menukey->addMenuItem(menulaunch);
  MyMenuKey * menureset = new MyMenuKey("reset", NULL, engine);
  menukey->addMenuItem(menureset);

  MenuFct* menuapply = new MyMenuApply("apply", NULL, engine);
  menuaudio->addMenuItem(menuapply);
  //menucfg->addMenuItem(menuapply);
  menugfx->addMenuItem(menuapply);
  //menukey->addMenuItem(menuapply);

  MenuFct* menucancel = new MyMenuCancel("back", NULL, engine);
  menucfg->addMenuItem(menucancel);
  menugfx->addMenuItem(menucancel);
  menuaudio->addMenuItem(menucancel);
  menuload->addMenuItem(menucancel);
  menukey->addMenuItem(menucancel);

  get_config();
  return menu;
}

#endif //MENU_HPP