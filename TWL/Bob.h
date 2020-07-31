#pragma once
#include "PlayableCharacter.h"

class Bob : public PlayableCharacter
{
public:
	Bob();

	bool virtual handleInput();
};