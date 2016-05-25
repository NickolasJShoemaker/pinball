/***************************************************************************
                          Animation.h  -  description
                             -------------------
    begin                : Wed Jan 26 2000
    copyright            : (C) 2000 by 
    email                : 
 ***************************************************************************/

#ifndef STDANIMATION_HPP
#define STDANIMATION_HPP

constexpr int EM_TYPE_STDANIMATION = 1001;

constexpr int EM_ROTATION        = 1;
constexpr int EM_TRANSLATION     = 2;
constexpr int EM_LIGHT           = 4;
constexpr int EM_BILLBOARD_SIZE  = 8;

#include <vector>

#include "EMath.h"
#include "Behavior.h"

#include "Private.h"
#include "Group.h"
#include "math.h"
#include "Light.hpp"
#include "BillBoard.h"

class Group;

/**
 * Animation moves or rotates a group according to a given path.
 *
 * Animation is represented as list of "x, y, z" points.
 * The x, y, z can be a translation or a rotation.
 * Each time the engines render method is called the animation
 * object will interpolate the group it is attached to, from one point
 * to an other. When the animation has reached its end it will
 * start over.
 * 
 * Usage.
 * Points are added to the animation with the 'add' method.
 * The order of the points will be same in which they are added
 * to the animation.
 *
 * Example:
 *  Group* group = new Group();
 *  StdAnimation anim = new StdAnimation(20, E_TRANSLATION);
 *  
 *  anim->add(0, 0, 0);
 *  anim->add(100, 0, 0);
 *  anim->add(0, 100, 0);
 *  anim->setEnd(0, 0, 0);
 *  
 *  group->addBehavior(anim);
 *
 * This example will create an animation which moves the group from origo to (100, 0 ,0) 
 * and then to (0, 100, 0) and back towards origo. Each movement will last for 20 engine 
 * ticks. When it reaches the end it will start over again.
 * @see Group
 */
class StdAnimation : public Behavior {
  vector<Vertex3D> m_vVertex;
  int m_iStep;
  int m_iTick;
  int m_iIndex;
  int m_iAnimType;
  Vertex3D m_vtxEnd;
public:
  /** Animation(step, type). */
  StdAnimation(int step, int type): Behavior(){
    this->setType(EM_TYPE_STDANIMATION);
    m_iAnimType = type;
    m_iStep = step;
    m_iTick = 0;
    m_iIndex = 0;
    m_vtxEnd.x = 0;
    m_vtxEnd.y = 0;
    m_vtxEnd.z = 0;
  };
  ~StdAnimation() = default;
  inline void setStep(int s){ m_iStep = s; };
  inline int getStep(){ return m_iStep; };
  inline void setAnimType(int t){ m_iAnimType = t; };
  inline void clear(){ m_vVertex.clear(); };
  void onSignal(int, Group*){};
  void onCollision(const Vertex3D&, const Vertex3D&, Group*){};
  void add(float x, float y, float z){
    Vertex3D vtx;
    vtx.x = x;
    vtx.y = y;
    vtx.z = z;
    m_vVertex.push_back(vtx);
  }
  void setEnd(float x, float y, float z){
    m_vtxEnd.x = x;
    m_vtxEnd.y = y;
    m_vtxEnd.z = z;
  }
  /** Sets the end point to the first point. */
  void setEndStart(){
    if(m_vVertex.size() == 0) return;
    m_vtxEnd.x = m_vVertex[0].x;
    m_vtxEnd.y = m_vVertex[0].y;
    m_vtxEnd.z = m_vVertex[0].z;
  }
  void onTick(){
    EmAssert(this->getParent() != NULL, "Parent not allowed to be null");
    
    float x, y, z;
    float sX, sY, sZ;
    float eX, eY, eZ;
    float k=0.0;
    int index;
    int size = m_vVertex.size();
    
    if(m_iTick >= size*m_iStep){
      m_iTick = 0;
    }
    
    index = (int)(m_iTick/m_iStep);
      
    sX = m_vVertex[index].x;
    sY = m_vVertex[index].y;
    sZ = m_vVertex[index].z;    
    
    if(index + 1 < size){
      eX = m_vVertex[index+1].x;
      eY = m_vVertex[index+1].y;
      eZ = m_vVertex[index+1].z;    
    }else{
      eX = m_vtxEnd.x;
      eY = m_vtxEnd.y;
      eZ = m_vtxEnd.z;    
    } 

    k = ((float)(m_iTick%m_iStep)/m_iStep);
    x = (float)(sX + (eX - sX)*k);
    y = (float)(sY + (eY - sY)*k);
    z = (float)(sZ + (eZ - sZ)*k);

    m_iTick++;

    if(m_iAnimType & EM_TRANSLATION){
      this->getParent()->setTranslation(x, y, z);
    }else if(m_iAnimType & EM_ROTATION){
      this->getParent()->setRotation(x, y, z);
    }else if(m_iAnimType & EM_LIGHT){
      Light* l = this->getParent()->getLight();
      if(l != NULL){
        l->setColor(x, y, z);
      }
    }else if(m_iAnimType & EM_BILLBOARD_SIZE){
      BillBoard * b = this->getParent()->getBillBoard();
      if(b != NULL){
        b->setSize(x, y);
        b->setZOffset(z);
      }
    }
  }
};

#endif // ANIMATION_HPP
