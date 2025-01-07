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
#include <iostream>

namespace {
const TCHAR* DEFAULT_LOG_NAME = L"easy_log.log";
HANDLE g_mutex = ::CreateMutex(NULL, FALSE, NULL);
}

#define EASY_LOG easy::Log::Log() << __FUNCTION__ << " " << (int)__LINE__ << "|"

namespace easy {
class Log {
public:
    Log(LPCTSTR szLogName = NULL) : m_bNeedPreLog(true) {
        ::WaitForSingleObject(g_mutex, INFINITE);
        CString strLogFileName = szLogName;
        if (strLogFileName.IsEmpty()) {
            strLogFileName = DEFAULT_LOG_NAME;
        }

        TCHAR szPath[MAX_PATH] = { 0 };
        ::SHGetFolderPath(NULL, CSIDL_DESKTOPDIRECTORY, NULL, 0, szPath);
        CPath desktopPath(szPath);
        desktopPath.Combine(szPath, strLogFileName);
        m_outFile.open(desktopPath.m_strPath, std::ios::app);
    }

    ~Log() {
        if (m_outFile.is_open()) {
            m_outFile.close();
        }
        ::ReleaseMutex(g_mutex);
    }

    // 写入字符串
    Log& operator<<(LPCSTR str) {
        write(str);
        return *this;
    }

    Log& operator<<(LPCWSTR str) {
        CStringA strA;
        strA = str;
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

private:
    std::ofstream m_outFile;
    bool m_bNeedPreLog;
};
}




