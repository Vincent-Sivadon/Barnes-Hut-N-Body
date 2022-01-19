#include "init.h"

#include <math.h>

#include <iostream>

float randAroundZero(float size)
{
    return 2 * size * (float)rand() / (float) RAND_MAX - size;
} 


glm::mat4* initMat(u64 N, float size)
{
    glm::mat4* modelMatrices;
    modelMatrices = new glm::mat4[N];

    // rand seed init
    srand(getpid()); 

    for (u64 i = 0 ; i < N/2 ; i++)
    {
        glm::mat4 model = glm::mat4(1.0f);
        float r = randAroundZero(size/3) + size/3;
        float theta = randAroundZero(3.1415/2) + 3.1415;
        float phi   = randAroundZero(3.1415);
        float x = r * cos(phi) * sin(theta) - size/2;
        float y = r * sin(theta) * sin(phi);
        float z = r * cos(theta);
        model = glm::translate(model, glm::vec3(x, y, z));

        // 2. scale: Scale between 0.05 and 0.25f
        float scale = randAroundZero(0.01) + 0.02;
        model = glm::scale(model, glm::vec3(scale));

        // 3. rotation: add random rotation around a (semi)randomly picked rotation axis vector
        float rotAngle = static_cast<float>((rand() % 360));
        model = glm::rotate(model, rotAngle, glm::vec3(0.4f, 0.6f, 0.8f));

        // 4. now add to list of matrices
        modelMatrices[i] = model;
    }

    for (u64 i = N/2; i < N; i++)
    {
        glm::mat4 model = glm::mat4(1.0f);
        float r = randAroundZero(size/3) + size/3;
        float theta = randAroundZero(3.1415/2) + 3.1415/2;
        float phi   = randAroundZero(2* 3.1415) + 3.1415;
        float x = r * cos(phi) * sin(theta) + size/2;
        float y = r * sin(theta) * sin(phi);
        float z = r * cos(theta);
        model = glm::translate(model, glm::vec3(x, y, z));

        // 2. scale: Scale between 0.05 and 0.25f
        float scale = randAroundZero(0.02) + 0.02;
        model = glm::scale(model, glm::vec3(scale));

        // 3. rotation: add random rotation around a (semi)randomly picked rotation axis vector
        float rotAngle = static_cast<float>((rand() % 360));
        model = glm::rotate(model, rotAngle, glm::vec3(0.4f, 0.6f, 0.8f));

        // 4. now add to list of matrices
        modelMatrices[i] = model;
    }

    return modelMatrices;
}

glm::vec3* initVel(u64 N)
{
    glm::vec3* velocities;
    velocities = new glm::vec3[N];

    for (u64 i = 0; i < N; i++)
    {
        float vx = randAroundZero(0.1);
        float vy = randAroundZero(0.1);
        float vz = randAroundZero(0.1);
        velocities[i] = glm::vec3(0,0,0);
    }

    return velocities;
}