#include "notificationServiceTest.h"

NotificationService& NotificationServiceTest::notificationService{ NotificationService::getInstance()};
MockCamera* NotificationServiceTest::mockCamera1 = nullptr;
MockCamera* NotificationServiceTest::mockCamera2 = nullptr;

void NotificationServiceTest::SetUpTestSuite() {
	mockCamera1 = new MockCamera();
	mockCamera2 = new MockCamera();
}

void NotificationServiceTest::TearDownTestSuite() {
	delete mockCamera1;
	delete mockCamera2;
}

TEST_F(NotificationServiceTest, NotifyOnReshapeWindow) {
	notificationService.subscribeListener(mockCamera1);
	notificationService.subscribeListener(mockCamera2);

	EXPECT_CALL(*mockCamera1, onWindowReshape)
		.Times(1);
	EXPECT_CALL(*mockCamera2, onWindowReshape)
		.Times(1);
	notificationService.notifyOnReshapeWindow(1, 1);

	notificationService.unsubscribeListener(mockCamera1);
	notificationService.unsubscribeListener(mockCamera2);

	EXPECT_CALL(*mockCamera1, onWindowReshape)
		.Times(0);
	EXPECT_CALL(*mockCamera2, onWindowReshape)
		.Times(0);
	notificationService.notifyOnReshapeWindow(1, 1);
}