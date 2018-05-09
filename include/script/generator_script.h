#ifndef SCRIPT_GENERATOR_SCRIPT_H
#define SCRIPT_GENERATOR_SCRIPT_H

#include <lua.hpp>
#include <luabind/luabind.hpp>

class GeneratorScript
{
public:
    GeneratorScript(lua_State* L) : L_(L)
    {

    }

    ~GeneratorScript()
    {
        lua_close(L_);
    }

    void run()
    {
        luabind::call_function<void>(L_, "generate");
    }

private:
    lua_State * L_;
};

#endif // SCRIPT_GENERATOR_SCRIPT_H