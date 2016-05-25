/***************************************************************************
                          AllegroVisitor.cpp  -  description
                             -------------------
    begin                : Sat Jan 6 2001
    copyright            : (C) 2001 by Henrik Enqvist
    email                : henqvist@excite.com
 ***************************************************************************/

#include "Private.h"
#include "AllegroVisitor.h"
#include "Group.h"
#include "Shape3D.h"
#include "Polygon.h"
#include "BillBoard.h"
#include "Config.h"

AllegroVisitor * AllegroVisitor::p_AllegroVisitor = NULL;

AllegroVisitor::AllegroVisitor(){}
AllegroVisitor::~AllegroVisitor(){
	p_AllegroVisitor = NULL;
}

AllegroVisitor * AllegroVisitor::getInstance(){
	if (p_AllegroVisitor == NULL){
		p_AllegroVisitor = new AllegroVisitor();
	}
	return p_AllegroVisitor;
}

void AllegroVisitor::empty(){}
void AllegroVisitor::visit(Group *){}
