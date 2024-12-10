#include "notificationService.h"

ENG_API NotificationService::NotificationService() : m_listeners{std::vector<ReshapeListener*>()} {}

ENG_API NotificationService::~NotificationService() {
	for (auto* listener : m_listeners)
		delete listener;
	m_listeners.clear();
}

ENG_API NotificationService& NotificationService::getInstance() {
	static NotificationService instance;
	return instance;
}

ENG_API void NotificationService::subscribeListener(ReshapeListener* listener) {
	if (listener != nullptr) this->m_listeners.push_back(listener);
}

ENG_API void NotificationService::unsubscribeListener(ReshapeListener* listener) {
	if (listener != nullptr) this->m_listeners.erase(std::remove(this->m_listeners.begin(), this->m_listeners.end(), listener), this->m_listeners.end());
}

ENG_API void NotificationService::notifyOnReshapeWindow(int width, int height) const{
	for (auto* listener : this->m_listeners)
		listener->onWindowReshape(width, height);
}