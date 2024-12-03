/**
 * @file		engine.cpp
 * @brief	Graphics engine main file
 *
 * @author	Luca Fantò (C) SUPSI [luca.fanto@student.supsi.ch]
 * @author	Mattia Cainarca (C) SUPSI [mattia.cainarca@student.supsi.ch]
 * @author	Antonio Marroffino (C) SUPSI [antonio.marroffino@student.supsi.ch]
 */



//////////////
// #INCLUDE //
//////////////

   // Main include:
   #include "engine.h"
   #include "GL/freeglut.h"
   #include "fileOVOReader.h"
   
   // C/C++:
   #include <iostream>   
   #include <source_location>



/////////////////////////
// RESERVED STRUCTURES //
/////////////////////////

/**
 * @brief Base class reserved structure (using PIMPL/Bridge design pattern https://en.wikipedia.org/wiki/Opaque_pointer).
 */
struct Eng::Base::Reserved
{
    int windowId;
   // Flags:
   bool initFlag;

   FileOVOReader fileOVOReader;
   

   /**
    * Constructor.
    */
   Reserved() : windowId{ -1 }, initFlag{ false }, fileOVOReader{FileOVOReader()}
   {}
};



////////////////////////
// BODY OF CLASS Base //
////////////////////////

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/**
 * Constructor.
 */
ENG_API Eng::Base::Base() : reserved(std::make_unique<Eng::Base::Reserved>())
{  
#ifdef _DEBUG   
   std::cout << "[+] " << std::source_location::current().function_name() << " invoked" << std::endl;
#endif
}


/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/**
 * Destructor.
 */
ENG_API Eng::Base::~Base()
{
#ifdef _DEBUG
   std::cout << "[-] " << std::source_location::current().function_name() << " invoked" << std::endl;
#endif
}


/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/**
 * Gets a reference to the (unique) singleton instance.
 * @return reference to singleton instance
 */
Eng::Base ENG_API &Eng::Base::getInstance()
{
   static Base instance;
   return instance;
}


/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/**
 * Init internal components. 
 * @return TF
 */
bool ENG_API Eng::Base::init()
{
   // Already initialized?
   if (reserved->initFlag)
   {
      std::cout << "ERROR: engine already initialized" << std::endl;
      return false;
   }
   /*
   // Here you can initialize most of the graphics engine's dependencies and default settings...
   glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH);
   glutInitWindowPosition(100, 100);
   glutSetOption(GLUT_ACTION_ON_WINDOW_CLOSE, GLUT_ACTION_GLUTMAINLOOP_RETURNS);
   reserved->windowId = glutCreateWindow("Chess");

   //Set callback functions

   glEnable(GL_DEPTH_TEST);*/
   // Done:
   std::cout << "[>] " << LIB_NAME << " initialized" << std::endl;
   reserved->initFlag = true;
   return true;
}


ENG_API Node* Eng::Base::load(const std::string& fileName) {
    std::cout << "return pointer to root node" << std::endl;
    Node* rootNode = this->reserved->fileOVOReader.parseFile(fileName);
    return new Node("");
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/**
 * Swap buffers.
 */
void ENG_API Eng::Base::swap() {
    glutSwapBuffers();
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/**
 * Clear the screen.
 */
void ENG_API Eng::Base::clear() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}


/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/**
 * Free internal components.
 * @return TF
 */
bool ENG_API Eng::Base::free()
{
   // Not initialized?
   if (!reserved->initFlag)
   {
      std::cout << "ERROR: engine not initialized" << std::endl;
      return false;
   }

   // Here you can properly dispose of any allocated resource (including third-party dependencies)...

   // Done:
   std::cout << "[<] " << LIB_NAME << " deinitialized" << std::endl;
   reserved->initFlag = false;
   return true;
}
