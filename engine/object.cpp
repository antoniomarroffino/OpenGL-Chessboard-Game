#include "object.h"

unsigned int Object::m_cnt_object{ 0 };

Object::Object(const std::string& name)
	: m_name{name}, m_id{createNewId()} {}

unsigned int Object::getId() const {
	return this->m_id;
}

const std::string& Object::getName() const {
	return this->m_name;
}

void Object::setName(const std::string& name) {
	this->m_name = name;
}

unsigned int Object::createNewId() {
	return this->m_cnt_object++;
}