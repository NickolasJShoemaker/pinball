/***************************************************************************
                          ArmBehavior.h  -  description
                             -------------------
    begin                : Wed Jan 26 2000
    copyright            : (C) 2000 by 
    email                : 
 ***************************************************************************/

#ifndef ARMBEHAVIOR_HPP
#define ARMBEHAVIOR_HPP

#include <string>

#include "Behavior.h"

#include "EMath.h"
#include "Keyboard.h"

#include "Private.h"
#include "ArmBehavior.h"
#include "Group.h"
#include "Shape3D.h"
#include "Pinball.h"
#include "Keyboard.h"
#include "SoundUtil.h"
#include "Config.h"

/** A Behavior for the pinball demo. */
class ArmBehavior : public Behavior {
    Vertex3D m_vtxRot;
    bool m_bRight;
    int m_iCount;
    bool m_bOn;
    int m_iSound;
    bool m_bFirst;
    bool m_bTilt;
    
public:
    ArmBehavior(bool right = true) : Behavior(){
        m_bTilt = false;
        m_bRight = right;
        m_iCount = 0;
        m_bOn = false;
        m_iSound = -1;
        m_bFirst = true;
        this->setType(PBL_TYPE_ARMBEH);
    }
    ~ArmBehavior(){};

    inline void setSound(int s){ m_iSound = s; };
    inline int getSound(){ return m_iSound; };
    inline void setIsRight(bool r){ m_bRight = r; };
    inline bool getIsRight(){ return m_bRight; };

    void onCollision(const Vertex3D&, const Vertex3D&, Group*){};
    void onSignal(int em_signal, Group* em_group){
        if(em_signal == PBL_SIG_RESET_ALL){
            m_bTilt = false;
            m_iCount = 0;
            this->getParent()->setUserProperty(PBL_UNACTIVE_ARM);
            this->getParent()->unsetUserProperty(PBL_ACTIVE_ARM);
            this->getParent()->setRotation(0.0f, m_vtxRot.y, 0.0f);
            m_bOn = false;
        }
        else if(em_signal == PBL_SIG_TILT){
           m_bTilt = true;
        }
    }

    void onTick(){
        EM_COUT("ArmBehavior::onTick", 0);
        EmAssert(this->getParent() != NULL, "ArmBehavior::onTick");
        // get translation on first tick
        if(m_bFirst){
            this->getParent()->getRotation(m_vtxRot.x, m_vtxRot.y, m_vtxRot.z);
            m_bFirst = false;
        }

        if(m_bRight){
            string leftflip("rightflip");
            this->doArm(Config::getInstance()->getKey(leftflip));
            this->getParent()->setRotation(0.0f, m_vtxRot.y + 0.01f*m_iCount, 0.0f);
        }else{
            string rightflip("leftflip");
            this->doArm(Config::getInstance()->getKey(rightflip));
            this->getParent()->setRotation(0.0f, m_vtxRot.y - 0.01f*m_iCount, 0.0f);
        }
    }   
    void doArm(EMKey key){
        if(Keyboard::isKeyDown(key) && !m_bTilt){
            if(m_iCount < 10){
                m_iCount++;
                this->getParent()->setUserProperty(PBL_ACTIVE_ARM);
                this->getParent()->unsetUserProperty(PBL_UNACTIVE_ARM);
                if(m_iCount == 2){
                    if(m_bRight){
                      SignalSender::getInstance()->addSignal(PBL_SIG_RIGHTARM_ON, 0, this->getParent(), NULL);
                    }else{
                      SignalSender::getInstance()->addSignal(PBL_SIG_LEFTARM_ON, 0, this->getParent(), NULL);
                    }
                    SoundUtil::getInstance()->playSample(m_iSound, false);
                }
            }else{
                this->getParent()->setUserProperty(PBL_UNACTIVE_ARM);
                this->getParent()->unsetUserProperty(PBL_ACTIVE_ARM);
            }
        }else{
            this->getParent()->setUserProperty(PBL_UNACTIVE_ARM);
            this->getParent()->unsetUserProperty(PBL_ACTIVE_ARM);
            if(m_iCount > 0) m_iCount--;
        }
    }
};

#endif // ARMBEHAVIOR_HPP
