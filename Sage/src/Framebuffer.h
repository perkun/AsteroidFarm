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
    FramebufferTextureSpecification(FramebufferTextureFormat format) : texture_format(format) {}

    FramebufferTextureFormat texture_format = FramebufferTextureFormat::None;
    // TODO: filtering/wrap
};

struct FramebufferAttachmentSpecification
{
    FramebufferAttachmentSpecification() = default;
    FramebufferAttachmentSpecification(std::initializer_list<FramebufferTextureSpecification> texture_specs)
        : texture_specs(texture_specs)
    {}

    std::vector<FramebufferTextureSpecification> texture_specs;
};

struct FramebufferSpecification
{
    unsigned int width = 0, height = 0;
    FramebufferAttachmentSpecification attachments;
    unsigned int samples = 1;

    bool SwapChainTarget = false;
};

class Framebuffer
{
public:
    static void blit(Framebuffer *ms_framebuffer, Framebuffer *framebuffer, int, int);
    static GLenum texture_target(bool multisampled);
    static void create_textures(bool multisampled, unsigned int *out_id, unsigned int count);
    static void bind_texture(bool multisampled, unsigned int id);

    static void attach_color_texture(unsigned int id,
                                     int samples,
                                     GLenum internal_format,
                                     GLenum attachment_type,
                                     unsigned int width,
                                     unsigned int height,
                                     int index);

    static void attach_depth_texture(
        unsigned int id, int samples, GLenum internal_format, GLenum format, unsigned int width, unsigned int height);

    Framebuffer(const FramebufferSpecification &specs);
    ~Framebuffer();

    void invalidate();

    void bind();
    void bind_depth_texture(unsigned int slot);
    void bind_color_texture(unsigned int slot);
    void clear();
    void clear_attachment(int slot, int value);
    void unbind();

    void resize(unsigned int width, unsigned int height);

    int read_pixel(int slot, int x, int y);

    unsigned int get_color_attachment_id(int slot = 0) const
    {
        return color_attachments[slot];
    }
    unsigned int get_depth_attachment_id() const
    {
        return depth_attachment;
    }

    const FramebufferSpecification &get_specification() const
    {
        return specification;
    }
    unsigned int id = 0;
    FramebufferSpecification specification;

private:
    std::vector<unsigned int> color_attachments;
    unsigned int depth_attachment = 0;

    std::vector<FramebufferTextureSpecification> color_attachment_specs;
    FramebufferTextureSpecification depth_attachment_specs;
};

}  // namespace Sage