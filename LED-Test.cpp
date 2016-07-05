#include <cstdio>
#include "DisplayManager.h"
#include "PixelMatrix.h"

static const int HEIGHT = 32;
static const int WIDTH = 32;

int main(int argc, char* argv[])
{
	DisplayManager dm = DisplayManager(HEIGHT, WIDTH);
	dm.SetPixel(0, 0, 255, 255, 255);
	dm.SetPixel(5, 5, 255, 255, 255);
	dm.SetPixel(5, 10, 255, 255, 255);
	dm.SetPixel(10, 10, 255, 255, 255);
	dm.SetPixel(10, 5, 255, 255, 255);


	PixelMatrix pm = PixelMatrix(HEIGHT, WIDTH);
	*pm.At(0, 1) = Pixel{ 255, 255, 255, true };
	*pm.At(0, 2) = Pixel{ 255, 255, 255, true };
	*pm.At(0, 3) = Pixel{ 255, 255, 255, true };
	*pm.At(25, 7) = Pixel{ 255, 255, 255, true };

	dm.MergeMatrices(&pm);

	Pixel next_pixel;
	for (int i = 0; i < HEIGHT; i++)
	{
		for (int j = 0; j < WIDTH; j++)
		{
			next_pixel = dm.GetPixel(j, i);
			printf("Pixel at x=%d, y=%d : { %d, %d, %d }\n", j, i, next_pixel.red, next_pixel.green, next_pixel.blue);
		}

	}

	printf("test\n");
}