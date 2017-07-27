
#pragma once


#include <cppexpose/plugin/plugin_api.h>

#include <gloperate/gloperate-version.h>
#include <gloperate/pipeline/Stage.h>


/**
*  @brief
*    Stage that collects and provides components from GLM vectors using swizzling
*
*  @remarks
*    The swizzle patterns are provided through the names of the in- & outputs. Therefore
*    the length of the name has to match the number of provided / requested components.
*    Slots with names of the wrong length will be ignored.
*    Invalid entries in swizzling patterns are ignored for input components and produce
*    the value 0 for output components.
*
*  @remarks
*    When assigning the same component through multiple inputs, the value of the input added last will be used.
*/
class VectorStage : public gloperate::Stage
{
public:
    CPPEXPOSE_DECLARE_COMPONENT(
        VectorStage, gloperate::Stage
      , "" // Tags
      , "" // Icon
      , "" // Annotations
      , "Stage that collects and provides components from GLM vectors using swizzling"
      , GLOPERATE_AUTHOR_ORGANIZATION
      , "v1.0.0"
    )

    // All in- & outputs are dynamic

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
    VectorStage(gloperate::Environment * environment, const std::string & name = "VectorStage");

    /**
    *  @brief
    *    Destructor
    */
    virtual ~VectorStage();


protected:
    // Virtual Stage functions
    virtual void onProcess() override;

protected:
    static const std::map<char,size_t> VectorStage::s_indexByLabel;
};
