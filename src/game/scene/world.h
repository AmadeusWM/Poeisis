#pragma once
// other
#include <glm/glm.hpp>
// project
#include "../particles/particle.h"

class World {
    private:
        Particle* m_particles[100][100];
        float timePassed = 0.0f;
        void dropParticle(int x, int y);
    public:
        World();
        void draw() const;
        void addParticle(glm::vec2 pos);
        void removeParticle(glm::vec2 pos);
        void moveParticle(glm::vec2 posFrom, glm::vec2 posTo);
        void handleTime(float dt);
};