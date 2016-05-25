/***************************************************************************
                          BounceBehavior.hpp  -  description
                             -------------------
    begin                : Thu Mar 9 2000
    copyright            : (C) 2000 by 
    email                : 
 ***************************************************************************/

#ifndef BOUNCEBEHAVIOR_H
#define BOUNCEBEHAVIOR_H

#include <string>

#if EM_DEBUG
    #include <iomanip>
#endif

#include "Behavior.h"
#include "EMath.h"


#include "Private.h"
#include "Group.h"
#include "Pinball.h"
#include "Keyboard.h"
#include "StateBehavior.h"
#include "PlungerBehavior.h"
#include "BumperBehavior.h"
#include "Score.h"
#include "Loader.h"

#include "ArmBehavior.hpp"

constexpr float MAX_SPEED = 0.5f;
constexpr float FIRE_SPEED = 0.4f;
constexpr float MAX_SPEED_Y_DOWN = (MAX_SPEED*0.5f);
constexpr float SPEED_FCT = 0.6f;
constexpr float Y_GRAVITY = -(SPEED_FCT*0.005f); // -SPEED_FCT/200
constexpr float Z_GRAVITY = (SPEED_FCT*0.002f); //  SPEED_FCT/500
constexpr float BORDER = (SPEED_FCT*0.05f);
constexpr float BORDER2 = (SPEED_FCT*0.02f);

constexpr int ARM_TABLE_SIZE = 8; // do not use less than 3
constexpr float ARM_WIDTH = 6.1f;

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

/** A behavior for the pinball demo. */
class BounceBehavior : public Behavior {
    bool m_bAlive;
    int m_iBall;
    Vertex3D m_vtxDir;
    Vertex3D m_vtxOldDir;
    int m_iDirFactor;
    int m_iCollisionPrio;
    bool m_bFire;
    bool m_bStopped; 

    void checkSpeed();
public:
    BounceBehavior(int ball);
    ~BounceBehavior() = default;

    inline bool isAlive(){ return m_bAlive; };
    inline void setFire(bool f){ m_bFire = f; };

    void onTick();
    void onSignal(int em_signal, Group* em_group);

    /* The current direction is need by behaviors objects of other balls.
    * The upcomming direction may change, therefore we need to give the old direction. */
    void getDirection(Vertex3D& vtx);

    /** drops the ball at x,y,z */
    void activateBall(float x, float y, float z);
    void onCollision(const Vertex3D& vtxW, const Vertex3D& vtxOwn, Group* pGroup);
};

#endif // BOUNCEBEHAVIOR_H
