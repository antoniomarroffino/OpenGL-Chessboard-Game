#include "textManager.h"
#include "glm/gtc/type_ptr.hpp"
#include "GL/freeglut.h"
#include <iostream>

ENG_API TextManager::TextManager() {}

ENG_API TextManager& TextManager::getInstance() {
	static TextManager instance;
	return instance;
}

void ENG_API TextManager::displayText(const std::list<std::string>& texts, Camera* camera) const {
    if (dynamic_cast<OrthoCamera*>(camera) == nullptr)
        return;

    camera->render();

    glLoadMatrixf(glm::value_ptr(glm::mat4(1.0f)));

    float y = 10.0f;
    float yIncrement = 15.0f;

    glDisable(GL_LIGHTING);
    glDisable(GL_DEPTH_TEST);

    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glColor4f(0.0f, 0.0f, 0.0f, 0.6f);
    glBegin(GL_TRIANGLE_STRIP);
    glVertex2f(0.0f, 0.0f);
    glVertex2f(300.0f, 0.0f);
    glVertex2f(0.0f, yIncrement * texts.size() + y * 1.5f);
    glVertex2f(300.0f, yIncrement * texts.size() + y * 1.5f);
    glEnd();
    glDisable(GL_BLEND);

    glColor3f(1.0f, 1.0f, 1.0f);

    for (const auto& text : texts) {
        glRasterPos2f(5.0f, y);
        glutBitmapString(GLUT_BITMAP_8_BY_13, (const unsigned char*)text.c_str());
        y += yIncrement;
    }

    glEnable(GL_LIGHTING);
    glEnable(GL_DEPTH_TEST);
}