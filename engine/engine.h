/**
 * @file		engine.h
 * @brief	Graphics engine main include file
 *
 * @author	Luca Fantò (C) SUPSI [luca.fanto@student.supsi.ch]
 * @author	Mattia Cainarca (C) SUPSI [mattia.cainarca@student.supsi.ch]
 * @author	Antonio Marroffino (C) SUPSI [antonio.marroffino@student.supsi.ch]
 */
#pragma once


 
//////////////
// #INCLUDE //
//////////////

   // C/C++:         
   #include <memory> 
#include "node.h"
#include "camera.h"


/////////////
// VERSION //
/////////////

   // Generic info:
#ifdef _DEBUG
   #define LIB_NAME      "My Graphics Engine v0.1a (debug)"   ///< Library credits
#else
   #define LIB_NAME      "My Graphics Engine v0.1a"   ///< Library credits
#endif
   #define LIB_VERSION   10                           ///< Library version (divide by 10)

   // Export API:
#ifdef _WINDOWS
   // Specifies i/o linkage (VC++ spec):
   #ifdef ENGINE_EXPORTS
      #define ENG_API __declspec(dllexport)
   #else
      #define ENG_API __declspec(dllimport)
   #endif      

   // Get rid of annoying warnings:
   #pragma warning(disable : 4251) 
#else // Under linux
   #define ENG_API
#endif



///////////////
// NAMESPACE //
///////////////

namespace Eng {



//////////////
// #INCLUDE //
//////////////   

   // You can subinclude here other headers of your engine...



///////////////////////
// MAIN ENGINE CLASS //
///////////////////////

/**
 * @brief Base engine main class. This class is a singleton.
 */
class ENG_API Base final
{
//////////
public: //
//////////	      

   // Const/dest:
   Base(Base const &) = delete;
   ~Base();

   // Operators:
   void operator=(Base const &) = delete;

   // Singleton:
   static Base &getInstance();

   // Init/free:
   bool init(void(*reshapeCallback)(int, int) = nullptr);
   bool free();
   void clear();
   const float& getFPS();

   //add parameters
   //class Node;
   Node* load(const std::string& fileName);
   void passScene(Node* rootNode);
   void clearScene();
   void begin3D(Camera* camera);
   void end3D();

   void swap();

///////////
private: //
///////////	
    
    void handleReshape(int, int);

   // Reserved:
   static Eng::Base instance;
   struct Reserved;
   std::unique_ptr<Reserved> reserved;

   // Const/dest:
   Base();
};

}; // end of namespace Eng::

