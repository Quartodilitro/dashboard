#include "settingswindow.h"
#include "ui_settingswindow.h"

SettingsWindow::SettingsWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::SettingsWindow)
{
    ui->setupUi(this);  // setup  and title
    QFont font = QApplication::font();
    font.setPointSize(12);
    font.setItalic(true);
    ui->title->setFont(font);
    ui->title->setAlignment(Qt::AlignCenter);

    ui->leftTabButton->setIcon(QPixmap(":/image/left_black").scaled(QSize(120, 120), Qt::KeepAspectRatio));  // navigation button
    QObject::connect(this->ui->leftTabButton, SIGNAL(clicked()), this->parent(), SLOT(changeTabLeft()));

    settings = new Settings(QCoreApplication::organizationName(), QCoreApplication::applicationName());  // create settings manager

    try {  // no settings set ever before
        int l = settings->getDashboardConfiguration().size();
    } catch (...) {
        emit updateUserPref();  // create new settings
    }

    displayUserPref();
    QObject::connect(this->ui->updateSettingsButton, SIGNAL(clicked()), this, SLOT(updateUserPref()));  // connect update buttons to update functions
    QObject::connect(this, SIGNAL(updateSettings()), this->parent(), SLOT(updateSettings()));
}

SettingsWindow::~SettingsWindow()
{
    delete ui;
}

QVariant SettingsWindow::getUserPrefValue(const QString &key) {
    return settings->getValue(key);
}

void SettingsWindow::setUserPref(const QString &key, const QVariant &value) {
    settings->setValue(key, value);
}

/**
 * @brief SettingsWindow::updateUserPref
 * @return Check ui buttons for new settings; apply new settings, then call mainwindow to apply settings overall.
 */
void SettingsWindow::updateUserPref() {
    // dashboard settings
    QBitArray dashboardConfiguration = QBitArray(5);
    dashboardConfiguration.setBit(0, this->ui->rpmCheckBox->isChecked());
    dashboardConfiguration.setBit(1, this->ui->gearCheckBox->isChecked());
    dashboardConfiguration.setBit(2, this->ui->speedCheckBox->isChecked());
    dashboardConfiguration.setBit(3, this->ui->bpmCheckBox->isChecked());
    dashboardConfiguration.setBit(4, this->ui->gpsCheckBox->isChecked());
    settings->setDashboardConfiguration(dashboardConfiguration);

    // circuit settings
    if (this->ui->aragonCircuitButton->isChecked()) {
        settings->setCircuitMap(settings->CIRCUIT_ARAGON);
    } else if (this->ui->lagunasecaCircuitButton->isChecked()) {
        settings->setCircuitMap(settings->CIRCUIT_LAGUNA_SECA);
    } else if (this->ui->mugelloCircuitButton->isChecked()) {
        settings->setCircuitMap(settings->CIRCUIT_MUGELLO);
    }

    // theme settings
    settings->setTheme(this->ui->lightThemeButton->isChecked());

    emit this->updateSettings();  // call main window to update settings
}

/**
 * @brief SettingsWindow::displayUserPref
 * @return read settings config file, then update screen with user preferences
 */
void SettingsWindow::displayUserPref() {
    QBitArray dashboardConfiguration = settings->getDashboardConfiguration();  // get preferences
    this->ui->rpmCheckBox->setChecked(dashboardConfiguration.at(0));
    this->ui->gearCheckBox->setChecked(dashboardConfiguration.at(1));
    this->ui->speedCheckBox->setChecked(dashboardConfiguration.at(2));
    this->ui->bpmCheckBox->setChecked(dashboardConfiguration.at(3));
    this->ui->gpsCheckBox->setChecked(dashboardConfiguration.at(4));

    QString circuitName = settings->getCircuitMap();
    this->ui->aragonCircuitButton->setChecked(circuitName == settings->CIRCUIT_ARAGON);
    this->ui->lagunasecaCircuitButton->setChecked(circuitName == settings->CIRCUIT_LAGUNA_SECA);
    this->ui->mugelloCircuitButton->setChecked(circuitName == settings->CIRCUIT_MUGELLO);

    this->ui->lightThemeButton->setChecked(settings->hasLightTheme() == true);
    this->ui->darkThemeButton->setChecked(settings->hasLightTheme() == false);

    // theme
    if (settings->hasLightTheme()) {
       this->ui->leftTabButton->setIcon(QPixmap(":/image/left_black").scaled(QSize(120, 120), Qt::KeepAspectRatio));
    } else {
        this->ui->leftTabButton->setIcon(QPixmap(":/image/left_white").scaled(QSize(120, 120), Qt::KeepAspectRatio));
    }
}

