#include "Camera.hpp"

Camera::Camera(Viewport& viewport, Transform3D transform_3D, float field_of_view, float near_clip, float far_clip) : viewport(viewport), transform_3D(move(transform_3D)), field_of_view(field_of_view), near_clip(near_clip), far_clip(far_clip) {

}

Viewport& Camera::getViewport() {
    return viewport;
}

Transform3D& Camera::getTransform3D() {
    return transform_3D;
}

glm::mat4 Camera::getViewMatrix(){
    return calculateViewMatrix();
}

glm::mat4 Camera::getProjectionMatrix(){
    return calculateProjectionMatrix();
}

glm::mat4 Camera::calculateViewMatrix() {
    return getTransform3D().getInverseModelMatrix();
}

glm::mat4 Camera::calculateProjectionMatrix(){
    // Use all of the intrinsic values to create the projection matrix
    return glm::perspective(getFieldOfView(), getViewport().getAspectRatio(), getNearClip(), getFarClip());
}

void Camera::setNearClip(float near_clip) {
    this->near_clip = near_clip;
}

void Camera::setFarClip(float far_clip) {
    this->far_clip = far_clip;
}

void Camera::setFieldOfView(float field_of_view) {
    this->field_of_view = field_of_view;
}

float Camera::getNearClip() {
    return near_clip;
}

float Camera::getFarClip() {
    return far_clip;
}

float Camera::getFieldOfView(){
    return field_of_view;
}
