#pragma once

#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <windows.h>
#include <assert.h>
#include <functional>
#include <locale.h>
#include <DirectXMath.h>
#include <WICTextureLoader.h>

#pragma warning(push)
#pragma warning(disable:4005)

#include <d3d11.h>

#pragma warning(pop)


// ŠO•”ƒ‰ƒCƒuƒ‰ƒŠ
#pragma comment(lib,"directxtk.lib")
#pragma comment(lib,"directxtex.lib")
#pragma comment(lib,"d3d11.lib")
#pragma comment (lib,"winmm.lib")
#pragma comment (lib, "xinput.lib")

constexpr uint32_t SCREEN_WIDTH = 1280;
constexpr uint32_t SCREEN_HEIGHT = 720;

