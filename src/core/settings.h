#ifndef SETTINGS_H
#define SETTINGS_H

#include <QSettings>
#include <QVariant>
#include <QApplication>
#include <QDebug>
#include <QBitArray>
#include <QPalette>

#include <map>


class Settings
{
public:
    Settings(const QString &organization, const QString &application);

    enum CIRCUIT {
        ARAGON,
        LAGUNA_SECA,
        MUGELLO
    };

    QString CIRCUIT_ARAGON = QString::fromUtf8("Motorland Aragón (Spain)");
    QString CIRCUIT_LAGUNA_SECA = QString::fromUtf8("Mazda Raceway Laguna Seca (USA)");
    QString CIRCUIT_MUGELLO = QString::fromUtf8("Autodromo Internazionale del Mugello (Italy)");

    // general set/get preferences
    void setValue(const QString &key, const QVariant &value);
    QVariant getValue(const QString &key);
    void remove(const QString &key);
    void clearValues();

    // specific set/get preferences
    void setDashboardConfiguration(QBitArray dashboardConfiguration);
    void setCircuitMap(QString circuit);
    void setTheme(bool isLight);

    QBitArray getDashboardConfiguration();
    QString getCircuitMap();
    bool hasLightTheme();

private:
    QSettings *settings;
};

#endif // SETTINGS_H
