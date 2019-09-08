#include <QApplication>
#include <stdio.h>
#include <windows.h>
#include <tlhelp32.h>
#include <QDebug>
#include <QVector>
#include <QMessageBox>

static bool getProcessIdByProcessImageName(const QString &processImageName,
                                           unsigned int *targetProcessId)
{
    HANDLE processSnapshotHandle = nullptr;
    PROCESSENTRY32 processEntry32 = { 0 };
    processEntry32.dwSize = sizeof(PROCESSENTRY32);
    processSnapshotHandle = ::CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);
    if (processSnapshotHandle == INVALID_HANDLE_VALUE) {
        return false;
    }

    ::Process32First(processSnapshotHandle, &processEntry32);
    do {
        if (QString::fromWCharArray(processEntry32.szExeFile) == processImageName) {
            *targetProcessId = processEntry32.th32ProcessID;
            break;
        }
    } while (::Process32Next(processSnapshotHandle, &processEntry32));

    ::CloseHandle(processSnapshotHandle);
    processSnapshotHandle = nullptr;

    if (*targetProcessId == 0) {
        return false;
    }
    return true;
}

static bool getThreadIdsByProcessId(unsigned int processId, QVector<unsigned int> &threadIds)
{
    HANDLE threadSnapshotHandle = nullptr;
    THREADENTRY32 threadEntry32 = { 0 };
    threadEntry32.dwSize = sizeof(THREADENTRY32);

    threadSnapshotHandle = ::CreateToolhelp32Snapshot(TH32CS_SNAPTHREAD, 0);
    if (threadSnapshotHandle == INVALID_HANDLE_VALUE) {
        return false;
    }

    ::Thread32First(threadSnapshotHandle, &threadEntry32);
    do {
        if (threadEntry32.th32OwnerProcessID == processId) {
            threadIds.push_back(threadEntry32.th32ThreadID);
        }
    } while (::Thread32Next(threadSnapshotHandle, &threadEntry32));

    ::CloseHandle(threadSnapshotHandle);
    threadSnapshotHandle = nullptr;

    return true;
}

static bool getThreadIdByProcessId(unsigned int processId, unsigned int &threadId)
{
    HANDLE threadSnapshotHandle = nullptr;
    THREADENTRY32 threadEntry32 = { 0 };
    threadEntry32.dwSize = sizeof(THREADENTRY32);

    threadSnapshotHandle = ::CreateToolhelp32Snapshot(TH32CS_SNAPTHREAD, 0);
    if (threadSnapshotHandle == INVALID_HANDLE_VALUE) {
        return false;
    }

    ::Thread32First(threadSnapshotHandle, &threadEntry32);
    do {
        if (threadEntry32.th32OwnerProcessID == processId) {
            threadId = threadEntry32.th32ThreadID;
            break;
        }
    } while (::Thread32Next(threadSnapshotHandle, &threadEntry32));

    ::CloseHandle(threadSnapshotHandle);
    threadSnapshotHandle = nullptr;

    return true;
}

/**
 * https://github.com/AzureGreen/InjectCollection
 */
bool grantPriviledge(PWCHAR priviledgeName)
{
    TOKEN_PRIVILEGES tokenPrivileges, oldPrivileges;
    DWORD dwReturnLength = sizeof(oldPrivileges);
    HANDLE TokenHandle = nullptr;
    LUID uID;

    // 打开权限令牌
    if (!::OpenThreadToken(GetCurrentThread(), TOKEN_ADJUST_PRIVILEGES | TOKEN_QUERY, FALSE, &TokenHandle)) {
        if (::GetLastError() != ERROR_NO_TOKEN) {
            return false;
        }
        if (!::OpenProcessToken(GetCurrentProcess(), TOKEN_ADJUST_PRIVILEGES | TOKEN_QUERY, &TokenHandle)) {
            return false;
        }
    }

    // 通过权限名称查找uID
    if (!::LookupPrivilegeValue(nullptr, priviledgeName, &uID)) {
        ::CloseHandle(TokenHandle);
        return false;
    }

    tokenPrivileges.PrivilegeCount = 1; // 要提升的权限个数
    tokenPrivileges.Privileges[0].Attributes = SE_PRIVILEGE_ENABLED;   // 动态数组，数组大小根据Count的数目
    tokenPrivileges.Privileges[0].Luid = uID;

    // 在这里我们进行调整权限
    if (!::AdjustTokenPrivileges(TokenHandle, FALSE, &tokenPrivileges, sizeof(TOKEN_PRIVILEGES), &oldPrivileges, &dwReturnLength))  {
        ::CloseHandle(TokenHandle);
        return false;
    }

    ::CloseHandle(TokenHandle);
    return true;
}

static bool inject(unsigned int threadId)
{
    HMODULE hdll = LoadLibrary(L"calc-hook-process.dll");
    if (hdll == nullptr) {
        qDebug() << "LoadLibrary failed.";
        return false;
    }

    HOOKPROC hproc = (HOOKPROC)GetProcAddress(hdll, "hookProcedure");
    if (hproc == nullptr) {
        qDebug() << "GetProcAddress failed.";
        return false;
    }
    HHOOK hook = ::SetWindowsHookEx(WH_KEYBOARD, hproc, hdll, threadId);
    if (!hook) {
        DWORD error = ::GetLastError();
        qDebug() << __FUNCTION__ << "inject failed: " << threadId << ". GetLastError: " << error;
        return false;
    } else {
        qDebug() << __FUNCTION__ << "inject ok: " << threadId;
    }
    return true;
}

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    if (!grantPriviledge(SE_DEBUG_NAME)) {
        QMessageBox::critical(nullptr, "Error",  "grant priviledge failed.");
        return 0;
    }

    // 获取计算器的进程ID
    unsigned int pid = 0;
    bool ok = getProcessIdByProcessImageName("notepad++.exe", &pid);
    if (!ok) {
        QMessageBox::critical(nullptr, "Error",  "getProcessIdByProcessImageName failed.");
        return 0;
    }
    qDebug() << "pid: " << pid;

#if 0
    // 获取计算器进程下所有线程
    QVector<unsigned int> threadIds;
    ok = getThreadIdsByProcessId(pid, threadIds);
    Q_ASSERT_X(ok, "getThreadIdByProcessId", "error");
    qDebug() << "thread ids: " << threadIds;

    // 给目标线程的指定消息下钩
    for (auto threadId : threadIds) {
        inject(threadId);
    }
#endif
    unsigned int threadId = 0;
    ok = getThreadIdByProcessId(pid, threadId);
    if (!ok) {
        QMessageBox::critical(nullptr, "Error",  "getThreadIdByProcessId failed.");
        return 0;
    }
    qDebug() << "threadId: " << threadId;

    inject(threadId);

    return a.exec();
}
