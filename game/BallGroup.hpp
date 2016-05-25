/***************************************************************************
                          BallGroup.hpp  -  description
                             -------------------
    begin                : Sat Mar 8 2003
    copyright            : (C) 2000 by Henrik Enqvist
    email                : henqvist@excite.com
 ***************************************************************************/

#ifndef BALLGROUP_HPP
#define BALLGROUP_HPP

#include <cstdlib>

#include "Private.h"
#include "Pinball.h"
#include "Polygon.h"
#include "CollisionBounds.h"
#include "Config.h"

#include "Group.h"
#include "EMath.h"

#include "BounceBehavior.h"
#include "BigSphere.hpp"

#include "Engine.h"
#include "Shape3D.h"

class BounceBehavior;

//class Engine;
//class Group;
//class Shape3D;

/** */
class BallGroup : public Group {
    int m_iBall;
    int m_iFireTimer;
    Vertex3D vtxPrev;
    Group * aFire[8];
    Shape3D * aFireShape[8];
    Vertex3D aFireVtx[16];

public:
    BallGroup(float r, float g, float b, int pbl) : Group(){
        m_iBall = pbl;
        Shape3D* ballSphere = new BigSphere(1, 4, r, g, b, 1);
        ballSphere->setProperty(EM_SHAPE3D_SPECULAR);
        CollisionBounds* ballBounds = new CollisionBounds(1.0f/EM_SQRT_3);

        // create a transparent black polygon in the bottom of the ball - a shadow
        Shape3D* shadow = new Shape3D(8, 1);

        shadow->add(0, -1, 1, 0.0f, 0.0f, 0.0f, 0.5f,  0.0f, 0.0f);
        shadow->add(-0.707,-1, 0.707, 0.0f, 0.0f, 0.0f, 0.5f,  0.0f, 0.0f);
        shadow->add(-1, -1, 0, 0.0f, 0.0f, 0.0f, 0.5f,  0.0f, 0.0f);
        shadow->add(-0.707,-1, -0.707, 0.0f, 0.0f, 0.0f, 0.5f,  0.0f, 0.0f);
        shadow->add(0, -1, -1, 0.0f, 0.0f, 0.0f, 0.5f,  0.0f, 0.0f);
        shadow->add(0.707, -1, -0.707, 0.0f, 0.0f, 0.0f, 0.5f,  0.0f, 0.0f);
        shadow->add(1, -1, 0, 0.0f, 0.0f, 0.0f, 0.5f,  0.0f, 0.0f);
        shadow->add(0.707, -1, 0.707, 0.0f, 0.0f, 0.0f, 0.5f,  0.0f, 0.0f);

        Polygon3D * poly = new Polygon3D(shadow, 3);
        poly->add(0);
        poly->add(1);
        poly->add(2);
        poly->add(3);
        poly->add(4);
        poly->add(5);
        poly->add(6);
        poly->add(7);
        poly->setProperty(EM_POLY_TRANS);
        shadow->add(poly);
        shadow->setProperty(EM_SHAPE3D_USE_TRANS);
        shadow->countNormals();

        BounceBehavior* bouBeh = new BounceBehavior(pbl); //!rzr MLK
        if (Config::getInstance()->getFire()){
            bouBeh->setFire(true);
        }else{
            bouBeh->setFire(false);
        }

        this->setUserProperty(PBL_BALL);
        this->setCollisionGroup(9000+pbl);
        this->setCollisionBounds(ballBounds);
        this->addShape3D(ballSphere);
        this->addShape3D(shadow);
        this->setBehavior(bouBeh);

        this->setTransform(-4*pbl, 0, 40, 0, 0, 0);
        vtxPrev.x = -4*pbl;
        vtxPrev.y = 0;
        vtxPrev.z = 40;

        for (int a=0; a<16; ++a){
            aFireVtx[a].x = 0;
            aFireVtx[a].y = 0;
            aFireVtx[a].z = 0;
        }

        for (int a=0; a<8; ++a){
            aFire[a] = new Group();
            aFireShape[a] = new BigSphere(1.2f - (float)a/10.0f, 1, 1, 1, 0, 0.3);
            aFireShape[a]->setProperty(EM_SHAPE3D_ALWAYSLIT | EM_SHAPE3D_HIDDEN);
            aFire[a]->addShape3D(aFireShape[a]);
            this->add(aFire[a]);
        }

        m_iFireTimer = 0;
    }
    ~BallGroup() = default;


    /** -1 always, 0 off, >1 timer */
    inline void setFireTimer(int timer){ m_iFireTimer = timer; };
    inline int getBall(){ return m_iBall; };
    void updateFire(){
  
        for (int a=14; a>=0; --a){
            aFireVtx[a+1].x = aFireVtx[a].x;
            aFireVtx[a+1].y = aFireVtx[a].y;
            aFireVtx[a+1].z = aFireVtx[a].z;
        }

        Vertex3D vtx;
        vtx.x = 0;
        vtx.y = 0;
        vtx.z = 0;
        for (int a=0; a<16; ++a){
            vtx.x += aFireVtx[a].x;
            vtx.y += aFireVtx[a].y;
            vtx.z += aFireVtx[a].z;
            if (a%2 == 1){
              aFire[a/2]->setTranslation(vtx);
              float g = (float)random()/RAND_MAX;
              float r = (float)random()/RAND_MAX + g;
              aFire[a/2]->getShape3D(0)->setColor(r, g, 0, .3);
            }
        }

        this->getTranslation(vtx);
        aFireVtx[0].x = vtxPrev.x - vtx.x;
        aFireVtx[0].y = vtxPrev.y - vtx.y;
        aFireVtx[0].z = vtxPrev.z - vtx.z;
    }
    void resetFire(){
        m_iFireTimer = 0;
        for (int a=0; a<16; ++a){
            aFireVtx[a].x = 0.0f;
            aFireVtx[a].y = 0.0f;
            aFireVtx[a].z = 0.0f;
        }
        for (int as=0; as<8; ++as){
            aFireShape[as]->setProperty(EM_SHAPE3D_HIDDEN);
        }
    }
    void tick(){
        // a fast but unsafe check
        if (!Config::getInstance()->getFire()) return;
        if (m_iFireTimer == 0){
            this->resetFire();
        }else{
            for (int a=0; a<8; ++a){
                aFireShape[a]->unsetProperty(EM_SHAPE3D_HIDDEN);
            }
        if (m_iFireTimer != 0){
            this->updateFire();
            if (m_iFireTimer > 0){
                --m_iFireTimer;
            }
        }
        }
        this->getTranslation(vtxPrev);
    }
};

#endif // BALLGROUP_HPP
