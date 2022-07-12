#include "world.h"

World::World()
{
    for (auto &row : m_particles)
    {
        for (auto &particle : row)
            particle = nullptr;
    }
    m_particles[0][0] = new Particle{glm::vec3{0.0f, 0.0f, 0.0f}};
    m_particles[0][1] = new Particle{glm::vec3{1.0f, 0.0f, 0.0f}};
}

void World::draw() const
{
    for (const auto &row : m_particles)
    {
        for (const auto &particle : row)
            if (particle != nullptr)
                particle->draw();
    }
}

void World::addParticle(glm::vec2 pos)
{
    int x = static_cast<int>(pos.x), y = static_cast<int>(pos.y);
    std::cout << "particle at coord: "
              << "(" << x << ", " << y << " )" << std::endl;
    if (x < 0 || x >= 100 || y > 0 || y <= -100)
        return;
    m_particles[-y][x] = new Particle{glm::vec3{x, y, 0.0f}};
}

void World::removeParticle(glm::vec2 pos)
{
    int x = static_cast<int>(pos.x), y = static_cast<int>(pos.y);
    std::cout << "particle at coord: "
              << "(" << pos.x << ", " << pos.y << " )" << std::endl;
    if (x < 0 || x >= 100 || y > 0 || y <= -100 || m_particles[y][x] == nullptr)
        return;
    delete m_particles[-y][x];
    m_particles[-y][x] = nullptr;
}

void World::moveParticle(glm::vec2 posFrom, glm::vec2 posTo)
{
    int xFrom = static_cast<int>(posFrom.x), yFrom = static_cast<int>(posFrom.y);
    int xTo = static_cast<int>(posTo.x), yTo = static_cast<int>(posTo.y);
    if (m_particles[yFrom][xFrom] == nullptr)
        return;
    m_particles[yTo][xTo] = m_particles[yFrom][xFrom];
    m_particles[yFrom][xFrom] = nullptr;
    m_particles[yTo][xTo]->move(glm::vec2{posTo.x - posFrom.x, -(posTo.y - posFrom.y)});
}

void World::handleTime(float dt)
{
    timePassed += dt;
    if (timePassed < 0.1667f)
        return;
    std::cout << "dropping particle" << std::endl;
    timePassed = 0.0f;
    for (int i = 0; i < 100; i++)
    {
        for (int j = 0; j < 100; j++)
            if (m_particles[i][j] != nullptr)
                dropParticle(j, i);
    }
}

void World::dropParticle(int x, int y)
{
    if (y + 1 >= 100)
        return;
    else if (m_particles[y + 1][x] == nullptr)
        moveParticle(glm::vec2(x, y), glm::vec2(x, y + 1));
    else if (x >= 0 && m_particles[y + 1][x - 1] == nullptr)
        moveParticle(glm::vec2(x, y), glm::vec2(x - 1, y + 1));
    else if (x < 100 && m_particles[y + 1][x + 1] == nullptr)
        moveParticle(glm::vec2(x, y), glm::vec2(x + 1, y + 1));
}