#include "DisplayManager.h"
#include "PixelMatrix.h"
#include <cstdlib>

void DrawWhitePixel();
void DrawBlackPixel();

DisplayManager::DisplayManager(int height, int width)
{
	if(!(io_.Init()))
	{
		printf("\nUnable to init GPIO class. Are you root?\n");
		exit(1);
	}

	rgb_matrix_ = new RGBMatrix(&io_, 32, 1, 1);

	DisplayManager::height_ = height;
	DisplayManager::width_ = width;

	DisplayManager::curr_pm_ = new PixelMatrix(height, width);

}

DisplayManager::~DisplayManager()
{
	delete curr_pm_;
	delete rgb_matrix_;
}



bool DisplayManager::SetPixel(int x, int y, Color r, Color g, Color b)
{
	//checks if pixel is within bounds of matrix
	if (x > width_ || y > height_ || x < 0 || y < 0)
	{
		std::fprintf(stderr, "DisplayManager: Call to set pixel out of bounds of matrix.\n");
		return false;
	}

	//set pixel colors
	*(curr_pm_->At(x, y)) = { r, g, b };

	return true;
}

Pixel DisplayManager::GetPixel(int x, int y)
{
	//checks if pixel is within bounds of matrix
	if (x > width_ || y > height_ || x < 0 || y < 0)
	{
		std::fprintf(stderr, "DisplayManager: Call to get pixel out of bounds of matrix.\n");
		return Pixel{ 0, 0, 0 };
	}

	return *(curr_pm_->At(x, y));
}

//void DisplayManager::FillDisplay(Color r, Color g, Color b)
//{
//	curr_pm_->Fill(r, g, b);
//	return;
//}

//Clears the display and matrix
void DisplayManager::ClearDisplay()
{
	rgb_matrix_->Clear();
	curr_pm_->Clear();
	return;
}

//Merges the agument matrix into the DisplayManager's matrix
void DisplayManager::MergeMatrices(PixelMatrix& merging)
{
	curr_pm_->Merge(merging);
	return;
}

//Merges the argument matrix into the DisplayManager's matrix starting at start_x
//and start_y
void DisplayManager::MergeMatrices(PixelMatrix& merging, int start_x, int start_y)
{
	curr_pm_->Merge(merging, start_x, start_y);
}

//Pushes pixels from the matrix onto the display
void DisplayManager::Update()
{
	//clears the display for new pixels
	rgb_matrix_->Clear();

	//pushes new pixels onto the display.
	Pixel* next_pixel;
	for (int i = 0; i < width_; i++)
	{
		for (int j = 0; j < height_; j++)
		{
			next_pixel = curr_pm_->At(i, j);
			rgb_matrix_->SetPixel(i, j, next_pixel->red, next_pixel->green, next_pixel->blue);
		}
	}
}


/*
//Implement the Adafruit LED matrix library
void DisplayManager::Display()
{
	rgb_matrix_->UpdateScreen();
	return;
}
*/
