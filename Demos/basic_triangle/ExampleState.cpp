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
    glm::vec3 triangleVertices[] =
    {
        // Top Middle - Red
        glm::vec3( 0.0f,  0.5f, 0.0f),  glm::vec3(1.0f, 0.0f, 0.0f),

        // Bottom Right - Green
        glm::vec3( 0.5f, -0.5f, 0.0f),  glm::vec3(0.0f, 1.0f, 0.0f),

        // Bottom Left - Blue
        glm::vec3(-0.5f,  -0.5f, 0.0f), glm::vec3(0.0f, 0.0f, 1.0f)
    };

    // Create and fill the Vertex Buffer, and configure the VAO
    triVAO = std::make_shared<VAO>();
    triVBO = std::make_shared<Buffer>();

    triVAO->bind();
        triVBO->bind();
        triVBO->add_data(&triangleVertices, sizeof(glm::vec3) * 6);
        triVBO->upload_data();

        // Configuring vertex attributes must be done last
        triVAO->enable_attribute(0); // Position
        triVAO->configure_attribute(0, 3, GL_FLOAT, GL_FALSE, sizeof(glm::vec3) * 2, 0);

        triVAO->enable_attribute(1); // Color
        triVAO->configure_attribute(1, 3, GL_FLOAT, GL_FALSE, sizeof(glm::vec3) * 2, (GLvoid*)sizeof(glm::vec3));
    triVAO->unbind();

    // Create the shader program
    triProgram = std::make_shared<ShaderProgram>();
    triProgram->create_program();
    triProgram->add_shader_from_file("shaders/triVert.glsl", GL_VERTEX_SHADER);
    triProgram->add_shader_from_file("shaders/triFrag.glsl", GL_FRAGMENT_SHADER);
    triProgram->link_program();
}

void ExampleState::draw()
{
    triProgram->use();
    triVAO->bind();
    glDrawArrays(GL_TRIANGLES, 0, 3);
    triVAO->unbind();
}