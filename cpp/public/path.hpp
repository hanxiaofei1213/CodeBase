#pragma once
//////////////////////////////////////////////////////////////////////////
// FileName: path.hpp
// Author: wangwenxi
// Date: 2022.01.05
// Comment: �򵥵�·����
//////////////////////////////////////////////////////////////////////////


#include <windows.h>
#include <ShlObj.h>
#include <atlstr.h>

namespace easy {
    class Path {
    public:

        // ��ȡ��ǰģ������·��
        static CString getModuleFullPath() {
            TCHAR szFullPath[MAX_PATH] = { 0 };
            ::GetModuleFileName(NULL, szFullPath, MAX_PATH);
            return szFullPath;
        }

        // ��ȡ����·��
        static CString getDesktopPath() {
            return getKnownFolderPath(FOLDERID_Desktop);
        }

        // ��ȡָ��ϵͳ·��
        // id������
        // FOLDERID_Desktop        ����ȫ·��
        // FOLDERID_Documents      �ĵ�ȫ·��
        // FOLDERID_Downloads      ����ȫ·��
        // FOLDERID_LocalAppData    appdata\\local��·��
        // return ����ֵ������\\��β
		static CString getKnownFolderPath(REFKNOWNFOLDERID id) {
			CString strKnownFolderPath = L"";
			WCHAR* strPath = nullptr;
			if (SUCCEEDED(::SHGetKnownFolderPath(id, 0, nullptr, &strPath))) {
				strKnownFolderPath = strPath;
				CoTaskMemFree(strPath);
			}

			return strKnownFolderPath;
		}

        // �����·��תΪ����·��
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

        // ��ȡtempĿ¼
        static CString getTempPath() {
            WCHAR szPath[MAX_PATH] = { 0 };
            if (::GetTempPath(MAX_PATH, szPath) == 0) {
                return L"";
            }

            return CString(szPath);
        }
    };
};

