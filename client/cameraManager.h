#pragma once

#include <list>
#include <memory>

#include "camera.h"

class CameraManager {
public:
	CameraManager(const CameraManager&) = delete;
	CameraManager& operator=(const CameraManager&) = delete;

	~CameraManager();

	static CameraManager& getInstance();
	bool addNewCamera(Camera*, Node*);
	bool removeCamera(const std::string&, Node*);
	bool setNewMainCamera(const std::string&, Node*) const;
	Camera* getMainCamera(const Node*) const;
private:
	CameraManager();

	struct Reserved;
	std::unique_ptr<Reserved> m_reserved;
};
