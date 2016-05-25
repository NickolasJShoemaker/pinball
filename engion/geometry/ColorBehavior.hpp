/***************************************************************************
                          ColorBehavior.h  -  description
                             -------------------
    begin                : Tue Feb 15 2000
    copyright            : (C) 2000 by Henrik Enqvist
    email                : henqvist@excite.com
 ***************************************************************************/

#ifndef COLORBEHAVIOR_HPP
#define COLORBEHAVIOR_HPP

#include "Behavior.h"
#include "EMath.h"


#include "Private.h"
#include "Group.h"
#include "Shape3D.h"

/** A simple behavior that changes the color of all polygons in the Shape3D
 * to blue and then when collision occurs all polygons are changed to red.
 * The collision example uses this to demonstrate when collision is
 * detected between two Shape3Ds. */
class ColorBehavior : public Behavior {
 public:
	ColorBehavior(): Behavior() = default;
	~ColorBehavior() = default;
	void onCollision(const Vertex3D & vtxWall, const Vertex3D & vtxOwn, Group* g){
		EmAssert(this->getParent() != NULL, "ColorBehavior::onCollision parent NULL");
		EM_COUT("ColorBehavior::onCollision()" << endl, 0);
		if (this->getParent() != NULL){
			for (int a=0; a<this->getParent()->getShape3DSize(); a++){
				this->getParent()->getShape3D(a)->setColor(1.0, 1.0, 0.0, 0.0);
			}
		}
	}
	void onTick(){
		EmAssert(this->getParent() != NULL, "ColorBehavior::onTick parent NULL");
		for (int a=0; a<this->getParent()->getShape3DSize(); a++){
			this->getParent()->getShape3D(a)->setColor(1.0, 0.0, 0.0, 1.0);
		}
	}

	void onSignal(int em_signal, Group* em_group);
};

#endif // COLORBEHAVIOR_HPP
