
#include <gloperate/rendering/AbstractRenderTarget.h>

#include <glbinding/gl/types.h>
#include <glbinding/gl/enum.h>

#include <globjects/Framebuffer.h>
#include <globjects/FramebufferAttachment.h>
#include <globjects/Renderbuffer.h>
#include <globjects/Texture.h>


namespace gloperate
{


AbstractRenderTarget::AbstractRenderTarget()
: m_currentTargetType(RenderTargetType::Invalid)
, m_defaultFBOAttachment(gl::GL_NONE)
, m_texture(nullptr)
, m_renderbuffer(nullptr)
, m_userDefinedFBOAttachment(nullptr)
{
}

AbstractRenderTarget::~AbstractRenderTarget()
{
}

void AbstractRenderTarget::releaseTarget()
{
    switch (m_currentTargetType)
    {
    case RenderTargetType::Texture:
        m_texture = nullptr;
        break;
    case RenderTargetType::Renderbuffer:
        m_renderbuffer = nullptr;
        break;
    case RenderTargetType::DefaultFBOAttachment:
        m_defaultFBOAttachment = gl::GL_NONE;
        break;
    case RenderTargetType::UserDefinedFBOAttachment:
        m_userDefinedFBOAttachment = nullptr;
        break;
    case RenderTargetType::Invalid:
    default:
        m_defaultFBOAttachment = gl::GL_NONE;
        break;
    }

    m_currentTargetType = RenderTargetType::Invalid;
}

AttachmentType AbstractRenderTarget::underlyingAttachmentType() const
{
    return m_internalAttachmentType;
}

gl::GLenum AbstractRenderTarget::attachmentGLType() const
{
    switch (m_internalAttachmentType)
    {
    case AttachmentType::Depth:
        return gl::GL_DEPTH;
    case AttachmentType::Stencil:
        return gl::GL_STENCIL;
    case AttachmentType::DepthStencil:
        return gl::GL_DEPTH_STENCIL;
    case AttachmentType::Color:
    default:
        return gl::GL_COLOR;
    }
}

void AbstractRenderTarget::setUnderlyingAttachmentType(AttachmentType attachmentType)
{
    m_internalAttachmentType = attachmentType;
}

void AbstractRenderTarget::setTarget(globjects::Texture * texture)
{
    releaseTarget();

    m_currentTargetType = RenderTargetType::Texture;

    m_texture = texture;
}

void AbstractRenderTarget::setTarget(globjects::Renderbuffer * renderbuffer)
{
    releaseTarget();

    m_currentTargetType = RenderTargetType::Renderbuffer;

    m_renderbuffer = renderbuffer;
}

void AbstractRenderTarget::setTarget(gl::GLenum attachment)
{
    releaseTarget();

    m_currentTargetType = RenderTargetType::DefaultFBOAttachment;

    m_defaultFBOAttachment = attachment;
}

void AbstractRenderTarget::setTarget(globjects::FramebufferAttachment * fboAttachment)
{
    releaseTarget();

    m_currentTargetType = RenderTargetType::UserDefinedFBOAttachment;

    m_userDefinedFBOAttachment = fboAttachment;
}

RenderTargetType AbstractRenderTarget::currentTargetType() const
{
    return m_currentTargetType;
}

gl::GLenum AbstractRenderTarget::defaultFramebufferAttachment() const
{
    return m_defaultFBOAttachment;
}

globjects::Texture * AbstractRenderTarget::textureAttachment() const
{
    return m_texture;
}

globjects::Renderbuffer * AbstractRenderTarget::renderbufferAttachment() const
{
    return m_renderbuffer;
}

globjects::FramebufferAttachment * AbstractRenderTarget::framebufferAttachment() const
{
    return m_userDefinedFBOAttachment;
}

bool AbstractRenderTarget::attachmentRequiresUserDefinedFramebuffer() const
{
    return m_currentTargetType == RenderTargetType::Texture
        || m_currentTargetType == RenderTargetType::Renderbuffer
        || m_currentTargetType == RenderTargetType::UserDefinedFBOAttachment;
}

gl::GLenum AbstractRenderTarget::clearBufferAttachment() const
{
    return attachmentRequiresUserDefinedFramebuffer()
        ? attachmentGLType()
        : m_defaultFBOAttachment;
}

gl::GLint AbstractRenderTarget::clearBufferDrawBuffer(size_t index) const
{
    return attachmentRequiresUserDefinedFramebuffer()
        ? (m_internalAttachmentType == AttachmentType::Color ? index : 0)
        : 0;
}

gl::GLenum AbstractRenderTarget::drawBufferAttachment(size_t index) const
{
    return attachmentRequiresUserDefinedFramebuffer()
        ? gl::GL_COLOR_ATTACHMENT0 + index
        : m_defaultFBOAttachment;
}


} // namespace gloperate
