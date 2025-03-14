#include "drone_delivery/TPCamera.h"

using namespace m1;


TPCamera::TPCamera()
{
}

TPCamera::~TPCamera()
{
}

TPCamera::TPCamera(Drone *d)
{
    drone = d;
    distanceFromTarget = 3;

    pitch = 20;

    position = glm::vec3(0, 0, 0);
    up = glm::vec3(0, 1, 0);
}

void TPCamera::Update()
{
    float horizontalDist = distanceFromTarget * cos(RADIANS(pitch) + drone->pitch / 2);
    float verticalDist = distanceFromTarget * sin(RADIANS(pitch) + drone->pitch / 2);

    float offsetX = horizontalDist * sin(RADIANS(drone->yaw));
    float offsetZ = horizontalDist * cos(RADIANS(drone->yaw));

    position.x = drone->position.x - offsetX;
    position.z = drone->position.z - offsetZ;
    position.y = drone->position.y + verticalDist;

    viewMatrix = glm::lookAt(position, drone->position, up);
}

void TPCamera::UpdateDistance(float delta)
{
    distanceFromTarget += delta * 0.5;
    if (distanceFromTarget < 2) distanceFromTarget = 2;
    if (distanceFromTarget > 6) distanceFromTarget = 6;
}
