#include <vector>
#include "drone_delivery/Drone.h"
#include "drone_delivery/object3D.h"
#include "drone_delivery/colors.h"
#include "drone_delivery/House.h"


using namespace std;
using namespace m1;


Drone::Drone()
{
}


Drone::~Drone()
{
}

void Drone::Init(glm::vec3 startPosition)
{
	pitch = 0;
	yaw = 0;
	roll = 0;
	thrust = 0;
	rollUpdate = false;
	thrustUpdate = false;

	position = startPosition;
	forward = glm::vec3(0, 0, 1);

	this->package = nullptr;
	hasPackage = false;

	modelMatrix = glm::translate(glm::mat4(1), position);

	meshes.push_back(object3D::CreateBox("bar1", glm::vec3(-1, 0, -0.1), 2, 0.2, 0.2, colors::Gray));
	meshes.push_back(object3D::CreateBox("bar2", glm::vec3(-0.1, 0, -1), 0.2, 0.2, 2, colors::Gray));
	meshes.push_back(object3D::CreateBox("cube1", glm::vec3(-1, 0.2, -0.1), 0.2, 0.2, 0.2, colors::Gray));
	meshes.push_back(object3D::CreateBox("cube2", glm::vec3(0.8, 0.2, -0.1), 0.2, 0.2, 0.2, colors::Gray));
	meshes.push_back(object3D::CreateBox("cube3", glm::vec3(-0.1, 0.2, -1), 0.2, 0.2, 0.2, colors::Gray));
	meshes.push_back(object3D::CreateBox("cube4", glm::vec3(-0.1, 0.2, 0.8), 0.2, 0.2, 0.2, colors::Gray));

	propellerMesh = object3D::CreateBox("propeller", glm::vec3(-0.4, 0, -0.05), 0.8, 0.02, 0.1, colors::Black);

	propellersMM.resize(4);
	propellersMM[0] = glm::translate(glm::mat4(1), glm::vec3(-0.9, 0.4, 0));
	propellersMM[1] = glm::translate(glm::mat4(1), glm::vec3(0.9, 0.4, 0));
	propellersMM[2] = glm::translate(glm::mat4(1), glm::vec3(0, 0.4, -0.9));
	propellersMM[3] = glm::translate(glm::mat4(1), glm::vec3(0, 0.4, 0.9));

	propellersRotation = 0;

	arrowMeshes.push_back(object3D::CreatePrism("arr", glm::vec3(-0.2, 0, -0.05), 0.4, 0.1, 0.5, colors::Delivery));
	arrowMeshes.push_back(object3D::CreateBox("arr2", glm::vec3(-0.1, -0.5, -0.05), 0.2, 0.5, 0.1, colors::Delivery));
	arrowMM = glm::mat4(1);
	showArrow = false;
}

bool Drone::Update(float deltaTime, vector<vector<Obstacle*>>& obstacles)
{
	propellersRotation += deltaTime * 5;

	if (!rollUpdate && roll != 0) roll *= 0.9;
	rollUpdate = false;

	if (!thrustUpdate && thrust >= 0.01) thrust -= 0.01;
	if (!thrustUpdate && thrust <= -0.05) thrust += 0.05;
	thrustUpdate = false;

	yaw -= roll * 2;
	forward.y = -pitch;
	forward.x = sin(RADIANS(yaw));
	forward.z = cos(RADIANS(yaw));

	glm::vec3 newPos = position + forward * (deltaTime * thrust);

	if (!CheckCollisions(newPos, obstacles)) position = newPos;

	modelMatrix = glm::mat4(1);
	modelMatrix = glm::translate(modelMatrix, position);
	modelMatrix = glm::rotate(modelMatrix, RADIANS(yaw), glm::vec3(0, 1, 0));
	modelMatrix = glm::rotate(modelMatrix, pitch, glm::vec3(1, 0, 0));
	modelMatrix = glm::rotate(modelMatrix, roll, glm::vec3(0, 0, 1));
	modelMatrix = glm::rotate(modelMatrix, RADIANS(45), glm::vec3(0, 1, 0));
	modelMatrix = glm::scale(modelMatrix, glm::vec3(0.5, 0.5, 0.5));

	if (!hasPackage && package != nullptr && package->CheckCollision(position, 0.5)) {
		hasPackage = true;
		return true;
	}

	showArrow = false;

	if (hasPackage) {
		package->modelMatrix = modelMatrix * glm::translate(glm::mat4(1), glm::vec3(0.3, -0.9, 0));

		glm::vec2 dir = glm::vec2(package->destination.x - position.x, package->destination.z - position.z);
		
		if (length(dir) > 1.5) {
			dir = normalize(dir);
			float angle = atan2(dir.x, dir.y);
			arrowMM = glm::mat4(1);
			arrowMM = glm::translate(arrowMM, position);
			arrowMM = glm::rotate(arrowMM, angle, glm::vec3(0, 1, 0));
			arrowMM = glm::translate(arrowMM, glm::vec3(0, 0, 1));
			arrowMM = glm::rotate(arrowMM, RADIANS(90), glm::vec3(1, 0, 0));

			showArrow = true;
		}

	}

	return false;
}

bool Drone::CheckCollisions(glm::vec3 &pos, vector<vector<Obstacle*>>& obstacles)
{
	if (CheckLimits(pos)) return false;

	int i = static_cast<int>(pos.x) / 4;
	int j = static_cast<int>(pos.z) / 4;

	if (i < 0 || i > 9 || j < 0 || j > 9) return false;

	if (hasPackage && obstacles[i][j]->type == Obstacle::HOUSE) {
		House* house = dynamic_cast<House*>(obstacles[i][j]);
		if (house->CheckDeliveryPoint(pos, 0.5)) {
			hasPackage = false;
			package = nullptr;
		}
	}

	if (obstacles[i][j]->CheckCollision(pos, 0.5)) return true;

	return false;
}

bool Drone::CheckLimits(glm::vec3 &pos)
{
	if (pos.y < 0.8) pos.y = 0.8;

	bool onEdge = false;

	if (pos.x > 42) {
		pos.x = 42;
		onEdge = true;
	}
	if (pos.x < -2) {
		pos.x = -2;
		onEdge = true;
	}
	if (pos.z > 42) {
		pos.z = 42;
		onEdge = true;
	}
	if (pos.z < -2) {
		pos.z = -2;
		onEdge = true;
	}

	return onEdge;
}

void Drone::UpdateThrust(float deltaTime)
{
	thrustUpdate = true;
	thrust += 2 * deltaTime;
	if (thrust > 5) thrust = 5;
	if (thrust < -5) thrust = -5;
}

void Drone::UpdatePitch(float delta)
{
	pitch += delta * 0.01f;
	if (pitch < -0.8) pitch = -0.8;
	if (pitch > 0.9) pitch = 0.9;
}

void Drone::UpdateYaw(float delta)
{
	yaw += delta * 0.3f;
}

void Drone::UpdateRoll(float deltaTime)
{
	rollUpdate = true;
	roll += deltaTime;
	if (roll > 0.5) roll = 0.5;
	if (roll < -0.5) roll = -0.5;
}
