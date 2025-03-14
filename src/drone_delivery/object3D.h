#pragma once

#include <string>
#include "core/gpu/mesh.h"
#include "utils/glm_utils.h"

namespace object3D
{
	Mesh* CreateMesh(std::string name, std::vector<VertexFormat> vertices, std::vector<unsigned int> indices);
	
	Mesh* CreateBox(std::string name, glm::vec3 corner, float length, float height, float width,
					glm::vec3 color1, glm::vec3 color2 = glm::vec3(-1));
	Mesh* CreateCone(std::string name, glm::vec3 center, float radius, float height, float angular_step,
					glm::vec3 color1, glm::vec3 color2);
	Mesh* CreateDisk(std::string name, glm::vec3 center, float radius, float angular_step,
					glm::vec3 color);
	Mesh* CreateCylinder(std::string name, glm::vec3 center, float radius, float height, float angular_step,
					glm::vec3 color);
	Mesh* CreatePrism(std::string name, glm::vec3 corner, float width, float length, float height,
					glm::vec3 color1, glm::vec3 color2 = glm::vec3(-1), glm::vec3 color3 = glm::vec3(-1));
	Mesh* CreateStar(std::string name, glm::vec3 center, float radius1, float radius2, float thickness,
					glm::vec3 color1, glm::vec3 color2);
}
