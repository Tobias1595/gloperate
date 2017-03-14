
#include <demo-stages/DemoTransparencyPipeline.h>

#include <gloperate/gloperate.h>
#include <gloperate-glkernel/stages/TransparencyKernelStage.h>
#include <gloperate-glkernel/stages/NoiseKernelStage.h>

#include <demo-stages/DemoTransparencyStage.h>


namespace gloperate
{


CPPEXPOSE_COMPONENT(DemoTransparencyPipeline, gloperate::Stage)


DemoTransparencyPipeline::DemoTransparencyPipeline(Environment * environment, const std::string & name)
: Pipeline(environment, name)
, renderInterface(this)
, m_transparencyKernelStage(new gloperate_glkernel::TransparencyKernelStage(environment))
, m_noiseKernelStage(new gloperate_glkernel::NoiseKernelStage(environment))
, m_transparencyRenderStage(new DemoTransparencyStage(environment))
{
    addStage(m_transparencyKernelStage);
    m_transparencyKernelStage->kernelSize.setValue(glm::ivec2(256, 256));

    addStage(m_noiseKernelStage);
    m_noiseKernelStage->dimensions.setValue(glm::ivec3(64, 64, 64));

    addStage(m_transparencyRenderStage);
    m_transparencyRenderStage->renderInterface.backgroundColor << renderInterface.backgroundColor;
    m_transparencyRenderStage->renderInterface.deviceViewport << renderInterface.deviceViewport;
    m_transparencyRenderStage->renderInterface.frameCounter << renderInterface.frameCounter;
    m_transparencyRenderStage->renderInterface.targetFBO << renderInterface.targetFBO;
    m_transparencyRenderStage->renderInterface.timeDelta << renderInterface.timeDelta;
    m_transparencyRenderStage->renderInterface.virtualViewport << renderInterface.virtualViewport;
    m_transparencyRenderStage->transparencyKernel << m_transparencyKernelStage->texture;
    m_transparencyRenderStage->noiseKernel << m_noiseKernelStage->texture;

    renderInterface.rendered << m_transparencyRenderStage->renderInterface.rendered;
}

DemoTransparencyPipeline::~DemoTransparencyPipeline()
{
}


} // namespace gloperate
