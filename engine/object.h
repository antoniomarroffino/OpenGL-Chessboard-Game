/**
 * @file		object.h
 * @brief	Object include file
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
#include <string>
#include <iostream>
#include <iomanip>
#include <limits.h>
#include <cstring>
#include "glm/glm.hpp"
#include "glm/gtc/type_ptr.hpp"

/////////////
// VERSION //
/////////////

   // Generic info:
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


 ///////////////////////
 // MAIN OBJECT CLASS //
 ///////////////////////

 /**
  * @brief Abstract Object base class
  */
class ENG_API Object {
public:
	virtual ~Object() = default;
	const unsigned int& getId() const;
	const std::string& getName() const;
	void setName(const std::string&);
	void virtual render(const glm::mat4& = glm::mat4(1.0f)) = 0;
	const virtual unsigned int parse(const char*, unsigned int&) = 0;
protected:
	Object(const std::string& = "defaultObject");
	Object(const Object&);

	unsigned int createNewId();

	unsigned int m_id;
	std::string m_name;
	static unsigned int m_cnt_object;
};
