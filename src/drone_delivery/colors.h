#pragma once 

#include "utils/glm_utils.h"

namespace colors
{
	static constexpr auto Sky =			glm::vec3(0.06, 0.08, 0.30);

	static constexpr auto Black =		glm::vec3(0.00, 0.00, 0.00);
	static constexpr auto Gray =		glm::vec3(0.50, 0.50, 0.50);

	static constexpr auto Snow =		glm::vec3(0.80, 0.80, 1.00);
	static constexpr auto SnowDark =	glm::vec3(0.70, 0.70, 1.00);

	static constexpr auto Tree =		glm::vec3(0.10, 0.60, 0.40);
	static constexpr auto TreeDark =	glm::vec3(0.08, 0.50, 0.38);
	static constexpr auto TreeTrunk =	glm::vec3(0.47, 0.31, 0.12);
	
	static constexpr auto House =		glm::vec3(0.64, 0.39, 0.20);
	static constexpr auto HouseDark =	glm::vec3(0.58, 0.31, 0.18);

	static constexpr auto Star =		glm::vec3(1.00, 0.90, 0.00);
	static constexpr auto StarDark =	glm::vec3(1.00, 0.75, 0.00);

	static constexpr auto Delivery =	glm::vec3(0.40, 0.80, 0.40);


	static std::vector<glm::vec3> Package
	{
		glm::vec3(0.8, 0.2, 0.2),
		glm::vec3(0.9, 0.5, 0.1),
		glm::vec3(0.9, 0.9, 0.1),
		glm::vec3(0.2, 0.7, 0.2),
		glm::vec3(0.2, 0.6, 0.9),
		glm::vec3(0.7, 0.3, 1.0)
	};
}
