#include <vector>
#include <gloperate/plugin/plugin_api.h>
#include <gloperate/plugin/Plugin.h>
#include <extended-examples/ExtendedCubeScape/ExtendedCubeScape.h>


static std::vector<gloperate::Plugin *> g_plugins;


class Plugin_ExtendedCubeScape : public gloperate::Plugin {
public:
    Plugin_ExtendedCubeScape()
    : gloperate::Plugin(
        "Painter"
      , "ExtendedCubeScape"
      , "Displays a CubeScape"
      , "gloperate team"
      , "v1.0.0" )
    {
    }

    ~Plugin_ExtendedCubeScape()
    {
    }

    virtual gloperate::Painter * createPainter() const
    {
        return new ExtendedCubeScape();
    }
};


extern "C" GLOPERATE_PLUGIN_API void initPlugin()
{
    g_plugins.push_back(new Plugin_ExtendedCubeScape());
}

extern "C" GLOPERATE_PLUGIN_API int getNumOfPlugins()
{
    return (int)g_plugins.size();
}

extern "C" GLOPERATE_PLUGIN_API gloperate::Plugin * getPlugin(unsigned int index)
{
    if (index < (unsigned int)g_plugins.size()) {
        return g_plugins[index];
    } else {
        return nullptr;
    }
}

extern "C" GLOPERATE_PLUGIN_API void deinitPlugin()
{
    for (std::vector<gloperate::Plugin *>::iterator it = g_plugins.begin(); it != g_plugins.end(); ++it) {
        gloperate::Plugin * plugin = *it;
        delete plugin;
    }
    g_plugins.clear();
}