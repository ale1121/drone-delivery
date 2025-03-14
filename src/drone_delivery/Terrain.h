#pragma once

#include "utils/glm_utils.h"
#include "core/gpu/mesh.h"


namespace m1
{
    class Terrain2
    {
    public:
        Terrain2();
        ~Terrain2();
        void Init(int N);

        Mesh* mesh;
    };
}
