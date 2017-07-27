
#include "VectorStage.h"

#include <map>

#include <glm/vec2.hpp>
#include <glm/vec3.hpp>
#include <glm/vec4.hpp>

#include <cppassist/logging/logging.h>

#include <gloperate/gloperate.h>


CPPEXPOSE_COMPONENT(VectorStage, gloperate::Stage)


const std::map<char,size_t> VectorStage::s_indexByLabel = {
    {'x', 0}, {'y', 1}, {'z', 2}, {'w', 3},
    {'r', 0}, {'g', 1}, {'b', 2}, {'a', 3},
    {'s', 0}, {'t', 1}, {'p', 2}, {'q', 3},
    {'X', 0}, {'Y', 1}, {'Z', 2}, {'W', 3},
    {'R', 0}, {'G', 1}, {'B', 2}, {'A', 3},
    {'S', 0}, {'T', 1}, {'P', 2}, {'Q', 3}
};

VectorStage::VectorStage(gloperate::Environment * environment, const std::string & name)
: Stage(environment, "VectorStage", name)
{
}

VectorStage::~VectorStage()
{
}

void VectorStage::onProcess()
{
    glm::vec4 vec;

    // Collect provided values from inputs
    forAllInputs<float>([&vec](gloperate::Input<float>* input){
        auto name = input->name();

        if (name.size() != 1)
        {
            return;
        }

        auto value = **input;

        auto it = s_indexByLabel.find(name[0]);

        if (it != s_indexByLabel.end())
        {
            vec[it->second] = value;
        }
    });

    forAllInputs<glm::vec2>([&vec](gloperate::Input<glm::vec2>* input){
        auto name = input->name();

        if (name.size() != 2)
        {
            return;
        }

        auto value = **input;

        for (auto i = 0; i < 2; ++i)
        {
            auto it = s_indexByLabel.find(name[i]);

            if (it != s_indexByLabel.end())
            {
                vec[it->second] = value[i];
            }
        }
    });

    forAllInputs<glm::vec3>([&vec](gloperate::Input<glm::vec3>* input){
        auto name = input->name();

        if (name.size() != 3)
        {
            return;
        }

        auto value = **input;

        for (auto i = 0; i < 3; ++i)
        {
            auto it = s_indexByLabel.find(name[i]);

            if (it != s_indexByLabel.end())
            {
                vec[it->second] = value[i];
            }
        }
    });

    forAllInputs<glm::vec4>([&vec](gloperate::Input<glm::vec4>* input){
        auto name = input->name();

        if (name.size() != 4)
        {
            return;
        }

        auto value = **input;

        for (auto i = 0; i < 4; ++i)
        {
            auto it = s_indexByLabel.find(name[i]);

            if (it != s_indexByLabel.end())
            {
                vec[it->second] = value[i];
            }
        }
    });

    // Write requested values to outputs
    forAllOutputs<float>([&vec](gloperate::Output<float>* output){
        auto name = output->name();

        if (name.size() != 1)
        {
            return;
        }

        float value;

        auto it = s_indexByLabel.find(name[0]);

        if (it != s_indexByLabel.end())
        {
            value = vec[it->second];
        }

        *output = value;
    });

    forAllOutputs<glm::vec2>([&vec](gloperate::Output<glm::vec2>* output){
        auto name = output->name();

        if (name.size() != 2)
        {
            return;
        }

        glm::vec2 value;

        for (auto i = 0; i < 2; ++i)
        {
            auto it = s_indexByLabel.find(name[i]);

            if (it != s_indexByLabel.end())
            {
                value[i] = vec[it->second];
            }
        }

        *output = value;
    });

    forAllOutputs<glm::vec3>([&vec](gloperate::Output<glm::vec3>* output){
        auto name = output->name();

        if (name.size() != 3)
        {
            return;
        }

        glm::vec3 value;

        for (auto i = 0; i < 3; ++i)
        {
            auto it = s_indexByLabel.find(name[i]);

            if (it != s_indexByLabel.end())
            {
                value[i] = vec[it->second];
            }
        }

        *output = value;
    });

    forAllOutputs<glm::vec4>([&vec](gloperate::Output<glm::vec4>* output){
        auto name = output->name();

        if (name.size() != 4)
        {
            return;
        }

        glm::vec4 value;

        for (auto i = 0; i < 4; ++i)
        {
            auto it = s_indexByLabel.find(name[i]);

            if (it != s_indexByLabel.end())
            {
                value[i] = vec[it->second];
            }
        }

        *output = value;
    });
}
