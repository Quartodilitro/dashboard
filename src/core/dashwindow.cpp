#include <QDebug>  // DEBUG
#include <stdexcept>

#include "dashwindow.h"


DashWindow::DashWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::DashWindow)
{
    ui->setupUi(this);  // setup  and title
    QFont font = QApplication::font();
    font.setPointSize(15);
    font.setItalic(true);
    ui->title->setFont(font);
    ui->title->setAlignment(Qt::AlignCenter);

    connectionBridge = new ConnectionBridge();
    settings = new Settings(QCoreApplication::organizationName(), QCoreApplication::applicationName());  // create settings manager
    this->ui->rightTabButton->setIcon(QPixmap(":/image/right_black").scaled(QSize(120, 120), Qt::KeepAspectRatio));    QObject::connect(this->ui->rightTabButton, SIGNAL(clicked()), this->parent(), SLOT(changeTabRight()));  // navigation button

    ui->logoLabel->setAlignment(Qt::AlignCenter);  // logo at the bottom

    // bar
    ui->rpmBar->setRange(0, 15000);  // in order to have max rpm (9999) at (360 - 45)° degree
    ui->rpmBar->setDecimals(0);
    ui->rpmBar->setNullPosition(225);
    ui->rpmBar->setFormat("");
    ui->rpmBar->setDataPenWidth(10);
    ui->rpmBar->setOutlinePenWidth(10);
    ui->rpmBar->setBarStyle(QRoundProgressBar::StyleDonut);

    // labels
    font.setItalic(false);
    font.setBold(true);

    ui->bpmIndicator->setTitle(QString::fromUtf8("Heart beat (BPM)"));
    font.setPointSize(50); ui->rpmLabel->setFont(font);
    font.setPointSize(80); ui->gearLabel->setFont(font);
    font.setPointSize(30); ui->speedLabel->setFont(font);
}

DashWindow::~DashWindow()
{
    delete ui;
}

/**
 * @brief DashWindow::setValue
 * @param value new value to set
 * @param code field to set value of
 */
void DashWindow::setValue(double value, int code) {
    if (code == connectionBridge->DATA_CODE_SPEED) {
        speedValue = value;
        ui->speedLabel->setText(QString::number(value));
    } else if (code == connectionBridge->DATA_CODE_RPM) {
        rpmValue = value;
        ui->rpmLabel->setText(QString::number(value));
        ui->rpmBar->setValue(value);

        // change color of rpm bar
        QPalette barPalette = ui->rpmBar->palette();
        if (value > 10500) {
            barPalette.setBrush(QPalette::Highlight, Qt::red);
        } else if (value > 7500) {
            barPalette.setBrush(QPalette::Highlight, Qt::yellow);
        } else {
            barPalette.setBrush(QPalette::Highlight, Qt::green);
        }
        ui->rpmBar->setPalette(barPalette);

    } else if (code == connectionBridge->DATA_CODE_GEAR) {
        gearValue = value;
        ui->gearLabel->setText(QString::number(value));
    } else if (code == connectionBridge->DATA_CODE_BPM) {
        ui->bpmIndicator->setValue(value);
    }
}

/**
 * @brief DashWindow::getValue
 * @param code field to get value of
 * @return value of selected field
 */
double DashWindow::getValue(int code) {
    if (code == connectionBridge->DATA_CODE_SPEED) {
        return speedValue;
    } else if (code == connectionBridge->DATA_CODE_RPM) {
        return rpmValue;
    }  else if (code == connectionBridge->DATA_CODE_GEAR) {
        return gearValue;
    }
}

void DashWindow::updateSettings() {
    QBitArray dashboardConfiguration = QBitArray(5);  // settings->getDashboardConfiguration(); // retrieve setting
    dashboardConfiguration.fill(1);  // make visible all widgets

    // hide/show widgets
    this->ui->rpmLabel->setHidden(!dashboardConfiguration.at(0));
    this->ui->gearLabel->setHidden(!dashboardConfiguration.at(1));
    this->ui->speedLabel->setHidden(!dashboardConfiguration.at(2));
    this->ui->bpmIndicator->setHidden(!dashboardConfiguration.at(3));
    this->ui->timeTable->setHidden(!dashboardConfiguration.at(4));
    this->ui->mapLabel->setHidden(!dashboardConfiguration.at(4));

    // map
    QString circuitName = settings->getCircuitMap();
    QPixmap map;
    if (circuitName == settings->CIRCUIT_ARAGON) {
        if (settings->hasLightTheme()) {
            map = QPixmap(":/circuit/aragon_black").scaled(QSize(141, 141), Qt::KeepAspectRatio);
        } else {
            map = QPixmap(":/circuit/aragon_white").scaled(QSize(141, 141), Qt::KeepAspectRatio);
        }
    } else if (circuitName == settings->CIRCUIT_LAGUNA_SECA) {
        if (settings->hasLightTheme()) {
            map = QPixmap(":/circuit/lagunaseca_black").scaled(QSize(141, 141), Qt::KeepAspectRatio);
        } else {
            map = QPixmap(":/circuit/lagunaseca_white").scaled(QSize(141, 141), Qt::KeepAspectRatio);
        }
    } else if (circuitName == settings->CIRCUIT_MUGELLO) {
        if (settings->hasLightTheme()) {
            map = QPixmap(":/circuit/mugello_black").scaled(QSize(141, 141), Qt::KeepAspectRatio);
        } else {
            map = QPixmap(":/circuit/mugello_white").scaled(QSize(141, 141), Qt::KeepAspectRatio);
        }
    }
    this->ui->mapLabel->setPixmap(map);

    // theme
    if (settings->hasLightTheme()) {
       this->ui->rightTabButton->setIcon(QPixmap(":/image/right_black").scaled(QSize(120, 120), Qt::KeepAspectRatio));
       this->ui->logoLabel->setPixmap(QPixmap(":/image/logo").scaled(QSize(300, 100), Qt::KeepAspectRatio));
    } else {
        this->ui->rightTabButton->setIcon(QPixmap(":/image/right_white").scaled(QSize(120, 120), Qt::KeepAspectRatio));
        this->ui->logoLabel->setPixmap(QPixmap(":/image/logo_bw").scaled(QSize(300, 100), Qt::KeepAspectRatio));
    }
}
