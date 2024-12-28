#pragma once

#include <vector>
#include "listOfPiecesManager.h"

class HistoryManager {
public:
	HistoryManager(const HistoryManager&) = delete;
	HistoryManager& operator=(const HistoryManager&) = delete;
	~HistoryManager() = default;

	static HistoryManager& getInstance();
	void saveState();
	bool undo();
	bool redo();

private:
	HistoryManager();
	struct Reserved;
	std::vector<Reserved> m_history;
	Node* m_currentRootNode;
	ListOfPiecesManager& m_listOfPiecesManager;
	int m_pointer;
};