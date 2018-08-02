#ifndef DUTYMODEL_H
#define DUTYMODEL_H

#include <QObject>

class DutyModel : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QStringList leaders READ leaders WRITE setLeaders NOTIFY leadersChanged)
    Q_PROPERTY(QStringList drivers READ drivers WRITE setDrivers NOTIFY driversChanged)
    Q_PROPERTY(QStringList polices READ polices WRITE setPolices NOTIFY policesChanged)
    Q_PROPERTY(QString debugMessage READ debugMessage WRITE setDebugMessage NOTIFY debugMessageChanged)

public:
    explicit DutyModel(QObject *parent = nullptr);

    Q_INVOKABLE bool load(const QString &fileName);

    QStringList leaders() const;
    QStringList drivers() const;
    QStringList polices() const;
    QString debugMessage() const;

signals:
    void leadersChanged(QStringList leaders);
    void driversChanged(QStringList drivers);
    void policesChanged(QStringList polices);
    void debugMessageChanged(QString debugMessage);

public slots:
    void setLeaders(QStringList leaders);
    void setDrivers(QStringList drivers);
    void setPolices(QStringList polices);
    void setDebugMessage(QString debugMessage);

private :
    QStringList m_leaders;
    QStringList m_drivers;
    QStringList m_polices;
    QString m_debugMessage;
};

#endif // DUTYMODEL_H
