/***************************************************************************
                          KeyRorBehavior.h  -  description
                             -------------------
    begin                : Wed Jan 26 2000
    copyright            : (C) 2000 by Henrik Enqvist
    email                : henqvist@excite.com
 ***************************************************************************/

#ifndef KEYROTBEHAVIOR_HPP
#define KEYROTBEHAVIOR_HPP

#include "Behavior.h"

#include "Private.h"
#include "Group.h"
#include "Keyboard.h"

/** A Behavior that lets the users rotate the group with UP, DOWN
 * LEFT, RIGHT, PGUP, PGDOWN keys.Simply add a KeyRotationBehavior
 * object to a group to be able to rotate it. */
class KeyRotBehavior : public Behavior{
public:
	//KeyRotBehavior(): Behavior() = default;
	KeyRotBehavior() = default;
	~KeyRotBehavior() = default;
	virtual void onCollision(const Vertex3D&, const Vertex3D&, Group*){};
	virtual void onSignal(int, Group*){};
	void onTick(){
		EmAssert(this->getParent() != NULL, "KeyRotBehavior::onTick parent NULL");
		float x = 0, y = 0, z = 0;
		if (Keyboard::isKeyDown(SDLK_RIGHT)) y = 0.01f;	
		if (Keyboard::isKeyDown(SDLK_LEFT)) y = -0.01f;
		if (Keyboard::isKeyDown(SDLK_UP)) x = 0.01f;
		if (Keyboard::isKeyDown(SDLK_DOWN)) x = -0.01f;
		if (Keyboard::isKeyDown(SDLK_PAGEUP)) z = 0.01f;
		if (Keyboard::isKeyDown(SDLK_PAGEDOWN)) z = -0.01f;
		this->getParent()->addRotation(x, y, z);
	}
};

#endif // KEYROTBEHAVIOR_HPP
