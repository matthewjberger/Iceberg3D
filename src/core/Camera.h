#ifndef __CAMERA_H
#define __CAMERA_H

#include "GlobalIncludes.h"

class Camera
{
    public:

        Camera(vec3 pos = vec3(0.0f));
        ~Camera();

        void Update(mat4 &Projection, mat4 &ModelView);

        float GetPitchSensitivity()
        {
            return pitchSensitivity;
        }

        void SetPitchSensitivity(float newSens)
        {
            pitchSensitivity = newSens;
        }

        float GetYawSensitivity()
        {
            return yawSensitivity;
        }

        void SetYawSensitivity(float newSens)
        {
            yawSensitivity = newSens;
        }

    private:

        vec3 position;
        vec3 direction;
        vec3 right;
        vec3 up;

        float horizontalAngle;
        float verticalAngle;

        float initialFOV;
        float curFOV;

        float speed;
        float pitchSensitivity;
        float yawSensitivity;

        int mouseX;
        int mouseY;

        bool forward;
};

#endif
