#include "particle.h"

Particle::Particle(glm::vec3 pos)
    : Square(glm::vec3{pos.x*10, pos.y*10, pos.z})
{

}
void Particle::move(glm::vec2 direction){
    m_position += glm::vec3{direction.x * 10, direction.y * 10, 0.0f};
}