//#ident "$Id: ModuleProfessor.cpp,v 1.8 2003/07/16 20:02:04 rzr Exp $"
/***************************************************************************
                          Score.cpp  -  description
                             -------------------
    begin                : Fri Jan 26 2001
    copyright            : (C) 2001 by Henrik Enqvist
    email                : henqvist@excite.com
***************************************************************************/

#include "Private.h"
//#include "Keyboard.h"
#include "Config.h"
#include "Behavior.h"
#include "Group.h"
#include "Pinball.h"
#include "Loader.h"

#include "Table.h"
#include "Score.h"

class ProfessorBehavior : public Behavior {
public:
  ProfessorBehavior() : Behavior(){
    this->clear();
  };
  ~ProfessorBehavior(){};
  
  void onTick(){
    Table * table = Table::getInstance();
    Score * score = table->getScore();
    Loader * loader = Loader::getInstance();
    // init signals
    EmAssert(score != NULL, "ProfessorBehavior::onTick socre NULL");
    // launch ball
    string launch("launch");
    if (table->active() == 0 && 
        table->getCurrentBall() < MAX_BALL){
      switch (table->getCurrentBall()){
      case 0 :
        if (table->isBallDead(0) ){
          SignalSender::getInstance()->addSignal( loader->getSignal("game_start"), 0, this->getParent(), NULL );
          SignalSender::getInstance()->addSignal( PBL_SIG_BALL_ON, 0, this->getParent(), NULL );
          table->activateBall(0, 19.5f, 0.0f, 30.0f);   
          //score->clearText();
          break;
        }       
      case 1 :
        if (table->isBallDead(1)){
          SignalSender::getInstance()->addSignal( PBL_SIG_BALL_ON, 0, this->getParent(), NULL );
          table->activateBall(1, 19.5f, 0.0f, 30.0f);
          //score->clearText();
          break;
        }
      case 2 :
        if (table->isBallDead(2)){
          SignalSender::getInstance()->addSignal( PBL_SIG_BALL_ON, 0, this->getParent(), NULL );
          table->activateBall(2, 19.5f, 0.0f, 30.0f);
          //score->clearText();
          break;
        }
        if (table->isBallDead(0)){
          SignalSender::getInstance()->addSignal( PBL_SIG_BALL_ON, 0, this->getParent(), NULL );
          table->activateBall(0, 19.5f, 0.0f, 30.0f);   
          //score->clearText();
          break;
        }       
        if (table->isBallDead(1)){
          SignalSender::getInstance()->addSignal( PBL_SIG_BALL_ON, 0, this->getParent(), NULL );
          table->activateBall(1, 19.5f, 0.0f, 30.0f);
          //score->clearText();
          break;
        }
      default:
        throw string("all balls busy");
      }
      EM_COUT("Table::onTick() new ball", 1);
    }
  };
  
  void onCollision(const Vertex3D& em_vtx, const Vertex3D& em_vtxOwn, Group* em_group){};
  
  void onSignal(int em_signal, Group* em_group){
    //EM_COUT((int)em_signal, 1);
    Table * table = Table::getInstance();
    Score * score = table->getScore();
    Loader * loader = Loader::getInstance();

    if(em_signal ==  PBL_SIG_RESET_ALL ){
      this->clear();
    } 
    // ball dead
    else if(em_signal ==  PBL_SIG_BALL_OFF ){
      if (table->active() == 1){
        SignalSender::getInstance()->addSignal( loader->getSignal("multiball_off"), 0, this->getParent(), NULL );
      }
      if (table->active() == 0){
        SignalSender::getInstance()->addSignal( loader->getSignal("allballs_off"), 0, this->getParent(), NULL );
        if (table->getCurrentBall() < MAX_BALL){
          table->setCurrentBall(table->getCurrentBall()+1);
          if (table->getCurrentBall() == MAX_BALL){
            SignalSender::getInstance()->addSignal( PBL_SIG_GAME_OVER, 0, this->getParent(), NULL );
            EM_COUT("game over", 1);
          }
        }
      }
    }
    else if(em_signal == loader->getSignal("bump")){
      score->addScore(450);
    } 
  }
  
  void clear(){
  };
  
private:
  
};

extern "C"  void * new_object_fct(void){
  return new ProfessorBehavior();
}

