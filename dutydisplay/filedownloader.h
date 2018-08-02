#ifndef FILEDOWNLOADER_H
#define FILEDOWNLOADER_H

#include <QObject>
#include <QNetworkAccessManager>
#include <QFile>
#include <QTime>

class QNetworkReply;

class FileDownloader : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QString speed READ speed WRITE setSpeed NOTIFY speedChanged)
    Q_PROPERTY(int progress READ progress WRITE setProgress NOTIFY progressChanged)
public:
    explicit FileDownloader(QObject *parent = 0);
    Q_INVOKABLE void startDownload(const QUrl &url);
    QString speed() const;
    int progress() const;
public slots:
    void setSpeed(QString speed);
    void setProgress(int progress);
signals:
    void finished(QString filename);
    void failed();
    void speedChanged(QString speed);
    void progressChanged(int progress);
private slots:
    void onDownloadProgress(qint64 bytesReceived, qint64 bytesTotal);
    void onDownloadFinished();
    void onDownloadReadyRead();
private:
    QNetworkAccessManager manager_;
    QNetworkReply *current_download_ = nullptr;
    QFile output_;
    QTime download_time_;
    QString speed_;
    int m_progress;
};

#endif // FILEDOWNLOADER_H
