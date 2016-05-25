/***************************************************************************
                          BumperBehavior.h  -  description
                             -------------------
    begin                : Thu Mar 9 2000
    copyright            : (C) 2000 by 
    email                : 
 ***************************************************************************/

#ifndef BUMPERBEHAVIOR_E
#define BUMPERBEHAVIOR_E

#include "Behavior.h"
#include "EMath.h"
#include "Light.h"


/** A behavior for the pinball game. */
class BumperBehavior : public Behavior {
 public:
  BumperBehavior();
  ~BumperBehavior() = default;
  void onTick();
  void onSignal(int em_signal, Group* em_group);
  void onCollision(const Vertex3D& em_vtx, const Vertex3D& em_vtxOwn, Group* em_group);
  inline void setPower(float p){ m_fPower = p; };
  inline float getPower(){ return m_fPower; };
  inline void setSound(int s){ m_iSound = s; };
  inline int getSound(){ return m_iSound; };
 private:
  int m_sigBump;
  int m_iLightCounter;
  int m_iSound;
  float m_fPower;
  bool m_bTilt;
};

#endif // BounceBehavior
