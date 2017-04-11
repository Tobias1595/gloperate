
#pragma once


#include <cppexpose/plugin/plugin_api.h>

#include <globjects/VertexArray.h>
#include <globjects/Buffer.h>
#include <globjects/Program.h>
#include <globjects/Shader.h>
#include <globjects/Texture.h>

#include <gloperate/gloperate-version.h>
#include <gloperate/pipeline/Stage.h>
#include <gloperate/stages/interfaces/RenderInterface.h>
#include <gloperate/rendering/Camera.h>


/**
*  @brief
*    Demo stage that renders a static cube onto the screen
*/
class DemoDOFCubeStage : public gloperate::Stage
{
public:
    CPPEXPOSE_DECLARE_COMPONENT(
        DemoDOFCubeStage, gloperate::Stage
      , "RenderStage"   // Tags
      , ""              // Icon
      , ""              // Annotations
      , "Demo stage that renders a static cube onto the screen"
      , GLOPERATE_AUTHOR_ORGANIZATION
      , "v1.0.0"
    )


public:
    // Interfaces
    gloperate::RenderInterface renderInterface; ///< Interface for rendering into a viewer

    // Inputs
    Input<glm::vec2>           dofShift;        ///< DOF shift for multiframe rendering


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
    DemoDOFCubeStage(gloperate::Environment * environment, const std::string & name = "DemoDOFCubeStage");

    /**
    *  @brief
    *    Destructor
    */
    virtual ~DemoDOFCubeStage();


protected:
    // Virtual Stage functions
    virtual void onContextInit(gloperate::AbstractGLContext * context) override;
    virtual void onContextDeinit(gloperate::AbstractGLContext * context) override;
    virtual void onProcess(gloperate::AbstractGLContext * context) override;

    // Helper functions
    void setupGeometry();
    void setupProgram();


protected:
    // Rendering objects
    std::unique_ptr<globjects::VertexArray> m_vao;
    std::unique_ptr<globjects::Buffer>      m_vertexBuffer;
    std::unique_ptr<globjects::Program>     m_program;
    std::unique_ptr<globjects::Shader>      m_vertexShader;
    std::unique_ptr<globjects::Shader>      m_fragmentShader;
};