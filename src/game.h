#pragma once
// OPENGL
#include <glad/glad.h>
#include <GLFW/glfw3.h>
// math
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
// c++ functions
#include <vector>
// headerfiles project
#include "../libs/camera.h"
#include "game//scene/world.h"
// resources
#include "resource_handling/resourceManager.h"

class Game{
    private:
    // member variables
        GLFWwindow* m_window;
        Camera* m_camera;
        float m_dt;
        double xPosCursor, yPosCursor;
        World* m_world;
    // methods
        void processInput();
        void render();
        glm::vec2 mousePositionWorld() const;
    public:
        Game(int windowWidth, int windowHeight);
        ~Game();
    // public methods
        void renderLoop();
};