/***************************************************************************
                          Light.hpp  -  description
                             -------------------
    begin                : Sun Jan 30 2000
    copyright            : (C) 2000 by 
    email                : 
 ***************************************************************************/

#ifndef LIGHT_HPP
#define LIGHT_HPP

constexpr int EM_IGNORE_ANGLE_HALF = 1;
constexpr int EM_IGNORE_ANGLE_FULL = 2;
constexpr int EM_IGNORE_DISTANCE = 4;
constexpr int EM_USE_BOUNDS = 8;
constexpr int EM_USE_SPECULAR = 16;
constexpr int EM_USE_DIFFUSE = 32;

class Group;

#include <cstdlib>

#include "Private.h"
#include "Node.h"
/** Example:
 * <pre>
 * Group* groupL = new group;
 * Light* l = new Light(1.0, 10.0);
 * 
 * groupL->setLight(l);
 * engine->add(groupL);
 * 
 * engine->addLight(l);
 * </pre> */
class Light {
  friend class AmbientLightVisitor;
  friend class TransformVisitor;
  friend class Group;
  
  Group * p_Parent;
  float m_fConstant;
  float m_fLinear;
  float m_fQuadratic;
  float m_fR, m_fG, m_fB;
  float m_fBounds;
  bool m_bOn;
  int m_iProperties;

  void setParent(Group * p){
    p_Parent = p;
  };
public:
  Vertex3D m_vtxSrc;
  Vertex3D m_vtxTrans;
  Vertex3D m_vtxAlign;
  
  /** Light(constant, linear, quadratic, r, g, b). */
  Light(float c, float l, float q, float r=1.0, float g=1.0, float b=1.0){
    m_bOn = true;
    p_Parent = NULL;
    m_fConstant = EM_MAX(c, 0.0);
    m_fLinear = EM_MAX(l, 0.0);
    m_fQuadratic = EM_MAX(q, 0.0);
    m_fBounds = 1.0;
    m_iProperties = EM_USE_DIFFUSE + EM_USE_SPECULAR;
    m_fR = EM_MAX(EM_MIN(1.0, r), 0.0);
    m_fG = EM_MAX(EM_MIN(1.0, g), 0.0);
    m_fB = EM_MAX(EM_MIN(1.0, b), 0.0);
    m_vtxSrc.x = 0;
    m_vtxSrc.y = 0;
    m_vtxSrc.z = 0;
  };
  ~Light() = default;
  void setOn(bool on=true){ m_bOn = on;};
  bool getOn(){ return m_bOn;};
  // TODO fast clamp
  inline void setColor(float r, float g, float b){
    m_fR = EM_MAX(EM_MIN(1.0, r), 0.0);
    m_fG = EM_MAX(EM_MIN(1.0, g), 0.0);	
    m_fB = EM_MAX(EM_MIN(1.0, b), 0.0);	
  };
  void getColor(float & r, float & g, float & b){ r = m_fR; g = m_fG; b = m_fB; };
  void setProperty(int p){
    m_iProperties |= p;
  };
  void unsetProperty(int p){
    m_iProperties -= (m_iProperties & p);
  };
  void setBounds(float b){ m_fBounds = b; };
  void setIndex(int i);
  inline Group * getParent(){
    return p_Parent;
  };
};

#endif // LIGHT_HPP
