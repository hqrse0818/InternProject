#include "OBJ_PlayerCharacter.h"

OBJ_PlayerCharacter::OBJ_PlayerCharacter()
{
	p_move = new Com_CharacterMove;
	p_jump = new Com_CharacterJump;
	AddComponent(p_move);
	AddComponent(p_jump);
}

OBJ_PlayerCharacter::OBJ_PlayerCharacter(const char* _name)
	:OBJ_PlayerCharacter()
{
	sObjectName = _name;
}