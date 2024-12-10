#pragma once

#include "reshapeListener.h"
#include <vector>
#include <algorithm>

class ENG_API NotificationService {
public:
	NotificationService(const NotificationService&) = delete;
	NotificationService& operator=(const NotificationService&) = delete;

	~NotificationService();
	static NotificationService& getInstance();

	void subscribeListener(ReshapeListener*);
	void unsubscribeListener(ReshapeListener*);
	void notifyOnReshapeWindow(int, int) const;
private:
	NotificationService();

	std::vector<ReshapeListener*> m_listeners;
};
