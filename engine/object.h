#pragma once

#include <string>
#include "glm/glm.hpp"

class Object {
public:
	unsigned int getId() const;
	const std::string& getName() const;
	void setName(const std::string&);
	void virtual render(const glm::mat4& = glm::mat4(1.0f)) = 0;
protected:
	Object(const std::string&);
	unsigned int createNewId();

	unsigned int m_id;
	std::string m_name;
	static unsigned int m_cnt_object;
};