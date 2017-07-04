
#pragma once


#include <cppexpose/plugin/plugin_api.h>

#include <glm/vec4.hpp>

#include <globjects/Program.h>
#include <globjects/Shader.h>
#include <globjects/Texture.h>
#include <globjects/Framebuffer.h>

#include <gloperate/gloperate-version.h>
#include <gloperate/pipeline/Stage.h>
#include <gloperate/stages/interfaces/RenderInterface.h>
#include <gloperate/rendering/ScreenAlignedQuad.h>

#include <gloperate-glkernel/gloperate-glkernel_api.h>


namespace gloperate_glkernel
{


/**
*  @brief
*    Stage that aggregates multiple subsequent frames into a single framebuffer
*/
class GLOPERATE_GLKERNEL_API MultiFrameAggregationStage : public gloperate::Stage
{
public:
    CPPEXPOSE_DECLARE_COMPONENT(
        MultiFrameAggregationStage, gloperate::Stage
      , ""
      , ""
      , ""
      , "Stage that aggregates multiple subsequent frames into a single framebuffer"
      , GLOPERATE_AUTHOR_ORGANIZATION
      , "v0.1.0"
    )


public:
    // Inputs
    Input<globjects::Framebuffer *>  aggregationFBO;    ///< FBO to aggregate into
    Input<globjects::Texture *>      texture;           ///< New frame to add to aggregation
    Input<bool>                      textureRerendered; ///< Add texture to aggregation?
    Input<glm::vec4>                 viewport;          ///< Target viewport
    Input<float>                     aggregationFactor; ///< Weight of new frame in current aggregation

    // Outputs
    Output<globjects::Framebuffer *> aggregatedFBO;     ///< Framebuffer containing aggregation


public:
    /**
    *  @brief
    *    Constructor
    *
    *  @param[in] environment
    *    Environment to which the stage belongs (must NOT be null!)
    *  @param[in] name
    *    Stage name
    */
    MultiFrameAggregationStage(gloperate::Environment * environment, const std::string & name = "MultiFrameAggregationStage");

    /**
    *  @brief
    *    Destructor
    */
    virtual ~MultiFrameAggregationStage();


protected:
    // Virtual Stage interface
    virtual void onContextInit(gloperate::AbstractGLContext * context) override;
    virtual void onContextDeinit(gloperate::AbstractGLContext * context) override;
    virtual void onProcess() override;


protected:
    // Data
    std::unique_ptr<gloperate::ScreenAlignedQuad> m_quad;           ///< Screen aligned quad
};


} // namespace gloperate_glkernel
