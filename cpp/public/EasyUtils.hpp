#pragma once
//////////////////////////////////////////////////////////////////////////
// FileName: EasyUtils.hpp
// Author: wangwenxi
// Date: 2022.06.20
//////////////////////////////////////////////////////////////////////////

#include <atlstr.h>
#include <time.h>
#include <fstream>
#include <atlpath.h>
#include <vector>

namespace easy {
	// 时间戳转字符串函数
	static CString timestamp2Str(const __time64_t& timer) {
		if (timer <= 0) {
			return L"";
		}

		CString strTime = L"";
		struct tm tm1;
		localtime_s(&tm1, &timer);
		strTime.Format(L"%d-%02d-%02d %02d:%02d:%02d", tm1.tm_year + 1900, tm1.tm_mon + 1, tm1.tm_mday, tm1.tm_hour, tm1.tm_min, tm1.tm_sec);
		return strTime;
	}

	// 系统时间转字符串
	static CString systimeTime2Str(const SYSTEMTIME& systemTime) {
        CString strTime = L"";
        strTime.Format(L"%d-%02d-%02d %02d:%02d:%02d", systemTime.wYear, systemTime.wMonth, systemTime.wDay, systemTime.wHour, systemTime.wMinute, systemTime.wSecond);
        return strTime;
	}

	// 系统时间转时间戳
	static __time64_t systime2Timestamp(const SYSTEMTIME& systemTime) {
        __time64_t timer = 0;
        struct tm tm1;
        tm1.tm_year = systemTime.wYear - 1900;
        tm1.tm_mon = systemTime.wMonth - 1;
        tm1.tm_mday = systemTime.wDay;
        tm1.tm_hour = systemTime.wHour;
        tm1.tm_min = systemTime.wMinute;
        tm1.tm_sec = systemTime.wSecond;
        tm1.tm_isdst = -1;
        timer = mktime(&tm1);
        return timer;
	}

	// 将字符串保存至指定文件
	static bool saveStrToSpecificPath(LPCTSTR szContent, const CString& strPath) {
		std::ofstream outFile;
		outFile.open(strPath, std::ios::out);
		if (!outFile.is_open()) {
			return false;
		}

		CStringA strContent = szContent;
		outFile << strContent << std::endl;

		outFile.close();
		return true;
	}

	// 使用explorer打开文件或文件夹
	static void openFileWithExplorer(LPCTSTR szFilePath) {
		CPath filePath = szFilePath;
		if (!filePath.FileExists()) {
		    return;
		}

		CString strCmd;
		if (filePath.IsDirectory()) {
			strCmd = szFilePath;
		} else {
			strCmd.Format(L"/select, %s", szFilePath);
		}

		::ShellExecute(NULL, L"open", L"Explorer.exe", strCmd, NULL, SW_SHOWDEFAULT);
	}

	// 分割CString字符串
	std::vector<CString> splitCString(const CString& strSource, const CString& strSplitTag) {
		if (strSource.IsEmpty() || strSplitTag.IsEmpty()) {
			return {};
		}

		CString strNeedSplit = strSource;
		std::vector<CString> vecAns;
		int nPos = strNeedSplit.Find(strSplitTag);
		while (nPos != -1) {
			CString strPart = strNeedSplit.Left(nPos);
			if (!strPart.IsEmpty()) {
				vecAns.push_back(strPart);
			}
			strNeedSplit = strNeedSplit.Right(strNeedSplit.GetLength() - nPos - 1);
			nPos = strNeedSplit.Find(strSplitTag);
		}

		if (!strNeedSplit.IsEmpty()) {
			vecAns.push_back(strNeedSplit);
		}

		return vecAns;
	}
}