#ifndef TRANSFORM_MANAGER_H
#define TRANSFORM_MANAGER_H

#include "GlobalIncludes.h"

namespace iceberg
{
    class ICEBERGAPI TransformManager
    {
    public:
        TransformManager();
        ~TransformManager();

        glm::mat4 model_matrix() const;

        // Transformations
        void scale(glm::vec3 scale);
        void scale(glm::mat4 base, glm::vec3 scale);

        void rotate(float angle_in_degrees, glm::vec3 rotationAxes);
        void rotate(glm::mat4 base, float angle_in_degrees, glm::vec3 rotationAxes);

        void translate(glm::vec3 position);
        void translate(glm::mat4 base, glm::vec3 position);

        void assign_model(glm::mat4 matrix);

    private:
        glm::mat4 modelMatrix_;
    };
}
#endif