#ifndef DISPLAY_MANAGER_H
#define DISPLAY_MANAGER_H

#include <cstdio>
#include "PixelMatrix.h"
#include <Windows.h>

class DisplayManager
{
private:
	PixelMatrix* curr_pm_;
	int height_;
	int width_;
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
	void Display();

};

#endif