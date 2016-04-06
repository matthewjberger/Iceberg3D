#include "TransformManager.h"

TransformManager::TransformManager()
{
    modelMatrix_ = glm::mat4(1.0f);
}

TransformManager::~TransformManager()
{
    
}

glm::mat4 TransformManager::model_matrix() const
{
    return modelMatrix_;
}

void TransformManager::rotate(float angle_in_degrees, glm::vec3 rotationAxes)
{
    modelMatrix_ = glm::rotate(modelMatrix_, angle_in_degrees, rotationAxes);
}

void TransformManager::rotate(glm::mat4 base, float angle_in_degrees, glm::vec3 rotationAxes)
{
    modelMatrix_ = glm::rotate(base, angle_in_degrees, rotationAxes);
}

void TransformManager::scale(glm::vec3 scale)
{
    modelMatrix_ = glm::scale(modelMatrix_, scale);
}

void TransformManager::scale(glm::mat4 base, glm::vec3 scale)
{
    modelMatrix_ = glm::scale(base, scale);
}

void TransformManager::translate(glm::vec3 position)
{
    modelMatrix_ = glm::translate(modelMatrix_, position);
}

void TransformManager::translate(glm::mat4 base, glm::vec3 position)
{
    modelMatrix_ = glm::translate(base, position);
}

void TransformManager::assign_model(glm::mat4 matrix)
{
    modelMatrix_ = matrix;
}

