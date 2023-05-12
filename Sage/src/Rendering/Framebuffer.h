#pragma once

#include "glad/glad.h"

#include <initializer_list>
#include <vector>

namespace Sage {

enum class FramebufferTextureFormat
{
    None = 0,

    // Color
    RGBA8,
    RGBA32F,
    RED_INTEGER,

    // Depth/stencil
    DEPTH24STENCIL8,
    DEPTH32FSTENCIL8,

    // Defaults
    Depth = DEPTH32FSTENCIL8
};

struct FramebufferTextureSpecification
{
    FramebufferTextureSpecification() = default;
    FramebufferTextureSpecification(FramebufferTextureFormat format) : textureFormat(format) {}

    FramebufferTextureFormat textureFormat = FramebufferTextureFormat::None;
    // TODO: filtering/wrap
};

struct FramebufferAttachmentSpecification
{
    FramebufferAttachmentSpecification() = default;
    FramebufferAttachmentSpecification(
        std::initializer_list<FramebufferTextureSpecification> textureSpecs)
        : textureSpecs(textureSpecs)
    {}

    std::vector<FramebufferTextureSpecification> textureSpecs;
};

struct FramebufferSpecification
{
    unsigned int width = 0;
    unsigned int height = 0;
    unsigned int samples = 1;
    FramebufferAttachmentSpecification attachments;
};

class Framebuffer
{
public:
    static void blit(Framebuffer *ms_framebuffer, Framebuffer *framebuffer, int, int);
    static GLenum textureTarget(bool multisampled);
    static void createTextures(bool multisampled, unsigned int *out_id, unsigned int count);
    static void bindTexture(bool multisampled, unsigned int id);

    static void attachColorTexture(unsigned int id,
                                   int samples,
                                   GLenum internal_format,
                                   GLenum attachment_type,
                                   unsigned int width,
                                   unsigned int height,
                                   int index);

    static void attachDepthTexture(unsigned int id,
                                   int samples,
                                   GLenum internal_format,
                                   GLenum format,
                                   unsigned int width,
                                   unsigned int height);

    Framebuffer(const FramebufferSpecification &specs);
    ~Framebuffer();

    void invalidate();

    void bind();
    void bindDepthTexture(unsigned int slot);
    void bindColorTexture(unsigned int slot);
    void clear();
    void clearAttachment(int slot, int value);
    void unbind();

    void resize(unsigned int width, unsigned int height);

    int readPixel(int slot, int x, int y);

    unsigned int getColorAttachmentId(int slot = 0) const
    {
        return _colorAttachments[slot];
    }
    unsigned int getDepthAttachmentId() const
    {
        return _depthAttachment;
    }

    const FramebufferSpecification &getSpecification() const
    {
        return specification;
    }
    unsigned int id = 0;
    FramebufferSpecification specification;

private:
    std::vector<unsigned int> _colorAttachments;
    unsigned int _depthAttachment = 0;

    std::vector<FramebufferTextureSpecification> _colorAttachmentSpecs;
    FramebufferTextureSpecification _depthAttachmentSpecs;
};

}  // namespace Sage
