#pragma once

#include <string>
#include "glm/glm.hpp"

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

class ENG_API Object {
public:
	const unsigned int& getId() const;
	const std::string& getName() const;
	void setName(const std::string&);
	void virtual render(const glm::mat4& = glm::mat4(1.0f)) = 0;
protected:
	Object(const std::string&);
	Object(const Object&);
	virtual ~Object() = default;

	unsigned int createNewId();

	unsigned int m_id;
	std::string m_name;
	static unsigned int m_cnt_object;
};