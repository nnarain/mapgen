#ifndef SCRIPT_PARAMETERS_H
#define SCRIPT_PARAMETERS_H

#include <parameters/parameter_loader.h>
#include <parameters/parameter_value.h>
#include <generator/color.h>

#include <FastNoise.h>
#include <factory/fastnoise_factory.h>

#include <unordered_map>
#include <stdexcept>

class Parameters
{
public:
    Parameters(ParameterLoader::GeneratorParameters& params) :
        params_(params)
    {
    }

    float getFloat(const std::string& name)
    {
        return getParam(params_, name).param.value;
    }

    Color* getColor(const std::string& name)
    {
        if (color_map_.find(name) != color_map_.end())
        {
            return &color_map_[name];
        }
        else
        {
            float* values = getParam(params_, name).param.color;
            Color c(values[0], values[1], values[2], values[3]);

            color_map_[name] = c;

            return &color_map_[name];
        }
    }

    FastNoise* getNoise(const std::string& name)
    {
        if (noise_map_.find(name) != noise_map_.end())
        {
            return &noise_map_[name];
        }
        else
        {
            auto noise_params = getParam(params_, name).param.noise;
            noise_map_[name] = FastNoiseFactory::create(noise_params);

            return &noise_map_[name];
        }
    }

private:
    ParameterValue & getParam(ParameterLoader::GeneratorParameters& params, const std::string& name)
    {
        for (auto& param : params)
        {
            if (param.first == name)
            {
                return param.second;
            }
        }

        throw std::runtime_error("Could not find parameter value");
    }

    ParameterLoader::GeneratorParameters& params_;
    std::unordered_map<std::string, Color> color_map_;
    std::unordered_map<std::string, FastNoise> noise_map_;
};

#endif // SCRIPT_PARAMETERS_H