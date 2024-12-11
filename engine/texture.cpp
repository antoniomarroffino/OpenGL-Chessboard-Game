#include <GL/freeglut.h> // Include OpenGL e GLUT
#include "FreeImage.h"   // Libreria per immagini
#include "texture.h"


struct Texture::Reserved {
	unsigned int m_textureId;
	FIBITMAP* m_bitmap;

	Reserved() : m_textureId{ 0 }, m_bitmap{ nullptr } { }
	
};

ENG_API Texture::Texture(const std::string& name) : Object(name), m_reserved{std::make_unique<Texture::Reserved>()} {
}

ENG_API Texture::~Texture() { 
	if(this->m_reserved->m_bitmap != nullptr)
		FreeImage_Unload(this->m_reserved->m_bitmap);
}

ENG_API void Texture::render(const glm::mat4& matrix) {
    // Verifica che la texture esista
    if (this->m_reserved->m_bitmap == nullptr) {
        std::cerr << "Texture not loaded or bitmap is nullptr!" << std::endl;
        return;
    }

    // Se l'ID della texture non è stato generato prima, generalo ora (solo una volta)
    if (this->m_reserved->m_textureId == 0) {
        glGenTextures(1, &this->m_reserved->m_textureId);  // Genera l'ID della texture
        glBindTexture(GL_TEXTURE_2D, this->m_reserved->m_textureId);  // Associa l'ID della texture

        // Imposta le proprietà di wrapping per S e T (ripetizione della texture)
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

        // Imposta le proprietà di filtraggio (minimizzazione e ingrandimento)
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

        // Carica la texture in OpenGL
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA,
            FreeImage_GetWidth(this->m_reserved->m_bitmap),
            FreeImage_GetHeight(this->m_reserved->m_bitmap),
            0, GL_BGRA_EXT, GL_UNSIGNED_BYTE,
            (void*)FreeImage_GetBits(this->m_reserved->m_bitmap));

        // (Opzionale) Se la texture ha mipmaps, puoi generarle
        // glGenerateMipmap(GL_TEXTURE_2D);
    }

    // Dopo la prima generazione, fai solo il binding
    glBindTexture(GL_TEXTURE_2D, this->m_reserved->m_textureId);  // Associa la texture già creata

    // Se vuoi usare mipmaps, disabilitali se non necessari
    // glBindTexture(GL_TEXTURE_2D, 0); // Dissocia la texture, ma per renderizzare non serve qui
}




const ENG_API unsigned int Texture::parse(const char* data, unsigned int& position) {
    FreeImage_Initialise();
	std::string filename = "textures/" + this->getName();

    FIBITMAP* bitmap = FreeImage_Load(FreeImage_GetFileType(filename.c_str(), 0), filename.c_str());
    if (!bitmap) {
        std::cerr << "Impossibile caricare il file: " << filename << std::endl;
        FreeImage_DeInitialise();
        return 0;
    }
    this->m_reserved->m_bitmap = bitmap;
    if (this->m_reserved->m_bitmap == nullptr) std::cout << "sono un figlio di puttana" << std::endl;
    else std::cout << "sono paternack" << std::endl;
    FreeImage_DeInitialise();
	return 0;
}