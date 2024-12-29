#pragma once

#include <vector>
#include "omniLight.h"
#include "spotLight.h"
#include "directLight.h"

#define LAMP_OMNI "Omni001"
#define CHESSBOARD_SPOT "Fspot001"

class LightManager
{
public:
	LightManager(const LightManager&) = delete;
	LightManager& operator=(const LightManager&) = delete;

	static LightManager& getInstance();

	void turnOn(const std::string&, Node* = nullptr);
	void turnOff(const std::string&, Node* = nullptr);
	bool isLightOn(const std::string&, Node* = nullptr) const;

	void increaseLight(const std::string&, Node* = nullptr);
	void decreaseLight(const std::string&, Node* = nullptr);
private:
	LightManager();

	Light* isLightPresent(const std::string&) const;

	std::vector<Light*> m_lights;
};

