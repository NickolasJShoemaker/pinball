/***************************************************************************
                          Cone.h  -  description
                             -------------------
    begin                : Wed Jan 26 2000
    copyright            : (C) 2000 by Henrik Enqvist
    email                : henqvist@excite.com
 ***************************************************************************/

#ifndef CONE_HPP
#define CONE_HPP

#include "EMath.h"
#include "Shape3D.h"

#include "Private.h"
#include "Polygon.h"

/** A simple cone. @see Shape3D */
class Cone : public Shape3D {
 public:
	/** Cone(size, r, g, b, a). Color given by r, g, b and a. You must enable
	 * transparency to use the alpha color. */
	Cone(float fSize, int sides, float fR, float fG, float fB, float fA) : Shape3D(8+1, 8+1){
		if (sides < 3) sides = 3;
		Polygon3D* p;
		// Top vertex.
		this->add(0, fSize/2, 0);
		// Ring of vertices.
		for (float a=0; a<sides; ++a){
			this->add( EMath::emSin(a/sides)*fSize/2, -fSize/2 , EMath::emCos(a/sides)*fSize/2, fR, fG, fB, fA, 0.0f, 0.0f);
		}	
		// The ring of polygons.
		for (int a = 1; a < sides; ++a){
			p = new Polygon3D(this, 3);
			p->add(0);
			p->add(a+1);
			p->add(a);
			this->add(p);
		}
		// the last one
		p = new Polygon3D(this, 3);
		p->add(0);
		p->add(1);
		p->add(sides);
		this->add(p);
		// The bottom of the cone.
		p = new Polygon3D(this, sides);
		for (int a = 0; a < sides; ++a){
			p->add(a+1);
		}
		this->add(p);
		
		this->countNormals();
	}
};

#endif // CONE_HPP
