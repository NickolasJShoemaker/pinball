/***************************************************************************
                          EyeBehavior.h  -  description
                             -------------------
    begin                : Wed Jan 26 2000
    copyright            : (C) 2000 by Henrik Enqvist
    email                : henqvist@excite.com
 ***************************************************************************/

#ifndef EYEBEHAVIOR_H
#define EYEBEHAVIOR_H

#include "Behavior.h"


// locked view
constexpr float TX0 = -1.75f;
constexpr float TY0 = 40.0f;
constexpr float TZ0 = 40.0f;
constexpr float RX0 = 0.15f;
constexpr float RY0 = 0.0f;
constexpr float RZ0 = 0.0f;

// soft pan & scan view
constexpr float TX1 = -1.75f;
constexpr float TY1 = 35.0f;
constexpr float TZ1 = 37.0f;
constexpr float RX1 = 0.14f;
constexpr float RY1 = 0.0f;
constexpr float RZ1 = 0.0f;

// moving pan & scan view
constexpr float TX2 = -1.75f;
constexpr float TY2 = 32.0f;
constexpr float TZ2 = 34.0f;
constexpr float RX2 = 0.14f;
constexpr float RY2 = 0.0f;
constexpr float RZ2 = 0.0f;

// top view
constexpr float TX3 = -1.75f;
constexpr float TY3 = 40.0f;
constexpr float TZ3 = 10.0f;
constexpr float RX3 = 0.23f;
constexpr float RY3 = 0.0f;
constexpr float RZ3 = 0.0f;

class Score;

/**
 * <p>A Behavior for the pinball demo.</p>
 */
class EyeBehavior : public Behavior {
 public:
  EyeBehavior();
  ~EyeBehavior() = default;
  void onTick();
  void onSignal(int em_signal, Group* em_group);
  void onCollision(const Vertex3D& em_vtx, const Vertex3D& em_vtxOwn, Group* em_group){ EmAssert(false, "EyeBehavior::onCollision(const Vertex3D& em_vtx, const Vertex3D& em_vtxOwn, Group* em_group) not implemented"); };
  inline void setSound(int s){ m_iSound = s; };
 private:
  int m_iNudgeTick;
  int m_iNudgeType;
  int m_iTiltTick;
  float m_fXNudge;
  float m_fZNudge;
  int m_iSound;
  bool m_bTilt;
  bool m_bFButton;
};

#endif // EYEBEHAVIOR_H
