#include <QCoreApplication>
#include <windows.h>
#include <QString>
#include <QDebug>

static QString getVersionString(QString fileName)
{
#ifdef Q_OS_WIN
    // first of all, GetFileVersionInfoSize
    DWORD dwHandle;
    DWORD dwLen = GetFileVersionInfoSize(fileName.toStdWString().c_str(), &dwHandle);

    // GetFileVersionInfo
    LPVOID lpData = new BYTE[dwLen];
    if (!GetFileVersionInfo(fileName.toStdWString().c_str(), dwHandle, dwLen, lpData)) {
        qDebug() << "error in GetFileVersionInfo";
        delete[] lpData;
        return "";
    }

    // VerQueryValue
    VS_FIXEDFILEINFO* lpBuffer = NULL;
    UINT uLen;

    if (!VerQueryValue(lpData,
                       QString("\\").toStdWString().c_str(),
                       (LPVOID*)& lpBuffer,
                       &uLen)) {

        qDebug() << "error in VerQueryValue";
        delete[] lpData;
        return "";
    } else {
        return QString("%1.%2.%3.%4")
                .arg((lpBuffer->dwFileVersionMS >> 16) & 0xffff)
                .arg((lpBuffer->dwFileVersionMS) & 0xffff)
                .arg((lpBuffer->dwFileVersionLS >> 16) & 0xffff)
                .arg((lpBuffer->dwFileVersionLS) & 0xffff);
    }
#else
    Q_ASSERT_X(false, "platform", "Only support windows platform.");
#endif
}

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    QString version = getVersionString("C:/Qt/Qt5.6.3/5.6.3/msvc2015_64/bin/Qt5Gui.dll");
    qDebug() << version;

    return a.exec();
}
