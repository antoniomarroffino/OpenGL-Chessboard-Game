#pragma once

#include "ovoObjectFactory.h"
#include "node.h"
#include "material.h"
#include <map>

class ENG_API FileOVOReader {
public:
	FileOVOReader();
	bool hasOVOExtension(const std::string&);
	Node* parseFile(const std::string&);
private:
	const bool openFile(const std::string&);

	static std::string ovoExtension;
	FILE *m_dat;
	std::map<std::string, Material*> m_materialsMap;
};
