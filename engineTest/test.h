#pragma once

#include <iostream>
#include <cassert>
#include <memory>


#include "object.h"
#include "node.h"
#include "glm/glm.hpp"
#include "glm/geometric.hpp"
#include "glm/gtc/matrix_transform.hpp"

class Test {
protected:
	void virtual test() = 0;
};