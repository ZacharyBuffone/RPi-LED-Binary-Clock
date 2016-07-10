#include <cstdio>
#include <ctime>
#include <vector>
#include <thread>
#include <cstring>
#include <cstdlib>
#include "DisplayManager.h"
#include "PixelMatrix.h"
#include "FontGenerator.h"

static const int HEIGHT = 32;
static const int WIDTH = 32;
static const int FONT_HEIGHT = 4;
static const int FONT_WIDTH = 3;
static const int FONT_BUFFER = 1;

void PrintPixels(DisplayManager& dm);


int main(int argc, char* argv[])
{
	int brightness = 100;
	for(int i = 0; i < argc; i++)
	{
		if(std::strcmp(argv[i], "-b") == 0)
			brightness = std::atoi(argv[i+1]);
	}

	//set up locals for Display manager and FontGenerator
	DisplayManager dm = DisplayManager(HEIGHT, WIDTH, brightness);
	FontGenerator fg = FontGenerator();
	bool playing = true;

	printf("Binary clock running.\nPress ctrl-c to exit.\n");

	while (playing)
	{
		//clears the display and updates the font generator
		dm.ClearDisplay();
		fg.Update();

		std::vector<PixelMatrix*>* hour = fg.GetHourVector();
		std::vector<PixelMatrix*>* minute = fg.GetMinuteVector();
		std::vector<PixelMatrix*>* second = fg.GetSecondVector();

		//pointers to the PixelMatrix in font vectors are merged with DisplayManager's matrix
		for (int i = 0; i < (int) hour->size(); i++)
			dm.MergeMatrices(*(hour->at(i)), 1 + i * (FontGenerator::FONT_WIDTH + 1), 1);
		for (int i = 0; i < (int) minute->size(); i++)
			dm.MergeMatrices(*(minute->at(i)), 1 + i * (FontGenerator::FONT_WIDTH + 1), FontGenerator::FONT_HEIGHT  + 4);
		for (int i = 0; i < (int) second->size(); i++)
			dm.MergeMatrices(*(second->at(i)), 1 + i * (FontGenerator::FONT_WIDTH + 1), (FontGenerator::FONT_HEIGHT *  2) + 7);

		//update and sleep the thread for about 1 sec
		dm.Update();

		std::this_thread::sleep_for(std::chrono::milliseconds(1010));
	}

	return 0;
}


//for debuging. prints pixels in DisplayManager's matrix
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
