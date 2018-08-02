#include "filedownloader.h"
#include <QNetworkReply>
#include <QNetworkRequest>
#include <QStandardPaths>
#include <QDir>
#include <QUuid>
#include <QtMath>
#include <QDebug>

FileDownloader::FileDownloader(QObject *parent) : QObject(parent)
{
}

void FileDownloader::startDownload(const QUrl &url)
{
    QString path = QStandardPaths::writableLocation(QStandardPaths::DownloadLocation)
            + QDir::separator() + "duty.csv";
    output_.setFileName(path);
    if (QFile::exists(path)) {
        QFile::remove(path);
    }
    if (!output_.open(QIODevice::WriteOnly)) {
        emit failed();
        return;
    }
    QNetworkRequest request(url);
    current_download_ = manager_.get(request);
    connect(current_download_, SIGNAL(downloadProgress(qint64,qint64)),
            this, SLOT(onDownloadProgress(qint64,qint64)));
    connect(current_download_, SIGNAL(finished()),
            this, SLOT(onDownloadFinished()));
    connect(current_download_, SIGNAL(readyRead()),
            this, SLOT(onDownloadReadyRead()));
    download_time_.start();
}

QString FileDownloader::speed() const
{
    return speed_;
}

int FileDownloader::progress() const
{
    return m_progress;
}

void FileDownloader::setSpeed(QString speed)
{
    if (speed_ == speed)
        return;

    speed_ = speed;
    emit speedChanged(speed);
}

void FileDownloader::setProgress(int progress)
{
    if (m_progress == progress)
        return;

    m_progress = progress;
    emit progressChanged(progress);
}

void FileDownloader::onDownloadProgress(qint64 bytesReceived, qint64 bytesTotal)
{
    double speed = bytesReceived * 1000.0 / download_time_.elapsed();
    QString unit;
    if (speed < 1024) {
        unit = "bytes/sec";
    } else if (speed < 1024*1024) {
        speed /= 1024;
        unit = "kB/s";
    } else {
        speed /= 1024*1024;
        unit = "MB/s";
    }
    setProgress(qCeil(bytesReceived * 1.0 / bytesTotal * 100));
    setSpeed(QString::fromLatin1("%1 %2")
             .arg(speed, 3, 'f', 1).arg(unit));
}

void FileDownloader::onDownloadFinished()
{
    QString filename = output_.fileName();
    output_.close();
    if (current_download_->error()) {
        emit failed();
    } else {
        emit finished(filename);
    }
    current_download_->deleteLater();
}

void FileDownloader::onDownloadReadyRead()
{
    output_.write(current_download_->readAll());
}
