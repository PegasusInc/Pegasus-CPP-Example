#pragma once
#include "../stdafx.hpp"

#define info(fmt, ...) GetLog()->Print(consoleForeground::DARKCYAN, "I", fmt, ##__VA_ARGS__);
#define warn(fmt, ...) GetLog()->Print(consoleForeground::DARKYELLOW, "W", fmt, ##__VA_ARGS__);
#define error(fmt, ...) GetLog()->Print(consoleForeground::RED, "E", fmt, ##__VA_ARGS__);
#define success(fmt, ...) GetLog()->Print(consoleForeground::GREEN, "Pegasus Auth -", fmt, ##__VA_ARGS__);
#define CustomInfo(name, fmt, ...) GetLog()->Print(consoleForeground::DARKCYAN, name, fmt, ##__VA_ARGS__);
#define CustomWarn(name, fmt, ...) GetLog()->Print(consoleForeground::DARKYELLOW, name, fmt, ##__VA_ARGS__);
#define CustomError(name, fmt, ...) GetLog()->Print(consoleForeground::RED, name, fmt, ##__VA_ARGS__);
#define CustomSuccess(name, fmt, ...) GetLog()->Print(consoleForeground::GREEN, name, fmt, ##__VA_ARGS__);

#ifdef DEV
#define dev(fmt, ...) GetLog()->print(log::consoleForeground::DARKMAGENTA, "DEV", fmt, ##__VA_ARGS__);
#else
#define dev(fmt, ...)
#endif

namespace consoleForeground {
	enum {
		BLACK = 0,
		DARKBLUE = FOREGROUND_BLUE,
		DARKGREEN = FOREGROUND_GREEN,
		DARKCYAN = FOREGROUND_GREEN | FOREGROUND_BLUE,
		DARKRED = FOREGROUND_RED,
		DARKMAGENTA = FOREGROUND_RED | FOREGROUND_BLUE,
		DARKYELLOW = FOREGROUND_RED | FOREGROUND_GREEN,
		DARKGRAY = FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE,
		GRAY = FOREGROUND_INTENSITY,
		BLUE = FOREGROUND_INTENSITY | FOREGROUND_BLUE,
		GREEN = FOREGROUND_INTENSITY | FOREGROUND_GREEN,
		CYAN = FOREGROUND_INTENSITY | FOREGROUND_GREEN | FOREGROUND_BLUE,
		RED = FOREGROUND_INTENSITY | FOREGROUND_RED,
		MAGENTA = FOREGROUND_INTENSITY | FOREGROUND_RED | FOREGROUND_BLUE,
		YELLOW = FOREGROUND_INTENSITY | FOREGROUND_RED | FOREGROUND_GREEN,
		WHITE = FOREGROUND_INTENSITY | FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE,
	};
}
namespace consoleBackground {
	enum {
		BLACK = 0,
		DARKBLUE = BACKGROUND_BLUE,
		DARKGREEN = BACKGROUND_GREEN,
		DARKCYAN = BACKGROUND_GREEN | BACKGROUND_BLUE,
		DARKRED = BACKGROUND_RED,
		DARKMAGENTA = BACKGROUND_RED | BACKGROUND_BLUE,
		DARKYELLOW = BACKGROUND_RED | BACKGROUND_GREEN,
		DARKGRAY = BACKGROUND_RED | BACKGROUND_GREEN | BACKGROUND_BLUE,
		GRAY = BACKGROUND_INTENSITY,
		BLUE = BACKGROUND_INTENSITY | BACKGROUND_BLUE,
		GREEN = BACKGROUND_INTENSITY | BACKGROUND_GREEN,
		CYAN = BACKGROUND_INTENSITY | BACKGROUND_GREEN | BACKGROUND_BLUE,
		RED = BACKGROUND_INTENSITY | BACKGROUND_RED,
		MAGENTA = BACKGROUND_INTENSITY | BACKGROUND_RED | BACKGROUND_BLUE,
		YELLOW = BACKGROUND_INTENSITY | BACKGROUND_RED | BACKGROUND_GREEN,
		WHITE = BACKGROUND_INTENSITY | BACKGROUND_RED | BACKGROUND_GREEN | BACKGROUND_BLUE,
	};
}

class Logger {
public:
	const char* GetTimeString();
	void SetColor(int color);
	void Print(int color, const char* type, const char* fmt, ...);
}; Logger* GetLog();
