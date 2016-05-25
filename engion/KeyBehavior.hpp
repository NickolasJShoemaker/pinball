/***************************************************************************
                          KeyBehavior.h  -  description
                             -------------------
    begin                : Wed Jan 26 2000
    copyright            : (C) 2000 by Henrik Enqvist
    email                : henqvist@excite.com
 ***************************************************************************/

#ifndef KEYBEHAVIOR_HPP
#define KEYBEHAVIOR_HPP

#include "Behavior.h"

#include "Private.h"
#include "Group.h"
#include "Shape3D.h"
#include "Keyboard.h"

/** A Behavior that lets the users move the group with A, S, D, Q, W, E keys.
 * Simply add a KeyBehavior object to a group to be able to move it.  */
class KeyBehavior : public Behavior {
	float m_x, m_y, m_z;
public:
	KeyBehavior(): Behavior(){
		m_x = 0;
		m_y = 0;
		m_z = 0;
	}
	~KeyBehavior() = default;
	virtual void onCollision(const Vertex3D&, const Vertex3D&, Group*){};
	virtual void onSignal(int, Group*){};
	void onTick(){
		EmAssert(this->getParent() != NULL, "KeyBehavior::onTick parent NULL");
		m_x = this->getParent()->m_mtxSrc.t[0];
		m_y = this->getParent()->m_mtxSrc.t[1];
		m_z = this->getParent()->m_mtxSrc.t[2];
		if (Keyboard::isKeyDown(SDLK_a)) m_x -= 0.2;
		if (Keyboard::isKeyDown(SDLK_d)) m_x += 0.2;
		if (Keyboard::isKeyDown(SDLK_w)) m_z -= 0.2;
		if (Keyboard::isKeyDown(SDLK_s)) m_z += 0.2;
		if (Keyboard::isKeyDown(SDLK_q)) m_y -= 0.2;
		if (Keyboard::isKeyDown(SDLK_e)) m_y += 0.2;
		this->getParent()->setTranslation(m_x, m_y, m_z);
	}
};

#endif // KEYBEHAVIOR_HPP
