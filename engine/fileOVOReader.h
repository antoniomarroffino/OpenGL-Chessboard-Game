#pragma once

#include "ovoObjectFactory.h"
#include "node.h"
#include "material.h"
#include <map>

class ENG_API FileOVOReader {
public:
	FileOVOReader(const FileOVOReader&) = delete;
	FileOVOReader& operator=(const FileOVOReader&) = delete;

	static FileOVOReader& getInstance();

	bool hasOVOExtension(const std::string&);
	Node* parseFile(const std::string&);
private:
	FileOVOReader();

	const bool openFile(const std::string&);
	char* getDataOfChunkFromFile(unsigned int&, unsigned int&);
	void undoReadDataFromFile(const unsigned int&);
	void retrieveMaterials();
	Node* recursiveLoad();

	static std::string ovoExtension;
	FILE *m_dat;
	std::map<std::string, Material*> m_materialsMap;
};
