#ifndef SCRIPT_GENERATOR_SCRIPT_H
#define SCRIPT_GENERATOR_SCRIPT_H

#include "script/layers.h"

#include <lua.hpp>
#include <luabind/luabind.hpp>

#include <memory>
#include <iostream>
#include <string>

class GeneratorScript
{
public:
    using Ptr = std::unique_ptr<GeneratorScript>;

    GeneratorScript(lua_State* L) : L_(L)
    {

    }

    ~GeneratorScript()
    {
        lua_close(L_);
    }

    void generate(Layers layers)
    {
        try
        {
            luabind::call_function<void>(L_, "generate", &layers);
        }
        catch (luabind::error& e)
        {
            std::string error = lua_tostring(e.state(), -1);
            std::cout << error << std::endl;
        }
    }

private:
    lua_State * L_;
};

#endif // SCRIPT_GENERATOR_SCRIPT_H