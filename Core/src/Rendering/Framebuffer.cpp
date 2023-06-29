#include "Framebuffer.h"
#include <fmt/core.h>

namespace AsteroidFarm {

static const uint32_t s_MaxFramebufferSize = 8192;

void Framebuffer::blit(Framebuffer *ms_framebuffer,
                       Framebuffer *framebuffer,
                       int ms_color_attachment_index,
                       int fb_color_attachment_index)
{
    glBindFramebuffer(GL_READ_FRAMEBUFFER, ms_framebuffer->id);
    glBindFramebuffer(GL_DRAW_FRAMEBUFFER, framebuffer->id);

    glReadBuffer(GL_COLOR_ATTACHMENT0 + ms_color_attachment_index);
    glDrawBuffer(GL_COLOR_ATTACHMENT0 + fb_color_attachment_index);

    glBlitFramebuffer(0,
                      0,
                      framebuffer->specification.width,
                      framebuffer->specification.height,
                      0,
                      0,
                      framebuffer->specification.width,
                      framebuffer->specification.height,
                      GL_COLOR_BUFFER_BIT,
                      GL_NEAREST);
}

Framebuffer::Framebuffer(const FramebufferSpecification &specs)
{
    specification = specs;

    for (FramebufferTextureSpecification tex_spec : specification.attachments.textureSpecs)
    {
        if (tex_spec.textureFormat == FramebufferTextureFormat::DEPTH24STENCIL8)
            _depthAttachmentSpecs = tex_spec;
        else if (tex_spec.textureFormat == FramebufferTextureFormat::DEPTH32FSTENCIL8)
            _depthAttachmentSpecs = tex_spec;
        else
            _colorAttachmentSpecs.emplace_back(tex_spec);
    }

    invalidate();
}

Framebuffer::~Framebuffer()
{
    glDeleteFramebuffers(1, &id);
    glDeleteTextures(_colorAttachments.size(), _colorAttachments.data());
    glDeleteTextures(1, &_depthAttachment);
}

void Framebuffer::createTextures(bool multisampled, unsigned int *out_id, unsigned int count)
{
    glCreateTextures(textureTarget(multisampled), count, out_id);
}

void Framebuffer::attachColorTexture(unsigned int id,
                                     int samples,
                                     GLenum internal_format,
                                     GLenum format,
                                     unsigned int width,
                                     unsigned int height,
                                     int index)
{
    bool multisampled = samples > 1;

    if (multisampled)
    {
        glTexParameteri(GL_TEXTURE_2D_MULTISAMPLE, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D_MULTISAMPLE, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

        glTexImage2DMultisample(
            GL_TEXTURE_2D_MULTISAMPLE, samples, internal_format, width, height, GL_TRUE);

        glFramebufferTexture2D(
            GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0 + index, GL_TEXTURE_2D_MULTISAMPLE, id, 0);
    }
    else
    {
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

        glTexImage2D(
            GL_TEXTURE_2D, 0, internal_format, width, height, 0, format, GL_UNSIGNED_BYTE, nullptr);

        glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0 + index, GL_TEXTURE_2D, id, 0);
    }
}

void Framebuffer::attachDepthTexture(unsigned int id,
                                     int samples,
                                     GLenum format,
                                     GLenum attachment_type,
                                     unsigned int width,
                                     unsigned int height)
{
    bool multisampled = samples > 1;

    if (multisampled)
    {
        glTexImage2DMultisample(GL_TEXTURE_2D_MULTISAMPLE, samples, format, width, height, GL_TRUE);

        glFramebufferTexture2D(GL_FRAMEBUFFER, attachment_type, GL_TEXTURE_2D_MULTISAMPLE, id, 0);
    }
    else
    {
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

        glTexStorage2D(GL_TEXTURE_2D, 1, format, width, height);
        glFramebufferTexture2D(GL_FRAMEBUFFER, attachment_type, GL_TEXTURE_2D, id, 0);
    }
}

GLenum Framebuffer::textureTarget(bool multisampled)
{
    return multisampled ? GL_TEXTURE_2D_MULTISAMPLE : GL_TEXTURE_2D;
}

void Framebuffer::bindTexture(bool multisampled, unsigned int id)
{
    glBindTexture(textureTarget(multisampled), id);
}

void Framebuffer::invalidate()
{
    if (id)
    {
        glDeleteFramebuffers(1, &id);
        glDeleteTextures(_colorAttachments.size(), _colorAttachments.data());
        glDeleteTextures(1, &_depthAttachment);

        _colorAttachments.clear();
        _depthAttachment = 0;
    }

    glCreateFramebuffers(1, &id);
    glBindFramebuffer(GL_FRAMEBUFFER, id);

    // Attachments :
    bool multisampled = specification.samples > 1;

    if (_colorAttachmentSpecs.size())
    {
        _colorAttachments.resize(_colorAttachmentSpecs.size());
        createTextures(multisampled, _colorAttachments.data(), _colorAttachments.size());

        for (int i = 0; i < _colorAttachments.size(); i++)
        {
            bindTexture(multisampled, _colorAttachments[i]);
            switch (_colorAttachmentSpecs[i].textureFormat)
            {
            case FramebufferTextureFormat::RGBA8:
                attachColorTexture(_colorAttachments[i],
                                   specification.samples,
                                   GL_RGBA8,
                                   GL_RGBA,
                                   specification.width,
                                   specification.height,
                                   i);
                break;

            case FramebufferTextureFormat::RGBA32F:
                attachColorTexture(_colorAttachments[i],
                                   specification.samples,
                                   GL_RGBA32F,
                                   GL_RGBA,
                                   specification.width,
                                   specification.height,
                                   i);
                break;

            case FramebufferTextureFormat::RED_INTEGER:
                attachColorTexture(_colorAttachments[i],
                                   specification.samples,
                                   GL_R32I,
                                   GL_RED_INTEGER,
                                   specification.width,
                                   specification.height,
                                   i);
                break;
            }
        }
    }

    if (_depthAttachmentSpecs.textureFormat != FramebufferTextureFormat::None)
    {
        createTextures(multisampled, &_depthAttachment, 1);
        bindTexture(multisampled, _depthAttachment);

        switch (_depthAttachmentSpecs.textureFormat)
        {
        case FramebufferTextureFormat::DEPTH24STENCIL8:
            attachDepthTexture(_depthAttachment,
                               specification.samples,
                               GL_DEPTH24_STENCIL8,
                               GL_DEPTH_STENCIL_ATTACHMENT,
                               specification.width,
                               specification.height);
            break;

        case FramebufferTextureFormat::DEPTH32FSTENCIL8:
            attachDepthTexture(_depthAttachment,
                               specification.samples,
                               GL_DEPTH32F_STENCIL8,
                               GL_DEPTH_STENCIL_ATTACHMENT,
                               specification.width,
                               specification.height);
            break;
        }
    }

    if (_colorAttachments.size() > 1)
    {
        // CORE_ASSERT(color_attachments.size() <= 4, "Supporting only up to 4 color attachments");

        GLenum buffers[4] = {
            GL_COLOR_ATTACHMENT0, GL_COLOR_ATTACHMENT1, GL_COLOR_ATTACHMENT2, GL_COLOR_ATTACHMENT3};
        glDrawBuffers(_colorAttachments.size(), buffers);
    }
    else if (_colorAttachments.empty())
    {
        // Only depth-pass
        glDrawBuffer(GL_NONE);
    }

    //   glCheckFramebufferStatus(GL_FRAMEBUFFER);
    if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
    {
        fmt::print("Framebuffer invalidation failed.");
    }

    glBindFramebuffer(GL_FRAMEBUFFER, 0);
}

void Framebuffer::bind()
{
    //     if (specification.flags & MULTISAMPLING)
    //     {
    //         glBindFramebuffer(GL_DRAW_FRAMEBUFFER, 0); // Make sure no FBO is set as the draw
    //         framebuffer glBindFramebuffer(GL_READ_FRAMEBUFFER, id); // Make sure your
    //         multisampled FBO is the read framebuffer glDrawBuffer(GL_BACK); // Set the back
    //         buffer as the draw buffer glBlitFramebuffer(0, 0, specification.width,
    //         specification.height, 0, 0,
    //                           specification.width, specification.height,
    //                           GL_COLOR_BUFFER_BIT | GL_STENCIL_BUFFER_BIT | GL_DEPTH_BUFFER_BIT,
    //                           GL_NEAREST);
    //     }
    //     else
    //     {
    glBindFramebuffer(GL_FRAMEBUFFER, id);
    //     }
    glViewport(0, 0, specification.width, specification.height);
}

void Framebuffer::clear()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

static GLenum FBTextureFormatToGL(FramebufferTextureFormat format)
{
    switch (format)
    {
    case FramebufferTextureFormat::RGBA8:
        return GL_RGBA8;
    case FramebufferTextureFormat::RED_INTEGER:
        return GL_RED_INTEGER;
    }

    // CORE_ASSERT(false, "FramebufferTextureFormat not recognized");
    return 0;
}

void Framebuffer::clearAttachment(int slot, int value)
{
    // CORE_ASSERT(slot < color_attachments.size(), "Color attachment index to big");
    FramebufferTextureSpecification &spec = _colorAttachmentSpecs[slot];

    glClearTexImage(
        _colorAttachments[slot], 0, FBTextureFormatToGL(spec.textureFormat), GL_INT, &value);
}

int Framebuffer::readPixel(int slot, int x, int y)
{
    // CORE_ASSERT(slot < color_attachments.size(), "Color attachment index to big");
    glReadBuffer(GL_COLOR_ATTACHMENT0 + slot);

    int pixel_data;
    glReadPixels(x, y, 1, 1, GL_RED_INTEGER, GL_INT, &pixel_data);
    return pixel_data;
}

void Framebuffer::unbind()
{
    glBindFramebuffer(GL_FRAMEBUFFER, 0);
}

void Framebuffer::resize(unsigned int width, unsigned int height)
{
    if (width == 0 || height == 0 || width > s_MaxFramebufferSize || height > s_MaxFramebufferSize)
    {
        fmt::print("Attempted to rezize framebuffer to {}, {}", width, height);
        return;
    }
    specification.width = width;
    specification.height = height;

    invalidate();
}

void Framebuffer::bindDepthTexture(unsigned int slot)
{
    glActiveTexture(GL_TEXTURE0 + slot);
    glBindTexture(textureTarget(specification.samples > 1), _depthAttachment);
}

void Framebuffer::bindColorTexture(unsigned int slot)
{
    // CORE_ASSERT(slot < color_attachments.size(), "Color attachment index to big");
    glActiveTexture(GL_TEXTURE0 + slot);
    glBindTexture(textureTarget(specification.samples > 1), _colorAttachments[slot]);
}

}  // namespace AsteroidFarm
