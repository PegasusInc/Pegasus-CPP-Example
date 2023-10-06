#include "log.hpp"
#include <ctime>

const char* Logger::GetTimeString() {
	time_t rawtime;
	time(&rawtime);

	char* str = asctime(localtime(&rawtime));
	std::size_t n = strlen(str) - 1;

	if (n < 0)
		n = 0;

	str[n] = '\0';

	return str;
}

void Logger::SetColor(int color) {
	CONSOLE_SCREEN_BUFFER_INFO screenBuffer;
	GetConsoleScreenBufferInfo(GetStdHandle((DWORD)-11), &screenBuffer);

	WORD attributes = screenBuffer.wAttributes & ~FOREGROUND_RED & ~FOREGROUND_GREEN & ~FOREGROUND_BLUE & ~FOREGROUND_INTENSITY;
	attributes |= color;
	SetConsoleTextAttribute(GetStdHandle((DWORD)-11), attributes);
}

void Logger::Print(int color, const char* type, const char* fmt, ...) {
	char buffer[512];
	char buffer2[512];

	memset(buffer, 0, 512);
	memset(buffer2, 0, 512);

	va_list val;
	va_start(val, fmt);
	vsprintf_s(buffer, fmt, val);
	va_end(val);

	SetColor(color);
	printf(XOR("%s | %s\n"), type, buffer);

	SetColor(consoleForeground::WHITE);
}

Logger* GetLog() {
	static Logger instance;
	return &instance;
}
