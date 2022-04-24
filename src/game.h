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

class Game{
    private:
    // member variables
        GLFWwindow* m_window;
        Camera* m_camera;
        double xPosCursor, yPosCursor;
    // functions
        void processInput();
        void render();
    public:
        Game(int windowWidth, int windowHeight);
        ~Game();
        void renderLoop();
};