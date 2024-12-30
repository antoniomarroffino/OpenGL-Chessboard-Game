#pragma once

#include "reshapeListener.h"
#include "changeMatrixListener.h"
#include <vector>
#include <algorithm>

class ENG_API NotificationService {
public:
	NotificationService(const NotificationService&) = delete;
	NotificationService& operator=(const NotificationService&) = delete;

	~NotificationService();
	static NotificationService& getInstance();

	void subscribeListener(ReshapeListener*);
	void subscribeListener(ChangeMatrixListener*);
	void unsubscribeListener(ReshapeListener*);
	void unsubscribeListener(ChangeMatrixListener*);
	void notifyOnReshapeWindow(int, int) const;
	void notifyOnChangeMatrix(const unsigned int&) const;
private:
	NotificationService();

	std::vector<ReshapeListener*> m_reshapeListeners;
	std::vector<ChangeMatrixListener*> m_changeMatrixListeners;
};
