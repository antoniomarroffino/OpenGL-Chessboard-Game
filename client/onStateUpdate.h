#pragma once

#include "gameStatus.h"
#include <map>
#include <functional>

class OnStateUpdateListener {
public:
	OnStateUpdateListener();
	void onStateChangeUpdate(GameStatus);
	virtual void preGameHandler();
	virtual void gameHandler();
	virtual void endGameHandler();

protected:
	std::map<GameStatus, std::function<void()>> m_mapFunctionOnState;
};
