#ifndef GENERATOR_GENERATOR_BUFFER_PROXY_H
#define GENERATOR_GENERATOR_BUFFER_PROXY_H

#include "generator/generator_buffer.h"
#include "generator/color.h"

class GeneratorBufferProxy
{
public:
	GeneratorBufferProxy(GeneratorBuffer& buffer, int x, int y, int w, int h) :
		buffer_(buffer),
		x_(x),
		y_(y),
		w_(w),
		h_(h)

	{

	}

	void write(int x, int y, Color& c)
	{
		buffer_.write(x, y, c);
	}

	const GeneratorBuffer& getBuffer() const
	{
		return buffer_;
	}

	int startX() const
	{
		return x_;
	}

	int startY() const
	{
		return y_;
	}

	int endX() const
	{
		return x_ + w_;
	}

	int endY() const
	{
		return y_ + h_;
	}

	int getWidth() const
	{
		return w_;
	}

	int getHeight() const
	{
		return h_;
	}

	~GeneratorBufferProxy()
	{
	}

private:
	GeneratorBuffer & buffer_;

	int x_;
	int y_;
	int w_;
	int h_;

};

#endif  // GENERATOR_GENERATOR_BUFFER_PROXY_H