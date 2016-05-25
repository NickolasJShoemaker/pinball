/***************************************************************************
                          Grid.h  -  description
                             -------------------
    begin                : Tue Feb 8 2000
    copyright            : (C) 2000 by Henrik Enqvist
    email                : henqvist@excite.com
 ***************************************************************************/

#ifndef GRID_HPP
#define GRID_HPP

#include "Shape3D.h"

#include "Private.h"
#include "Polygon.h"

/** A simple grid. @see Shape3D */
class Grid : public Shape3D {
    public:
      /**
       * <p>Grid(Texture, SizeForEachStepX, SizeForEachStepY, Steps, SizeForEachBitmapStep, 
         * r, g, b, a)</p>
       * <pre>
       *
       *  v-sizex-v            Steps=3
       *  ----------------------
       *  |      |      |      |
       *  |      |      |      |
       *  ---------------------- <
       *  |      |      |      | | sizey
       *  |      |      |      | |
       *  ---------------------- <
       *  |      |      |      |
       *  |      |      |      |
       *  ---------------------- Steps=3
       * </pre>
       */
        Grid(EmTexture* texture, float sizex, float sizey, int step, float bmStep, float fR=1.0, float fG=1.0, float fB=1.0, float fA=1.0) : Shape3D((step+1)*(step+1), step*step){
            Polygon3D* poly;

            sizex /= step;
            sizey /= step;
            
            for (int a = 0; a <= step; a++){
                for (int b = 0; b <= step; b++){
                    this->add( a*sizex - step*sizex*0.5, 0, -b*sizey + step*sizey*0.5, fR, fG, fB, fA, b*bmStep, a*bmStep);
                }
            }

            for(int a = 0; a < step; a++){
                for(int b = 0; b < step; b++){ 
                    poly = new Polygon3D(this, 4);
        //          poly->add(a + b*(step+1),               a*bmStep, b*bmStep,             fR, fG, fB, fA);
        //          poly->add((a+1) + b*(step+1),           (a+1)*bmStep, b*bmStep,         fR, fG, fB, fA);
        //          poly->add((a+1) + (b+1)*(step+1),       (a+1)*bmStep, (b+1)*bmStep,     fR, fG, fB, fA);
        //          poly->add(a + (b+1)*(step+1),           a*bmStep, (b+1)*bmStep,         fR, fG, fB, fA);
                    poly->add(a + b*(step+1));
                    poly->add((a+1) + b*(step+1));
                    poly->add((a+1) + (b+1)*(step+1));
                    poly->add(a + (b+1)*(step+1));
                    this->add(poly);
                }
            }

            this->setTexture(texture);
            this->countNormals();
    }
};

#endif // GRID_HPP
