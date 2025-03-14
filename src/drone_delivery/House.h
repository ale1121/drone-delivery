#pragma once

#include "utils/glm_utils.h"
#include "drone_delivery/Obstacle.h"


namespace m1
{
    class House : public Obstacle
    {
    public:
        House();
        House(int x, int z);
        bool CheckCollision(glm::vec3 center, float radius) override;
        bool CheckDeliveryPoint(glm::vec3 center, float radius);
        bool hasDeliveryPoint;
        glm::vec3 deliveryPoint;

    private:
        glm::vec3 minVertex;
        glm::vec3 maxVertex;
    };
}  
