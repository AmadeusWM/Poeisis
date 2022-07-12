#pragma once
// other
#include <glm/glm.hpp>
// project
#include "../../shapes/square.h"

class Particle : public Square{
    private:
    public:
        Particle(glm::vec3 pos);
        void move(glm::vec2 direction);
};