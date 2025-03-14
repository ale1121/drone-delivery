#include "drone_delivery/Obstacle.h"

using namespace m1;


Obstacle::Obstacle()
{
	modelMatrix = glm::mat4(1);
	type = NONE;
}

bool Obstacle::CheckCollision(glm::vec3 center, float radius)
{
	return false;
}
