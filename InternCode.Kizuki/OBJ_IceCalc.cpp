#include "OBJ_IceCalc.h"
#include "../InternCodeAdachi/OBJ_Ice.h"

OBJ_IceCalc::OBJ_IceCalc()
{
	GetScene()->GetGameObjects<OBJ_Ice*>();
}

void OBJ_IceCalc::Update()
{
	//iIceRemain = 
}
