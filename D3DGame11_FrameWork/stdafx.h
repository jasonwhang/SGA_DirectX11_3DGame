#pragma once

#include <Windows.h>
// assert는 디버그모드에서만 작동
// 릴리스모드에서는 따로 예외처리를 해주어야 한다.
#include <assert.h>
#include <time.h>

// STL
#include <vector>
#include <map>
#include <functional>
using namespace std;

// DirectX 3D
#include <dxgi1_2.h>
#include <d3dcommon.h>
#include <d3dcompiler.h>
#include <d3d11shader.h>
#include <d3d11.h>
// 11부터는 기본적으로 제공하는 math들을 제거하였다.
#include <D3DX10math.h>
#include <D3DX11async.h>

#pragma comment(lib, "dxgi.lib")
#pragma comment(lib, "d3d11.lib")
#pragma comment(lib, "d3dx9.lib")
#pragma comment(lib, "d3dx10.lib")
#pragma comment(lib, "d3dx11.lib")
#pragma comment(lib, "d3dcompiler.lib")
#pragma comment(lib, "dxguid.lib")

typedef unsigned int uint;

// Macro function
#define SAFE_RELEASE(p)			{if (p) { (p)->Release(); (p) = nullptr; } }
#define SAFE_DELETE(p)			{if (p) { delete (p); (p) = nullptr; } }
#define SAFE_DELETE_ARRAY(p)	{if (p) { delete[] (p); (p) = nullptr; } }

// Virtual Key Code
#define VK_0 0x30
#define VK_1 0x31
#define VK_2 0x32
#define VK_3 0x33
#define VK_4 0x34
#define VK_5 0x35
#define VK_6 0x36
#define VK_7 0x37
#define VK_8 0x38
#define VK_9 0x39

#define VK_A 0x41
#define VK_B 0x42
#define VK_C 0x43
#define VK_D 0x44
#define VK_E 0x45
#define VK_F 0x46
#define VK_G 0x47
#define VK_H 0x48
#define VK_I 0x49
#define VK_J 0x4A
#define VK_K 0x4B
#define VK_L 0x4C
#define VK_M 0x4D
#define VK_N 0x4E
#define VK_O 0x4F
#define VK_P 0x50
#define VK_Q 0x51
#define VK_R 0x52
#define VK_S 0x53
#define VK_T 0x54
#define VK_U 0x55
#define VK_V 0x56
#define VK_W 0x57
#define VK_X 0x58
#define VK_Y 0x59
#define VK_Z 0x5A

// FrameWork
#include "./FrameWork/Core/Settings.h"
#include "./FrameWork/Core/Context.h"

// D3D11 Wraper Class
#include "./FrameWork/Core/D3D11/Vertex.h"

// Utility
#include "./FrameWork/Utility/Geometry.h"

// Subsystem
#include "./FrameWork/Core/Subsystem/Graphics.h"
#include "./FrameWork/Core/Subsystem/Input.h"
