#include "CIntroState.h"
#include "Globals.h"

IntroState *IntroState::inst = 0;

void IntroState::Init(Game *game)
{
    printf("Intro Init\n");

    // Initialize variables
    angle = 0.0f;

    vec3 pyramidPositions[] =
    {
        // Front face
        glm::vec3(0.0f, 0.5f, 0.0f),
        glm::vec3(-0.5f, -0.5f, 0.5f),
        glm::vec3(0.5f, -0.5f, 0.5f),

        // Back face
        glm::vec3(0.0f, 0.5f, 0.0f),
        glm::vec3(0.5f, -0.5f, -0.5f),
        glm::vec3(-0.5f, -0.5f, -0.5f),

        // Left face
        glm::vec3(0.0f, 0.5f, 0.0f), 
        glm::vec3(-0.5f, -0.5f, -0.5f),
        glm::vec3(-0.5f, -0.5f, 0.5f),

        // Right face
        glm::vec3(0.0f, 0.5f, 0.0f),
        glm::vec3(0.5f, -0.5f, 0.5f), 
        glm::vec3(0.5f, -0.5f, -0.5f)
    };

    vec2 texCoordsPyramid[] =
    {
        glm::vec2(0.5f, 1.0f), glm::vec2(0.0f, 0.0f), glm::vec2(1.0f, 0.0f)
    };

    vec3 vertexPositions[] =
    {
        // Front face
        glm::vec3(-0.5f, 0.5f, 0.5f),
        glm::vec3(0.5f, 0.5f, 0.5f), 
        glm::vec3(0.5f, -0.5f, 0.5f),
        glm::vec3(0.5f, -0.5f, 0.5f),
        glm::vec3(-0.5f, -0.5f, 0.5f), 
        glm::vec3(-0.5f, 0.5f, 0.5f),
        // Back face
        glm::vec3(0.5f, 0.5f, -0.5f), glm::vec3(-0.5f, 0.5f, -0.5f), glm::vec3(-0.5f, -0.5f, -0.5f), glm::vec3(-0.5f, -0.5f, -0.5f), glm::vec3(0.5f, -0.5f, -0.5f), glm::vec3(0.5f, 0.5f, -0.5f),
        // Left face
        glm::vec3(-0.5f, 0.5f, -0.5f), glm::vec3(-0.5f, 0.5f, 0.5f), glm::vec3(-0.5f, -0.5f, 0.5f), glm::vec3(-0.5f, -0.5f, 0.5f), glm::vec3(-0.5f, -0.5f, -0.5f), glm::vec3(-0.5f, 0.5f, -0.5f),
        // Right face
        glm::vec3(0.5f, 0.5f, 0.5f), glm::vec3(0.5f, 0.5f, -0.5f), glm::vec3(0.5f, -0.5f, -0.5f), glm::vec3(0.5f, -0.5f, -0.5f), glm::vec3(0.5f, -0.5f, 0.5f), glm::vec3(0.5f, 0.5f, 0.5f),
        // Top face
        glm::vec3(-0.5f, 0.5f, -0.5f), glm::vec3(0.5f, 0.5f, -0.5f), glm::vec3(0.5f, 0.5f, 0.5f), glm::vec3(0.5f, 0.5f, 0.5f), glm::vec3(-0.5f, 0.5f, 0.5f), glm::vec3(-0.5f, 0.5f, -0.5f),
        // Bottom face
        glm::vec3(-0.5f, -0.5f, 0.5f), glm::vec3(0.5f, -0.5f, 0.5f), glm::vec3(0.5f, -0.5f, -0.5f), glm::vec3(0.5f, -0.5f, -0.5f), glm::vec3(-0.5f, -0.5f, -0.5f), glm::vec3(-0.5f, -0.5f, 0.5f),

        // Floor
        vec3(-100.0f, -3.0f, -100.0f), // top left  
        vec3( 100.0f, -3.0f, -100.0f), // top right
        vec3(100.0f, -3.0f, 100.0f), // bottom right

        vec3(100.0f, -3.0f, 100.0f), // bottom right
        vec3(-100.0f, -3.0f,  100.0f), // bottom left
        vec3(-100.0f, -3.0f, -100.0f), // top left  

    };

    vec2 textureCoords[] = 
    {
        glm::vec2(0.0f, 1.0f), glm::vec2(1.0f, 1.0f), glm::vec2(1.0f, 0.0f), glm::vec2(1.0f, 0.0f), glm::vec2(0.0f, 0.0f), glm::vec2(0.0f, 1.0f)
    };

    triVAO.Create();
    triVAO.Bind();

    // Create the buffer
    triVBO.Create();

    // Bind VBO for use
    triVBO.Bind();

    // Add vertex data
    for (int i = 0; i < (sizeof(vertexPositions)/sizeof(*vertexPositions)); i++)
    {
        triVBO.AddData(&vertexPositions[i], sizeof(vec3));
        triVBO.AddData(&textureCoords[i%6], sizeof(vec2));
    }

    // Add vertex data
    for (int i = 0; i < (sizeof(pyramidPositions)/sizeof(*pyramidPositions)); i++)
    {
        triVBO.AddData(&pyramidPositions[i], sizeof(vec3));
        triVBO.AddData(&texCoordsPyramid[i % 3], sizeof(vec2));
    }

    // Upload data
    triVBO.UploadData(GL_STATIC_DRAW);

    // Enable vertex attributes
    triVAO.EnableAttribute(0);

    // Describe how to load data from currently bound VBO
    triVAO.ConfigureAttribute(0, 3, GL_FLOAT, GL_FALSE, sizeof(vec3)+sizeof(vec2), 0); // position

    // Enable texture coords
    triVAO.EnableAttribute(1); // texture

    // Describe how to load data
    triVAO.ConfigureAttribute(1, 2, GL_FLOAT, GL_FALSE, sizeof(vec3) + sizeof(vec2), (void *)sizeof(vec3)); // color

    triVAO.Unbind();

    // Create VAO
    colorVAO.Create();

    // Bind VAO for use
    colorVAO.Bind();

    // Enable vertex attributes
    colorVAO.EnableAttribute(0); // position

    // Describe how to load data from currently bound VBO
    colorVAO.ConfigureAttribute(0, 3, GL_FLOAT, GL_FALSE, sizeof(vec3)+sizeof(vec2), 0); // position

    // Unbind VAO
    colorVAO.Unbind();

    // Make shaders
    vShader.Load("Shaders/VertexShader.glvs", GL_VERTEX_SHADER);
    fShader.Load("Shaders/FragmentShader.glfs", GL_FRAGMENT_SHADER);

    vColorShader.Load("Shaders/ColorVertex.glvs", GL_VERTEX_SHADER);
    fColorShader.Load("Shaders/ColorFrag.glfs", GL_FRAGMENT_SHADER);

    // Create the program
    mainProg.CreateProgram();

    // Attach shaders
    mainProg.AddShader(&vShader);
    mainProg.AddShader(&fShader);

    // Delete shaders
    vShader.DeleteShader();
    fShader.DeleteShader();

    // Link Program
    mainProg.LinkProgram();

    // Create the program
    colorProg.CreateProgram();

    // Attach shaders
    colorProg.AddShader(&vColorShader);
    colorProg.AddShader(&fColorShader);

    // Link Program
    colorProg.LinkProgram();

    // Delete shaders
    vShader.DeleteShader();
    fShader.DeleteShader();

    vColorShader.DeleteShader();
    fColorShader.DeleteShader();

    // Use the program
    mainProg.UseProgram();

    // Load textures
    quadTexture.Load("Textures/blue.jpg", true);

    otherTexture.Load("Textures/companion.jpg", true);

    floorTexture.Load("Textures/floor.jpg", true);

    // Load Camera
    myCamera = new Camera(vec3(0, 4, 40));

}

void IntroState::Finalize()
{
    // Delete the program
    mainProg.DeleteProgram();
    colorProg.DeleteProgram();

    // Delete VAO
    triVAO.Free();
    colorVAO.Free();

    // Delete VBO
    triVBO.Free();

    // Delete texture
    quadTexture.Free();
    floorTexture.Free();
    otherTexture.Free();

    // Delete camera
    delete myCamera;

    printf("Intro Finalize");
}

void IntroState::Draw(Game *game)
{
    // Set clear color
    glClearColor(0.3f, 0.5f, 1.0f, 0.0f);

    // Clear the screen
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    // Enable textures
    glEnable(GL_TEXTURE_2D);

    // Use proper shader program
    mainProg.UseProgram();

    // Bind VAO for use
    triVAO.Bind();

    // Find shader variable locations
    ProjectionMatrixLoc = glGetUniformLocation(mainProg.GetID(), "projectionMatrix");
    ModelViewMatrixLoc = glGetUniformLocation(mainProg.GetID(), "modelViewMatrix");
    samplerLoc = glGetUniformLocation(mainProg.GetID(), "texture");

    // Send Projection Matrix data to shader
    glUniformMatrix4fv(ProjectionMatrixLoc, 1, GL_FALSE, value_ptr(ProjectionMatrix));

    // Send ModelView Matrix data to shader
    glUniformMatrix4fv(ModelViewMatrixLoc, 1, GL_FALSE, value_ptr(ModelViewMatrix));

    // Set sampler location
    glUniform1i(samplerLoc, 0);

    // Bind active texture
    floorTexture.Bind(0);

    // Draw here

    // Floor

    // Set floor to render at starting modelViewMat
    glUniformMatrix4fv(ModelViewMatrixLoc, 1, GL_FALSE, value_ptr(ModelViewMatrix));

    // Draw floor
    glDrawArrays(GL_TRIANGLES, 36, 6);

    // Bind active texture
    otherTexture.Bind(0);

    // Cube

    // Translate copy of modelView
    mat4 mCurrent = translate(ModelViewMatrix, vec3(-70.0f, 4.0f, -40.0f));

    // Translate copy of modelView
    mCurrent = translate(mCurrent, vec3(0.0f, -3*sin(angle), 0.0f));

    // Rotate copy of modelview
    mCurrent = rotate(mCurrent, angle, vec3(1.0f, 1.0f, 1.0f));

    // Rotate copy of modelview
    mCurrent = scale(mCurrent, vec3((abs(sin(angle)) + 1)*2.0f, (abs(sin(angle)) + 1)*2.0f, (abs(sin(angle)) + 1)*2.0f));

    // Update model view matrix with current matrix
    glUniformMatrix4fv(ModelViewMatrixLoc, 1, GL_FALSE, value_ptr(mCurrent));

    // Draw
    glDrawArrays(GL_TRIANGLES, 0, 36);

    // Cube

    // Translate copy of modelView
    mCurrent = translate(ModelViewMatrix, vec3(0.0f, 10.0f, -30.0f));

    // Translate copy of modelView
    mCurrent = translate(mCurrent, vec3(0.0f, 6 * sin(angle), 0.0f));

    // Rotate copy of modelview
    mCurrent = rotate(mCurrent, float(PI), vec3(0.0f, 0.0f, 1.0f));

    // Rotate copy of modelview
    mCurrent = rotate(mCurrent, angle, vec3(0.0f, 1.0f, 0.0f));

    // Rotate copy of modelview
    mCurrent = scale(mCurrent, vec3(8.0f, 8.0f, 8.0f));

    // Update model view matrix with current matrix
    glUniformMatrix4fv(ModelViewMatrixLoc, 1, GL_FALSE, value_ptr(mCurrent));

    // Draw
    glDrawArrays(GL_TRIANGLES, 0, 36);

    // Bind active texture
    quadTexture.Bind(0);

    // Pyramid

    // Translate copy of modelView
    mCurrent = translate(ModelViewMatrix, vec3(0.0f, 8.0f, -70.0f));

    // Translate copy of modelView
    mCurrent = translate(mCurrent, vec3(0.0f, 3*sin(angle), 0.0f));

    // Rotate copy of modelview
    mCurrent = rotate(mCurrent, angle, vec3(0.0f, 1.0f, 0.0f));

    // Rotate copy of modelview
    mCurrent = scale(mCurrent, vec3(10.0f, 10.0f, 10.0f));

    // Update model view matrix with current matrix
    glUniformMatrix4fv(ModelViewMatrixLoc, 1, GL_FALSE, value_ptr(mCurrent));

    // Draw
    glDrawArrays(GL_TRIANGLES, 42, 54);

    // Cube

    // Translate copy of modelView
    mCurrent = translate(ModelViewMatrix, vec3(-70.0f, 10.0f, -60.0f));

    // Translate copy of modelView
    mCurrent = translate(mCurrent, vec3(0.0f, 6 * sin(angle), 0.0f));

    // Rotate copy of modelview
    mCurrent = rotate(mCurrent, angle, vec3(1.0f, 1.0f, 1.0f));

    // Rotate copy of modelview
    mCurrent = scale(mCurrent, vec3(8.0f, 8.0f, 8.0f));

    // Update model view matrix with current matrix
    glUniformMatrix4fv(ModelViewMatrixLoc, 1, GL_FALSE, value_ptr(mCurrent));

    // Draw
    glDrawArrays(GL_TRIANGLES, 0, 36);

    // Pyramid

    // Translate copy of modelView
    mCurrent = translate(ModelViewMatrix, vec3(30.0f, 10.0f, 26.0f));

    // Translate copy of modelView
    mCurrent = translate(mCurrent, vec3(0.0f, -6*sin(angle), 0.0f));

    // Rotate copy of modelview
    mCurrent = rotate(mCurrent, angle, vec3(0.0f, 1.0f, 0.0f));

    // Rotate copy of modelview
    mCurrent = scale(mCurrent, vec3(6.0f, 6.0f, 6.0f));

    // Update model view matrix with current matrix
    glUniformMatrix4fv(ModelViewMatrixLoc, 1, GL_FALSE, value_ptr(mCurrent));

    // Draw
    glDrawArrays(GL_TRIANGLES, 42, 54);

    // Unbind VAO
    triVAO.Unbind();

    // Disuse shader program
    mainProg.DisUseProgram();

    // Disable textures
    glDisable(GL_TEXTURE_2D);

    // Use color program
    colorProg.UseProgram();

    // Bind color vao
    colorVAO.Bind();

    // Find shader variable locations
    ProjectionMatrixLoc = glGetUniformLocation(colorProg.GetID(), "projectionMatrix");
    ModelViewMatrixLoc = glGetUniformLocation(colorProg.GetID(), "modelViewMatrix");
    colorLoc = glGetUniformLocation(colorProg.GetID(), "color");

    // Send Projection Matrix data to shader
    glUniformMatrix4fv(ProjectionMatrixLoc, 1, GL_FALSE, value_ptr(ProjectionMatrix));

    // Enable blending
    glEnable(GL_BLEND);

    // Set blend mode
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    // Disable writing to depth buffer
    glDepthMask(0);

    // Cube 1
    // Translate copy of modelView
    mCurrent = translate(ModelViewMatrix, vec3(20.0f, 5.0f, 50.0f));

    // Rotate copy of modelview
    mCurrent = rotate(mCurrent, angle, vec3(0.0f, 0.0f, 1.0f));

    // Rotate copy of modelview
    mCurrent = scale(mCurrent, vec3(7.0f, 7.0f, 7.0f));

    // Update shader variables
    glUniformMatrix4fv(ModelViewMatrixLoc, 1, GL_FALSE, value_ptr(mCurrent));
    glUniform4fv(colorLoc, 1, glm::value_ptr(vec4(1.0f, 0.5f, 0.0f, 0.3f)));

    // Draw
    glDrawArrays(GL_TRIANGLES, 0, 36);

    // Cube 2

    // Translate copy of modelView
    mCurrent = translate(ModelViewMatrix, vec3(40.0f, 15.0f, -30.0f));

    // Rotate copy of modelview
    mCurrent = rotate(mCurrent, angle, vec3(0.0f, 1.0f, 1.0f));

    // Rotate copy of modelview
    mCurrent = scale(mCurrent, vec3(18.0f, 18.0f, 18.0f));

    // Update shader variables
    glUniformMatrix4fv(ModelViewMatrixLoc, 1, GL_FALSE, value_ptr(mCurrent));
    glUniform4fv(colorLoc, 1, glm::value_ptr(vec4(1.0f, 0.5f, 1.0f, 0.6f)));

    // Draw
    glDrawArrays(GL_TRIANGLES, 0, 36);


    // Cube 3

    // Translate copy of modelView
    mCurrent = translate(ModelViewMatrix, vec3(-10.0f, 7.0f, -10.0f));

    // Rotate copy of modelview
    mCurrent = rotate(mCurrent, angle, vec3(1.0f, 0.0f, 0.0f));

    // Rotate copy of modelview
    mCurrent = scale(mCurrent, vec3(4.0f, 4.0f, 4.0f));

    // Update shader variables
    glUniformMatrix4fv(ModelViewMatrixLoc, 1, GL_FALSE, value_ptr(mCurrent));
    glUniform4fv(colorLoc, 1, glm::value_ptr(vec4(0.0f, 1.0f, 0.5f, 0.2f)));

    // Draw
    glDrawArrays(GL_TRIANGLES, 0, 36);

    // Cube 4

    // Translate copy of modelView
    mCurrent = translate(ModelViewMatrix, vec3(60.0f, 8.0f, 0.0f));

    // Rotate copy of modelview
    mCurrent = rotate(mCurrent, angle, vec3(1.0f, 1.0f, 1.0f));

    // Rotate copy of modelview
    mCurrent = scale(mCurrent, vec3(10.0f, 10.0f, 10.0f));

    // Update shader variables
    glUniformMatrix4fv(ModelViewMatrixLoc, 1, GL_FALSE, value_ptr(mCurrent));
    glUniform4fv(colorLoc, 1, glm::value_ptr(vec4(0.40f, 0.8f, 0.2f, 0.3f)));

    // Draw
    glDrawArrays(GL_TRIANGLES, 0, 36);

    // Disable blending
    glDisable(GL_BLEND);

    // Enable writing to depth buffer
    glDepthMask(1); 

    // Unbind color VAO
    colorVAO.Unbind();

    // Disuse color program
    colorProg.DisUseProgram();
}

void IntroState::Update(Game *game)
{
    angle += DEGREES_TO_RADIANS(3);

    if (angle > 2*PI)
    {
        angle = 0;
    }

    myCamera->Update(ProjectionMatrix, ModelViewMatrix);

    // Update Matrices
    glUniform4fv(ProjectionMatrixLoc, 1, value_ptr(ProjectionMatrix));
    glUniform4fv(ModelViewMatrixLoc, 1, value_ptr(ModelViewMatrix));
}

void IntroState::HandleEvents(Game *game)
{
    SDL_Event event = game->GetEvent();
}

void IntroState::Pause()
{
    printf("Intro Paused\n");
}
void IntroState::Resume()
{
    printf("Intro Resumed\n");
}

