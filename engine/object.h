#pragma once

#include <string>
#include "glm/glm.hpp"
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

class Object {
public:
	unsigned int getId() const;
	std::string getName() const;
	void setName(std::string);
	void virtual render(glm::mat4);
protected:
	Object(std::string);
private:
	unsigned int m_id;
	static unsigned int m_cnt_object;
	std::string m_name;
};