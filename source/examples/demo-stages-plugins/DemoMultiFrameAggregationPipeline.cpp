
#include "DemoMultiFrameAggregationPipeline.h"

#include <gloperate/gloperate.h>
#include <gloperate-glkernel/stages/MultiFrameAggregationPipeline.h>

#include "TransparencyRenderingPipeline.h"

CPPEXPOSE_COMPONENT(DemoMultiFrameAggregationPipeline, gloperate::Stage)


DemoMultiFrameAggregationPipeline::DemoMultiFrameAggregationPipeline(gloperate::Environment * environment, const std::string & name)
: Pipeline(environment, name)
, canvasInterface(this)
, multiFrameCount("multiFrameCount", this, 256)
, m_multiFramePipeline(cppassist::make_unique<gloperate_glkernel::MultiFrameAggregationPipeline>(environment))
, m_transparencyPipeline(cppassist::make_unique<TransparencyRenderingPipeline>(environment))
{
    multiFrameCount.setOption("asSpinBox", true);
    multiFrameCount.setOption("minimumValue", 1);
    multiFrameCount.setOption("maximumValue", 4096);
    multiFrameCount.setOption("decimals", 0);
    multiFrameCount.setOption("type", "int"); // HACK: Override regular typename "int32" to display property editor

    addStage(m_multiFramePipeline.get());

    m_multiFramePipeline->addStage(m_transparencyPipeline.get());

    // Inputs
    *m_multiFramePipeline->canvasInterface.colorRenderTargetInput(0) << *createInput<gloperate::ColorRenderTarget *>("Color");
    m_multiFramePipeline->canvasInterface.viewport << canvasInterface.viewport;
    m_multiFramePipeline->canvasInterface.backgroundColor << canvasInterface.backgroundColor;
    m_multiFramePipeline->canvasInterface.frameCounter << canvasInterface.frameCounter;
    m_multiFramePipeline->canvasInterface.timeDelta << canvasInterface.timeDelta;
    m_multiFramePipeline->multiFrameCount << multiFrameCount;

    auto redAlphaInput   = createInput("redAlpha"  , 0.3f);
    auto greenAlphaInput = createInput("greenAlpha", 0.5f);
    auto blueAlphaInput  = createInput("blueAlpha" , 0.7f);
    m_transparencyPipeline->redAlpha   << *redAlphaInput;
    m_transparencyPipeline->greenAlpha << *greenAlphaInput;
    m_transparencyPipeline->blueAlpha  << *blueAlphaInput;
    m_multiFramePipeline->restartAggregationOn(redAlphaInput);
    m_multiFramePipeline->restartAggregationOn(greenAlphaInput);
    m_multiFramePipeline->restartAggregationOn(blueAlphaInput);

    // Outputs
    *createOutput<gloperate::ColorRenderTarget *>("ColorOut") << *m_multiFramePipeline->canvasInterface.colorRenderTargetOutput(0);
}

DemoMultiFrameAggregationPipeline::~DemoMultiFrameAggregationPipeline()
{
}
