#include "drone_delivery/Package.h"
#include "drone_delivery/object3D.h"
#include "drone_delivery/colors.h"

using namespace m1;


Package::Package() : Obstacle()
{
}

Package::Package(int x, int z, glm::vec3 dest)
{
	type = PACKAGE;
	destination = dest;

	modelMatrix = glm::mat4(1);
	modelMatrix = glm::translate(modelMatrix, glm::vec3(x, 0, z));

	float random = rand() % 360;
	modelMatrix = glm::rotate(modelMatrix, RADIANS(random), glm::vec3(0, 1, 0));

	modelMatrix = glm::translate(modelMatrix, glm::vec3(3, 0, 0));

	random = rand() % 360;
	modelMatrix = glm::rotate(modelMatrix, RADIANS(random), glm::vec3(0, 1, 0));

	center = glm::vec3(modelMatrix * glm::vec4(0, 0, 0, 1));

	random = rand() % colors::Package.size();
	mesh = object3D::CreateBox("package", glm::vec3(-0.5, 0.1, -0.5), 0.7, 0.7, 0.7, colors::Package[random]);
}

bool Package::CheckCollision(glm::vec3 center, float radius)
{
	return distance2(center, this->center) < radius + 0.7;
}
