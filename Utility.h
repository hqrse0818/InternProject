#pragma once

#include	<iostream>
#include	<functional>
#include <SimpleMath.h>
#include <thread>

#include    <assimp\Importer.hpp>
#include    <assimp\scene.h>
#include    <assimp\postprocess.h>
#include    <assimp/cimport.h>

#include "Format.h"

#define Gravity     4.0
#define PIE			3.1415926535
#define Horizontal	180
#define OriginalGroundHeight  0.0
#define EulerGap	Horizontal / PIE	// ���W�A������I�C���[�p�ɒ����Ƃ�
#define RadianGap	PIE / Horizontal	// �I�C���[�p���烉�W�A���ɒ����Ƃ�

#define Radian_To_Euler(Value) (Value * EulerGap)
#define Euler_To_Radian(Value) (Value * RadianGap)

#define GetMin(numA, numB)(numA < numB ? numA : numB)

#define GetMax(numA, numB)(numA > numB ? numA : numB)

#define BoxLineNum 12
#define RenderBoxVertexNum 24
#define BoxVertexNum 8

#define SAFE_RELEASE(p) {if(p){p->Release(); p = nullptr;}}
#define SAFE_DELETE(p) {if(p){delete p; p = nullptr;}}


// �t�@�C���p�X����t�@�C�����������擾����
std::string GetFileName(std::string FilePath);
// �t�@�C���p�X����t�@�C�����������擾����
std::wstring GetFileNameWide(std::string filepath);
// �t�@�C���p�X����t�@�C���g���q���擾����
std::string GetFileExt(std::string filepath);
// �t�@�C���p�X����e�f�B���N�g�����擾����
std::wstring GetParentDirectoryWide(std::string filepath);
