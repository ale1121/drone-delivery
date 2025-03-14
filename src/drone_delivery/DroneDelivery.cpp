#include <iostream>
#include <iomanip>
#include <string>
#include "drone_delivery/DroneDelivery.h"
#include "drone_delivery/object3D.h"
#include "colors.h"

using namespace std;
using namespace m1;


DroneDelivery::DroneDelivery()
{
}


DroneDelivery::~DroneDelivery()
{
}


void DroneDelivery::Init()
{
    {
        Shader* shader = new Shader("TerrainShader");
        shader->AddShader(PATH_JOIN(window->props.selfDir, "src", "drone_delivery", "shaders", "TerrainVertexShader.glsl"), GL_VERTEX_SHADER);
        shader->AddShader(PATH_JOIN(window->props.selfDir, "src", "drone_delivery", "shaders", "TerrainFragmentShader.glsl"), GL_FRAGMENT_SHADER);
        shader->CreateAndLink();
        shaders[shader->GetName()] = shader;
    }
    {
        Shader* shader = new Shader("FogShader");
        shader->AddShader(PATH_JOIN(window->props.selfDir, "src", "drone_delivery", "shaders", "VertexShader.glsl"), GL_VERTEX_SHADER);
        shader->AddShader(PATH_JOIN(window->props.selfDir, "src", "drone_delivery", "shaders", "FragmentShader.glsl"), GL_FRAGMENT_SHADER);
        shader->CreateAndLink();
        shaders[shader->GetName()] = shader;
    }
    {
        Shader* shader = new Shader("TreeShader");
        shader->AddShader(PATH_JOIN(window->props.selfDir, "src", "drone_delivery", "shaders", "TreeVertexShader.glsl"), GL_VERTEX_SHADER);
        shader->AddShader(PATH_JOIN(window->props.selfDir, "src", "drone_delivery", "shaders", "FragmentShader.glsl"), GL_FRAGMENT_SHADER);
        shader->CreateAndLink();
        shaders[shader->GetName()] = shader;
    }
    {
        Shader* shader = new Shader("ChristmasTreeShader");
        shader->AddShader(PATH_JOIN(window->props.selfDir, "src", "drone_delivery", "shaders", "ChristmasTreeVertexShader.glsl"), GL_VERTEX_SHADER);
        shader->AddShader(PATH_JOIN(window->props.selfDir, "src", "drone_delivery", "shaders", "FragmentShader.glsl"), GL_FRAGMENT_SHADER);
        shader->CreateAndLink();
        shaders[shader->GetName()] = shader;
    }

    camera = new TPCamera(&drone);
    projectionMatrix = glm::perspective(RADIANS(60), window->props.aspectRatio, 0.01f, 200.0f);

    terrain.Init(48);
    CreateMeshes();
    CreateObstacles();
    drone.Init(glm::vec3(20, 2, 16));
    CreatePackage();
    packagesDelivered = 0;
    score = 0;
}

void DroneDelivery::CreatePackage()
{
    int house = rand() % houses.size();
    houses[house]->hasDeliveryPoint = true;
    package = make_shared<Package>(20, 20, houses[house]->deliveryPoint);
    drone.package = package;
}

void DroneDelivery::CreateObstacles()
{
    christmasTree = new ChristmasTree(20, 20);

    int pos, i, j;
    int numHouses = 15;
    int numTrees = 40;

    obstacles.resize(10, vector<Obstacle*>(10, NULL));
    obstacles[4][4] = obstacles[4][5] = obstacles[5][4] = obstacles[5][5] = christmasTree;
    srand(time(NULL));

    while (numHouses > 0) {
        pos = rand() % 100;
        i = pos / 10;
        j = pos % 10;
        if (obstacles[i][j] == NULL) {
            obstacles[i][j] = new House(i, j);
            houses.push_back(dynamic_cast<House*>(obstacles[i][j]));
            numHouses--;
        }
    }

    while (numTrees > 0) {
        pos = rand() % 100;
        i = pos / 10;
        j = pos % 10;
        if (obstacles[i][j] == NULL) {
            obstacles[i][j] = new Tree(i, j);
            trees.push_back(dynamic_cast<Tree*>(obstacles[i][j]));
            numTrees--;
        }
    }

    for (int i = 0; i < 10; i++) {
        for (int j = 0; j < 10; j++) {
            if (obstacles[i][j] == NULL) {
                obstacles[i][j] = new Obstacle();
            }
        }
    }
}

void DroneDelivery::CreateMeshes()
{
    treeMeshes.push_back(object3D::CreateCylinder("treeTrunk", glm::vec3(0), 0.3, 0.7, 0.1, colors::TreeTrunk));
    treeMeshes.push_back(object3D::CreateDisk("treeBase1", glm::vec3(0, 0.7, 0), 1, 0.1, colors::Snow));
    treeMeshes.push_back(object3D::CreateCone("treeTop1", glm::vec3(0, 0.7, 0), 1, 1.5, 0.1, colors::Snow, colors::SnowDark));
    treeMeshes.push_back(object3D::CreateDisk("treeBase2", glm::vec3(0, 1.4, 0), 1, 0.1, colors::Snow));
    treeMeshes.push_back(object3D::CreateCone("treeTop2", glm::vec3(0, 1.4, 0), 1, 1.3, 0.1, colors::Snow, colors::SnowDark));

    christmasTreeMeshes.push_back(object3D::CreateStar("star", glm::vec3(0, 5.9, 0), 1, 0.5, 0.3, colors::Star, colors::StarDark));
    christmasTreeMeshes.push_back(object3D::CreateCylinder("trunk", glm::vec3(0), 0.6, 1.4, 0.1, colors::TreeTrunk));
    christmasTreeMeshes.push_back(object3D::CreateDisk("base1", glm::vec3(0, 1.4, 0), 2.3, 0.05, colors::Tree));
    christmasTreeMeshes.push_back(object3D::CreateCone("top1", glm::vec3(0, 1.4, 0), 2.3, 2.5, 0.05, colors::Tree, colors::TreeDark));
    christmasTreeMeshes.push_back(object3D::CreateDisk("base2", glm::vec3(0, 2.6, 0), 2.2, 0.05, colors::Tree));
    christmasTreeMeshes.push_back(object3D::CreateCone("top2", glm::vec3(0, 2.6, 0), 2.2, 2.3, 0.05, colors::Tree, colors::TreeDark));
    christmasTreeMeshes.push_back(object3D::CreateDisk("base3", glm::vec3(0, 3.7, 0), 2, 0.05, colors::Tree));
    christmasTreeMeshes.push_back(object3D::CreateCone("top3", glm::vec3(0, 3.7, 0), 2, 2, 0.05, colors::Tree, colors::TreeDark));

    houseMeshes.push_back(object3D::CreateBox("house", glm::vec3(-0.6, 0, 0.4), 1.2, 1, 1.6, colors::House, colors::HouseDark));
    houseMeshes.push_back(object3D::CreatePrism("roof", glm::vec3(-0.8, 1, 0.2), 1.6, 2, 1, colors::SnowDark, colors::Snow, colors::House));
    meshes["deliveryPoint"] = object3D::CreateDisk("delivery", glm::vec3(0, 0.51, 0), 0.7, 0.1, colors::Delivery);
}


void DroneDelivery::FrameStart()
{
    glClearColor(colors::Sky.x, colors::Sky.y, colors::Sky.z, 1);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void DroneDelivery::RenderScene()
{
    RenderMesh(terrain.mesh, shaders["TerrainShader"], glm::translate(glm::mat4(1), glm::vec3(-4, 0, -4)));

    for (auto& mesh : drone.meshes) {
        RenderMesh(mesh, shaders["FogShader"], drone.modelMatrix);
    }
    for (auto& mm : drone.propellersMM) {
        RenderMesh(drone.propellerMesh, shaders["FogShader"],
            drone.modelMatrix * glm::rotate(mm, drone.propellersRotation, glm::vec3(0, 1, 0)));
    }
    if (drone.showArrow) {
        for (auto& mesh : drone.arrowMeshes) {
            RenderMesh(mesh, shaders["FogShader"], drone.arrowMM); 
        }
    }

    for (auto& tree : trees) {
        for (auto& mesh : treeMeshes) {
            RenderTree(mesh, tree, shaders["TreeShader"]);
        }
    }

    for (auto& house : houses) {
        for (auto& mesh : houseMeshes) {
            RenderMesh(mesh, shaders["FogShader"], house->modelMatrix);
        }
        if (house->hasDeliveryPoint && drone.hasPackage) {
            RenderMesh(meshes["deliveryPoint"], shaders["FogShader"], glm::translate(glm::mat4(1), house->deliveryPoint));
        }
    }

    RenderChristmasTree(christmasTreeMeshes[0], christmasTree, shaders["ChristmasTreeShader"], 0.2);
    for (int i = 1; i < christmasTreeMeshes.size(); i++) {
        RenderChristmasTree(christmasTreeMeshes[i], christmasTree, shaders["ChristmasTreeShader"], 0.15);
    }

    RenderMesh(package->mesh, shaders["FogShader"], package->modelMatrix);
}

void DroneDelivery::Update(float deltaTimeSeconds)
{
    if (drone.Update(deltaTimeSeconds, obstacles)) {
        pickUpTime = chrono::high_resolution_clock::now();
    }

    if (drone.package == nullptr) {
        packagesDelivered++;
        deliveryTime = chrono::high_resolution_clock::now();
        chrono::duration<double> duration = deliveryTime - pickUpTime;
        float timeBonus = max(0.0, (5 - duration.count()) / 2);
        score += timeBonus + 1;

        cout << fixed << setprecision(2);
        cout << "Delivery completed in " << duration.count() << "s\n";
        cout << "Time bonus: " << timeBonus << "\n";
        cout << "Packages delivered: " << packagesDelivered << "\n";
        cout << "Score: " << score << "\n\n";

        CreatePackage();
    }

    camera->Update();

    glm::ivec2 resolution = window->GetResolution();
    glViewport(0, 0, resolution.x, resolution.y);
    RenderScene();
}

void DroneDelivery::FrameEnd()
{
}

void DroneDelivery::RenderMesh(Mesh* mesh, Shader* shader, const glm::mat4& modelMatrix)
{
    if (!mesh || !shader || !shader->program)
        return;

    shader->Use();
    glUniformMatrix4fv(shader->loc_view_matrix, 1, GL_FALSE, glm::value_ptr(camera->viewMatrix));
    glUniformMatrix4fv(shader->loc_projection_matrix, 1, GL_FALSE, glm::value_ptr(projectionMatrix));
    glUniformMatrix4fv(shader->loc_model_matrix, 1, GL_FALSE, glm::value_ptr(modelMatrix));

    int drone_position = glGetUniformLocation(shader->program, "drone_position");
    glUniform3fv(drone_position, 1, glm::value_ptr(drone.position));

    mesh->Render();
}

void DroneDelivery::RenderTree(Mesh *mesh, Tree* tree, Shader* shader)
{
    if (!mesh || !shader || !shader->program)
        return;

    shader->Use();
    glUniformMatrix4fv(shader->loc_view_matrix, 1, GL_FALSE, glm::value_ptr(camera->viewMatrix));
    glUniformMatrix4fv(shader->loc_projection_matrix, 1, GL_FALSE, glm::value_ptr(projectionMatrix));
    glUniformMatrix4fv(shader->loc_model_matrix, 1, GL_FALSE, glm::value_ptr(tree->modelMatrix));

    int drone_position = glGetUniformLocation(shader->program, "drone_position");
    glUniform3fv(drone_position, 1, glm::value_ptr(drone.position));

    glm::vec2 center = glm::vec2(tree->center.x, tree->center.z);
    int tree_center = glGetUniformLocation(shader->program, "tree_center");
    glUniform2fv(tree_center, 1, glm::value_ptr(center));

    int tree_height = glGetUniformLocation(shader->program, "tree_height");
    glUniform1f(tree_height, tree->height);

    mesh->Render();
}

void DroneDelivery::RenderChristmasTree(Mesh* mesh, ChristmasTree* tree, Shader* shader, float kd)
{
    if (!mesh || !shader || !shader->program)
        return;

    shader->Use();
    glUniformMatrix4fv(shader->loc_view_matrix, 1, GL_FALSE, glm::value_ptr(camera->viewMatrix));
    glUniformMatrix4fv(shader->loc_projection_matrix, 1, GL_FALSE, glm::value_ptr(projectionMatrix));
    glUniformMatrix4fv(shader->loc_model_matrix, 1, GL_FALSE, glm::value_ptr(tree->modelMatrix));

    int drone_position = glGetUniformLocation(shader->program, "drone_position");
    glUniform3fv(drone_position, 1, glm::value_ptr(drone.position));

    int light_position = glGetUniformLocation(shader->program, "light_position");
    glUniform3fv(light_position, 1, glm::value_ptr(tree->starPosition));

    int material_kd = glGetUniformLocation(shader->program, "material_kd");
    glUniform1f(material_kd, kd);

    mesh->Render();
}


void DroneDelivery::OnInputUpdate(float deltaTime, int mods)
{
    if (window->KeyHold(GLFW_KEY_W)) {
        drone.UpdateThrust(deltaTime);
    }
    if (window->KeyHold(GLFW_KEY_S)) {
        drone.UpdateThrust(-deltaTime);
    }

    if (window->KeyHold(GLFW_KEY_RIGHT)) {
        drone.UpdateRoll(deltaTime);
    }
    if (window->KeyHold(GLFW_KEY_LEFT)) {
        drone.UpdateRoll(-deltaTime);
    }

    if (window->KeyHold(GLFW_KEY_UP)) {
        drone.UpdatePitch(deltaTime * 100);
    }
    if (window->KeyHold(GLFW_KEY_DOWN)) {
        drone.UpdatePitch(-deltaTime * 100);
    }
}


void DroneDelivery::OnKeyPress(int key, int mods)
{
}


void DroneDelivery::OnKeyRelease(int key, int mods)
{
}


void DroneDelivery::OnMouseMove(int mouseX, int mouseY, int deltaX, int deltaY)
{
    if (window->MouseHold(GLFW_MOUSE_BUTTON_LEFT)) {
        drone.UpdateYaw(deltaX);
        drone.UpdatePitch(-deltaY);
    }
}


void DroneDelivery::OnMouseBtnPress(int mouseX, int mouseY, int button, int mods)
{
}


void DroneDelivery::OnMouseBtnRelease(int mouseX, int mouseY, int button, int mods)
{
}


void DroneDelivery::OnMouseScroll(int mouseX, int mouseY, int offsetX, int offsetY)
{
    camera->UpdateDistance(-offsetY);
}


void DroneDelivery::OnWindowResize(int width, int height)
{
}
