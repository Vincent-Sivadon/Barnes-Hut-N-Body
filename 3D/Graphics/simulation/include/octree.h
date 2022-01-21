/*
    Un octree est une boite dans l'espace, avec 8 enfants
    qui sont eux aussi des octrees avec des boites correspondant
    à des sous espace de leur parent.
    On divise l'espace avec cette structure jusqu'à ce que
    chaque sous octree ne contiennt qu'une particule
*/

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

    // Initialise les enfants de cet octree
    void subdivide();
    // Insert le corps d'indice i dans l'octree
    void insert(u64 i, glm::mat4 * mM);
    // supprime l'espace mémoire allouée par cet octree et ses enfants
    void destroy();
};

