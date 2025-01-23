#pragma once
//////////////////////////////////////////////////////////////////////////
// FileName: path.hpp
// Author: wangwenxi
// Date: 2022.01.05
// Comment: 简单的路径类
//////////////////////////////////////////////////////////////////////////


#include <windows.h>
#include <ShlObj.h>
#include <atlstr.h>

namespace easy {
    class Path {
    public:

        // 获取当前模块完整路径
        static CString getModuleFullPath() {
            TCHAR szFullPath[MAX_PATH] = { 0 };
            ::GetModuleFileName(NULL, szFullPath, MAX_PATH);
            return szFullPath;
        }

        // 获取桌面路径
        static CString getDesktopPath() {
            return getKnownFolderPath(FOLDERID_Desktop);
        }

        // 获取指定系统路径
        // id参数：
        // FOLDERID_Desktop        桌面全路径
        // FOLDERID_Documents      文档全路径
        // FOLDERID_Downloads      下载全路径
        // FOLDERID_LocalAppData    appdata\\local下路径
        // return 返回值不会以\\结尾
		static CString getKnownFolderPath(REFKNOWNFOLDERID id) {
			CString strKnownFolderPath = L"";
			WCHAR* strPath = nullptr;
			if (SUCCEEDED(::SHGetKnownFolderPath(id, 0, nullptr, &strPath))) {
				strKnownFolderPath = strPath;
				CoTaskMemFree(strPath);
			}

			return strKnownFolderPath;
		}

        // 将相对路径转为绝对路径
        static BOOL ConvertToAbsolutePath(CString& strRelativePath) {
            if (strRelativePath.IsEmpty()) {
                return FALSE;
            }

            wchar_t szAbsolutePath[MAX_PATH];
            if (!::GetFullPathName(strRelativePath, MAX_PATH, szAbsolutePath, nullptr)) {
                return FALSE;
            }

            strRelativePath = szAbsolutePath;
            return TRUE;
        }

        // 获取temp目录
        static CString getTempPath() {
            WCHAR szPath[MAX_PATH] = { 0 };
            if (::GetTempPath(MAX_PATH, szPath) == 0) {
                return L"";
            }

            return CString(szPath);
        }
    };
};

