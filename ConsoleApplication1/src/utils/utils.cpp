#include "utils.hpp"
#include <algorithm>
#include <iomanip>
#include <unordered_map>
namespace Utils {
	void* AllocateMemory(int len) {
		void* allocated = malloc(len);
		memset(allocated, 0, len);
		return allocated;
	}

    // Function to format a string with variable arguments (variadic function)
    char* va(const char* text, ...) {
        static char vaBuffer[0x1000];
        memset(vaBuffer, 0, 0x1000);
        va_list ap;
        va_start(ap, text);
        vsprintf_s(vaBuffer, text, ap);
        va_end(ap);
        return vaBuffer;
    }

    // Function to convert a formatted string to a wide character string
    wchar_t* vaw(const char* text, ...) {
        CHAR Buffer[0x1000];
        CHAR MessageBuffer[0x100];
        static WCHAR Message[0x100];

        va_list pArgList;
        va_start(pArgList, text);
        sprintf(Buffer, text, pArgList);
        va_end(pArgList);

        sprintf(MessageBuffer, Buffer);
        mbstowcs(Message, MessageBuffer, strlen(MessageBuffer) + 1);

        ZeroMemory(Buffer, sizeof(Buffer));
        ZeroMemory(MessageBuffer, sizeof(MessageBuffer));

        return Message;
    }

    // Function to create a random string of given length
    std::string CreateRandomString(size_t length) {
        auto randchar = []() -> char {
            const char charset[] =
                "0123456789"
                "ABCDEFGHIJKLMNOPQRSTUVWXYZ"
                "abcdefghijklmnopqrstuvwxyz";
            const size_t max_index = (sizeof(charset) - 1);
            return charset[rand() % max_index];
        };

        std::string str(length, 0);
        std::generate_n(str.begin(), length, randchar);
        return str;
    }

    // Function to extract the directory path from a file path
    std::string ExtractPath(std::string strFilePath) {
        auto pos = strFilePath.rfind("\\", strFilePath.length());
        if (pos != std::string::npos) {
            return strFilePath.substr(0, pos);
        }
        return strFilePath;
    }

    // Function to build a file path using the current module's path and a given filename
    std::string BuildFilePath(std::string filename) {
        char filePath[MAX_PATH];
        GetModuleFileNameA(0, filePath, MAX_PATH);

        std::string path = ExtractPath(filePath);
        if (!path.empty()) {
            return path + "\\" + filename;
        }
        return filename;
    }

    // Function to convert an array of bytes to a hexadecimal string
    std::string ConvertBytesToString(BYTE* data, int len) {
        std::stringstream str;
        str.setf(std::ios_base::hex, std::ios::basefield);
        str.setf(std::ios_base::uppercase);
        str.fill('0');

        for (int i = 0; i < len; ++i) {
            str << std::setw(2) << (unsigned short)data[i];
        }

        return str.str();
    }

    // Function to apply the ROT13 substitution cipher to a string
    std::string Rot13(std::string input) {
        for (std::size_t len = input.length(), idx = 0; idx != len; ++idx) {
            if (input[idx] >= 'a' && input[idx] <= 'm') {
                input[idx] = input[idx] + 13;
            }
            else if (input[idx] >= 'n' && input[idx] <= 'z') {
                input[idx] = input[idx] - 13;
            }
            else if (input[idx] >= 'A' && input[idx] <= 'M') {
                input[idx] = input[idx] + 13;
            }
            else if (input[idx] >= 'N' && input[idx] <= 'Z') {
                input[idx] = input[idx] - 13;
            }
        }
        return input;
    }

    // Function to apply ROT13 to numerical characters in a string
    std::string Rot13Number(std::string input) {
        for (std::size_t len = input.length(), idx = 0; idx != len; ++idx) {
            switch (input[idx]) {
            case '0': input[idx] = '3'; break;
            case '1': input[idx] = '4'; break;
            case '2': input[idx] = '5'; break;
            case '3': input[idx] = '6'; break;
            case '4': input[idx] = '7'; break;
            case '5': input[idx] = '8'; break;
            case '6': input[idx] = '9'; break;
            case '7': input[idx] = '0'; break;
            case '8': input[idx] = '1'; break;
            case '9': input[idx] = '2'; break;
            }
        }
        return input;
    }

    // Function to execute a callback function after a specified number of seconds and then close the application
    void TimedClose(int sec, void(*callback)(int)) {
        static int seconds = sec;
        do {
            callback(seconds);
            Sleep(1000);
            seconds--;
        } while (seconds);

        ExitProcess(0);
    }

    // Function to execute a callback function after a specified number of seconds
    void TimedMessage(int sec, void(*callback)(int)) {
        static int seconds = sec;
        do {
            callback(seconds);
            Sleep(1000);
            seconds--;
        } while (seconds);
    }

    // Function to retrieve the serial number of the C drive (Windows environment only)
    std::string GetSerial()
    {
        DWORD lVolSerialNbr = 0;
        char sHDSerial[255] = "";

        // Get the volume serial number of the C drive
        GetVolumeInformationA(XOR("C:\\"), 0, 0, &lVolSerialNbr, 0, 0, 0, NULL);

        // Convert the serial number to a string
        _ultoa_s(lVolSerialNbr, sHDSerial, 10);

        std::string c(sHDSerial);
        return c;
    }
}