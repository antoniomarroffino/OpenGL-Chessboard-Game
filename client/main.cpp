/**
 * @file		main.cpp
 * @brief	Client application (that uses the graphics engine)
 *
 * @author	Achille Peternier (C) SUPSI [achille.peternier@supsi.ch] << change this to your group members
 */



//////////////
// #INCLUDE //
//////////////

   // Library header:
   #include "engine.h"
   #include "node.h"
   #include "perspCamera.h"
   #include "glm/glm.hpp"

#include "glm/gtc/matrix_transform.hpp"

   // C/C++:
   #include <iostream>

Eng::Base& eng = Eng::Base::getInstance();
Node* rootNode;


void displayCallback() {
	eng.clear();

	Camera* mainCamera = new PerspCamera("mainCamera", 1000.0f, 1000.0f, 1.0f, 200.0f, glm::radians(45.0f));
	mainCamera->setMainCamera(true);

	rootNode->addChild(mainCamera);

	mainCamera = static_cast<Camera*>(rootNode->getMainCamera());

	rootNode->setMatrix(glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 20.0f, 100.0f)));
	//rootNode->setMatrix(glm::rotate(glm::mat4(1.0f), glm::radians(-55.0f), glm::vec3(1.0f, 0.0f, 0.0f)));


	eng.begin3D(mainCamera);


	eng.swap();
}



//////////
// MAIN //
//////////

/**
 * Application entry point.
 * @param argc number of command-line arguments passed
 * @param argv array containing up to argc passed arguments
 * @return error code (0 on success, error code otherwise)
 */
int main(int argc, char *argv[])
{
   // Credits:
   std::cout << "Client application example, A. Peternier (C) SUPSI" << std::endl;
   std::cout << std::endl;

   //FUNZIONA SOLO CON PERCORSO ASSOLUTO (LINUX)
	//Node* node = eng.load("/home/lucaf/LabSoftware/Grafica/Progetto/a.ovo");

	//WINDOWS
   rootNode = eng.load("cornellBox2.ovo");
   if (rootNode == nullptr) {
	   std::cerr << "ERROR: Error during parse of the scene" << std::endl;
	   return 1;
   }

   eng.passScene(rootNode);

   // Init engine:
   eng.init(displayCallback);


   // Release engine:
   eng.free();

   // Done:
   std::cout << "\n[application terminated]" << std::endl;
   return 0;
}
