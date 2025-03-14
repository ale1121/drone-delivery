#include <vector>
#include "drone_delivery/Terrain.h"
#include "drone_delivery/object3D.h"

using namespace std;
using namespace m1;


Terrain2::Terrain2()
{
}


Terrain2::~Terrain2()
{
}

void Terrain2::Init(int N)
{
    N *= 5;
    vector<VertexFormat> vertices;
    for (int i = 0; i < N + 1; i++) {
        for (int j = 0; j < N + 1; j++) {
            vertices.push_back(VertexFormat(glm::vec3((float)i/5, 0, (float)j/5), glm::vec3(0.5, 0.5, 1)));
        }
    }

    vector<unsigned int> indices;
    indices.reserve(6 * N * N);

    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            int corner = i * (N + 1) + j;
            indices.push_back(corner);
            indices.push_back(corner + 1);
            indices.push_back(corner + N + 2);

            indices.push_back(corner);
            indices.push_back(corner + N + 2);
            indices.push_back(corner + N + 1);
        }
    }

    mesh = object3D::CreateMesh("terrain", vertices, indices);
}
