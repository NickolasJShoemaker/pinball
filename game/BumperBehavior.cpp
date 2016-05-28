/***************************************************************************
                          BumperBehavopr.cpp  -  description
                             -------------------
    begin                : Thu Mar 9 2000
    copyright            : (C) 2000 by 
    email                : 
***************************************************************************/

#include "Private.h"
#include "BumperBehavior.h"

#include "Group.h"
#include "Pinball.h"
#include "Polygon.h"
#include "Shape3D.h"
#include "SoundUtil.h"
#include "Loader.h"

#include "SignalSender.h"

// these values are pure guesses
Vertex3D g_vtxArmTable[] = { 
    {0.07f, 0.0f, -0.07f},
    {0.09f, 0.0f, -0.18},
    {0.1f, 0.0f, -0.33},
    {0.07f, 0.0f, -0.45f},
    {0.0f, 0.0f, -0.5f},
    {-0.11f, 0.0f, -0.5f},
    {-0.15f, 0.0f, -0.3f},
    {-0.14f, 0.0f, -0.14f} };

BumperBehavior::BumperBehavior() : Behavior(){
  m_fPower = 0.5f;
  m_bTilt = false;
  m_iLightCounter = -1;
  m_iSound = -1;
  m_sigBump = Loader::getInstance()->getSignal("bump");
  this->setType(PBL_TYPE_BUMPERBEH);
}

void BumperBehavior::onTick(){
  if (m_iLightCounter > -1) m_iLightCounter--;
  if (m_iLightCounter == 0 ) if(this->getLight() != NULL) this->getLight()->setOn(false);
}

void BumperBehavior::onSignal(int em_signal, Group* em_group){
  if(em_signal == PBL_SIG_RESET_ALL){
    m_bTilt = false;
    if(this->getLight() != NULL) this->getLight()->setOn(false);
    m_iLightCounter = -1;
  }
  else if(em_signal == PBL_SIG_TILT){
    m_bTilt = true;
  }
}

void BumperBehavior::onCollision(const Vertex3D& em_vtx, const Vertex3D& em_vtxOwn, Group* em_group){
  EM_COUT("BumperBehavior::onCollision(const Vertex3D& em_vtx, const Vertex3D& em_vtxOwn, Group* em_group)", 0);

  if (m_bTilt) return;

  if(em_group != NULL && (em_group->getUserProperties() & PBL_BALL)){
    if (m_iLightCounter > 10){
      return;
    }
    m_iLightCounter = 20;
    if(this->getLight() != NULL) this->getLight()->setOn(true);
    SignalSender::getInstance()->addSignal(m_sigBump, 0, this->getParent(), NULL);
    SoundUtil::getInstance()->playSample(m_iSound, false);
  }
}
