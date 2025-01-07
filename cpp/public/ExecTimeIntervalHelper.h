#pragma once
// ≈–∂œ÷¥––º‰∏Ù∞Ô÷˙¿‡

#include <atlstr.h>

class ExecTimeIntervalHelper {
public:
    ExecTimeIntervalHelper(const CString& strCfgPath);
    ~ExecTimeIntervalHelper();

    bool isNeedExec(const CString& strName);
    bool updateExecTime(const CString& strName);


};

