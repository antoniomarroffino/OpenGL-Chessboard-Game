#pragma once

#include <iostream>
#include <cassert>
#include <memory>


#include "object.h"
#include "node.h"
#include "glm/glm.hpp"

class Test {
protected:
	void virtual test() = 0;
};