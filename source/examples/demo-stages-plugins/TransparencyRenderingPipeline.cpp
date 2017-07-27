
#include "TransparencyRenderingPipeline.h"

#include <glbinding/gl/enum.h>

#include <gloperate/gloperate.h>
#include <gloperate/stages/base/TextureRenderTargetStage.h>

#include <gloperate-glkernel/stages/TransparencyKernelStage.h>
#include <gloperate-glkernel/stages/NoiseKernelStage.h>

#include "TransparentCirclesStage.h"
#include "IntegerVectorStage.h"


CPPEXPOSE_COMPONENT(TransparencyRenderingPipeline, gloperate::Stage)


TransparencyRenderingPipeline::TransparencyRenderingPipeline(gloperate::Environment * environment, const std::string & name)
: Pipeline(environment, name)
, canvasInterface(this)
, m_transparencyKernelStage(cppassist::make_unique<gloperate_glkernel::TransparencyKernelStage>(environment))
, m_noiseKernelStage(cppassist::make_unique<gloperate_glkernel::NoiseKernelStage>(environment))
, m_depthBufferStage(cppassist::make_unique<gloperate::TextureRenderTargetStage>(environment))
, m_transparencyRenderStage(cppassist::make_unique<TransparentCirclesStage>(environment))
{
    auto transparencySizeStage = cppassist::make_unique<IntegerVectorStage>(environment);
    transparencySizeStage->createInput("x") = 256;
    transparencySizeStage->createInput("y") = 64; // TODO: pipe multiframe count into here

    addStage(m_transparencyKernelStage.get());
    m_transparencyKernelStage->kernelSize << *transparencySizeStage->createOutput<glm::ivec2>("xy");

    auto noiseSizeStage = cppassist::make_unique<IntegerVectorStage>(environment);
    noiseSizeStage->createInput("xy") = glm::ivec2(64);
    noiseSizeStage->createInput("z") = 64; // TODO: pipe multiframe count into here

    addStage(m_noiseKernelStage.get());
    m_noiseKernelStage->dimensions << *noiseSizeStage->createOutput<glm::ivec3>("xyz");

    addStage(m_depthBufferStage.get());
    m_depthBufferStage->size << canvasInterface.viewport;
    m_depthBufferStage->type = gl::GL_BYTE;
    m_depthBufferStage->format = gl::GL_DEPTH_COMPONENT;
    m_depthBufferStage->internalFormat = gl::GL_DEPTH_COMPONENT;

    addStage(m_transparencyRenderStage.get());
    m_transparencyRenderStage->canvasInterface.backgroundColor << canvasInterface.backgroundColor;
    m_transparencyRenderStage->canvasInterface.viewport << canvasInterface.viewport;
    m_transparencyRenderStage->canvasInterface.frameCounter << canvasInterface.frameCounter;
    m_transparencyRenderStage->canvasInterface.timeDelta << canvasInterface.timeDelta;
    m_transparencyRenderStage->transparencyKernel << m_transparencyKernelStage->texture;
    m_transparencyRenderStage->noiseKernel << m_noiseKernelStage->texture;
    m_transparencyRenderStage->createInput("Color") << *createInput<gloperate::ColorRenderTarget *>("Color");
    m_transparencyRenderStage->createInput("Depth") << m_depthBufferStage->depthRenderTarget;

    *createOutput<gloperate::ColorRenderTarget *>("ColorOut") << *m_transparencyRenderStage->createOutput<gloperate::ColorRenderTarget *>("ColorOut");

    addStage(std::move(transparencySizeStage));
    addStage(std::move(noiseSizeStage));
}

TransparencyRenderingPipeline::~TransparencyRenderingPipeline()
{
}
