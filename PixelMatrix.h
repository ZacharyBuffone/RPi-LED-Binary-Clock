#ifndef PIXEL_MATRIX_H_
#define PIXEL_MATRIX_H_

#include <vector>

typedef unsigned char Color;

typedef struct pixel
{
	Color red;
	Color green;
	Color blue;

} Pixel;


class PixelMatrix
{
private:
	int height_;
	int width_;
	std::vector<Pixel*>* pixels_;

public:
	PixelMatrix(int, int);
	PixelMatrix(PixelMatrix&);
	~PixelMatrix();

	int GetHeight() { return height_; };
	int GetWidth() { return width_; }

	Pixel* At(int, int);

	void Clear();

	bool Merge(PixelMatrix&);
	bool Merge(PixelMatrix&, int, int);
};

#endif