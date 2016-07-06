#include "PixelMatrix.h"

//PixelMatrix is a matrix of Colors such that coords (x, y)
//are in vector pixels_ as (x*width) + y.

PixelMatrix::PixelMatrix(int height, int width)
{
	height_ = height;
	width_ = width;

	pixels_ = new std::vector<Pixel*>(height*width);

	for (int i = 0; i < height*width; i++)
		pixels_->at(i) = new Pixel{ 0, 0, 0 };

	return;
}

PixelMatrix::PixelMatrix(PixelMatrix& copy_of)
{
	height_ = copy_of.height_;
	width_ = copy_of.width_;

	pixels_ = new std::vector<Pixel*>(height_*width_);

	for (int i = 0; i < height_*width_; i++)
	{
		pixels_->at(i) = new Pixel(*(copy_of.pixels_->at(i)));
	}

	return;
}

PixelMatrix::~PixelMatrix()
{
	for (int i = 0; i < height_*width_; i++)
		delete pixels_->at(i);
	delete pixels_;

	return;
}

Pixel* PixelMatrix::At(int x, int y)
{
	return pixels_->at((x*width_) + y);
}

void PixelMatrix::Clear()
{
	Pixel* next_pixel;

	for (int i = 0; i < height_*width_; i++)
	{
		next_pixel = pixels_->at(i);
		*next_pixel = Pixel{ 0, 0, 0 };
	}

	return;
}

bool PixelMatrix::Merge(PixelMatrix& merging)
{
	if (height_ < merging.height_ || width_ < merging.width_)
		return false;

	Pixel* next_pixel_to_merge;
	Pixel* next_pixel_to_change;
	for (int i = 0; i < merging.height_*merging.width_; i++)
	{
		next_pixel_to_merge = merging.pixels_->at(i);
		next_pixel_to_change = this->pixels_->at(i);

		*next_pixel_to_change = *next_pixel_to_merge;
	}
	return true;
}

bool PixelMatrix::Merge(PixelMatrix& merging, int start_x, int start_y)
{
	if (start_x + merging.width_ > height_ || start_y + merging.height_ > width_)
		return false;

	Pixel* next_pixel_to_merge;
	Pixel* next_pixel_to_change;

	for (int i = 0; i < merging.width_; i++)
	{
		for (int j = 0; j < merging.height_; j++)
		{
			next_pixel_to_merge = merging.At(i, j);
			next_pixel_to_change = this->At(start_x + i, start_y + j);

			*next_pixel_to_change = *next_pixel_to_merge;
		}
	}

	return true;
}
