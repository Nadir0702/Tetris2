#include "human.h"

extern HANDLE hStdOut;


GameConfig::eCommands Human::getDirection(const char& input)
{
	for (size_t i = 0; i < GameConfig::NUM_OF_KEYS; i++)
		if (keys[i] - input == GameConfig::LOWER_UPPER_DIFF ||
			keys[i] - input == 0)
			return (GameConfig::eCommands)i;

	return GameConfig::eCommands::DOWN;
}


bool Human::isDrop(const char& input) const
{
	return input == keys[(int)GameConfig::eCommands::DROP] ||
		input + GameConfig::LOWER_UPPER_DIFF == keys[(int)GameConfig::eCommands::DROP];
}
