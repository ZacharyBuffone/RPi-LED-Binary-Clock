#include "FontGenerator.h"

FontGenerator::FontGenerator()
{
	update_count_ = 0;
	hour_font_vector_ = new std::vector<PixelMatrix*>(HOUR_VECTOR_COUNT);
	for (int i = 0; i < HOUR_VECTOR_COUNT; i++)
		hour_font_vector_->at(i) = new PixelMatrix(FONT_HEIGHT, FONT_WIDTH);

	minute_font_vector_ = new std::vector<PixelMatrix*>(MINUTE_VECTOR_COUNT);
	for (int i = 0; i < MINUTE_VECTOR_COUNT; i++)
		minute_font_vector_->at(i) = new PixelMatrix(FONT_HEIGHT, FONT_WIDTH);

	second_font_vector_ = new std::vector<PixelMatrix*>(SECOND_VECTOR_COUNT);
	for(int i = 0; i < SECOND_VECTOR_COUNT; i++)
		second_font_vector_->at(i) = new PixelMatrix(FONT_HEIGHT, FONT_WIDTH);

	return;
}

FontGenerator::~FontGenerator()
{
	for (int i = 0; i < hour_font_vector_->size(); i++)
		delete hour_font_vector_->at(i);
	delete hour_font_vector_;

	for (int i = 0; i < minute_font_vector_->size(); i++)
		delete minute_font_vector_->at(i);
	delete minute_font_vector_;

	for (int i = 0; i < second_font_vector_->size(); i++)
		delete second_font_vector_->at(i);
	delete second_font_vector_;


	return;
}

void FontGenerator::Update()
{
	ClearVectors();

	time_t time;
	std::time(&time);
	struct tm* time_info = std::localtime(&time);

	std::string* hour_binary = DecToBin(time_info->tm_hour % 12);
	std::string* minute_binary = DecToBin(time_info->tm_min);
	std::string* second_binary = DecToBin(time_info->tm_sec);

	for (int i = 0; i < hour_binary->size(); i++)
	{
		hour_font_vector_->push_back(new PixelMatrix(FONT_HEIGHT, FONT_WIDTH));
		SetMatrixToCharacter(hour_font_vector_->at(i), hour_binary->at(i));
	}
	for (int i = 0; i < minute_binary->size(); i++)
	{
		minute_font_vector_->push_back(new PixelMatrix(FONT_HEIGHT, FONT_WIDTH));
		SetMatrixToCharacter(minute_font_vector_->at(i), minute_binary->at(i));
	}
	for (int i = 0; i < second_binary->size(); i++)
	{
		second_font_vector_->push_back(new PixelMatrix(FONT_HEIGHT, FONT_WIDTH));
		SetMatrixToCharacter(second_font_vector_->at(i), second_binary->at(i));
	}

	delete hour_binary;
	delete minute_binary;
	delete second_binary;

	update_count_++;

	return;
}

void FontGenerator::ClearVectors()
{
	for (int i = 0; i < hour_font_vector_->size(); i++)
		delete hour_font_vector_->at(i);
	hour_font_vector_->clear();

	for (int i = 0; i < minute_font_vector_->size(); i++)
		delete minute_font_vector_->at(i);
	minute_font_vector_->clear();

	for (int i = 0; i < second_font_vector_->size(); i++)
		delete second_font_vector_->at(i);
	second_font_vector_->clear();

	return;
}

void FontGenerator::SetMatrixToCharacter(PixelMatrix* pm, char c)
{
	if (c == '0')
	{
		*(pm->At(0, 0)) = Pixel{ 255, 255, 255 };
		*(pm->At(1, 0)) = Pixel{ 255, 255, 255 };
		*(pm->At(2, 0)) = Pixel{ 255, 255, 255 };
		*(pm->At(0, 3)) = Pixel{ 255, 255, 255 };
		*(pm->At(1, 3)) = Pixel{ 255, 255, 255 };
		*(pm->At(2, 3)) = Pixel{ 255, 255, 255 };
		*(pm->At(0, 1)) = Pixel{ 255, 255, 255 };
		*(pm->At(0, 2)) = Pixel{ 255, 255, 255 };
		*(pm->At(2, 1)) = Pixel{ 255, 255, 255 };
		*(pm->At(2, 2)) = Pixel{ 255, 255, 255 };
	}
	else if (c == '1')
	{
		*(pm->At(2, 0)) = Pixel{ 255, 255, 255 };
		*(pm->At(2, 1)) = Pixel{ 255, 255, 255 };
		*(pm->At(2, 2)) = Pixel{ 255, 255, 255 };
		*(pm->At(2, 3)) = Pixel{ 255, 255, 255 };
		*(pm->At(1, 0)) = Pixel{ 255, 255, 255 };
	}
	else //if c == ':'
	{
		*(pm->At(1, 0)) = Pixel{ 255, 255, 255 };
		*(pm->At(1, 3)) = Pixel{ 255, 255, 255 };
	}

	return;
}

std::string* FontGenerator::DecToBin(int dec)
{
	std::string* bin = new std::string();

	if (dec == 0)
	{
		bin->push_back('0');
		return bin;
	}

	while (dec > 0)
	{
		if (dec & 1)
			bin->insert(0, "1");
		else
			bin->insert(0, "0");

		dec = dec >> 1;
	}

	return bin;
}