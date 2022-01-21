/*
    Initialisation de la simulation  
*/

#pragma once

#include <unistd.h>

#include "glm.hpp"
#include "gtc/matrix_transform.hpp"
#include "gtc/type_ptr.hpp"

typedef unsigned long long u64;

// Fonctions d'initalisation des positions, vitesses, et modèles instanciés (OpenGL)
glm::mat4* initMat(u64 N, float size);
glm::vec3* initVel(u64 N);