#pragma once
//////////////////////////////////////////////////////////////////////////
// FileName: RegUtils.hpp
// Author: wangwenxi
// Date: 2022.07.18
//////////////////////////////////////////////////////////////////////////
#include <atlstr.h>
#include <map>

namespace easy {
class RegUtils {
public:
	// 查询注册表函数
	static CString queryRegValue(HKEY hKey, LPCTSTR lpszPath, LPCTSTR lpszKey) {
		if (lpszPath == NULL || lpszKey == NULL) {
			return L"";
		}

		CRegKey regKey;
		if (ERROR_SUCCESS != regKey.Open(hKey, lpszPath, KEY_READ | KEY_WOW64_32KEY)) {
			return L"";
		}

		const int BUFFER_SIZE = 2048;
		TCHAR buffer[BUFFER_SIZE] = { 0 };
		ULONG uChars = BUFFER_SIZE;
		if (ERROR_SUCCESS != regKey.QueryStringValue(lpszKey, buffer, &uChars)) {
			return L"";
		}

		return buffer;
	}

	// 遍历注册表，获取子项
	static std::map<CString, CString> enumRegKey(HKEY hKey, LPCTSTR lpszPath) {
		if (lpszPath == NULL) {
			return {};
		}

		std::map<CString, CString> mapRegKeyValue;
		CRegKey regKey;
		if (ERROR_SUCCESS != regKey.Open(hKey, lpszPath)) {
			return {};
		}

		wchar_t  subKeyName[MAX_PATH] = { 0 };
		DWORD dwLength = MAX_PATH;
		for (DWORD dwIndex = 0; regKey.EnumKey(dwIndex, subKeyName, &dwLength) != ERROR_NO_MORE_ITEMS; dwLength = MAX_PATH, ++dwIndex) {
			mapRegKeyValue[subKeyName] = queryRegValue(hKey, lpszPath, subKeyName);
		}

		return mapRegKeyValue;
	}

};
}