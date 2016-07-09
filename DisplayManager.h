#ifndef DISPLAY_MANAGER_H
#define DISPLAY_MANAGER_H

#include <cstdio>
#include "PixelMatrix.h"

#include "rpi-rgb-led-matrix/include/led-matrix.h"

using namespace rgb_matrix;

class DisplayManager
{
private:
	PixelMatrix* curr_pm_;
	int height_;
	int width_;
	GPIO io_;
	Canvas* rgb_matrix_;

	bool IsBlack(Pixel p);

public:
	DisplayManager(int, int);
	~DisplayManager();
	void Update();
	bool SetPixel(int, int, Color, Color, Color);
	Pixel GetPixel(int, int);
	void TogglePixelActivity(int, int);
	void FillDisplay(Color, Color, Color);
	void ClearDisplay();
	void MergeMatrices(PixelMatrix&);
	void MergeMatrices(PixelMatrix&, int, int);
//	void Display();

};

#endif
