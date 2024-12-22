#pragma once

#include "gameStatus.h"

class OnStateUpdateListener {
public:
	OnStateUpdateListener() = default;
	virtual void onStateChangeUpdate(GameStatus) = 0;
};
