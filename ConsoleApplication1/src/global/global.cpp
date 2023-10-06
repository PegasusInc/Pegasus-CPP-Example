#include "global.hpp"

namespace Global::Vars {
	std::string g_Url = ("http://pauth.online/endpoints/test.php/");
	std::string g_New = ("http://pauth.online/updates/eek.exe");
	CSimpleIniA g_AuthIni;
	std::string g_Username;
	std::string g_Token;
	std::string g_Version = ("1.15");
	nlohmann::json g_JsonResponseDecoder;
	bool g_LoggedIn;
}