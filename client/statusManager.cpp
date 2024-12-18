#include "statusManager.h"

struct StatusManager::Reserved
{
	void (*keyboardCallback)(unsigned char, int, int);
	void (*specialKeyCallback)(int, int, int);
	std::list<std::string> menu;

	Reserved() : keyboardCallback(nullptr), specialKeyCallback(nullptr), menu(std::list<std::string>()) {}
};

StatusManager::StatusManager() : m_reserved{ std::map<GameStatus, StatusManager::Reserved>() }, m_engine{Eng::Base::getInstance()} {}

StatusManager::~StatusManager() = default;

void StatusManager::addGameStatusAndCallbacks(const GameStatus& gameStatus, void (*keyboardCallback)(unsigned char, int, int),
		void (*specialKeyCallback)(int, int, int), const std::list<std::string> menu) {
	Reserved reserved;
	reserved.keyboardCallback = keyboardCallback;
	reserved.specialKeyCallback = specialKeyCallback;
	reserved.menu = menu;

	this->m_reserved[gameStatus] = reserved;
}

void StatusManager::changeState(const GameStatus& gameStatus) {
	this->m_engine.setKeyboardCallback(this->getKeyboardCallback(gameStatus) == nullptr ? [](unsigned char, int, int) {} : this->getKeyboardCallback(gameStatus));
	this->m_engine.setSpecialCallback(this->getSpecialKeyCallback(gameStatus) == nullptr ? [](int, int, int) {} : this->getSpecialKeyCallback(gameStatus));
	if (!this->m_reserved[gameStatus].menu.empty())
		this->m_engine.setMenu(this->m_reserved[gameStatus].menu);
}

void (*StatusManager::getKeyboardCallback(const GameStatus& gameStatus))(unsigned char, int, int) {
	if (this->m_reserved.count(gameStatus))
		return this->m_reserved[gameStatus].keyboardCallback;
    return nullptr;
}

void (*StatusManager::getSpecialKeyCallback(const GameStatus& gameStatus))(int, int, int) {
	if (this->m_reserved.count(gameStatus))
		return this->m_reserved[gameStatus].specialKeyCallback;
    return nullptr;
}

std::list<std::string> StatusManager::getMenu(const GameStatus& gameStatus) {
	if (this->m_reserved.count(gameStatus))
		return this->m_reserved[gameStatus].menu;
    return {};
}