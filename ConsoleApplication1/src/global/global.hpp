#pragma once
#include "stdafx.hpp"
#include "libs/json/single_include/nlohmann/json.hpp"

namespace Global::Vars {
	extern std::string g_Url;
	extern std::string g_Version;
	extern std::string g_New;
	extern CSimpleIniA g_AuthIni;
	extern std::string g_Username;
	extern std::string g_Token;
	extern std::string g_Version;
	extern nlohmann::json g_JsonResponseDecoder;
	extern bool g_LoggedIn;

}