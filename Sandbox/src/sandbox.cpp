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
    // constexpr int windowWidth = 256;
    // constexpr int windowHeight = 256;

    // GraphicsEngine graphicsEngine{
    //     {.width = windowWidth, .height = windowHeight, .title = "RenderEngine window", .fullscreen = false, .visible = false}};
    // auto &scene = graphicsEngine.getScene();

    // auto mesh = Mesh::loadFromObj("data/model_shifted.obj");
    // mesh.rotateToPrincipalAxes();

    // auto shader = std::make_shared<Shader>("data/basic.vs", "data/basic.fs");

    // auto asteroid = scene.createEntity();
    // asteroid.addComponent<VaoComponent>(mesh);
    // auto &t = asteroid.addComponent<TransformComponent>();
    // auto &m = asteroid.addComponent<MaterialComponent>(shader);
    // t.position = glm::vec3{0., 5., 0};

    // // auto sun = scene.createEntity();
    // // sun.addComponent<CameraComponent>(std::make_shared<OrthograficCamera>(4., 1., 0.1, 10.));
    // // sun.addComponent<TransformComponent>();
    // auto camera = std::make_shared<OrthograficCamera>(4., 1., 0.1, 10.);
    // camera->position = glm::vec3{1., 2., 3.};
    // camera->updateTarget(t.position);

    // scene.camera = camera.get();

    // FramebufferSpecification fb_specs;
    // fb_specs.attachments = {FramebufferTextureFormat::RGBA32F,
    //                         FramebufferTextureFormat::DEPTH32FSTENCIL8};
    // fb_specs.width = windowWidth;
    // fb_specs.height = windowHeight;
    // fb_specs.samples = 1;

    // Framebuffer framebuffer(fb_specs);

    // glViewport(0,0, windowWidth, windowHeight);
    // graphicsEngine.getRenderer().bgColor = glm::vec4(0.2, 1., 0.3, 1.0);
    // graphicsEngine.getRenderer().framebuffer = &framebuffer;

    // scene.draw();
    // graphicsEngine.getWindow().update();

    // std::vector<float> pixelBuffRed(windowWidth*windowHeight);
    // std::vector<float> pixelBuffGreen(windowWidth*windowHeight);
    // std::vector<float> pixelBuffBlue(windowWidth*windowHeight);

    // glReadPixels(0,0, windowWidth, windowHeight, GL_RED, GL_FLOAT, pixelBuffRed.data());
    // glReadPixels(0,0, windowWidth, windowHeight, GL_GREEN, GL_FLOAT, pixelBuffGreen.data());
    // glReadPixels(0,0, windowWidth, windowHeight, GL_BLUE, GL_FLOAT, pixelBuffBlue.data());

    // SaveToJson(pixelBuffRed, "data/pixelBuffRed.json");
    // SaveToJson(pixelBuffGreen, "data/pixelBuffGreen.json");
    // SaveToJson(pixelBuffBlue, "data/pixelBuffBlue.json");

    return 0;
}
