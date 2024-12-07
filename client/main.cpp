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
   #include "glm/glm.hpp"

   // C/C++:
   #include <iostream>



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

   // Init engine:
   Eng::Base &eng = Eng::Base::getInstance();
   eng.init();

   //FUNZIONA SOLO CON PERCORSO ASSOLUTO (LINUX)
   //Node* node = eng.load("/home/lucaf/LabSoftware/Grafica/Progetto/a.ovo");

   //WINDOWS
   Node* rootNode = eng.load("C:/Users/lucaf/OneDrive - SUPSI/Desktop/Supsi/I3B/LabSoftware/GraficaProg/cg_ovosdk/examples/b.ovo");
   if (rootNode == nullptr) {
	   std::cerr << "ERROR: Error during parse of the scene" << std::endl;
	   return 1;
   }

   eng.passScene(rootNode);

   //if (node == nullptr) std::cout << "fails" << std::endl;

   //std::cout << "Node root: " << node->getName() << std::endl;

   // Release engine:
   eng.free();

   // Done:
   std::cout << "\n[application terminated]" << std::endl;
   return 0;
}
