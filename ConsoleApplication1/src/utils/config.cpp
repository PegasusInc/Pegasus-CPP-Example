#include "config.hpp"
#include "../utils/utils.hpp"
#include <shlobj.h>
#include <shlwapi.h>
#include <direct.h>
#include <vector>

void Config::Initialize() {
	SHGetFolderPathA(NULL, CSIDL_PERSONAL, NULL, SHGFP_TYPE_CURRENT, DocumentsPath);
	SHGetFolderPathA(NULL, CSIDL_APPDATA, NULL, SHGFP_TYPE_CURRENT, AppdataPath);

	// setup the paths
	snprintf(BasePath, MAX_PATH, XOR("%s\\Pegasus"), DocumentsPath);
	snprintf(ConfigPath, MAX_PATH, XOR("%s\\Pegasus\\Config.ini"), DocumentsPath);
	snprintf(LogPath, MAX_PATH, XOR("%s\\Pegasus\\Log.txt"), DocumentsPath);
	snprintf(AuthPath, MAX_PATH, XOR("%s\\Pegasus\\Pegasus.auth"), DocumentsPath);
	snprintf(NewPath, MAX_PATH, XOR("%s\\Pegasus\\new.exe"), DocumentsPath);
	// create folders that don't alread exist
	_mkdir(Utils::va(XOR("%s\\Pegasus"), DocumentsPath));
}

bool Config::DoesFileExist(std::string file) {
	std::ifstream stream(file);
	if (stream.good()) {
		stream.close();
		return true;
	}

	return false;
}

std::vector<std::string> Config::GetFilesInDirectory(std::string folder, std::string extension) {
	std::vector<std::string> buffer;

	std::string loc = folder + "\\*" + extension;
	WIN32_FIND_DATAA fd;
	auto vit = FindFirstFileA(loc.c_str(), &fd);
	if (vit != INVALID_HANDLE_VALUE) {
		do {
			if (!(fd.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY)) {
				std::string orig = fd.cFileName;
				buffer.push_back(orig.substr(0, orig.length() - extension.length()));
			}
		} while (FindNextFileA(vit, &fd));
		FindClose(vit);
	}

	return buffer;
}

Config* GetConfig() {
	static Config instance;
	return &instance;
}