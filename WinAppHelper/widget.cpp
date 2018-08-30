#include "widget.h"
#include "ui_widget.h"

#include <WinUser.h>
#include <tlhelp32.h>

#include <QDebug>
#include <QMessageBox>

static DWORD findProcess(const QString &exe)
{
    PROCESSENTRY32 pe32;
    pe32.dwSize = sizeof(pe32);
    HANDLE hProcessSnap = ::CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);

    DWORD dwRet = 0;
    if (hProcessSnap != INVALID_HANDLE_VALUE) {
        BOOL bMore = ::Process32First(hProcessSnap, &pe32);
        while (bMore) {
            if (QString::fromWCharArray(pe32.szExeFile) == exe) {
                dwRet = pe32.th32ProcessID;
            }
            bMore = ::Process32Next(hProcessSnap, &pe32);
        }
        ::CloseHandle(hProcessSnap);
    }
    return dwRet;
}

static HWND findWindowHandle(const QString &title)
{
    return ::FindWindow(NULL, title.toStdWString().c_str());
}

static BOOL closeWindowHandle(HWND wnd)
{
    return ::CloseWindow(wnd);
}

Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    ui->setupUi(this);
}

Widget::~Widget()
{
    delete ui;
}

void Widget::on_pushButton_findProcess_clicked()
{
    DWORD processId = findProcess("QQ.exe");
    qDebug() << __FUNCTION__ << processId;
}

void Widget::on_pushButton_findWindowHandle_clicked()
{
    HWND wnd = findWindowHandle("QQ");
    qDebug() << __FUNCTION__ << wnd;
}

void Widget::on_pushButton_closeWindowHandle_clicked()
{
    HWND wnd = findWindowHandle("QQ");
    qDebug() << __FUNCTION__ << wnd;
    closeWindowHandle(wnd);
}


void Widget::on_pushButton_bind_clicked()
{
    // 根据主窗体标题查找窗体句柄
    // 你可以用 AccExplorer 2.0 / Microsoft Spy++ / UI Spy 查找这些信息
    const QString title = QString("Polar Si8000 Controlled Impedance Quick Solver - [Untitled.Si8]");
    wnd_ = findWindowHandle(title);
    qDebug() << __FUNCTION__ << wnd_;

    if (wnd_ == NULL) {
        QMessageBox::warning(this, "Warning", "Window not found.");
        return;
    }

    // 找到你要控制的控件的相对坐标（相对于主窗体）
    // H1 (742, 74)
    // Calculate (993, 217)

    // 置 "GO" 按钮为可用状态
    ui->pushButton_bind->setEnabled(false);
    ui->pushButton_go->setEnabled(true);
}

void Widget::on_pushButton_go_clicked()
{
    // 获取H1的句柄
    ::POINT p;
    p.x = 742;
    p.y = 74;
    HWND h1_wnd = ::ChildWindowFromPoint(wnd_, p);
    qDebug() << __FUNCTION__ << "H1 wnd: " << h1_wnd;
    ::SendMessage(h1_wnd, WM_SETFOCUS, 0, 0);

    // 获取H1的值
    TCHAR buff[1024] = {0};
    ::SendMessage(h1_wnd, WM_GETTEXT, 1024, (LPARAM)buff);
    qDebug() << __FUNCTION__ << "H1 value: " << QString::fromWCharArray(buff);

    // 设置H1的值
    ::SendMessage(h1_wnd, WM_SETTEXT, 0, (LPARAM)QString("9.5").toStdWString().c_str());

    // 计算
    p.x = 993;
    p.y = 217;
    HWND calc_wnd = ::ChildWindowFromPoint(wnd_, p);
    qDebug() << __FUNCTION__ << "calc wnd: " << calc_wnd;
    ::SendMessage(calc_wnd, BM_CLICK, 0, 0);
}
