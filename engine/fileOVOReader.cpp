#include "fileOVOReader.h"
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

ENG_API Node* FileOVOReader::parseFile(const std::string& fileName) {
    std::filesystem::path filePath(fileName);

    if (!std::filesystem::exists(filePath)) return nullptr;
   
    std::string normalizedPath = filePath.string();
    if (!this->hasOVOExtension(normalizedPath)) return nullptr;
    
    if (!this->openFile(normalizedPath)) return nullptr;

    unsigned int chunkId, chunkSize;
    while (true)
    {
        fread(&chunkId, sizeof(unsigned int), 1, this->m_dat);
        if (feof(this->m_dat))
            break;
        fread(&chunkSize, sizeof(unsigned int), 1, this->m_dat);

        char* data = new char[chunkSize];
        if (fread(data, sizeof(char), chunkSize, this->m_dat) != chunkSize)
        {
            fclose(this->m_dat);
            delete[] data;
            return nullptr;
        }

        unsigned int position = 0;
        Object* objectToParse = OVOObjectFactory::createObjectByChunkID(chunkId, data);
        if (objectToParse == nullptr) continue;

        Material* material = dynamic_cast<Material*>(objectToParse);
        //Recuperare il nome del material dalla classe OVOObjectFactory....
        //creare nuova pair nella mappa come:
        if (material != nullptr) this->m_materialsMap["nameOfMaterial"] = material;

        //Così posso passare al parse un'istanza di questa classe che mette a disposizione il metodo getMaterialByName e lui può assegnarlo
        //altrimenti deve assegnare il material solo se l'object passato è una mesh ma deve recuperare il nome del Material legato a quella Mesh
        unsigned int children = objectToParse->parse(data, position);

        std::cout << "\n\n" << std::endl;
    }

    return nullptr;
}

