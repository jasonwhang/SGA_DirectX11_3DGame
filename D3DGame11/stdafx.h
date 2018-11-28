#pragma once

#include <Windows.h>
// assert�� ����׸�忡���� �۵�
// ��������忡���� ���� ����ó���� ���־�� �Ѵ�.
#include <assert.h>
#include <time.h>

// STL
#include <vector>
#include <map>
using namespace std;

// DirectX 3D
#include <dxgi1_2.h>
#include <d3dcommon.h>
#include <d3dcompiler.h>
#include <d3d11shader.h>
#include <d3d11.h>
// 11���ʹ� �⺻������ �����ϴ� math���� �����Ͽ���.
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

// FrameWork
#include "./System/Settings.h"
