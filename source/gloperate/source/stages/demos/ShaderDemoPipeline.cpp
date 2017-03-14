
#include <gloperate/stages/demos/ShaderDemoPipeline.h>

#include <gloperate/gloperate.h>
#include <gloperate/stages/base/BasicFramebufferStage.h>
#include <gloperate/stages/base/MixerStage.h>
#include <gloperate/stages/demos/TimerStage.h>
#include <gloperate/stages/demos/SpinningRectStage.h>
#include <gloperate/stages/demos/ColorizeStage.h>

#include <gloperate/stages/base/TextureLoadStage.h>
#include <gloperate/stages/base/ProgramStage.h>
#include <gloperate/stages/base/ShaderStage.h>
#include <gloperate/stages/demos/DemoRenderStage.h>


namespace gloperate
{


CPPEXPOSE_COMPONENT(ShaderDemoPipeline, gloperate::Stage)


ShaderDemoPipeline::ShaderDemoPipeline(Environment * environment, const std::string & name)
: Pipeline(environment, name)
, renderInterface(this)
, shader1("shader1", this)
, shader2("shader2", this)
, texture("texture", this)
, m_textureLoadStage(cppassist::make_unique<TextureLoadStage>(environment, "TextureLoadStage"))
, m_shaderStage(cppassist::make_unique<ShaderStage>(environment, "ShaderStage"))
, m_programStage(cppassist::make_unique<ProgramStage>(environment, "ProgramStage"))
, m_framebufferStage(cppassist::make_unique<BasicFramebufferStage>(environment, "BasicFramebufferStage"))
, m_renderStage(cppassist::make_unique<DemoRenderStage>(environment, "RenderStage"))
, m_mixerStage(cppassist::make_unique<MixerStage>(environment, "MixerStage"))
{
    // Get data path
    std::string dataPath = gloperate::dataPath();

    // Setup parameters
    shader1 = dataPath + "/gloperate/shaders/Demo/Demo.frag";
    shader2 = dataPath + "/gloperate/shaders/Demo/Demo.vert";

    texture = dataPath + "/gloperate/textures/gloperate-logo.png";

    // Texture loader stage
    addStage(m_textureLoadStage.get());
    m_textureLoadStage->filename << texture;

    // Shader stage
    addStage(m_shaderStage.get());
    m_shaderStage->filePath << shader2;

    // Basic program stage
    addStage(m_programStage.get());
    m_programStage->createInput("shader1") << shader1;
    m_programStage->createInput("shader2") << m_shaderStage->shader;

    // Framebuffer stage for spinning rect
    addStage(m_framebufferStage.get());
    m_framebufferStage->viewport << renderInterface.deviceViewport;

    // Spinning rectangle stage
    addStage(m_renderStage.get());
    m_renderStage->renderInterface.deviceViewport  << renderInterface.deviceViewport;
    m_renderStage->renderInterface.targetFBO       << m_framebufferStage->fbo;
    m_renderStage->renderInterface.backgroundColor << renderInterface.backgroundColor;
    m_renderStage->colorTexture                    << m_framebufferStage->colorTexture;
    m_renderStage->texture                         << m_textureLoadStage->texture;
    m_renderStage->program                         << m_programStage->program;

    // Mixer stage
    addStage(m_mixerStage.get());
    m_mixerStage->viewport  << renderInterface.deviceViewport;
    m_mixerStage->targetFBO << renderInterface.targetFBO;
    m_mixerStage->texture   << m_renderStage->colorTextureOut;

    // Outputs
    renderInterface.rendered << m_mixerStage->rendered;
}

ShaderDemoPipeline::~ShaderDemoPipeline()
{
}

} // namespace gloperate
