#include "settings.h"

Settings::Settings(const QString &organization, const QString &application)
{
    settings = new QSettings(organization, application);
}

/**
 * @brief Settings::setValue
 * @param key data field to edit
 * @param value new value to edit
 */
void Settings::setValue(const QString &key, const QVariant &value) {
    settings->setValue(key, value);
}

/**
 * @brief Settings::getValue
 * @param key field data to select
 * @return value of given field
 */
QVariant Settings::getValue(const QString &key) {
    return settings->value(key);
}

/**
 * @brief Settings::remove
 * @param key field data to remove
 * @return remove given field data
 */
void Settings::remove(const QString &key) {
    settings->remove(key);
}

/**
 * @brief Settings::clearAllValues
 * @return remove all data
 */
void Settings::clearValues() {
    settings->clear();
}

/**
 * @brief Settings::setDashboardConfiguration
 * @return set new user preferences regarding dashboard
 */
void Settings::setDashboardConfiguration(QBitArray dashboardConfiguration) {
    setValue("DASHBOARD", dashboardConfiguration);
}

/**
 * @brief Settings::getDashboardConfiguration
 * @return boolean values on whether dashboard has widgets
 */
QBitArray Settings::getDashboardConfiguration() {
    return getValue("DASHBOARD").toBitArray();
}

/**
 * @brief Settings::setCircuitMap
 * @param circuit name of circuit to set map
 * @return set map of given circuit in window
 */
void Settings::setCircuitMap(QString circuit) {
    setValue("CIRCUIT", circuit);
}

/**
 * @brief Settings::getCircuitMap
 * @return get name of circuit default
 */
QString Settings::getCircuitMap() {
    return getValue("CIRCUIT").toString();
}

/**
 * @brief Settings::setTheme
 * @param isLight whether user opted for light or dark theme
 * @return set preference on theme
 */
void Settings::setTheme(bool isLight) {
    setValue("THEME::LIGHT", isLight);
}

/**
 * @brief Settings::getTheme
 * @return user preference on theme (true = light, false = dark theme)
 */
bool Settings::hasLightTheme() {
    return getValue("THEME::LIGHT").toBool();
}
