/***************************************************************************
                          BigSphere.cpp  -  description
                             -------------------
    begin                : Wed Jan 26 2000
    copyright            : (C) 2000 by Henrik Enqvist
    email                : henqvist@excite.com
***************************************************************************/
#ifndef BIGSPHERE_HPP
#define BIGSPHERE_HPP

#include "Shape3D.h"

#include "Private.h"
#include "Polygon.h"

inline Vertex3D median(Vertex3D v1, Vertex3D v2){
  Vertex3D vo;
  vo.x = v1.x + (v2.x - v1.x)/2;
  vo.y = v1.y + (v2.y - v1.y)/2;
  vo.z = v1.z + (v2.z - v1.z)/2;
  return vo;
}

class BigSphere : public Shape3D {
public:
  BigSphere(float fSize, int level, float fR, float fG, float fB, float fA) : Shape3D(1, 1){

    //create a cube mapping
    this->add(0, -1*fSize, 0, fR, fG, fB, fA, 0.0f, 0.0f); // top vertex
    this->add(-EM_SIN_45*fSize, 0, EM_SIN_45*fSize, fR, fG, fB, fA, 0.0f, 0.0f);  // front left
    this->add(EM_SIN_45*fSize, 0, EM_SIN_45*fSize, fR, fG, fB, fA, 0.0f, 0.0f);   // front right
    this->add(EM_SIN_45*fSize, 0, -EM_SIN_45*fSize, fR, fG, fB, fA, 0.0f, 0.0f);  // back left
    this->add(-EM_SIN_45*fSize, 0, -EM_SIN_45*fSize, fR, fG, fB, fA, 0.0f, 0.0f); // back right
    this->add(0, 1*fSize, 0, fR, fG, fB, fA, 0.0f, 0.0f); // bottom vertex

    // TODO: Check if this causes a memory leak!!!
    // push back first eight triangles
    vector<int> triangles = { 0, 1, 2,
                              0, 2, 3,
                              0, 3, 4,
                              0, 4, 1,
                              5, 2, 1,
                              5, 3, 2,
                              5, 4, 3,
                              5, 1, 4 };

    int start = 0;
    int end = triangles.size();

    // split each triangle into three triangles
    while (level-- > 0){
      for (int a = start; a < end; a += 3){
        int A = triangles[a];
        int B = triangles[a+1];
        int C = triangles[a+2];
        Vertex3D vtxA = *(this->getVertex3D(triangles[a]));
        Vertex3D vtxB = *(this->getVertex3D(triangles[a+1]));
        Vertex3D vtxC = *(this->getVertex3D(triangles[a+2]));
        
        // new vertices
        Vertex3D vtxD = median(vtxA, vtxB); 
        Vertex3D vtxE = median(vtxB, vtxC); 
        Vertex3D vtxF = median(vtxC, vtxA);
        
        // move vertices out to the sphere surface
        EMath::normalizeVector(vtxD);
        EMath::normalizeVector(vtxE);
        EMath::normalizeVector(vtxF);
        EMath::scaleVector(vtxD, fSize);
        EMath::scaleVector(vtxE, fSize);
        EMath::scaleVector(vtxF, fSize);
        
        EM_COUT("BigSphere::BigSphere() vtxA " << vtxA.x <<" "<< vtxA.y <<" "<< vtxA.z, 0);
        EM_COUT("BigSphere::BigSphere() vtxB " << vtxB.x <<" "<< vtxB.y <<" "<< vtxB.z, 0);
        EM_COUT("BigSphere::BigSphere() vtxC " << vtxC.x <<" "<< vtxC.y <<" "<< vtxC.z, 0);
        
        EM_COUT("BigSphere::BigSphere() vtxD " << vtxD.x <<" "<< vtxD.y <<" "<< vtxD.z, 0);
        EM_COUT("BigSphere::BigSphere() vtxE " << vtxE.x <<" "<< vtxE.y <<" "<< vtxE.z, 0);
        EM_COUT("BigSphere::BigSphere() vtxF " << vtxF.x <<" "<< vtxF.y <<" "<< vtxF.z, 0);
        
        int D, E, F;
        if ((D = this->find(vtxD.x, vtxD.y, vtxD.z, 0.001)) == -1){
          D = this->add(vtxD.x, vtxD.y, vtxD.z, fR, fG, fB, fA, 0.0f, 0.0f);
        }
        if ((E = this->find(vtxE.x, vtxE.y, vtxE.z, 0.001)) == -1){
          E = this->add(vtxE.x, vtxE.y, vtxE.z, fR, fG, fB, fA, 0.0f, 0.0f);
        }
        if ((F = this->find(vtxF.x, vtxF.y, vtxF.z, 0.001)) == -1){
          F = this->add(vtxF.x, vtxF.y, vtxF.z, fR, fG, fB, fA, 0.0f, 0.0f);
        }
        
        // push back four new triangles
        triangles.push_back(A);
        triangles.push_back(D);
        triangles.push_back(F);
        
        triangles.push_back(D);
        triangles.push_back(B);
        triangles.push_back(E);
        
        triangles.push_back(F);
        triangles.push_back(E);
        triangles.push_back(C);
        
        triangles.push_back(D);
        triangles.push_back(E);
        triangles.push_back(F);
      }
      // discard the old triangles
      start = end;
      end = triangles.size();
    }

    // add the triangles to the shape
    for (int a = start; a < end; a +=  3){
      Polygon3D * p;
      p = new Polygon3D(this, 3);
      p->add(triangles[a]);
      p->add(triangles[a+1]);
      p->add(triangles[a+2]);
      if (fA < 0.95f){
        p->setProperty(EM_POLY_TRANS);
      }
      this->add(p);
    }
    if (fA < 0.95f){
      this->setProperty(EM_SHAPE3D_USE_TRANS);
    }

    this->countNormals();
  }
};

#endif //BIGSPHERE_HPP