#pragma once

#include <chrono>
#include "components/simple_scene.h"
#include "drone_delivery/Terrain.h"
#include "drone_delivery/Drone.h"
#include "drone_delivery/TPCamera.h"
#include "drone_delivery/Obstacle.h"
#include "drone_delivery/Tree.h"
#include "drone_delivery/House.h"
#include "drone_delivery/ChristmasTree.h"
#include "drone_delivery/Package.h"


namespace m1
{
    class DroneDelivery : public gfxc::SimpleScene
    {
    public:
        DroneDelivery();
        ~DroneDelivery();

        void Init() override;

    private:
        void FrameStart() override;
        void Update(float deltaTimeSeconds) override;
        void FrameEnd() override;

        void OnInputUpdate(float deltaTime, int mods) override;
        void OnKeyPress(int key, int mods) override;
        void OnKeyRelease(int key, int mods) override;
        void OnMouseMove(int mouseX, int mouseY, int deltaX, int deltaY) override;
        void OnMouseBtnPress(int mouseX, int mouseY, int button, int mods) override;
        void OnMouseBtnRelease(int mouseX, int mouseY, int button, int mods) override;
        void OnMouseScroll(int mouseX, int mouseY, int offsetX, int offsetY) override;
        void OnWindowResize(int width, int height) override;

        void RenderMesh(Mesh* mesh, Shader* shader, const glm::mat4& modelMatrix) override;
        void RenderTree(Mesh* mesh, Tree* tree, Shader* shader);
        void RenderChristmasTree(Mesh* mesh, ChristmasTree* tree, Shader* shader, float kd);
        void RenderScene();
        void CreateMeshes();
        void CreateObstacles();
        void CreatePackage();
    
    protected:
        TPCamera *camera;
        glm::mat4 projectionMatrix;

        Terrain2 terrain;
        Drone drone;

        std::vector<Mesh*> treeMeshes;
        std::vector<Mesh*> houseMeshes;
        std::vector<Mesh*> christmasTreeMeshes;

        std::vector<Tree*> trees;
        std::vector<House*> houses;
        ChristmasTree *christmasTree;
        std::shared_ptr<Package> package;

        std::vector<std::vector<Obstacle*>> obstacles;

        std::chrono::high_resolution_clock::time_point pickUpTime;
        std::chrono::high_resolution_clock::time_point deliveryTime;
        int packagesDelivered;
        float score;
    };
}
