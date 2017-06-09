
#pragma once


#include <cppexpose/plugin/plugin_api.h>

#include <gloperate/gloperate-version.h>
#include <gloperate/pipeline/Pipeline.h>
#include <gloperate/pipeline/Input.h>
#include <gloperate/stages/interfaces/RenderInterface.h>


namespace gloperate_glkernel
{
    class MultiFrameAggregationPipeline;
}

namespace gloperate
{
    class MultiFrameAggregationPipeline;
}

class DemoAntialiasingPipeline;
class DemoDOFPipeline;
class DemoTransparencyPipeline;
class DemoSSAOPipeline;


/**
*  @brief
*    Demo pipeline showing multiframe aggregation
*/
class DemoMultiFramePipeline : public gloperate::Pipeline
{
public:
    CPPEXPOSE_DECLARE_COMPONENT(
        DemoMultiFramePipeline, gloperate::Stage
      , "RenderStage Demos" // Tags
      , ""                  // Icon
      , ""                  // Annotations
      , "Demo pipeline showing multiframe aggregation"
      , GLOPERATE_AUTHOR_ORGANIZATION
      , "v0.1.0"
    )


public:
    // Interfaces
    gloperate::RenderInterface renderInterface; ///< Interface for rendering into a viewer

    // Inputs
    Input<int>                 multiFrameCount; ///< Number of frames to aggregate


public:
    /**
    *  @brief
    *    Constructor
    *
    *  @param[in] environment
    *    Environment to which the pipeline belongs (must NOT be null!)
    *  @param[in] name
    *    Pipeline name
    */
    DemoMultiFramePipeline(gloperate::Environment * environment, const std::string & name = "DemoMultiFramePipeline");

    /**
    *  @brief
    *    Destructor
    */
    virtual ~DemoMultiFramePipeline();


protected:
    // Stages
    std::unique_ptr<gloperate_glkernel::MultiFrameAggregationPipeline> m_multiFramePipeline;   ///< Aggregation Pipeline

    // Demo pipelines using multiframe effects
    std::unique_ptr<DemoAntialiasingPipeline>                 m_antialiasingPipeline;
    std::unique_ptr<DemoDOFPipeline>                          m_dofPipeline;
    std::unique_ptr<DemoTransparencyPipeline>                 m_transparencyPipeline;
    std::unique_ptr<DemoSSAOPipeline>                         m_ssaoPipeline;
};
