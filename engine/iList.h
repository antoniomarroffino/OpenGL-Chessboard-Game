#pragma once

#include "object.h"

class ENG_API IList {
public:
    virtual ~IList() = default;
    virtual bool addRowToListOfNodeToRender(Object*, const glm::mat4&) = 0;
    virtual void clearList() = 0;
    virtual void renderElements(const glm::mat4&) const = 0;
};
