#include "fileOVOReader.h"
#include "mesh.h"
#include <iostream>
#include <filesystem>
#include <cstdio>

ENG_API std::string FileOVOReader::ovoExtension{ "ovo" };

ENG_API FileOVOReader::FileOVOReader() : m_dat{ nullptr }, m_materialsMap{std::map<std::string, Material*>()} {}

ENG_API bool FileOVOReader::hasOVOExtension(const std::string& fileName) {
    return fileName.size() >= ovoExtension.size() &&
        std::equal(ovoExtension.rbegin(), ovoExtension.rend(), fileName.rbegin());
}

const ENG_API bool FileOVOReader::openFile(const std::string& fileName) {
    return !fopen_s(&this->m_dat, fileName.c_str(), "rb");
}

ENG_API char* FileOVOReader::getDataOfChunkFromFile(unsigned int& chunkId, unsigned int& chunkSize) {
    fread(&chunkId, sizeof(unsigned int), 1, this->m_dat);
    if (feof(this->m_dat))
        return nullptr;
    fread(&chunkSize, sizeof(unsigned int), 1, this->m_dat);

    char* data = new char[chunkSize];
    if (fread(data, sizeof(char), chunkSize, this->m_dat) != chunkSize)
    {
        fclose(this->m_dat);
        delete[] data;
        return nullptr;
    }
    return data;
}

ENG_API void FileOVOReader::undoReadDataFromFile(const unsigned int& chunkSize) {
    long offset = -static_cast<long>(sizeof(unsigned int) * 2 + chunkSize);
    fseek(this->m_dat, offset, SEEK_CUR);
}

ENG_API Node* FileOVOReader::parseFile(const std::string& fileName) {
    std::filesystem::path filePath(fileName);

    if (!std::filesystem::exists(filePath)) return nullptr;

    std::string normalizedPath = filePath.string();
    if (!this->hasOVOExtension(normalizedPath)) return nullptr;

    if (!this->openFile(normalizedPath)) return nullptr;

    this->retrieveMaterials();

    Node* rootNode = this->recursiveLoad();

    return rootNode;
}

ENG_API void FileOVOReader::retrieveMaterials() {
    unsigned int chunkId, chunkSize, position;
    while (true) {
        char* data = this->getDataOfChunkFromFile(chunkId, chunkSize);

        if (data == nullptr) break;

        position = 0;
        Object* objectToParse = OVOObjectFactory::createObjectByChunkID(chunkId, data);
        if (objectToParse == nullptr) continue;

        Material* material = dynamic_cast<Material*>(objectToParse);
        
        if (material != nullptr) this->m_materialsMap["nameOfMaterial"] = material;
        else {
            this->undoReadDataFromFile(chunkSize);
            break;
        }

        objectToParse->parse(data, position);
    }
}

ENG_API Node* FileOVOReader::recursiveLoad() {
    unsigned int chunkId, chunkSize, position = 0;

    char* data = this->getDataOfChunkFromFile(chunkId, chunkSize);
    Node* nodeToParse = dynamic_cast<Node*>(OVOObjectFactory::createObjectByChunkID(chunkId, data));

    if (nodeToParse == nullptr) return nullptr;

    unsigned int numberOfChildren = nodeToParse->parse(data, position);

    Mesh* possibleMesh = dynamic_cast<Mesh*>(nodeToParse);

    //da chiedere. Tanti if quanti oggetti hanno il material
    if (possibleMesh != nullptr && possibleMesh->getMaterial() != nullptr) possibleMesh->setMaterial(this->m_materialsMap[possibleMesh->getMaterial()->getName()]);

    if(numberOfChildren)
        for (unsigned int i = 0; i < numberOfChildren; i++) {
            Node* childNode = this->recursiveLoad();
            nodeToParse->addChild(childNode);
        }

    return nodeToParse;
}

