#include "DisplayManager.h"
#include "PixelMatrix.h"

void DrawWhitePixel();
void DrawBlackPixel();

DisplayManager::DisplayManager(int height, int width)
{

	DisplayManager::height_ = height;
	DisplayManager::width_ = width;

	DisplayManager::curr_pm_ = new PixelMatrix(height, width);

}

DisplayManager::~DisplayManager()
{
	delete curr_pm_;
}

bool DisplayManager::SetPixel(int x, int y, Color r, Color g, Color b)
{
	if (x > width_ || y > height_ || x < 0 || y < 0)
	{
		std::fprintf(stderr, "DisplayManager: Call to set pixel out of bounds of matrix.\n");
		return false;
	}
	Pixel* p = curr_pm_->At(x, y);
	p->red = (char)r;
	p->green = (char)g;
	p->blue = (char)b;
	p->active = true;

	return true;
}

Pixel DisplayManager::GetPixel(int x, int y)
{
	if (x > width_ || y > height_ || x < 0 || y < 0)
	{
		std::fprintf(stderr, "DisplayManager: Call to get pixel out of bounds of matrix.\n");
		return Pixel{ 0, 0, 0, false };
	}

	return *(curr_pm_->At(x, y));
}

void DisplayManager::TogglePixelActivity(int x, int y)
{
	curr_pm_->TogglePixelActivity(x, y);
	return;
}

void DisplayManager::FillDisplay(Color r, Color g, Color b)
{
	curr_pm_->FillMatrix(r, g, b);
	return;
}

void DisplayManager::ClearDisplay()
{
	curr_pm_->ClearMatrix();
	return;
}

void DisplayManager::MergeMatrices(PixelMatrix merging)
{
	curr_pm_->MergeMatrices(merging);
	return;
}

//Implement the Adafruit LED matrix library
void DisplayManager::Update()
{

	return;
}