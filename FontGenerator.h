#ifndef FONT_GENERATOR_H_
#define FONT_GENERATOR_H_

#include <vector>
#include <ctime>
#include <string>
#include "PixelMatrix.h"



typedef enum character { ZERO, ONE, COLON } Character;

class FontGenerator
{
private:
	int update_count_;
	std::vector<PixelMatrix*>* hour_font_vector_;
	std::vector<PixelMatrix*>* minute_font_vector_;
	std::vector<PixelMatrix*>* second_font_vector_;
	std::string* DecToBin(int dec);
	void SetMatrixToCharacter(PixelMatrix*, char);

public:
	FontGenerator();
	~FontGenerator();
	void Update();
	void ClearVectors();
	std::vector<PixelMatrix*>* GetHourVector() { return hour_font_vector_; }
	std::vector<PixelMatrix*>* GetMinuteVector() { return minute_font_vector_; }
	std::vector<PixelMatrix*>* GetSecondVector() { return second_font_vector_; }
	
	static const int HOUR_VECTOR_COUNT = 4;
	static const int MINUTE_VECTOR_COUNT = 6;
	static const int SECOND_VECTOR_COUNT = 6;
	static const int FONT_WIDTH = 3;
	static const int FONT_HEIGHT = 4;

};


#endif