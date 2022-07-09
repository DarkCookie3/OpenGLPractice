#include <iostream>
#include <cmath>
#include "DecToHex.h"

std::string DecToHex(unsigned int& decimal)
{
	//97 a
	std::string result("0000");
	int reminder;
	for (int i = 3; decimal != 0; i--)
	{
		reminder = decimal % 16;
		result[i] = (char)((int)(reminder > 10) * 38 + 48 + reminder);
		decimal /= 16;
	}
	return result;
}