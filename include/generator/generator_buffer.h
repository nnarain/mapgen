#ifndef GENERATOR_GENERATOR_BUFFER_H
#define GENERATOR_GENERATOR_BUFFER_H

#include <vector>

class GeneratorBuffer
{
public:
	const int PIXEL_SIZE = 4;

	GeneratorBuffer(int w, int h) :
		buffer_(w * h * 4, 255),
		width_(w),
		height_(h)
	{
	}

	template<typename PixelT>
	void write(int x, int y, PixelT& pixel)
	{
		const unsigned int pixels_per_row = width_;

		unsigned int byte_offset = ((y * pixels_per_row) + x) * PIXEL_SIZE;

		buffer_[byte_offset + 0] = pixel.r;
		buffer_[byte_offset + 1] = pixel.g;
		buffer_[byte_offset + 2] = pixel.b;
		buffer_[byte_offset + 3] = pixel.a;
	}

	uint8_t* get()
	{
		return &buffer_[0];
	}

	int getWidth() const
	{
		return width_;
	}

	int getHeight() const
	{
		return height_;
	}

private:
	std::vector<uint8_t> buffer_;
	int width_;
	int height_;
};

#endif // GENERATOR_GENERATOR_BUFFER_H