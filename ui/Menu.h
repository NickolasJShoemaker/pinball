/***************************************************************************
                          Menu.h  -  description
                             -------------------
    begin                : Tue Feb 15 2000
    copyright            : (C) 2000 by Henrik Enqvist
    email                : henqvist@excite.com
 ***************************************************************************/

#ifndef MENU_H
#define MENU_H

#include <vector>

#include "TextureUtil.h"

class Engine;
class EmFont;

constexpr int EM_MENU_NOP         = 0;
constexpr int EM_MENU_EXIT        = 1;
constexpr int EM_MENU_RESUME      = 2;
constexpr int EM_MENU_BACK        = 3;

constexpr int EM_MENU             = 0;
constexpr int EM_MENU_SUB         = 1;
constexpr int EM_MENU_CHOOSE      = 2;
constexpr int EM_MENU_INPUT       = 3;
constexpr int EM_MENU_FCT         = 4;

constexpr int MAX_MENU_NAME       = 63;

/** The base class for all menus. */
class MenuItem{
protected:
  EmTexture* p_Texture;
  EmFont* p_EmFont;
  Engine* p_Engine;
  int m_iType;

public:
  MenuItem(Engine* e, int type);
  virtual ~MenuItem() = default;
  virtual const char* getText() = 0;
  virtual int perform() = 0;

  inline int getType(){ return m_iType; };
  inline Engine* getEngine(){ return p_Engine; };
  inline void setBackground(EmTexture* tex){ p_Texture = tex; };
};

/** A meny holding sub menus, can also be used for a back or exit item */
class MenuSub : public MenuItem{
protected:
  char m_Name[MAX_MENU_NAME + 1];
  int m_iCurrent;
  int m_iAction;
  vector<MenuItem*> m_vMenuItem;
  vector<char*> m_vInfoText;
  char m_BottomText[MAX_MENU_NAME + 1];
public:
  MenuSub(const char* name, Engine* e);
  ~MenuSub() = default;
  /** Gives the number of submenus */
  inline int size(){ return m_vMenuItem.size(); };
  inline void setAction(int a){ m_iAction = a; };
  inline const char* getText(){ return m_Name; };
  /** Add a text which is to appear under the name when the item is selected. TODO */
  void addInfoText(const char * text);
  /** Add a text which is to appear under the name when the item is selected */
  void setBottomText(const char * text);
  void addMenuItem(MenuItem* m);
  int perform();
  void draw();
};

class MenuChoose : public MenuItem{
protected:
  int m_iCurrent;
  /** Previous is the currently active alternative in the engine. */
  int m_iPrevious;
  vector<char*> m_vText;
  char t_Str[MAX_MENU_NAME + 1];
public:
  MenuChoose(Engine* e);
  ~MenuChoose() = default;
  void addText(const char * text);
  const char* getText();
  int perform();
  int next();
  int prev();
  
  inline int getCurrent(){ return m_iCurrent; }
  
  inline void setCurrent(int c){
    if ( c < m_vText.size() ){ m_iCurrent = c; m_iPrevious = c; }
  }
};


/***************************************************************************
 * A menu that performs a function when choosen */

constexpr int MAX_INPUT_STRING     = 12;

class MenuInput : public MenuItem{
protected:
  int m_iAction;
  char m_Name[MAX_MENU_NAME + 1];
  char m_Input[MAX_INPUT_STRING + 1];
public:
	MenuInput(const char* name, Engine* e);
	~MenuInput() = default;
	inline const char* getText(){ return m_Name; };
  inline void setAction(int a){ m_iAction = a; };
	const char* getInput();
  int perform();
  void draw();
};

/** You can create a MenuFct instance and pass i a function
 * or you can subclass it and override the 'perform' fucntion. 
 * The perform function should return EM_MENU_BACK, EM_MENU_NOP or EM_MENU_QUIT. */
class MenuFct : public MenuItem{
protected:
  char m_Name[MAX_MENU_NAME + 1];
  int (*p_Fct)(void);
public:
  MenuFct(const char* name, int (*fct)(void), Engine* e);
  ~MenuFct() = default;
  virtual const char* getText(){ return m_Name; };
  int perform();
};

#endif // MENU_H
