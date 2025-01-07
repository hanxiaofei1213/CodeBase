#pragma once
//////////////////////////////////////////////////////////////////////////
// FileName: log.hpp
// Author: wangwenxi
// Date: 2022.01.05
// Comment: 简单的日志类
//////////////////////////////////////////////////////////////////////////

#include <string>
#include <ShlObj.h>
#include <atlstr.h>
#include <atlpath.h>
#include <windows.h>
#include <fstream>
#include <assert.h>
#include <mutex>
#include <iostream>

namespace {
const TCHAR* DEFAULT_LOG_NAME = L"easy_log.log";
std::mutex g_mutex;
}


#define EASY_LOG easy::Log::Log() << __FUNCTION__ << " " << (int)__LINE__ << "|"

namespace easy {
    class Log {
    public:
		Log(LPCTSTR szLogName = nullptr) : m_lock(g_mutex) {
			CPath logPath;
			CString strLogFileName = szLogName;
			if (strLogFileName.IsEmpty()) { 
				strLogFileName = DEFAULT_LOG_NAME;
			}

			CString strDesktopPath = getDesktopPath();
			logPath.Combine(strDesktopPath, strLogFileName);
			if (isFileExist(logPath.m_strPath)) {
                m_outFile.open(logPath.m_strPath, std::ios::app);
			}
		}

		~Log() {
			if (m_outFile.is_open()) {
				m_outFile.close();
			}
		}

        // 写入字符串
		Log& operator<<(LPCSTR str) {
			write(str);
			return *this;
		}

		Log& operator<<(LPCWSTR str) {
			CStringA strA = str;
			return operator<<(strA);
		}

		Log& operator<<(int num) {
			CString str;
			str.Format(L"%d", num);
			return operator<<(str);
		}

		Log& operator<<(double num) {
			CString str;
			str.Format(L"%lf", num);
			return operator<<(str);
		}

        Log& operator<<(const std::string& str) {
            return operator<<(str.c_str());
        }

        bool write(LPCSTR str) {
			if (!m_outFile.is_open())
				return false;

			CStringA strLogData;
			if (m_bNeedPreLog) {
				strLogData = getPreLogStr();
				m_bNeedPreLog = false;
			}

			strLogData += str;
			std::cout << strLogData;
			m_outFile << strLogData;
			m_outFile.flush();
			assert(m_outFile.good());
			return true;
        }

    protected:
		CStringA getPreLogStr() {
			CStringA strPreLog;
			SYSTEMTIME sys_time;
			::GetLocalTime(&sys_time);

			strPreLog.Format("\n%04d-%02d-%02d %02d:%02d:%02d:%03d|~%d|", sys_time.wYear, sys_time.wMonth, sys_time.wDay, sys_time.wHour, sys_time.wMinute, sys_time.wSecond, sys_time.wMilliseconds, GetCurrentThreadId());
			return strPreLog;
		}

        CString getDesktopPath() {
			CString strKnownFolderPath = L"";
			WCHAR* strPath = nullptr;
			if (SUCCEEDED(::SHGetKnownFolderPath(FOLDERID_Desktop, 0, nullptr, &strPath))) {
				strKnownFolderPath = strPath;
				CoTaskMemFree(strPath);
			}

			return strKnownFolderPath;
        }

        bool isFileExist(LPCTSTR filePath) {
            if (!filePath)
                return false;

            WIN32_FILE_ATTRIBUTE_DATA attrs = { 0 };
            return 0 != ::GetFileAttributesEx(filePath, ::GetFileExInfoStandard, &attrs);
        }

    private:
        std::ofstream m_outFile;
		bool m_bNeedPreLog = true;
		std::unique_lock<std::mutex> m_lock;
    };
}




