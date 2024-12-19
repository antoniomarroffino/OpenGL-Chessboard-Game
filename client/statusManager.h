#pragma once

#include <memory>
#include <list>
#include <map>
#include <string>
#include "gameStatus.h"
#include "engine.h"

class StatusManager {
public:
	StatusManager();
	StatusManager(const StatusManager&) = delete;
	StatusManager& operator=(const StatusManager&) = delete;
	~StatusManager();

	void addGameStatusAndCallbacks(const GameStatus&, void (*)(unsigned char, int, int) = nullptr,
		void (*)(int, int, int) = nullptr, const std::list<std::string> = std::list<std::string>());

	void changeState(const GameStatus&);
	const std::list<std::string> getMenu() const;

private:
	void (*getKeyboardCallback(const GameStatus&))(unsigned char, int, int);
	void (*getSpecialKeyCallback(const GameStatus&))(int, int, int);

	struct Reserved;
	std::map<GameStatus, Reserved> m_reserved;
	GameStatus m_currentState;

	Eng::Base& m_engine;
};