#pragma once

#include "utils/glm_utils.h"
#include "drone_delivery/Drone.h"


namespace m1
{
    class TPCamera
    {
    public:
        glm::mat4 viewMatrix;

        TPCamera();
        ~TPCamera();
        TPCamera(Drone *d);
        void Update();
        void UpdateDistance(float delta);

    private:
        Drone* drone;
        float distanceFromTarget;
        float pitch;

        glm::vec3 position;
        glm::vec3 up;
    };
}  
