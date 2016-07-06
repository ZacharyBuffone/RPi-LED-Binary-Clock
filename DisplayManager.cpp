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

	return true;
}

Pixel DisplayManager::GetPixel(int x, int y)
{
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

void DisplayManager::ClearDisplay()
{
	curr_pm_->Clear();
	return;
}

void DisplayManager::MergeMatrices(PixelMatrix& merging)
{
	curr_pm_->Merge(merging);
	return;
}

void DisplayManager::MergeMatrices(PixelMatrix& merging, int start_x, int start_y)
{
	curr_pm_->Merge(merging, start_x, start_y);
}


//Implement the Adafruit LED matrix library
void DisplayManager::Display()
{
	printf("\n   ");

	Pixel* next_pixel;
	for (int i = 0; i < width_; i++)
	{
		for (int j = 0; j < height_; j++)
		{
			next_pixel = curr_pm_->At(j, i);
			if (!(next_pixel->red) && !(next_pixel->green) && !(next_pixel->blue))		//Detects if not black pixel
				printf(".");
			else
				printf("X");

			printf(" ");
		}
		printf("\n   ");
	}
	return;
}
