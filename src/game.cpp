#include "game.h"
// cpp headers
#include <iostream>

void framebuffer_size_callback(GLFWwindow *window, int width, int height);

/**
 * @brief Construct a new Game:: Game object
 *
 * @param windowWidth : width of the game window
 * @param windowHeight : height of the game window
 */
Game::Game(int windowWidth, int windowHeight)
{
    glfwInit();                                                    // initialize GLFW
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);                 // version 3
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 4);                 // version 3
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE); // we use the core profile (GLAD)

    m_window = glfwCreateWindow(windowWidth, windowHeight, "Spring Mass Simulator", NULL, NULL);
    if (m_window == NULL)
    {
        std::cout << "Failed to create a GLFW window" << std::endl;
        glfwTerminate();
    }
    glfwMakeContextCurrent(m_window);

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "Failed to initialize GLAD." << std::endl;
        glfwTerminate();
        exit(3);
    }
    glViewport(0, 0, windowWidth, windowHeight);
    // framebuffersize callback to change the screen width and height
    glfwSetFramebufferSizeCallback(m_window, framebuffer_size_callback);
    glEnable(GL_DEPTH_TEST);
    // init shader objects
    Shader particle_shader = ResourceManager::loadShader("particles/particle_shader.vert", "particles/particle_shader.frag", nullptr, "particle_shader");

    // init perspective projection matrix
    glm::mat4 projection = glm::ortho(0.0f, static_cast<float>(windowWidth), 0.0f, static_cast<float>(windowHeight), -1.0f, 100.0f); // for ortho view matrix
    // glm::mat4 projection = glm::perspective(glm::radians(45.0f), (float)windowWidth / (float)windowHeight, 0.1f, 1000.0f);
    particle_shader.setMatrix4("projection", projection, true);

    // init camera for camera view matrix etc.
    m_camera = new Camera{glm::vec3{-windowWidth/2, -windowHeight/2, 20.0f}};
    // init world
    m_world = new World{};
}

Game::~Game()
{
    delete m_camera;
}

void Game::renderLoop()
{
	m_dt = 0.0f;
	float oldTime = 0.0f;
    while (!glfwWindowShouldClose(m_window))
    {
        // handle delta time
        float newTime = glfwGetTime();
        m_dt = newTime - oldTime;
		if (m_dt > 0.1f) { m_dt = 0.1f; }
        oldTime = newTime;
        // input
        processInput();

        // rendering commands
        glClearColor(0.0f, 0.0f, 0.0f, 1.0f);               // sets the clear color
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); // uses clear color
        // do main functions
        render();

        // check and call events and swap the buffers
        glfwSwapBuffers(m_window);
        glfwPollEvents();
    }
    glfwTerminate();
}

// process all input: query GLFW whether relevant keys are pressed/released this frame and react accordingly
// ---------------------------------------------------------------------------------------------------------
void Game::processInput()
{
    // set view matrix uniform according to current camera position
    // m_camera->ProcessMouseMovement(xPosCursor - xPosPrev, yPosCursor - yPosPrev);
    glfwGetCursorPos(m_window, &xPosCursor, &yPosCursor);

    if (glfwGetKey(m_window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(m_window, true);
    // if (glfwGetKey(m_window, GLFW_KEY_W) == GLFW_PRESS)
    //     m_camera->ProcessKeyboard(Camera_Movement::FORWARD, 0.1);
    // if (glfwGetKey(m_window, GLFW_KEY_S) == GLFW_PRESS)
    //     m_camera->ProcessKeyboard(Camera_Movement::BACKWARD, 0.1);
    if (glfwGetKey(m_window, GLFW_KEY_A) == GLFW_PRESS)
        m_camera->ProcessKeyboard(Camera_Movement::LEFT, 0.1);
    if (glfwGetKey(m_window, GLFW_KEY_D) == GLFW_PRESS)
        m_camera->ProcessKeyboard(Camera_Movement::RIGHT, 0.1);
    if (glfwGetKey(m_window, GLFW_KEY_SPACE) == GLFW_PRESS)
        m_camera->ProcessKeyboard(Camera_Movement::UP, 0.1);
    if (glfwGetKey(m_window, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS)
        m_camera->ProcessKeyboard(Camera_Movement::DOWN, 0.1);
    if (glfwGetMouseButton(m_window, GLFW_MOUSE_BUTTON_LEFT) == GLFW_PRESS){
        m_world->addParticle(mousePositionWorld());
    }
    if (glfwGetMouseButton(m_window, GLFW_MOUSE_BUTTON_RIGHT) == GLFW_PRESS){
        m_world->removeParticle(mousePositionWorld());
    }

}
/**
 * @brief : Draw every object and determine view matrix
 *
 */
void Game::render()
{
    Shader shader = ResourceManager::getShader("particle_shader").use();
    glm::mat4 view = m_camera->GetViewMatrix();
    shader.setMatrix4("view", view); // set the uniform
    m_world->handleTime(m_dt);
    m_world->draw();
}

/**
 * @brief changes the width and height of the viewport from the current window
 *
 * @param window : current window
 * @param width : new width
 * @param height : new height
 */
void framebuffer_size_callback(GLFWwindow *window, int width, int height)
{
    glViewport(0, 0, width, height);
}


glm::vec2 Game::mousePositionWorld() const{
    int width, height;
    glfwGetWindowSize(m_window, &width, &height);

    glm::vec3 camPos = m_camera->Position;
    float xWorld = camPos.x / 10 + (xPosCursor) / 10;
    float yWorld = camPos.y / 10 - (yPosCursor - height) / 10;

    glm::vec2 posWorld{xWorld, yWorld};
    return posWorld;
}