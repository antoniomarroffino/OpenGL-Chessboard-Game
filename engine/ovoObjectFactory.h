#pragma once

#include "object.h"

class ENG_API OVOObjectFactory {
public:
	static Object* createObjectByChunkID(const unsigned int&, const char*);

private:
	static const unsigned char skipToSubtype(const char*);
	static Object* createLight(const unsigned char&);
};
