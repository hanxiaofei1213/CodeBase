#pragma once
//////////////////////////////////////////////////////////////////////////
// FileName: RegUtils.hpp
// Author: wangwenxi
// Date: 2022.07.18
//////////////////////////////////////////////////////////////////////////
#include <atlstr.h>
#include <map>
#include <vector>

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

        ULONG uChars = 0;
        LONG lResult = regKey.QueryStringValue(lpszKey, nullptr, &uChars);
        if (lResult != ERROR_SUCCESS || uChars == 0) {
            return L"";
        }

        std::vector<TCHAR> buffer(uChars);
        if (ERROR_SUCCESS != regKey.QueryStringValue(lpszKey, buffer.data(), &uChars)) {
            return L"";
        }

        return CString(buffer.data());
	}

    // 查询注册表函数
	static DWORD queryDWordRegValue(HKEY hKey, LPCTSTR lpszPath, LPCTSTR lpszKey) {
        if (lpszPath == NULL || lpszKey == NULL) {
            return -1;
        }

        CRegKey regKey;
        if (ERROR_SUCCESS != regKey.Open(hKey, lpszPath, KEY_READ | KEY_WOW64_32KEY)) {
            return -1;
        }

        DWORD dwRes = 0;
        if (ERROR_SUCCESS != regKey.QueryDWORDValue(lpszKey, dwRes)) {
            return -1;
        }

        return dwRes;
	}

    // 写入注册表
    static bool saveRegValue(HKEY hKey, LPCTSTR lpszPath, LPCTSTR lpszKey, LPCTSTR lpszValue) {
        if (lpszPath == NULL || lpszKey == NULL || lpszValue == NULL) {
            return false;
        }

        CRegKey regKey;
        LONG lResult = regKey.Open(hKey, lpszPath, KEY_WRITE);
        if (ERROR_SUCCESS != lResult) {
            lResult = regKey.Create(hKey, lpszPath);
            if (ERROR_SUCCESS != lResult) {
                return false;
            }
        }

        if (ERROR_SUCCESS != regKey.SetStringValue(lpszKey, lpszValue)) {
            return false;
        }

        return true;
    }

    // 写入注册表
    static bool saveRegDwordValue(HKEY hKey, LPCTSTR lpszPath, LPCTSTR lpszKey, DWORD dwValue) {
        if (lpszPath == NULL || lpszKey == NULL) {
            return false;
        }

        CRegKey regKey;
        LONG lResult = regKey.Open(hKey, lpszPath, KEY_WRITE);
        if (ERROR_SUCCESS != lResult) {
            lResult = regKey.Create(hKey, lpszPath);
            if (ERROR_SUCCESS != lResult) {
                return false;
            }
        }

        if (ERROR_SUCCESS != regKey.SetDWORDValue(lpszKey, dwValue)) {
            return false;
        }

        return true;
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