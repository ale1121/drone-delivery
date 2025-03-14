#pragma once

#include "utils/glm_utils.h"
#include "core/gpu/mesh.h"
#include "drone_delivery/Obstacle.h"


namespace m1
{
    class Package : public Obstacle
    {
    public:
        Package();
        Package(int x, int z, glm::vec3 dest);
        bool CheckCollision(glm::vec3 center, float radius) override;

        Mesh* mesh;
        glm::vec3 destination;

    protected:
        glm::vec3 center;
    };
}  
