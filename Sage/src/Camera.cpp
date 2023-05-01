#include "Camera.h"

#include <glm/gtx/transform.hpp>

namespace Sage {

Camera::Camera(float aspect, float zNear, float zFar) : _aspect(aspect)
{
    _boundingBox.near = zNear;
    _boundingBox.far = zFar;

    up = glm::vec3(0., 0., 1.);
    front = glm::vec3(1., 0., 0.);

    position = glm::vec3(0.0);
    updateTarget(glm::vec3(1., 1., 1.));
}

glm::mat4 Camera::getView() const
{
    return glm::lookAt(position, position + front, up);
}

void Camera::updateTarget(glm::vec3 newTarget)
{
    if (length(newTarget - position) == 0)
        return;
    front = normalize(newTarget - position);
    update();
}

void Camera::update()
{
    right = normalize(cross(front, up));
    right.z = 0.0;
    up = normalize(cross(right, front));
}

PerspectiveCamera::PerspectiveCamera(float fov, float aspect, float zNear, float zFar)
    : Camera(aspect, zNear, zFar), _fov(fov)
{}

glm::mat4 PerspectiveCamera::getPerspective() const
{
    return glm::perspective(_fov, _aspect, _boundingBox.near, _boundingBox.far);
}

OrthographicCamera::OrthographicCamera(float size_x, float aspect, float zNear, float zFar)
    : Camera(aspect, zNear, zFar), _sizeX(size_x)
{}

glm::mat4 OrthographicCamera::getPerspective() const
{
    return glm::ortho(_boundingBox.left,
                      _boundingBox.right,
                      _boundingBox.bottom,
                      _boundingBox.top,
                      _boundingBox.near,
                      _boundingBox.far);
}

void OrthographicCamera::update()
{
    Camera::update();
    _boundingBox.left = -_sizeX / 2.0;
    _boundingBox.right = _sizeX / 2.0;

    _boundingBox.top = _sizeX / 2.0 / _aspect;
    _boundingBox.bottom = -_sizeX / 2.0 / _aspect;
}

}  // namespace Sage