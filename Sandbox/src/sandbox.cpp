#include <fmt/format.h>

#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtx/pca.hpp>
#include <iostream>

#include "Camera.h"
#include "Mesh.h"
#include "Observations.h"
#include "Parsers/JsonLoader.h"
#include "GraphicsEngine.h"
#include "Components.h"
#include "Framebuffer.h"
// #include "AsteroidParams.h"

using namespace Sage;

int main()
{
    GraphicsEngine graphicsEngine;
    auto &scene = graphicsEngine.getScene();

    auto mesh = Mesh::loadFromObj("data/model_shifted.obj");
    mesh.rotateToPrincipalAxes();

    auto shader = std::make_shared<Shader>("data/basic.vs", "data/basic.fs");

    auto asteroid = scene.createEntity();
    asteroid.addComponent<VaoComponent>(mesh);
    auto &t = asteroid.addComponent<TransformComponent>();
    auto &m = asteroid.addComponent<MaterialComponent>(shader);
    t.position = glm::vec3{0., 5., 0};

    // auto sun = scene.createEntity();
    // sun.addComponent<CameraComponent>(std::make_shared<OrthograficCamera>(4., 1., 0.1, 10.));
    // sun.addComponent<TransformComponent>();
    auto camera = std::make_shared<OrthograficCamera>(4., 1., 0.1, 10.);
    camera->position = glm::vec3{0.};
    camera->updateTarget(t.position);

    scene.camera = camera.get();

    // FramebufferSpecification fb_specs;
    // fb_specs.attachments = {FramebufferTextureFormat::RGBA32F,
    //                         FramebufferTextureFormat::RED_INTEGER,
    //                         FramebufferTextureFormat::DEPTH32FSTENCIL8};
    // fb_specs.width = 600;
    // fb_specs.height = 600;
    // fb_specs.samples = 1;

    // Framebuffer framebuffer(fb_specs);


    for(int i = 0; i < 10; i++)
    {
		glViewport(0,0,600, 600);
        scene.draw();
        graphicsEngine._window.update();
    }

    getchar();

    return 0;
}
