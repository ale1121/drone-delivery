#pragma once

#include "utils/glm_utils.h"
#include "drone_delivery/Tree.h"


namespace m1
{
    class ChristmasTree : public Tree
    {
    public:
        ChristmasTree();
        ChristmasTree(int x, int z);

        glm::vec3 starPosition;
    };
}  
