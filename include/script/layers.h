#ifndef SCRIPT_LAYERS_H
#define SCRIPT_LAYERS_H

#include "generator/color.h"
#include "generator/generator_buffer_proxy.h"

#include <vector>

class Layers
{
public:
    Layers(std::vector<GeneratorBufferProxy>& p) : proxies_(p)
    {

    }

    void set(int i, int x, int y, Color& c)
    {
        proxies_[i].write(x, y, c);
    }

    int startX() const
    {
        return proxies_[0].startX();
    }

    int startY() const
    {
        return proxies_[0].startY();
    }

    int endX() const
    {
        return proxies_[0].endX();
    }

    int endY() const
    {
        return proxies_[0].endY();
    }

    int getWidth() const
    {
        return proxies_[0].getWidth();
    }

    int getHeight() const
    {
        return proxies_[0].getHeight();
    }


private:
    std::vector<GeneratorBufferProxy> proxies_;
};

#endif //