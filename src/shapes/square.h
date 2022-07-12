#pragma once

// OPENGL
#include <glad/glad.h>
#include <GLFW/glfw3.h>

// shaders
#include "../rendering/shader.h"
#include "../resource_handling/resourceManager.h"

// math
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

/**
 * @brief Generate a shape with a position, color, rotation,...
 * 
 */
class Square{
    protected:
        glm::vec3 m_position;
        glm::vec3 m_scale;

        glm::vec4 m_color;

        unsigned int VAO; // the Vertex Array Object
    public:
        // constructor
        Square(glm::vec3 pos = glm::vec3{0.0f, 0.0f, 0.0f}); 
        void setPosition(glm::vec3 pos);

        void draw() const;
};