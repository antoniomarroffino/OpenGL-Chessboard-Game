#pragma once

#include "node.h"

class ENG_API IList {
public:
    virtual ~IList() = default;
    virtual void pass(const Node*) = 0;
    virtual void clearList() = 0;
    virtual void renderElements(const glm::mat4&) const = 0;
};
