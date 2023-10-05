#pragma once
#include "../GameObject/GameObject.h"
#include "Com_CharacterMove.h"
#include "Com_CharacterJump.h"

class OBJ_PlayerCharacter :public GameObject
{
protected:
	Com_CharacterMove* p_move;
	Com_CharacterJump* p_jump;

public:
	OBJ_PlayerCharacter();
	OBJ_PlayerCharacter(const char* _name);
};