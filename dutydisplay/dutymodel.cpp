#include "dutymodel.h"
#include <QDebug>
#include <QDir>
#include <QFile>
#include <QTextStream>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
#include <QStandardPaths>
#include <QStorageInfo>

DutyModel::DutyModel(QObject *parent) : QObject(parent)
{

}

bool DutyModel::load(const QString &fileName)
{
    QString cfgPath = fileName;

    if (!QFile::exists(cfgPath)) {
        setDebugMessage("duty.csv does not exist.");
        return false;
    }
    QFile file(cfgPath);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        setDebugMessage("open duty.csv failed.");
        return false;
    }
    QTextStream stream(&file);
    QStringList tempLst;
    while (!stream.atEnd()) {
        QString line = stream.readLine();
        if (!line.trimmed().isEmpty()) {
            tempLst << line;
        }
    }
    file.close();

    if (tempLst.count() <= 1) {
        setDebugMessage("data of duty.csv is empty.");
        return false;
    }
    tempLst.removeFirst();

    QStringList leaders, drivers, polices;
    for (QString item : tempLst) {
        QStringList lineLst = item.split(",");
        lineLst.removeFirst();
        if (lineLst.count() != 3) {
            setDebugMessage("data of duty.csv is invalid.");
            return false;
        }
        leaders << lineLst.at(0);
        drivers << lineLst.at(1);
        polices << lineLst.at(2);
    }
    setLeaders(leaders);
    setDrivers(drivers);
    setPolices(polices);
    setDebugMessage("");
    return true;
}

QStringList DutyModel::leaders() const
{
    return m_leaders;
}

QStringList DutyModel::drivers() const
{
    return m_drivers;
}

QStringList DutyModel::polices() const
{
    return m_polices;
}

QString DutyModel::debugMessage() const
{
    return m_debugMessage;
}

void DutyModel::setLeaders(QStringList leaders)
{
    if (m_leaders == leaders)
        return;

    m_leaders = leaders;
    emit leadersChanged(m_leaders);
}

void DutyModel::setDrivers(QStringList drivers)
{
    if (m_drivers == drivers)
        return;

    m_drivers = drivers;
    emit driversChanged(m_drivers);
}

void DutyModel::setPolices(QStringList polices)
{
    if (m_polices == polices)
        return;

    m_polices = polices;
    emit policesChanged(m_polices);
}

void DutyModel::setDebugMessage(QString debugMessage)
{
    if (m_debugMessage == debugMessage)
        return;

    m_debugMessage = debugMessage;
    emit debugMessageChanged(m_debugMessage);
}

