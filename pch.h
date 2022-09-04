#pragma once


#include <Windows.h>
#include <vector>
#include <TlHelp32.h>
#include <iostream>
#include "MyStructs.h"
#include <thread>

#include <assert.h>

#include "Offsets.h"

#include <d3d9.h>
#include <d3dx9.h>
#pragma comment(lib, "d3d9.lib")
#pragma comment(lib, "d3dx9.lib")

#include <DxErr.h> //get error from error code
#pragma comment(lib, "dxerr.lib")
#pragma comment(lib, "legacy_stdio_definitions.lib")