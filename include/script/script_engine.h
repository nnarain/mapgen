#ifndef SCRIPT_SCRIPT_ENGINE
#define SCRIPT_SCRIPT_ENGINE

#include "script/generator_script.h"

#include <lua.hpp>
#include <luabind/luabind.hpp>

#include <fstream>
#include <string>
#include <sstream>
#include <stdexcept>

/**
    Load and 
*/
class ScriptEngine
{
public:
    ScriptEngine(const std::string& filename) :
        script_(filename)
    {
    }

    ~ScriptEngine()
    {
    }

    GeneratorScript createGenerator()
    {
        using namespace luabind;

        // create a lua instance
        lua_State* L = lua_open();

        // open the lua instance and import libs
        open(L);
        luaL_openlibs(L);

        // enable JIT
        luaJIT_setmode(L, 0, LUAJIT_MODE_ENGINE | LUAJIT_MODE_ON);
        //luaJIT_setmode(L, 0, LUAJIT_MODE_ALLFUNC | LUAJIT_MODE_ON);

        // load the file
        luaL_dofile(L, script_.c_str());

        // grab file metadata...

        return GeneratorScript(L);
    }

private:
    std::string script_;
};

#endif