#include <iostream>
#include <fstream>
#include <ctime>

#include "Util/Random.h"
#include "Util/Config.h"
#include "Util/Singleton.h"
#include "Util/Native.h"

#include "Application.h"
#include "Display.h"



#ifdef __WIN32
    extern "C"
    {
        //Enable dedicated graphics
        __declspec(dllexport) bool NvOptimusEnablement = true;
        __declspec(dllexport) bool AmdPowerXpressRequestHighPerformance = true;
    }
#endif // __WIN32


namespace
{
    void errorMessage(const std::string& message)
    {
        #ifdef __WIN32
            MessageBox(nullptr, message.c_str(), "Error", MB_OK);
            std::cerr << message << std::endl;
        #elif __linux__ || __APPLE__
            const std::string command = "zenity --error --text \"" + message + "\"";
            system(command.c_str());
        #else
            std::cerr << message << std::endl;
            std::cin.ignore();
        #endif
    }

    void initilize()
    {
        //cheeky
        getDisplay();
        Random::init();

        //This is so that the RNG is more random
        //Or else, first value seems to be the same
        for (int i = 0; i < 15; i++)
        {
            Random::intInRange(0, RAND_MAX);
        }
    }

    void loadConfig()
    {
        const std::string fileName = "HopsonCraft.conf";
        std::ifstream inFile (fileName);

        if(inFile.is_open())
        {
            Singleton<Config>::get().loadFromStream(fileName, inFile);
        }
    }
}

//entry
int main()
{
    try
    {
        initilize();
        loadConfig();

        Application app;
        app.runMainGameLoop();
        return EXIT_SUCCESS;
    }
    catch(std::exception& e)
    {
        return EXIT_FAILURE;
    }
}
