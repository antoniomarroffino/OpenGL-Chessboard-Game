#pragma once

#include <vector>
#include "listOfPiecesManager.h"
#include "movementManager.h"
#include "onStateUpdate.h"
#include "statusManager.h"
#include "cameraManager.h"

class HistoryManager : public OnStateUpdateListener {
public:
	HistoryManager(const HistoryManager&) = delete;
	HistoryManager& operator=(const HistoryManager&) = delete;
	~HistoryManager() = default;

	static HistoryManager& getInstance();
	void takeSnapshot();
	bool undo();
	bool redo();
	void setUndoRedoCalled(const bool&);
private:
	HistoryManager();
	bool isUndoRedoCalled();

	void preGameHandler() override;
	void choiceHandler() override;
	void endGameHandler() override;

	
	struct Reserved;
	std::vector<Reserved> m_history;
	ListOfPiecesManager& m_listOfPiecesManager;
	MovementManager& m_movementManager;
	StatusManager& m_statusManager;
	int m_pointer;
	bool m_undoRedoCalled;
};