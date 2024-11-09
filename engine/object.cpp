#include "object.h"

unsigned int Object::m_cnt_object{ 0 };

Object::Object(std::string name)
	: m_name{ name } 
{
	this->m_id = this->m_cnt_object;
	this->m_cnt_object++;
}

unsigned int Object::getId() const {
	return this->m_id;
}

std::string Object::getName() const {
	return this->m_name;
}

void Object::setName(std::string name) {
	this->m_name = name;
}