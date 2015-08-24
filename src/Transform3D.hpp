#ifndef Transform3D_h
#define Transform3D_h

#include "includes/glm.hpp"

class Transform3D {
public:

    Transform3D();

    void moveByGlobal(glm::vec3 move_vector);
    void rotateByGlobal(glm::vec3 rotation_vec);

    void moveByLocal(glm::vec3 move_vector);
    void rotateByLocal(glm::vec3 rotation_vec);

    glm::mat4 getModelMatrix();
    glm::mat4 getInverseModelMatrix();
    glm::mat4 getRotationMatrix();
    glm::mat4 getTranslationMatrix();
    glm::mat4 getScaleMatrix();

    void setPosition(glm::vec3 position);
    void setScale(glm::vec3 scale);

    glm::vec3 getPosition();
    glm::vec3 getScale();

private:
    void setLocalAxes();
    void transformLocalAxes(glm::mat4 rotation_matrix);

    void rotateByAxisAngle(glm::vec3 axis, float angle);

    void moveXLocal(float);
    void moveYLocal(float);
    void moveZLocal(float);

    void setRotationMatrix(glm::mat4 rotation_matrix);
    void rotateByMatrix(glm::mat4 rotation_matrix);

    glm::mat4 calculateRotationMatrix();
    glm::mat4 calculateTranslationMatrix();
    glm::mat4 calculateScaleMatrix();

    glm::vec3 local_x;
    glm::vec3 local_y;
    glm::vec3 local_z;

    glm::vec3 position;
    glm::vec3 scale;

    glm::mat4 rotation_matrix;

};

#endif
