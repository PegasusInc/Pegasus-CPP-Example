#pragma once
#include "../stdafx.hpp"

namespace Utils {
	void* AllocateMemory(int len);
	char* va(const char* text, ...);
	wchar_t* vaw(const char* text, ...);
	std::string CreateRandomString(size_t length);
	std::string ExtractPath(std::string strFilePath);
	std::string BuildFilePath(std::string filename);
	std::string ConvertBytesToString(BYTE* data, int len);
	std::string Rot13(std::string input);
	std::string Rot13Number(std::string input);
	void TimedClose(int sec, void(*callback)(int));
	void TimedMessage(int sec, void(*callback)(int));
	std::string GetSerial();
}
