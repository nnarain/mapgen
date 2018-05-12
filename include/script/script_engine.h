#ifndef SCRIPT_SCRIPT_ENGINE
#define SCRIPT_SCRIPT_ENGINE

#include "script/generator_script.h"

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
    ScriptEngine(const std::string& filename);

    ~ScriptEngine();

    GeneratorScript::Ptr createGenerator();

private:
    std::string script_;
};

#endif