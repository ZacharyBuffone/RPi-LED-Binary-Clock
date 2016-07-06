#include <cstdio>
#include <time.h>
#include "DisplayManager.h"
#include "PixelMatrix.h"

static const int HEIGHT = 32;
static const int WIDTH = 32;
static const int FONT_HEIGHT = 4;
static const int FONT_WIDTH = 3;
static const int FONT_BUFFER = 1;

void PrintPixels(DisplayManager& dm);

int main(int argc, char* argv[])
{
	DisplayManager dm = DisplayManager(HEIGHT, WIDTH);
	dm.SetPixel(0, 0, 255, 255, 255);
	dm.SetPixel(2, 9, 255, 255, 255);
	dm.SetPixel(5, 10, 255, 255, 255);
	dm.SetPixel(10, 10, 255, 255, 255);
	dm.SetPixel(10, 5, 255, 255, 255);


	PixelMatrix pm = PixelMatrix(4, 3);
	*pm.At(0, 0) = Pixel{ 255, 255, 255 };
	*pm.At(1, 0) = Pixel{ 255, 255, 255 };
	*pm.At(2, 0) = Pixel{ 255, 255, 255 };
	*pm.At(0, 3) = Pixel{ 255, 255, 255 };
	*pm.At(1, 3) = Pixel{ 255, 255, 255 };
	*pm.At(2, 3) = Pixel{ 255, 255, 255 };
	*pm.At(0, 1) = Pixel{ 255, 255, 255 };
	*pm.At(0, 2) = Pixel{ 255, 255, 255 };
	*pm.At(2, 1) = Pixel{ 255, 255, 255 };
	*pm.At(2, 2) = Pixel{ 255, 255, 255 };

	dm.MergeMatrices(pm, 1, 1);
	dm.Display();
	PrintPixels(dm);

	printf("test\n");
}

void PrintPixels(DisplayManager& dm)
{
	Pixel next_pixel;
	for (int i = 0; i < HEIGHT; i++)
	{
		for (int j = 0; j < WIDTH; j++)
		{
			next_pixel = dm.GetPixel(j, i);
			printf("Pixel at x=%d, y=%d : { %d, %d, %d }\n", j, i, next_pixel.red, next_pixel.green, next_pixel.blue);
		}

	}
	return;
}

std::vector<PixelMatrix>* GetBinaryTime()
{
	std::vector<PixelMatrix>* font_vector = new std::vector<PixelMatrix>();
	time_t time;

	time(&time);


}