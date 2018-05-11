#ifndef GENERATOR_MAP_GENERATOR_MANAGER_H
#define GENERATOR_MAP_GENERATOR_MANAGER_H

#include "generator/map_generator.h"
#include "generator/generator_buffer_proxy.h"
#include "script/script_engine.h"
#include "script/generator_script.h"

#include <array>
#include <chrono>
#include <vector>
#include <string>
#include <thread>

class MapGeneratorManager
{
public:
	using LayerList = std::vector<GeneratorBuffer>;
	using ProxyList = std::vector<GeneratorBufferProxy>;

	MapGeneratorManager(ScriptEngine& engine, ParameterLoader::GeneratorParameters& parameter_map, int buffer_size) :
        engine_(engine),
		layers_(),
		parameter_list_(parameter_map),
		current_layer(0),
		buffer_width_(buffer_size),
		buffer_height_(buffer_size),
		update_ready_(false)
	{
        for (auto i = 0u; i < generators_.size(); ++i)
        {
            generators_[i] = engine.createGenerator();
        }

        layer_names_ = generators_[0]->getLayerNames();

        for (int i = 0; i < layer_names_.size(); ++i)
        {
            layers_.emplace_back(buffer_width_, buffer_height_);
        }
	}

	void generate()
	{
        auto w = buffer_width_ / 2;
        auto h = buffer_height_ / 2;

        auto t1 = startWorker(generators_[0], 0, 0, w, h);
        auto t2 = startWorker(generators_[1], w, 0, w, h);
        auto t3 = startWorker(generators_[2], 0, h, w, h);
        auto t4 = startWorker(generators_[3], w, h, w, h);

        t1.join();
        t2.join();
        t3.join();
        t4.join();

        update_ready_ = true;
	}

	std::thread startWorker(GeneratorScript::Ptr& generator, int x, int y, int w, int h)
	{
		ProxyList proxies;

		for (auto& buffer : layers_)
		{
			proxies.emplace_back(buffer, x, y, w, h);
		}

        Layers layers(proxies);

		return std::thread(&GeneratorScript::generate, generator.get(), layers);
	}

	uint8_t* getBufferData()
	{
		update_ready_ = false;
		return layers_[current_layer].get();
	}

	bool isUpdateReady() const
	{
		return update_ready_;
	}

	void setUpdateReady(bool ready)
	{
		update_ready_ = ready;
	}

	void setCurrentLayer(int select)
	{
		current_layer = select;
	}

	const std::vector<std::string>& getCurrentLayerNames() const
	{
		return layer_names_;
	}

private:
    ScriptEngine & engine_;
	LayerList layers_;
	ProxyList proxies_;
    std::vector<std::string> layer_names_;

    std::array<GeneratorScript::Ptr, 4> generators_;

	ParameterLoader::GeneratorParameters& parameter_list_;

	int current_layer;
	int buffer_width_;
	int buffer_height_;

	volatile bool update_ready_;
};

#endif // GENERATOR_MAP_GENERATOR_MANAGER_H