#include "object.h"

ENG_API unsigned int Object::m_cnt_object{ 0 };

ENG_API Object::Object(const std::string& name)
	: m_name{name}, m_id{createNewId()} {}

Object::Object(const Object& object)
	: m_id{object.m_id}, m_name{object.m_name} {}

const ENG_API unsigned int& Object::getId() const {
	return this->m_id;
}

const ENG_API std::string& Object::getName() const {
	return this->m_name;
}

void ENG_API Object::setName(const std::string& name) {
	this->m_name = name;
}

unsigned int ENG_API Object::createNewId() {
	return this->m_cnt_object++;
}