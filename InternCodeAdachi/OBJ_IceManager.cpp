#include "OBJ_IceManager.h"
#include "CSVLoad.h"

using namespace std;
using namespace DirectX::SimpleMath;

float OBJ_IceManager::fShakeTime = 0;
float OBJ_IceManager::fShakePower = 0;
Vector3 OBJ_IceManager::mColCenter{};
Vector3 OBJ_IceManager::mColSize{};
Vector3 OBJ_IceManager::mIceScale{};
std::list<OBJ_Ice*> OBJ_IceManager::IceList{};

OBJ_IceManager::OBJ_IceManager()
{
	
}

OBJ_IceManager::OBJ_IceManager(const char* _name)
{
}

OBJ_IceManager::OBJ_IceManager(const char* _name, const char* _FileName)
{
	sObjectName = _name;

	string sState = ReadDataFromCSV(_FileName, 1);
	vector<string> sv = SeparateString(sState, ',');

	fShakeTime = stof(sv[0]);
	fShakePower = stof(sv[1]);
	mColCenter = Vector3(stof(sv[2]), stof(sv[3]), stof(sv[4]));
	mColSize = Vector3(stof(sv[5]), stof(sv[6]), stof(sv[7]));
	mIceScale = Vector3(stof(sv[8]), stof(sv[9]), stof(sv[10]));
}

void OBJ_IceManager::Uninit()
{
	IceList.clear();
}
