#pragma once

#include <vector>
#include "utils/glm_utils.h"
#include "core/gpu/mesh.h"
#include "drone_delivery/Obstacle.h"
#include "drone_delivery/Package.h"


namespace m1
{
    class Drone
    {
    public:
        Drone();
        ~Drone();
        void Init(glm::vec3 startPosition);
        bool Update(float deltaTime, std::vector<std::vector<Obstacle*>>& obstacles);
        void UpdateThrust(float deltaTime);
        void UpdatePitch(float deltaY);
        void UpdateYaw(float deltaX);
        void UpdateRoll(float deltaTime);


        float pitch;
        float yaw;
        float roll;
        float thrust;
        bool rollUpdate;
        bool thrustUpdate;
        glm::vec3 position;
        glm::vec3 forward;

        std::vector<Mesh*> meshes;
        Mesh* propellerMesh;
        glm::mat4 modelMatrix;
        std::vector<glm::mat4> propellersMM;
        float propellersRotation;

        std::vector<Mesh*> arrowMeshes;
        glm::mat4 arrowMM;
        bool showArrow;

        std::shared_ptr<Package> package;
        bool hasPackage;

    private:
        bool CheckCollisions(glm::vec3 &pos, std::vector<std::vector<Obstacle*>> &obstacles);
        bool CheckLimits(glm::vec3& pos);
    };
}
