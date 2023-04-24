#pragma once

#include <glm/glm.hpp>

namespace Sage {

class Camera
{
public:
	Camera(float aspect, float zNear, float zFar);
    virtual ~Camera() = default;

	virtual glm::mat4 getPerspective() = 0;

	glm::mat4 getView();
	void updateTarget(glm::vec3 newTarget);
	void update();

	glm::vec3 position;
    glm::vec3 front;
    glm::vec3 up;
    glm::vec3 right;

protected:
	float _aspect;

    struct BoundingBox {
        float left{0.};
        float right{0.};
        float top{0.};
        float bottom{0.};
        float near{0.};
        float far{0.};
    };

    BoundingBox _boundingBox;
};


class PerspectiveCamera : public Camera
{
public:
    PerspectiveCamera(float fov, float aspect, float zNear, float zFar);
    virtual ~PerspectiveCamera() = default;

	virtual glm::mat4 getPerspective() override;

protected:
	float _fov;
};


class OrthograficCamera : public Camera
{
public:
    OrthograficCamera(float size_x, float aspect, float zNear, float zFar);
    virtual ~OrthograficCamera() = default;

	virtual glm::mat4 getPerspective() override;

protected:
    void updateViewBox();
    float _sizeX;
};


} //