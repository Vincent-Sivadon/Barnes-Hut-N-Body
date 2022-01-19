#pragma once

#include <stdlib.h>
#include <math.h>
#include <stdbool.h>

#include "glm.hpp"
#include "gtc/matrix_transform.hpp"
#include "gtc/type_ptr.hpp"

#include "box.h"

typedef unsigned long long u64;


struct Octree {
    Box box;
    u64 size;
    u64 id;
    bool isDivided;

    Octree* subtrees[2][2][2];

    // Constructeur
    Octree(Box box) : box(box), size(0), isDivided(false), id(-1) {}

    void subdivide();
    void insert(u64 i, glm::mat4 * mM);
    void destroy();
};

