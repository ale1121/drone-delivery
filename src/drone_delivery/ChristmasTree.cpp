#include "drone_delivery/ChristmasTree.h"

using namespace m1;


ChristmasTree::ChristmasTree() : Tree()
{
}

ChristmasTree::ChristmasTree(int x, int z)
{
	type = TREE;

	modelMatrix = glm::translate(glm::mat4(1), glm::vec3(x, 0, z));

	height = 6.2;
	radius = 2.5;
	center = glm::vec3(x, 0, z);

	starPosition = glm::vec3(modelMatrix * glm::vec4(0, 5.9, 0, 1));
}
