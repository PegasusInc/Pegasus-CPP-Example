#pragma once
#define WIN32_LEAN_AND_MEAN
#define _CRT_SECURE_NO_WARNINGS
#define _SILENCE_ALL_CXX17_DEPRECATION_WARNINGS
#include <windows.h>
#include <atlsecurity.h> 
#include <strsafe.h> 
#include <string>
#include <stdio.h>
#include <iostream>
#include <shellapi.h>
#include <sstream> 
#include <iomanip> 
#include <fstream> 
#include <libs/curl/include/curl/curl.h>
#include "utils/SimpleIni.h"
#include "utils/xor/xor.hpp"
#pragma comment(lib, "libcurl_c.lib")
#pragma comment(lib, "Winmm.lib")
#pragma comment(lib, "Ws2_32.lib")

#pragma warning(disable : 4244)


