#include "drone_delivery/Tree.h"

using namespace m1;


Tree::Tree() : Obstacle()
{
}

Tree::Tree(int x, int z)
{
	type = TREE;

	glm::vec3 squareCorner = glm::vec3(x * 4, 0, z * 4);
	modelMatrix = glm::translate(glm::mat4(1), squareCorner);

	modelMatrix = glm::translate(modelMatrix, glm::vec3(1, 0, 1));

	float offsetX = static_cast<float>(rand() % 200) / 100;
	float offsetZ = static_cast<float>(rand() % 200) / 100;
	modelMatrix = glm::translate(modelMatrix, glm::vec3(offsetX, 0, offsetZ));

	float scale = static_cast<float>(rand() % 40) / 100 + 0.6;
	modelMatrix = glm::scale(modelMatrix, glm::vec3(scale));

	float horizScale = static_cast<float>(rand() % 40) / 100 + 0.6;
	modelMatrix = glm::scale(modelMatrix, glm::vec3(horizScale, 1, horizScale));

	height = 2.5 * scale;
	radius = 0.1 * scale * horizScale;
	center = glm::vec3(modelMatrix * glm::vec4(0, 0, 0, 1));
}

bool Tree::CheckCollision(glm::vec3 center, float radius)
{
	if (center.y > height) return false;

	center.y = 0;
	return distance2(center, this->center) < radius + this->radius;
}
