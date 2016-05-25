/***************************************************************************
                          AllegroVisitor.h  -  description
                             -------------------
    begin                : Fri Jun 7 2002
    copyright            : (C) 2002 by Henrik Enqvist IB (GPL)
    email                : henqvist@excite.com
 ***************************************************************************/


#ifndef ALLEGROVISITOR_H
#define ALLEGROVISITOR_H

#ifndef PRIVATE_H
	#error Must include Private.h before AllegroVisitor.h
#endif

#include "Visitor.h"

#define EM_ALLEGRO_GCOL_TEX        0 
#define EM_ALLEGRO_GCOL_TEX_TRANS  2
#define EM_ALLEGRO_CLEAN           4

class Group;
class Shape3D;

#if EM_DEBUG
extern int em_poly;
extern float em_poly_m;
#endif

/** @author Henrik Enqvist */

class AllegroVisitor : public Visitor  {
 protected:
	AllegroVisitor();
 public:
	~AllegroVisitor();
	static AllegroVisitor * getInstance();
	void visit(Group* g);
	void empty();
	int getMode(){ return m_iMode; };
	void setMode(int m){ m_iMode = m; };
 private:
	void visit(Shape3D* s, Group* g);
	static AllegroVisitor * p_AllegroVisitor;
	int m_iMode;
};

#endif // ALLEGROVISITOR_H

