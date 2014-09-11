/******************************************************************************\
 * gloperate
 *
 * Copyright (C) 2014 Computer Graphics Systems Group at the 
 * Hasso-Plattner-Institut (HPI), Potsdam, Germany.
\******************************************************************************/
#include <gloperate/plugin/PluginManager.h>
#include <globjects/logging.h>
#include <gloperate/plugin/PluginLibrary.h>
#include <gloperate/plugin/Plugin.h>


#ifdef WIN32
    // Implementation for Windows
    #include <Windows.h>

    class PluginLibraryImpl : public gloperate::PluginLibrary
    {
    public:
        PluginLibraryImpl(const std::string & filename)
            : gloperate::PluginLibrary(filename)
            , m_dll(0)
        {
            // Open library
            m_dll = LoadLibraryA(filename.c_str());
            if (m_dll) {
                // Get function pointers
                *reinterpret_cast<void**>(&m_initPluginPtr)      = GetProcAddress(m_dll, "initPlugin");
                *reinterpret_cast<void**>(&m_getNumOfPluginsPtr) = GetProcAddress(m_dll, "getNumOfPlugins");
                *reinterpret_cast<void**>(&m_getPluginPtr)       = GetProcAddress(m_dll, "getPlugin");
                *reinterpret_cast<void**>(&m_deinitPluginPtr)    = GetProcAddress(m_dll, "deinitPlugin");
            }
        }

        virtual ~PluginLibraryImpl() {
            // Close library
            if (m_dll) {
                FreeLibrary(m_dll);
            }
        }

    protected:
        HMODULE m_dll;
    };
#else
    // Implementation for POSIX systems
    #include <dlfcn.h>
    #include <libgen.h>

    class PluginLibraryImpl : public gloperate::PluginLibrary
    {
    public:
        PluginLibraryImpl(const std::string & filename)
        : gloperate::PluginLibrary(filename)
        , m_handle(0)
        {
            // Open library
            m_handle = dlopen(filename.c_str(), RTLD_NOW);
            if (m_handle) {
                // Get function pointers
                *reinterpret_cast<void**>(&m_initPluginPtr)      = dlsym(m_handle, "initPlugin");
                *reinterpret_cast<void**>(&m_getNumOfPluginsPtr) = dlsym(m_handle, "getNumOfPlugins");
                *reinterpret_cast<void**>(&m_getPluginPtr)       = dlsym(m_handle, "getPlugin");
                *reinterpret_cast<void**>(&m_deinitPluginPtr)    = dlsym(m_handle, "deinitPlugin");
            } else {
                globjects::debug() << dlerror();
            }
        }

        virtual ~PluginLibraryImpl() {
            // Close library
            if (m_handle) {
                dlclose(m_handle);
            }
        }

    protected:
        void * m_handle;
    };
#endif


namespace gloperate
{


std::string PluginManager::s_defaultPluginPath = "";


/**
*  @brief
*    Initialize plugin manager
*/
void PluginManager::init(const std::string & executablePath)
{
    #ifdef WIN32
        // Set default plugin path to the path of the executable
        HMODULE appModule = GetModuleHandle(0);
        char szFilename[MAX_PATH];
        char szDrive[8];
        char szPath[MAX_PATH];
        if (GetModuleFileNameA(appModule, szFilename, MAX_PATH) > 0) {
            _splitpath(szFilename, szDrive, szPath, NULL, NULL);
            PluginManager::s_defaultPluginPath = std::string(szDrive) + std::string(szPath);
        }
    #else
        // Save default plugin path
        PluginManager::s_defaultPluginPath = dirname(const_cast<char *>(executablePath.c_str()));
    #endif

    // Print default search path
    globjects::info() << "Default plugin path: " << PluginManager::s_defaultPluginPath;
}

/**
*  @brief
*    Constructor
*/
PluginManager::PluginManager()
{
}

/**
*  @brief
*    Destructor
*/
PluginManager::~PluginManager()
{
    // Note: The plugins do not need to (and must not) be destroyed, because this is done
    // inside the plugin library, when deinitialize() is called.

    // Close libraries
    for (gloperate::PluginLibrary * library : m_libraries) {
        library->deinitialize();
        delete library;
    }
}

/**
*  @brief
*    Get plugin directory
*
*  @return
*    Directory from which plugins are loaded
*/
std::string PluginManager::pluginDirectory() const
{
    return m_pluginDirectory;
}

/**
*  @brief
*    Set plugin directory
*
*  @param[in] path
*    Directory from which plugins are loaded
*/
void PluginManager::setPluginDirectory(const std::string & path)
{
    m_pluginDirectory = path;
}

/**
*  @brief
*    Load plugin
*/
void PluginManager::loadPlugin(const std::string & name)
{
    std::string dir = m_pluginDirectory.empty() ? PluginManager::s_defaultPluginPath : m_pluginDirectory;

#ifdef WIN32
    loadPluginLibrary(dir + "\\" + name + ".dll");
#elif defined(LINUX)
    loadPluginLibrary(dir + "/lib" + name + ".so");
#else
    loadPluginLibrary(dir + "/lib" + name + ".so");
#endif
}

/**
*  @brief
*    Load plugin library
*/
void PluginManager::loadPluginLibrary(const std::string & filename)
{
    PluginLibraryImpl * library = new PluginLibraryImpl(filename);
    if (library->isValid()) {
        // Add library
        m_libraries.push_back(library);

        // Initialize library
        library->initialize();

        // Iterate over plugins
        unsigned int numPlugins = library->getNumOfPlugins();
        for (unsigned int i=0; i<numPlugins; i++) {
            // Get plugin
            gloperate::Plugin * plugin = library->getPlugin(i);
            if (plugin) {
                // Add plugin
                m_plugins.push_back(plugin);
                std::string name = plugin->name();
                m_pluginsByName[name] = plugin;
            }
        }
    } else {
        // Error, close library
        delete library;
    }
}

/**
*  @brief
*    Get available plugins
*/
const std::vector<Plugin *> & PluginManager::plugins() const
{
    return m_plugins;
}

/**
*  @brief
*    Get plugin by name
*/
Plugin * PluginManager::plugin(const std::string & name) const
{
    // Get plugin
    if (m_pluginsByName.count(name) > 0) {
        return m_pluginsByName.at(name);
    }

    // Plugin not found
    return nullptr;
}


} // namespace gloperate
