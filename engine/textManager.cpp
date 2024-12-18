#include "textManager.h"
#include "glm/gtc/type_ptr.hpp"
#include "GL/freeglut.h"
#include <iostream>

ENG_API TextManager::TextManager() {}

ENG_API TextManager::~TextManager() = default;

ENG_API TextManager& TextManager::getInstance() {
	static TextManager instance;
	return instance;
}

void ENG_API TextManager::displayText(const std::list<std::string>& texts) const {
    //glm::mat4 ortho = glm::ortho(0.0f, (float)width, 0.0f, (float)height, -1.0f, 1.0f);
    glm::mat4 ortho = glm::ortho(0.0f, (float)100, 0.0f, (float)100, -1.0f, 1.0f);

    glMatrixMode(GL_PROJECTION);
    glLoadMatrixf(glm::value_ptr(ortho));
    glMatrixMode(GL_MODELVIEW);
    glLoadMatrixf(glm::value_ptr(glm::mat4(1.0f)));

    glDisable(GL_LIGHTING);

    glColor3f(1.0f, 1.0f, 1.0f);

    float y = 0.0f;
    float yIncrement = 15.0f;

    for (const auto& text : texts) {
        glRasterPos2f(0.0f, y);
        glutBitmapString(GLUT_BITMAP_8_BY_13, (const unsigned char*)text.c_str());
        y += yIncrement;
    }

    glEnable(GL_LIGHTING);
}