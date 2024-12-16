#pragma once

#include "test.h"
#include "mockCamera.h"
#include "notificationService.h"

class NotificationServiceTest : public ::testing::Test {
protected:
	static NotificationService& notificationService;
	static MockCamera* mockCamera1;
	static MockCamera* mockCamera2;

	static void SetUpTestSuite();

	static void TearDownTestSuite();
};
