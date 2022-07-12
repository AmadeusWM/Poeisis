#include "square.h"

Square::Square(glm::vec3 pos)
    : m_position{pos}
{
    // basic information
    m_color = glm::vec4{0.5f,0.5f,0.5f,1.0f};
    m_scale = glm::vec3{10.0f,10.0f,10.0f};
    // vertices and indices
    float vertices[] = {
        0.0f,  1.0f, 0.0f,
        1.0f, 0.0f, 0.0f,
        0.0f, 0.0f, 0.0f,
        1.0f,  1.0f, 0.0f
    };
	unsigned int indices[] = {
		0, 1, 2,
		0, 1, 3};
    // generate vertex arrays object and vertex buffer object
    glGenVertexArrays(1, &VAO);

    unsigned int VBO; // id of VBO
    unsigned int EBO; // id of EBO
    glGenBuffers(1, &VBO);
	glGenBuffers(1, &EBO);
    // bind VAO
    glBindVertexArray(VAO);
    // copy vertices array in buffer
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_DYNAMIC_DRAW);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_DYNAMIC_DRAW);
    // set vertex attribute pointers
    glEnableVertexAttribArray(0); // enables the vertex attribute
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*) 0);
    // unbind VBO
    glBindBuffer(GL_ARRAY_BUFFER, 0); 

    // unbind VAO
    glBindVertexArray(0);
}


/**
 * @brief sets the current position of the shape
 * 
 * @param pos 
 */
void Square::setPosition(glm::vec3 pos){
    m_position = pos;
}

/**
 * @brief Draw the particle
 * 
 * @param shader 
 */
void Square::draw() const{
    // set model matrix
    glm::mat4 model = glm::mat4{1.0f};
    // translate
    model = glm::translate(model, m_position);
    // scale
    model = glm::scale(model, m_scale);

    // set the model uniform
    Shader shader = ResourceManager::getShader("particle_shader");
    // if (&shader == nullptr){
    //     return;
    // }
    shader.use();
    shader.setMatrix4("model", model);

    // set the color uniform
    shader.setVector4f("objectColor", m_color, false);

    // bind vao
    glBindVertexArray(VAO);
    // draw the cube
	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
    glBindVertexArray(0);
}
