#include "ExampleState.h"
#include "GlobalIncludes.h"

using namespace iceberg;

void ExampleState::pause() {}
void ExampleState::resume() {}
void ExampleState::finalize() {}
void ExampleState::handle_events() {}
void ExampleState::update(){}

void ExampleState::initialize()
{
    // Specify vertices
    glm::vec3 quadVertices[] =
    {
        // Top Left
        glm::vec3( -0.5f,  0.5f, 0.0f),

        // Top Right
        glm::vec3(  0.5f,  0.5f, 0.0f),  

        // Bottom Left
        glm::vec3( -0.5f, -0.5f, 0.0f), 

        // Bottom Right
        glm::vec3(  0.5f, -0.5f, 0.0f)
    };

    // Specify texture coordinates
    glm::vec2 quadUVCoords[] = 
    {
      glm::vec2(0.0f, 1.0f),
      glm::vec2(1.0f, 1.0f),
      glm::vec2(0.0f, 0.0f),
      glm::vec2(1.0f, 0.0f)
    };

    // Specify indices
    GLuint indices[] = 
    {
        1, 2, 0, // First triangle
        2, 1, 3  // Second Triangle
    };

    // Create and fill buffers and configure the VAO
    quadVAO = std::make_unique<VAO>();
    quadVBO = std::make_unique<VBO>();
    quadIBO = std::make_unique<VBO>();

    quadVAO->create();
    quadVBO->create();
    quadIBO->create();

    quadVAO->bind();

        // VBO
        quadVBO->bind();
        for(int i = 0; i < 4; i++)
        {
            quadVBO->add_data(&quadVertices[i], sizeof(glm::vec3));
            quadVBO->add_data(&quadUVCoords[i], sizeof(glm::vec2));
        }
        quadVBO->upload_data();

        // IBO
        quadIBO->bind(GL_ELEMENT_ARRAY_BUFFER);
        quadIBO->add_data(&indices, sizeof(indices));
        quadIBO->upload_data();

        // Configuring vertex attributes must be done last
        quadVAO->enable_attribute(0); // Position
        quadVAO->configure_attribute(0, 3, GL_FLOAT, GL_FALSE, sizeof(glm::vec3) + sizeof(glm::vec2), 0);

        quadVAO->enable_attribute(1); // Texture Coordinates
        quadVAO->configure_attribute(1, 2, GL_FLOAT, GL_FALSE, sizeof(glm::vec3) + sizeof(glm::vec2), (GLvoid*)sizeof(glm::vec3));

    quadVAO->unbind();

    // Create the shader program
    quadProgram = std::make_unique<ShaderProgram>();
    quadProgram->create_program();
    quadProgram->add_shader_from_file("shaders/quadVert.glsl", GL_VERTEX_SHADER);
    quadProgram->add_shader_from_file("shaders/quadFrag.glsl", GL_FRAGMENT_SHADER);
    quadProgram->link_program();

    // Load the texture
    quadTexture = std::make_unique<Texture>();
    quadTexture->load("assets/iceberg.png");
}

void ExampleState::draw()
{
    // Build a model-view-projection matrix
    static glm::mat4 projectionMatrix = glm::perspective(45.0f, 3.0f / 4.0f, 0.1f, 100.0f);
    static glm::mat4 viewMatrix = glm::lookAt(glm::vec3(0.0f, 0.0f, -2.0f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f));
    static TransformManager transformManager; // Manages the model matrix transformations
    static glm::mat4 mvpMatrix;
 
    quadProgram->use();
    quadVAO->bind();

    quadTexture->bind();

    // Rotate the quad's model matrix and assign it to the quad in the shader
    transformManager.rotate(glm::mat4(1.0f), sin(static_cast<float>(glfwGetTime())) * 0.5f, glm::vec3(0.0f, 1.0f, 0.0f));
    mvpMatrix = projectionMatrix * viewMatrix * transformManager.model_matrix();
    quadProgram->set_uniform("mvpMatrix", mvpMatrix);

    // Draw the quad
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

    quadVAO->unbind();
}