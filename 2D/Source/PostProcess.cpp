#include "PostProcess.h"
#include "MathUtils.h"
#include <algorithm>
#include <cmath>

namespace PostProcess
{
	void Invert(std::vector<color_t>& buffer)
	{

		
		std::for_each(buffer.begin(), buffer.end(), [](auto& c)
			{
				c.r = 255 - c.r;
				c.g = 255 - c.g;
				c.b = 255 - c.b;
			});
	}

	void Monochrome(std::vector<color_t>& buffer)
	{
		std::for_each(buffer.begin(), buffer.end(), [](auto& c)
			{
				uint8_t average = static_cast<uint8_t>((c.r + c.g + c.b) / 3);
				
				c.r = average;
				c.g = average;
				c.b = average;
			});
	}
	void Brightness(std::vector<color_t>& buffer, int16_t brightness)
	{
		std::for_each(buffer.begin(), buffer.end(), [brightness](auto& c)
			{
				
				c.r = static_cast<uint8_t>(Clamp(c.r + brightness, 255,0));
				c.g = static_cast<uint8_t>(Clamp(c.g + brightness,255,0));
				c.b = static_cast<uint8_t>(Clamp(c.b + brightness, 255, 0));
			});
	}
	void ColorBalance(std::vector<color_t>& buffer, int ro, int go, int bo)
	{
		std::for_each(buffer.begin(), buffer.end(), [ro,go,bo](auto& c)
			{

				c.r = static_cast<uint8_t>(Clamp((c.r + ro), 255, 0));
				c.g = static_cast<uint8_t>(Clamp((c.g + go), 255, 0));
				c.b = static_cast<uint8_t>(Clamp((c.b + bo), 255, 0));
			});
		
	}
	void Noise(std::vector<color_t>& buffer, uint8_t noise)
	{
		std::for_each(buffer.begin(), buffer.end(), [noise](auto& c)
			{
				int offset = (rand() % ((noise * 2) + 1)) - noise;
				
				
				c.r = c.r + static_cast<uint8_t>(Clamp(c.r + offset, 255, 0));
				c.g = c.g + static_cast<uint8_t>(Clamp(c.g + offset, 255, 0));
				c.b = c.b + static_cast<uint8_t>(Clamp(c.b + offset, 255, 0));
			});
	}
	void BoxBlur(std::vector<color_t>& buffer, int width, int height)
	{
		std::vector<color_t> source = buffer;
		int k[3][3] =
		{
			{1,1,1},
			{1,1,1},
			{1,1,1}
		};

		for (int i = 0; i < buffer.size(); i++)
		{
			int x = i % width;
			int y = i / width;

			if (x < 1 || x + 1 >= width || y < 1 || y + 1 >= height) continue;

			int r = 0;
			int g = 0;
			int b = 0;
			for (int iy = 0; iy < 3; iy++)
			{
				for (int ix = 0; ix < 3; ix++)
				{
					color_t pixel = source[(x + ix - 1) + (y + iy - 1) * width];
					int weight = k[iy][ix];

					r += pixel.r * weight;
					g += pixel.g * weight;
					b += pixel.b * weight;
				}
			}
			color_t& color = buffer[i];
			color.r = static_cast<uint8_t>(r / 9);
			color.g = static_cast<uint8_t>(g / 9);
			color.b = static_cast<uint8_t>(b / 9);
		}
	}
	void GauseanBlur(std::vector<color_t>& buffer, int width, int height)
	{
		std::vector<color_t> source = buffer;
		int k[3][3] =
		{
			{1,2,1},
			{2,4,2},
			{1,2,1}
		};

		for (int i = 0; i < buffer.size(); i++)
		{
			int x = i % width;
			int y = i / width;

			if (x < 1 || x + 1 >= width || y < 1 || y + 1 >= height) continue;

			int r = 0;
			int g = 0;
			int b = 0;
			for (int iy = 0; iy < 3; iy++)
			{
				for (int ix = 0; ix < 3; ix++)
				{
					color_t pixel = source[(x + ix - 1) + (y + iy - 1) * width];
					int weight = k[iy][ix];

					r += pixel.r * weight;
					g += pixel.g * weight;
					b += pixel.b * weight;
				}
			}
			color_t& color = buffer[i];
			color.r = static_cast<uint8_t>(r / 16);
			color.g = static_cast<uint8_t>(g / 16);
			color.b = static_cast<uint8_t>(b / 16);
		}
	}
	void Sharpen(std::vector<color_t>& buffer, int width, int height)
	{
		std::vector<color_t> source = buffer;
		int k[3][3] =
		{
			{0,-1,0},
			{-1,5,-1},
			{0,-1,0}
		};

		for (int i = 0; i < buffer.size(); i++)
		{
			int x = i % width;
			int y = i / width;

			if (x < 1 || x + 1 >= width || y < 1 || y + 1 >= height) continue;

			int r = 0;
			int g = 0;
			int b = 0;
			for (int iy = 0; iy < 3; iy++)
			{
				for (int ix = 0; ix < 3; ix++)
				{
					color_t pixel = source[(x + ix - 1) + (y + iy - 1) * width];
					int weight = k[iy][ix];

					r += pixel.r * weight;
					g += pixel.g * weight;
					b += pixel.b * weight;
				}
			}
			color_t& color = buffer[i];
			color.r = static_cast<uint8_t>(Clamp(r, 255,0));
			color.g = static_cast<uint8_t>(Clamp(g,255,0));
			color.b = static_cast<uint8_t>(Clamp(b,255,0));
		}
	}
	void Edge(std::vector<color_t>& buffer, int width, int height, int threshold)
	{
		std::vector<color_t> source = buffer;
		int16_t hk[3][3] =
		{
			{ 1, 0, -1 },
			{ 2, 0, -2 },
			{ 1, 0, -1 },
		};

		int16_t vk[3][3] =
		{
			{ -1, -2, -1 },
			{  0,  0,  0 },
			{  1,  2,  1 },
		};

		for (int i = 0; i < buffer.size(); i++)
		{
			int x = i % width;
			int y = i / width; 

			if (x < 1 || x >= width - 1 || y < 1 || y >= height - 1) continue;

			int h = 0;
			int v = 0;

			//chat gpt helped configer a range that wasn't out of bounds 
			for (int iy = -1; iy <= 1; iy++)  
			{
				for (int ix = -1; ix <= 1; ix++)  
				{
					h += source[(x + ix) + (y + iy) * width].r * hk[iy + 1][ix + 1];
					v += source[(x + ix) + (y + iy) * width].r * vk[iy + 1][ix + 1];
				}
			}

			uint16_t m = (uint16_t)sqrt((h * h) + (v * v));
			m = (m > threshold) ? m : 0;

			uint8_t c = (m < 0) ? 0 : ((m > 255) ? 255 : m);

			color_t& color = buffer[i];
			color.r = c;
			color.g = c;
			color.b = c;
		}
		
	}
	void Threshold(std::vector<color_t>& buffer, uint8_t threshold)
	{
		std::for_each(buffer.begin(), buffer.end(), [threshold](auto& c)
			{
				if (c.r > threshold && c.g > threshold && c.b > threshold)
				{
					c.r = c.g = c.b = 255;
				}
				else
				{
					c.r = c.g = c.b = 0;
				}
			
			});
	}
	void Posterize(std::vector<color_t>& buffer, uint8_t levels)
	{
		uint8_t colorLevel = static_cast < uint8_t>(255 / levels);
		std::for_each(buffer.begin(), buffer.end(), [colorLevel](auto& c)
			{

				c.r = (c.r / colorLevel) * colorLevel;
				c.g = (c.g / colorLevel) * colorLevel;
				c.b = (c.b / colorLevel) * colorLevel;
			});
	}
	void Emboss(std::vector<color_t>& buffer, int width, int height)
	{
		std::vector<color_t> source = buffer;
		int16_t hk[3][3] =
		{
			{-1,-1,0},
			{-1,0,1},
			{0,1,1}
		};


		for (int i = 0; i < buffer.size(); i++)
		{
			int x = i % width;
			int y = i / width;
			if (x < 1 || x >= width - 1 || y < 1 || y >= height - 1) continue;

			int r = 0;
			int g = 0;
			int b = 0;


			for (int iy = -1; iy <= 1; iy++)
			{
				for (int ix = -1; ix <= 1; ix++)
				{
					//helped with chat gpt 
					const color_t& pixel = source[(x + ix) + (y + iy) * width];
					int weight = hk[iy + 1][ix + 1];

					r += pixel.r * weight;
					g += pixel.g * weight;
					b += pixel.b * weight;
				}
			}

			color_t& color = buffer[i];
			color.r = static_cast<uint8_t>(Clamp(r + 128, 255, 0));
			color.g = static_cast<uint8_t>(Clamp(g + 128, 255, 0));
			color.b = static_cast<uint8_t>(Clamp(b + 128, 255, 0));
		}
		
	}
	void Alpha(std::vector<color_t>& buffer, uint8_t alpha)
	{
		std::for_each(buffer.begin(), buffer.end(), [alpha](color_t& c)
			{
				c.a = alpha;
			});
	}
}
