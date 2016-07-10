#include "FontGenerator.h"

FontGenerator::FontGenerator()
{

	//sets up the vectors for hour, minutes and seconds
	//and allocates space for PixelMatrix vector elements will point to.
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
	for (int i = 0; i < (int) hour_font_vector_->size(); i++)
		delete hour_font_vector_->at(i);
	delete hour_font_vector_;

	for (int i = 0; i < (int) minute_font_vector_->size(); i++)
		delete minute_font_vector_->at(i);
	delete minute_font_vector_;

	for (int i = 0; i < (int) second_font_vector_->size(); i++)
		delete second_font_vector_->at(i);
	delete second_font_vector_;


	return;
}

//updates the vectors to hold infomation on current time
void FontGenerator::Update()
{
	ClearVectors();

	//getting the time using CTime
	time_t time;
	std::time(&time);
	struct tm* time_info = std::localtime(&time);

	//Strings hold the characters we would like in our vectors
	std::string* hour_binary = DecToBin(time_info->tm_hour % 12);
	std::string* minute_binary = DecToBin(time_info->tm_min);
	std::string* second_binary = DecToBin(time_info->tm_sec);

	//pushes the character specific matricies into the appropriate vector
	for (int i = 0; i < (int) hour_binary->size(); i++)
	{
		hour_font_vector_->push_back(new PixelMatrix(FONT_HEIGHT, FONT_WIDTH));
		SetMatrixToCharacter(hour_font_vector_->at(i), hour_binary->at(i));
	}
	for (int i = 0; i < (int) minute_binary->size(); i++)
	{
		minute_font_vector_->push_back(new PixelMatrix(FONT_HEIGHT, FONT_WIDTH));
		SetMatrixToCharacter(minute_font_vector_->at(i), minute_binary->at(i));
	}
	for (int i = 0; i < (int) second_binary->size(); i++)
	{
		second_font_vector_->push_back(new PixelMatrix(FONT_HEIGHT, FONT_WIDTH));
		SetMatrixToCharacter(second_font_vector_->at(i), second_binary->at(i));
	}

	//clean up
	delete hour_binary;
	delete minute_binary;
	delete second_binary;

	update_count_++;

	return;
}

void FontGenerator::ClearVectors()
{
	//free and zero all pointers in vectors
	for (int i = 0; i < (int) hour_font_vector_->size(); i++)
		delete hour_font_vector_->at(i);
	hour_font_vector_->clear();

	for (int i = 0; i < (int) minute_font_vector_->size(); i++)
		delete minute_font_vector_->at(i);
	minute_font_vector_->clear();

	for (int i = 0; i < (int) second_font_vector_->size(); i++)
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
	else //if (c == ':')
	{
		*(pm->At(1, 0)) = Pixel{ 255, 255, 255 };
		*(pm->At(1, 3)) = Pixel{ 255, 255, 255 };
	}

	return;
}

std::string* FontGenerator::DecToBin(int dec)
{
	std::string* bin = new std::string();

	//this function reads each bit stored for the decimal number.
	//each bit is binary OR'd with 1 for reading.

	//if the decimal number is 0, push zero into string.
	if (dec == 0)
	{
		bin->push_back('0');
		return bin;
	}

	while (dec > 0)
	{
		//if binary OR of dec against 1 equals 1, insert
		//1 into beginning of string
		if (dec & 1)
			bin->insert(0, "1");
		else
			bin->insert(0, "0");

		//shift the bits over one to read next bit
		dec = dec >> 1;
	}

	return bin;
}
