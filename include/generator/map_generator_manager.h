#ifndef GENERATOR_MAP_GENERATOR_MANAGER_H
#define GENERATOR_MAP_GENERATOR_MANAGER_H

#include "generator/map_generator.h"
#include "generator/generator_buffer_proxy.h"

#include <array>
#include <chrono>
#include <vector>
#include <string>
#include <thread>

class MapGeneratorManager
{
public:
	using GeneratorList = std::vector<MapGenerator::Ptr>;
	using LayerList = std::vector<GeneratorBuffer>;
	using ProxyList = std::vector<GeneratorBufferProxy>;

	MapGeneratorManager(GeneratorList& list, ParameterLoader::ParameterMap& parameter_map, int buffer_size) :
		generators_(list),
		layers_(),
		parameter_map_(parameter_map),
		current_map_generator_(0),
		current_layer(0),
		buffer_width_(buffer_size),
		buffer_height_(buffer_size),
		update_ready_(false)
	{
		setCurrentGenerator(current_map_generator_);
	}

	void generate()
	{
		// get the current generator
		auto& generator = generators_[current_map_generator_];

		if (generator)
		{
			// reload parameters
			generator->loadParams(parameter_map_[generator->getName()]);

			auto w = buffer_width_ / 2;
			auto h = buffer_height_ / 2;

			auto t1 = startWorker(generator, 0, 0, w, h);
			auto t2 = startWorker(generator, w, 0, w, h);
			auto t3 = startWorker(generator, 0, h, w, h);
			auto t4 = startWorker(generator, w, h, w, h);
			
			t1.join();
			t2.join();
			t3.join();
			t4.join();
		}

		update_ready_ = true;
	}

	std::thread startWorker(MapGenerator::Ptr& ptr, int x, int y, int w, int h)
	{
		ProxyList proxies;

		for (auto& buffer : layers_)
		{
			proxies.emplace_back(buffer, x, y, w, h);
		}

		return std::thread(&MapGenerator::generate, ptr.get(), proxies);
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

	const MapGenerator::Ptr& getCurrentMapGenerator() const
	{
		return generators_[current_map_generator_];
	}

	void setCurrentGenerator(int select)
	{
		current_map_generator_ = select;

		// allocate layers
		const auto num_layers = getCurrentLayerNames().size();
		layers_.clear();
		for (auto i = 0u; i < num_layers; ++i)
		{
			layers_.push_back(GeneratorBuffer(buffer_width_, buffer_height_));
		}
	}

	void setCurrentLayer(int select)
	{
		current_layer = select;
	}

	std::vector<std::string> getGeneratorNames() const
	{
		std::vector<std::string> names;
		for (const auto& generator : generators_)
		{
			names.push_back(generator->getName());
		}

		return names;
	}

	std::vector<std::string> getCurrentLayerNames() const
	{
		return generators_[current_map_generator_]->getLayerNames();
	}

private:
	using clock = std::chrono::system_clock;

	GeneratorList& generators_;
	LayerList layers_;
	ProxyList proxies_;

	ParameterLoader::ParameterMap& parameter_map_;

	int current_map_generator_;
	int current_layer;
	int buffer_width_;
	int buffer_height_;

	volatile bool update_ready_;
};

#endif // GENERATOR_MAP_GENERATOR_MANAGER_H