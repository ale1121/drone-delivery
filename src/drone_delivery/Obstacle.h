#pragma once

#include "utils/glm_utils.h"

namespace m1
{
    class Obstacle
    {
    public:
        enum Type {
            TREE,
            HOUSE,
            PACKAGE,
            NONE
        };

        Obstacle();
        ~Obstacle() = default;
        virtual bool CheckCollision(glm::vec3 center, float radius);

        Type type;
        glm::mat4 modelMatrix;
    };
}  
