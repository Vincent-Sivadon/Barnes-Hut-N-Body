#pragma once

#include "glm.hpp"
#include "gtc/matrix_transform.hpp"
#include "gtc/type_ptr.hpp"

#include "octree.h"

typedef unsigned long long u64;

// Mise à jour des positions de la simulation
// le vecteur position d'un corps est la 4ème colonne de la matrice de modèle
void update(glm::mat4* mM, glm::vec3* vel, glm::vec3* acc, u64 N, Box box);

