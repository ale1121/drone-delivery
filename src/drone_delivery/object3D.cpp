#include "drone_delivery/object3D.h"

using namespace std;


Mesh* object3D::CreateMesh(
    std::string name,
    vector<VertexFormat> vertices,
    vector<unsigned int> indices)
{
    unsigned int VAO = 0;
    glGenVertexArrays(1, &VAO);
    glBindVertexArray(VAO);

    unsigned int VBO;
    glGenBuffers(1, &VBO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);

    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices[0]) * vertices.size(), &vertices[0], GL_STATIC_DRAW);

    unsigned int IBO;
    glGenBuffers(1, &IBO);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, IBO);

    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices[0]) * indices.size(), &indices[0], GL_STATIC_DRAW);

    // vertex position
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(VertexFormat), 0);

    glBindVertexArray(0);

    CheckOpenGLError();

    Mesh* mesh = new Mesh(name);
    mesh->InitFromBuffer(VAO, static_cast<unsigned int>(indices.size()));
    mesh->vertices = vertices;
    mesh->indices = indices;

    return mesh;
}

Mesh* object3D::CreateBox(
    string name,
    glm::vec3 corner,
    float length, float height, float width,
    glm::vec3 color1, glm::vec3 color2)
{
    if (color2 == glm::vec3(-1)) color2 = color1;

    float L = length, H = height, W = width;

    vector<VertexFormat> vertices
    {
        VertexFormat(glm::vec3(0, 0, W) + corner, color1),
        VertexFormat(glm::vec3(L, 0, W) + corner, color1),
        VertexFormat(glm::vec3(0, H, W) + corner, color2),
        VertexFormat(glm::vec3(L, H, W) + corner, color2),
        VertexFormat(glm::vec3(0, 0, 0) + corner, color1),
        VertexFormat(glm::vec3(L, 0, 0) + corner, color1),
        VertexFormat(glm::vec3(0, H, 0) + corner, color2),
        VertexFormat(glm::vec3(L, H, 0) + corner, color2)
    };

    vector<unsigned int> indices
    {
        0, 1, 2,
        1, 3, 2,
        2, 3, 7,
        2, 7, 6,
        1, 7, 3,
        1, 5, 7,
        6, 7, 4,
        7, 5, 4,
        0, 4, 1,
        1, 4, 5,
        2, 6, 4,
        0, 2, 4
    };

    Mesh* mesh = new Mesh(name);
    mesh->InitFromData(vertices, indices);
    return mesh;

}

Mesh* object3D::CreateCone(
    string name,
    glm::vec3 center,
    float radius, float height, float angular_step,
    glm::vec3 color1, glm::vec3 color2)
{
    std::vector<VertexFormat> vertices(2 / angular_step + 2, glm::vec3(0));
    std::vector<unsigned int> indices(vertices.size());

    vertices[0] = VertexFormat(center, color1);
    vertices[0].position.y += height;
    indices[0] = 0;

    for (int i = 1; i < vertices.size(); i++) {
        vertices[i] = VertexFormat(
            center + radius * glm::vec3(cos((i - 1) * angular_step * M_PI), 0, sin((i - 1) * angular_step * M_PI)), color2);
        indices[i] = i;
    }

    Mesh* cone = new Mesh(name);
    cone->SetDrawMode(GL_TRIANGLE_FAN);
    cone->InitFromData(vertices, indices);
    return cone;
}

Mesh* object3D::CreateDisk(
    string name,
    glm::vec3 center,
    float radius, float angular_step,
    glm::vec3 color)
{
    return CreateCone(name, center, radius, 0, angular_step, color, color);
}

Mesh* object3D::CreateCylinder(
    string name,
    glm::vec3 center,
    float radius, float height, float angular_step,
    glm::vec3 color)
{
    std::vector<VertexFormat> vertices(2 * 2 / angular_step + 2, glm::vec3(0));
    std::vector<unsigned int> indices(vertices.size());

    for (int i = 0; i < vertices.size() / 2; i += 2) {
        float x = cos(i * angular_step * M_PI);
        float z = sin(i * angular_step * M_PI);

        vertices[i] = VertexFormat(center + radius * glm::vec3(x, 0, z), color);
        vertices[i + 1] = VertexFormat(center + radius * glm::vec3(x, height / radius, z), color);

        indices[i] = i;
        indices[i + 1] = i + 1;
    }

    Mesh* cylinder = new Mesh(name);
    cylinder->SetDrawMode(GL_TRIANGLE_STRIP);
    cylinder->InitFromData(vertices, indices);
    return cylinder;
}

Mesh* object3D::CreatePrism(
    string name,
    glm::vec3 corner,
    float width, float length, float height,
    glm::vec3 color1, glm::vec3 color2, glm::vec3 color3)
{
    if (color2 == glm::vec3(-1)) color2 = color1;
    if (color3 == glm::vec3(-1)) color3 = color1;

    float W = width, L = length, H = height;

    vector<VertexFormat> vertices(12, glm::vec3(0));

    vertices[0] = VertexFormat(corner + glm::vec3(0, 0, 0), color1);
    vertices[1] = VertexFormat(corner + glm::vec3(W, 0, 0), color1);
    vertices[2] = VertexFormat(corner + glm::vec3(W, 0, L), color1);
    vertices[3] = VertexFormat(corner + glm::vec3(0, 0, L), color1);
    vertices[4] = VertexFormat(corner + glm::vec3(W/2, H, 0), color2);
    vertices[5] = VertexFormat(corner + glm::vec3(W/2, H, L), color2);

    vertices[6] = VertexFormat(corner + glm::vec3(0, 0, 0), color3);
    vertices[7] = VertexFormat(corner + glm::vec3(W, 0, 0), color3);
    vertices[8] = VertexFormat(corner + glm::vec3(W, 0, L), color3);
    vertices[9] = VertexFormat(corner + glm::vec3(0, 0, L), color3);
    vertices[10] = VertexFormat(corner + glm::vec3(W / 2, H, 0), color3);
    vertices[11] = VertexFormat(corner + glm::vec3(W / 2, H, L), color3);

    vector<unsigned int> indices
    {
        6, 7, 10,
        1, 5, 4,
        1, 2, 5,
        8, 9, 11,
        0, 4, 3,
        3, 4, 5,
        6, 9, 7,
        7, 9, 8
    };

    Mesh* prism = new Mesh(name);
    prism->InitFromData(vertices, indices);
    return prism;
}

Mesh* object3D::CreateStar(
    std::string name,
    glm::vec3 center,
    float radius1, float radius2, float thickness,
    glm::vec3 color1, glm::vec3 color2)
{
    vector<VertexFormat> vertices;
    
    for (int i = 0; i < 5; i++) {
        vertices.push_back(VertexFormat(
            center + radius1 * glm::vec3(cos((i * 0.4 + 0.5) * M_PI), sin((i * 0.4 + 0.5) * M_PI), 0), color2));
    }

    for (int i = 0; i < 5; i++) {
        vertices.push_back(VertexFormat(
            center + radius2 * glm::vec3(cos((i * 0.4 + 0.7) * M_PI), sin((i * 0.4 + 0.7) * M_PI), 0), color2));
    }

    vertices.push_back(VertexFormat(center + glm::vec3(0, 0, -thickness), color1));
    vertices.push_back(VertexFormat(center + glm::vec3(0, 0, thickness), color1));

    vector<unsigned int> indices
    {
        0, 10, 5,
        5, 10, 1,
        1, 10, 6,
        6, 10, 2,
        2, 10, 7,
        7, 10, 3,
        3, 10, 8,
        8, 10, 4,
        4, 10, 9,
        9, 10, 0,
        0, 11, 5,
        5, 11, 1,
        1, 11, 6,
        6, 11, 2,
        2, 11, 7,
        7, 11, 3,
        3, 11, 8,
        8, 11, 4,
        4, 11, 9,
        9, 11, 0,
    };

    Mesh* star = new Mesh(name);
    star->InitFromData(vertices, indices);
    return star;
}
