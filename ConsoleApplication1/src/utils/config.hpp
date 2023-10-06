#pragma once
#include "../stdafx.hpp"
#include <vector>
class Config {
public:
	void Initialize();
	bool DoesFileExist(std::string file);
	std::vector<std::string> GetFilesInDirectory(std::string folder, std::string extension = ".txt");

	const char* GetDocumentsPath() { return DocumentsPath; }
	const char* GetAppDataPath() { return AppdataPath; }
	const char* GetConfigPath() { return ConfigPath; }
	const char* GetLogPath() { return LogPath; }
	const char* GetAuthPath() { return AuthPath; }
	const char* GetNewPath() { return NewPath; }
	const char* GetThemePath() { return ThemePath; }
	const char* GetTranslationPath() { return TranslationPath; }
	const char* GetClientPath() { return ClientPath; }
	const char* GetBasePath() { return BasePath; }
private:
	char DocumentsPath[MAX_PATH];
	char AppdataPath[MAX_PATH];
	char BasePath[MAX_PATH];
	char ConfigPath[MAX_PATH];
	char LogPath[MAX_PATH];
	char AuthPath[MAX_PATH];
	char ThemePath[MAX_PATH];
	char TranslationPath[MAX_PATH];
	char ClientPath[MAX_PATH];
	char NewPath[MAX_PATH];
}; Config* GetConfig();