#include "stdafx.hpp"
#include "utils/config.hpp"
#include "utils/log.hpp"
#include "utils/utils.hpp"
#include "utils/md5/md5.hh"
#include "global/global.hpp"

auto timedCloseCallback = [](int secondsLeft) -> void {
	warn(XOR("Application closing in %i second%s..."), secondsLeft, secondsLeft == 1 ? "" : "s");
	};

static size_t write_callback(void* contents, size_t size, size_t nmemb, void* userp) {
	((std::string*)userp)->append((char*)contents, size * nmemb);
	return size * nmemb;
}
void timedClose(int sec, void(*callback)(int)) {
	static int seconds = sec;
	do {
		callback(seconds);
		Sleep(1000);
		seconds--;
	} while (seconds);

	ExitProcess(0);
}
static std::string req(std::string data) {
	// Initialize libcurl
	CURL* curl = curl_easy_init();

	// Check if curl initialization is successful
	if (!curl)
		return XOR("null");

	std::string to_return;

	// Set the URL for the HTTP request
	curl_easy_setopt(curl, CURLOPT_URL, Global::Vars::g_Url.c_str());

	// Disable SSL certificate verification (for testing purposes only; should be used with caution)
	curl_easy_setopt(curl, CURLOPT_SSL_VERIFYPEER, 0);
	curl_easy_setopt(curl, CURLOPT_SSL_VERIFYHOST, 0);

	// Set the data to be sent with the POST request
	curl_easy_setopt(curl, CURLOPT_POSTFIELDS, data.c_str());

	// Set the callback function to handle the response data
	curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, write_callback);
	curl_easy_setopt(curl, CURLOPT_WRITEDATA, &to_return);

	// Perform the HTTP request
	auto code = curl_easy_perform(curl);

	// Check for any errors during the HTTP request and display an error message if necessary
	if (code != CURLE_OK)
		MessageBoxA(0, curl_easy_strerror(code), 0, MB_ICONERROR);

	// Clean up and release resources used by libcurl
	curl_easy_cleanup(curl);

	// Get the HTTP response code
	long http_code = 0;
	curl_easy_getinfo(curl, CURLINFO_RESPONSE_CODE, &http_code);

	if (http_code == 429) // client was rate limited
	{
		Sleep(3500);
		exit(0);
	}

	// Return the response received from the HTTP request
	return to_return;
}
void LoadConfig()
{
	// Set the auth INI file to use Unicode encoding
	Global::Vars::g_AuthIni.SetUnicode();

	// Load the auth configuration from the specified path
	Global::Vars::g_AuthIni.LoadFile(GetConfig()->GetAuthPath());

	// Check if the auth INI file is empty
	if (Global::Vars::g_AuthIni.IsEmpty())
	{
		// If empty, set default values for username and token
		Global::Vars::g_AuthIni.SetValue(XOR("authentication"), XOR("username"), XOR("username here"));
		Global::Vars::g_AuthIni.SetValue(XOR("authentication"), XOR("token"), XOR("token here"));

		// Display an error message asking the user to fill in the auth file
		error(XOR("Please fill in Pegasis.auth located in Documents/Pegasus"), Global::Vars::g_Username.c_str());
	}

	// Retrieve the username and token from the auth INI file
	Global::Vars::g_Username = Global::Vars::g_AuthIni.GetValue(XOR("authentication"), XOR("username"), FALSE);
	Global::Vars::g_Token = Global::Vars::g_AuthIni.GetValue(XOR("authentication"), XOR("token"), FALSE);

	// Save the updated auth configuration back to the file
	Global::Vars::g_AuthIni.SaveFile(GetConfig()->GetAuthPath());
}

static size_t write_data(void* ptr, size_t size, size_t nmemb, void* stream)
{
	size_t written = fwrite(ptr, size, nmemb, (FILE*)stream);
	return written;
}
void Get_Latest()
{


	if (CURL* curl = curl_easy_init()) {
		if (FILE* fp = fopen(GetConfig()->GetNewPath(), "wb")) {
			curl_easy_setopt(curl, CURLOPT_URL, Global::Vars::g_New.c_str());
			curl_easy_setopt(curl, CURLOPT_FAILONERROR, 1);
			curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, write_data);
			curl_easy_setopt(curl, CURLOPT_WRITEDATA, fp);
			curl_easy_setopt(curl, CURLOPT_FOLLOWLOCATION, 1L); 
			curl_easy_setopt(curl, CURLOPT_HTTPPROXYTUNNEL, 1L);

			CURLcode res = curl_easy_perform(curl);

			fclose(fp);
		}
		curl_easy_cleanup(curl);
	}
}

void AuthenticateUser()
{
	// Generate hardware ID using MD5 hash of the serial number
	std::string hardware_id = md5(Utils::GetSerial()).c_str();

	// Define the action and construct data string for the auth request
	std::string action = XOR("Authenticate");
	auto data =
		XOR("action=") + action +
		XOR("&hwid=") + hardware_id +
		XOR("&name=") + Global::Vars::g_Username +
		XOR("&token=") + Global::Vars::g_Token +
		XOR("&version=") + Global::Vars::g_Version;

	// Send auth request and parse the JSON response
	auto json = Global::Vars::g_JsonResponseDecoder.parse(req(data));

	// Check if the response contains "Good" indicating successful auth
	if (json.dump().find(XOR("Good")) != std::string::npos)
	{
		// If auth is successful, set logged in flag to true
		Global::Vars::g_LoggedIn = true;

		success(XOR("Successfully authenticated, Welcome Back %s!"), Global::Vars::g_Username.c_str());
	}
	// Check if the response contains "Outdated" indicating outdated version
	else if(json.dump().find(XOR("Outdated")) != std::string::npos)
	{
		success(XOR("Update Found, Hang Tight %s!"), Global::Vars::g_Username.c_str());
		
		// Grabbing latest file
		Get_Latest();

		// Timed close enough time to make sure download is completed before exiting. 
		timedClose(5, timedCloseCallback);
	}
	else
	{
		// If auth fails, set logged in flag to false
		Global::Vars::g_LoggedIn = false;

		printf(XOR("Auth Fail"));
		error(XOR("Please double check your Pegasus.auth or contact support"));
	}
}
int main()
{
	srand((unsigned int)time(0));
	GetConfig()->Initialize();
	GetLog()->SetColor(consoleForeground::WHITE);

	LoadConfig();

	AuthenticateUser();

	//while (Global::Vars::g_LoggedIn) {
	//	success("true");
	//}
}
