#include "drone_delivery/House.h"

using namespace m1;


House::House() : Obstacle()
{
}

House::House(int x, int z)
{
    type = HOUSE;
    hasDeliveryPoint = false;

	glm::vec3 squareCorner = glm::vec3(x * 4, 0, z * 4);
	modelMatrix = glm::translate(glm::mat4(1), squareCorner);

    float offset = static_cast<float>(rand() % 160) / 100 + 1.2;
	int rotate = rand() % 4;

    switch (rotate) {
    case 0:
        minVertex = glm::vec3(modelMatrix * glm::vec4(glm::vec3(-0.8 + offset, 0, 0.2), 1));
        maxVertex = glm::vec3(modelMatrix * glm::vec4(glm::vec3(0.8 + offset, 1.3, 2.2), 1));
        deliveryPoint = glm::vec3(modelMatrix * glm::vec4(glm::vec3(offset, 0, 3), 1));
        modelMatrix = glm::translate(modelMatrix, glm::vec3(offset, 0, 0));
        break;
    case 1:
        minVertex = glm::vec3(modelMatrix * glm::vec4(glm::vec3(0.2, 0, -0.8 + offset), 1));
        maxVertex = glm::vec3(modelMatrix * glm::vec4(glm::vec3(2.2, 1.3, 0.8 + offset), 1));
        deliveryPoint = glm::vec3(modelMatrix * glm::vec4(glm::vec3(3, 0, offset), 1));
        modelMatrix = glm::translate(modelMatrix, glm::vec3(0, 0, offset));
        break;
    case 2:
        minVertex = glm::vec3(modelMatrix * glm::vec4(glm::vec3(-0.8 + offset, 0, 1.8), 1));
        maxVertex = glm::vec3(modelMatrix * glm::vec4(glm::vec3(0.8 + offset, 1.3, 4), 1));
        deliveryPoint = glm::vec3(modelMatrix * glm::vec4(glm::vec3(offset, 0, 1), 1));
        modelMatrix = glm::translate(modelMatrix, glm::vec3(offset, 0, 4));
        break;
    case 3:
        minVertex = glm::vec3(modelMatrix * glm::vec4(glm::vec3(1.8, 0, -0.8 + offset), 1));
        maxVertex = glm::vec3(modelMatrix * glm::vec4(glm::vec3(4, 1.3, 0.8 + offset), 1));
        deliveryPoint = glm::vec3(modelMatrix * glm::vec4(glm::vec3(1, 0, offset), 1));
        modelMatrix = glm::translate(modelMatrix, glm::vec3(4, 0, offset));
        break;
    }

    modelMatrix = glm::rotate(modelMatrix, RADIANS(rotate * 90), glm::vec3(0, 1, 0));	
}

bool House::CheckCollision(glm::vec3 center, float radius)
{
    float x = std::max(minVertex.x, std::min(center.x, maxVertex.x));
    float y = std::max(minVertex.y, std::min(center.y, maxVertex.y));
    float z = std::max(minVertex.z, std::min(center.z, maxVertex.z));

    return (glm::distance2(glm::vec3(x, y, z), center) < 0.1);
}

bool House::CheckDeliveryPoint(glm::vec3 center, float radius)
{
    if (!hasDeliveryPoint) return false;

    if (center.y > 3) return false;
    
    center.y = 0;
    float dist = distance2(center, this->deliveryPoint);

    if (dist < radius + 1) {
        hasDeliveryPoint = false;
        return true;
    }

    return false;
}
