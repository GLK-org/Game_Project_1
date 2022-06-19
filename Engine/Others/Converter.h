#pragma once
#include <locale>
#include <codecvt>
#include <string>


static std::string GetLPSTR_Path(std::wstring uri) {
		wchar_t exeDir[1024];
	DWORD let = GetModuleFileName(NULL, exeDir, 1024);
	std::wstring et = std::wstring(exeDir);
	std::wstring fullpath(std::wstring(exeDir).replace(et.size() - 8, 8, L"\\Audio\\" + uri));
	std::wstring_convert<std::codecvt_utf8_utf16<wchar_t>> converter;

	using convert_typeX = std::codecvt_utf8<wchar_t>;
	std::wstring_convert<convert_typeX, wchar_t> converterX;

	std::string tet1 = converterX.to_bytes(fullpath);
	return tet1.c_str();
}


static std::wstring GetLPWSTR_Path(std::wstring uri, bool mode) {


	wchar_t exeDir[1024];
	DWORD let = GetModuleFileName(NULL, exeDir, 1024);
	
	std::wstring et = std::wstring(exeDir);
	std::wstring fullpath;
	if (mode) {
		std::wstring fullpath(std::wstring(exeDir).replace(et.size() - 8, 8, L"\\Artworks\\" + uri));

	}
	else {
		std::wstring fullpath(std::wstring(exeDir).replace(et.size() - 8, 8, L"\\Audio\\" + uri));
	}

	return fullpath.c_str();
}