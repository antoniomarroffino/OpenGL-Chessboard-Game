#pragma once

#include <string>
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtc/type_ptr.hpp"

class Object {
public:
	unsigned int getId() const;
	std::string getName() const;
	void setName(std::string);
	void virtual render(glm::mat4) = 0;
protected:
	Object(std::string);
	unsigned int createNewId();

	unsigned int m_id;
	std::string m_name;
	static unsigned int m_cnt_object;
};