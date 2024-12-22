#pragma once

#define MAIN_CAMERA "firstCamera"
#define CHESSBOARD_CAMERA "chessboardCamera"
#define PLAYER_WHITE_CAMERA "playerWhiteCamera"
#define PLAYER_BLACK_CAMERA "playerBlackCamera"
#define MENU_CAMERA "menuCamera"

#include <memory>
#include <functional>
#include "onStateUpdate.h"
#include "statusManager.h"
#include "perspCamera.h"
#include "orthoCamera.h"

class CameraManager : public OnStateUpdateListener
{
public:
	CameraManager(const CameraManager&) = delete;
	CameraManager& operator=(const CameraManager&) = delete;
	~CameraManager() = default;

	static CameraManager& getInstance();
	bool initialize(Node*);

	void onStateChangeUpdate(GameStatus);

	bool addNewCamera(Camera*, Node* = nullptr);
	bool removeCamera(const std::string&, Node* = nullptr);
	bool setNewMainCamera(const std::string&, Node* = nullptr) const;
	Camera* getMainCamera(const Node* = nullptr) const;
	Camera* findCameraByName(const std::string&, const Node* = nullptr) const;

private:
	CameraManager();

	void createCameras();
	void preGameHandler();
	void gameHandler();

	Node* m_rootNode;
	StatusManager& m_statusManager;
	std::map<GameStatus, std::function<void()>> m_mapFunctionOnState;
};
