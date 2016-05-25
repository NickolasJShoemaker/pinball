/***************************************************************************
 Simple test. A cube should be visible in the middle of the screen.
 The arrow keys rotates the cube.
***************************************************************************/

#include <iostream>

#include "Private.h"
#include "Engine.h"
#include "Camera.hpp"
#include "Cube.hpp"
#include "Keyboard.h"
#include "Behavior.h"
#include "Shape3D.h"


/** A behavior class that implements a onSignal method */
class SignalTest : public Behavior {
public:
  void onSignal(int em_signal, Group* em_group);
  void onCollision(const Vertex3D& em_vtx, const Vertex3D& em_vtxOwn, Group* em_group){};
  void onTick(){};
};

void SignalTest::onSignal(int em_signal, Group* em_group){
  if(em_signal == 1){
    cerr << "Got signal 1" << endl;
    if (this->getParent() != NULL){
      Shape3D* shape = this->getParent()->getShape3D(0);
      if (shape != NULL) shape->setColor(1,1,1,1);
    }
  }
  if(em_signal == 2){
    cerr << "Got signal 2" << endl;
    if (this->getParent() != NULL){
      Shape3D* shape = this->getParent()->getShape3D(0);
      if (shape != NULL) shape->setColor(1,0,1,1);
    }
  }
}

/** Main */
int main(int argc, char *argv[]){
  cerr << "Simple emilia test." << endl;
  
  // Create the engine.
  Engine* engine = new Engine(argc, argv);
  engine->setLightning(0.5f, 0.1f);

  // Add a camera. Move a bit.
  Camera* camera = new Camera();
  Group* groupCamera = new Group();
  engine->add(groupCamera);
  groupCamera->setCamera(camera);
  groupCamera->setTranslation(0, 0, 3);
  engine->setEngineCamera(groupCamera);
  // Add a cube.
  Cube* cube = new Cube(1.0, 1.0, 1.0, 0.0, 1.0);
  Group* groupCube = new Group();
  engine->add(groupCube);
  groupCube->addShape3D(cube);
	
  // Add a behavior to the cube
  SignalTest* beh = new SignalTest();
  groupCube->setBehavior(beh);
		
  engine->resetTick();
  while (!Keyboard::isKeyDown(SDLK_ESCAPE)){
    if (Keyboard::isKeyDown(SDLK_1)){
      // multicast a signal
      SignalSender::getInstance()->addSignal(1, 0, engine, NULL);
    }
    if (Keyboard::isKeyDown(SDLK_2)){
      // multicast a signal with delay
      SignalSender::getInstance()->addSignal(2, 50, engine, NULL);
    }
    if (engine->nextTickFPS(50)){
      engine->tick();
    }else{
      engine->render();
      engine->swap();
    }
  }
  delete(engine);
  return 0;
}



