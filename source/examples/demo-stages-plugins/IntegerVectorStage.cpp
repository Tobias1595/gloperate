
#include "IntegerVectorStage.h"

#include <map>

#include <glm/vec2.hpp>
#include <glm/vec3.hpp>
#include <glm/vec4.hpp>

#include <cppassist/logging/logging.h>

#include <gloperate/gloperate.h>


CPPEXPOSE_COMPONENT(IntegerVectorStage, gloperate::Stage)


const std::map<char, size_t> IntegerVectorStage::s_indexByLabel = {
    {'x', 0}, {'y', 1}, {'z', 2}, {'w', 3},
    {'r', 0}, {'g', 1}, {'b', 2}, {'a', 3},
    {'s', 0}, {'t', 1}, {'p', 2}, {'q', 3},
    {'X', 0}, {'Y', 1}, {'Z', 2}, {'W', 3},
    {'R', 0}, {'G', 1}, {'B', 2}, {'A', 3},
    {'S', 0}, {'T', 1}, {'P', 2}, {'Q', 3}
};

IntegerVectorStage::IntegerVectorStage(gloperate::Environment * environment, const std::string & name)
: Stage(environment, "IntegerVectorStage", name)
{
}

IntegerVectorStage::~IntegerVectorStage()
{
}

void IntegerVectorStage::onProcess()
{
    glm::ivec4 vec;

    // Collect provided values from inputs
    forAllInputs<int>([&vec](gloperate::Input<int>* input){
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

    forAllInputs<glm::ivec2>([&vec](gloperate::Input<glm::ivec2>* input){
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

    forAllInputs<glm::ivec3>([&vec](gloperate::Input<glm::ivec3>* input){
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

    forAllInputs<glm::ivec4>([&vec](gloperate::Input<glm::ivec4>* input){
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
    forAllOutputs<int>([&vec](gloperate::Output<int>* output){
        auto name = output->name();

        if (name.size() != 1)
        {
            return;
        }

        int value;

        auto it = s_indexByLabel.find(name[0]);

        if (it != s_indexByLabel.end())
        {
            value = vec[it->second];
        }

        *output = value;
    });

    forAllOutputs<glm::ivec2>([&vec](gloperate::Output<glm::ivec2>* output){
        auto name = output->name();

        if (name.size() != 2)
        {
            return;
        }

        glm::ivec2 value;

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

    forAllOutputs<glm::ivec3>([&vec](gloperate::Output<glm::ivec3>* output){
        auto name = output->name();

        if (name.size() != 3)
        {
            return;
        }

        glm::ivec3 value;

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

    forAllOutputs<glm::ivec4>([&vec](gloperate::Output<glm::ivec4>* output){
        auto name = output->name();

        if (name.size() != 4)
        {
            return;
        }

        glm::ivec4 value;

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
