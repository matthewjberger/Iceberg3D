#ifndef __CAMERA_H
#define __CAMERA_H

#include "GlobalIncludes.h"

class Camera
{
    public:

        Camera(glm::vec3 position = glm::vec3(0.0f), float speed = 0.7);
        ~Camera();

        void Update();

        // Membor Accessors
        float GetPitchSensitivity();
        void  SetPitchSensitivity(float newSens);
        float GetYawSensitivity();
        void  SetYawSensitivity(float newSens);

        void EnableInput(bool enabled = true);
        void LookAt(glm::vec3 position, glm::vec3 focusPoint, glm::vec3 up);

        glm::mat4 GetMVP(glm::mat4 &modelMatrix);

    private:

        glm::mat4 projectionMatrix;
        glm::mat4 viewMatrix;

        bool inputEnabled;

        glm::vec3 position;
        glm::vec3 direction;
        glm::vec3 right;
        glm::vec3 up;

        float horizontalAngle;
        float verticalAngle;

        float initialFOV;
        float curFOV;

        float speed;
        float pitchSensitivity;
        float yawSensitivity;

        int mouseX;
        int mouseY;

};

#endif
