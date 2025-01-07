#pragma once
//////////////////////////////////////////////////////////////////////////
// FileName: FileUtils.hpp
// Author: wangwenxi
// Date: 2022.07.18
//////////////////////////////////////////////////////////////////////////

#include <atlstr.h>
#include <fstream>
#include <windows.h>

namespace easy {
class FileUtils {
public:

    // 创建文件
	static bool createEmptyFile(LPCTSTR strFileName) {
		if (strFileName == nullptr) {
			return false;
		}

		std::ofstream outFile;
		outFile.open(strFileName);
		return outFile.is_open();
	}

    // 创建文件夹
	static bool createDirectory(LPCTSTR strDirPath) {
		if (strDirPath == nullptr || ::PathFileExists(strDirPath)) {
			return false;
		}

		// Todo(wangwenxi): 如果不存在啥都是对的
		if (!(::GetFileAttributes(strDirPath) & FILE_ATTRIBUTE_DIRECTORY)) {
			return false;
		}

		return ::CreateDirectory(strDirPath, NULL);
	}

	// 判断路径是不是在系统盘符里面
	static bool isPathInSystemDrive(const CString& strPath) {
		if (strPath.IsEmpty()) {
			return false;
		}

		TCHAR szPath[MAX_PATH];
		UINT uLen = ::GetSystemDirectory(szPath, MAX_PATH);
		CPath systemDirectoryPath(szPath);
		CPath filePath(strPath);

		return systemDirectoryPath.GetDriveNumber() == filePath.GetDriveNumber();
	}

    // 获取文件最后修改时间
    static SYSTEMTIME getFileLastWriteTime(LPCTSTR strFilePath) {
        HANDLE hFile = CreateFile(strFilePath, GENERIC_READ, FILE_SHARE_READ, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);

        if (hFile == INVALID_HANDLE_VALUE) {
            return { 0 };
        }

        FILETIME ftWrite;
        SYSTEMTIME stLocal = { 0 };
        if (GetFileTime(hFile, NULL, NULL, &ftWrite)) {
			SYSTEMTIME stUTC = { 0 };
            FileTimeToSystemTime(&ftWrite, &stUTC);
            SystemTimeToTzSpecificLocalTime(NULL, &stUTC, &stLocal);
        }

        CloseHandle(hFile);
        return stLocal;
    }

	// 判断路径是不是文件夹
	static bool isDir(const std::wstring& strFilePath) {
        DWORD attributes = ::GetFileAttributes(strFilePath.c_str());
        if (attributes == INVALID_FILE_ATTRIBUTES) {
            return false;
        }

        return (attributes & FILE_ATTRIBUTE_DIRECTORY) != 0;
	}

    // 读取UTF8文件
	static BOOL ReadUTF8File(const std::wstring& filePath, std::wstring& outContent) {
        HANDLE hFile = CreateFileW(filePath.c_str(), GENERIC_READ, FILE_SHARE_READ, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
        if (hFile == INVALID_HANDLE_VALUE) {
            return false;
        }

        LARGE_INTEGER fileSize;
        if (!GetFileSizeEx(hFile, &fileSize)) {
            CloseHandle(hFile);
            return false;
        }

        std::vector<char> buffer(static_cast<size_t>(fileSize.QuadPart));
        DWORD bytesRead;
        if (!ReadFile(hFile, &buffer[0], static_cast<DWORD>(fileSize.QuadPart), &bytesRead, NULL) || bytesRead != fileSize.QuadPart) {
            CloseHandle(hFile);
            return false;
        }

        CloseHandle(hFile);

        int startIdx = 0;
        if (buffer.size() >= 3 && buffer[0] == '\xEF' && buffer[1] == '\xBB' && buffer[2] == '\xBF') {
            startIdx = 3;
        }

        int wideCharSize = MultiByteToWideChar(CP_UTF8, 0, &buffer[0] + startIdx, static_cast<int>(buffer.size()) - startIdx, NULL, 0);
        outContent.resize(wideCharSize);
        MultiByteToWideChar(CP_UTF8, 0, &buffer[0] + startIdx, static_cast<int>(buffer.size()) - startIdx, &outContent[0], wideCharSize);
        return true;
	}


};
}