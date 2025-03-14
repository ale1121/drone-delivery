#pragma once

#include "utils/glm_utils.h"
#include "drone_delivery/Obstacle.h"


namespace m1
{
    class Tree : public Obstacle
    {
    public:
        Tree();
        Tree(int x, int z);
        bool CheckCollision(glm::vec3 center, float radius) override;

        glm::vec3 center;
        float height;
        float radius;
    };
}  
