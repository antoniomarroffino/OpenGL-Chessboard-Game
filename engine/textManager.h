#pragma once

#include <list>
#include <string>
#include <iostream>
#include <sstream>
#include <iomanip>
#include "orthoCamera.h"

class ENG_API TextManager {
public:
	TextManager(const TextManager&) = delete;
	TextManager& operator=(const TextManager&) = delete;
	~TextManager() = default;

	static TextManager& getInstance();

	void displayText(const std::list<std::string>&, Camera* orthoCamera) const;
	void displayFPS(const float&, Camera* orthoCamera) const;
private:
	TextManager();

	float setDynamicWidth(const std::list<std::string>&) const;
};

