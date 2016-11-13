#include <QDebug>  // DEBUG
#include <stdexcept>
#include <QPainter>

#include "dashwindow.h"


DashWindow::DashWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::DashWindow)
{
    ui->setupUi(this);  // setup  and title
    QFont font = QApplication::font();
    font.setPointSize(12);
    font.setItalic(true);
    ui->title->setFont(font);
    ui->title->setAlignment(Qt::AlignCenter);
    ui->timeTable->setFrameStyle(QFrame::NoFrame);

    connectionBridge = new ConnectionBridge();
    settings = new Settings(QCoreApplication::organizationName(), QCoreApplication::applicationName());  // create settings manager
    this->ui->rightTabButton->setIcon(QPixmap(":/image/right_black").scaled(QSize(120, 120), Qt::KeepAspectRatio));    QObject::connect(this->ui->rightTabButton, SIGNAL(clicked()), this->parent(), SLOT(changeTabRight()));  // navigation button

    ui->logoLabel->setAlignment(Qt::AlignCenter);  // logo at the bottom

    // bar
    ui->rpmBar->setRange(0, 19277);  // in order to have max rpm at (360 - 45)° degree
    ui->rpmBar->setDecimals(0);
    ui->rpmBar->setNullPosition(225);
    ui->rpmBar->setFormat("");
    ui->rpmBar->setDataPenWidth(10);
    ui->rpmBar->setOutlinePenWidth(10);
    ui->rpmBar->setBarStyle(QRoundProgressBar::StyleDonut);

    // labels
    font.setItalic(false);
    font.setBold(true);

    ui->bpmIndicator->setTitle(QString::fromUtf8("Heart beat\n      (BPM)"));
    font.setPointSize(45); ui->rpmLabel->setFont(font);
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
    } else if (code == connectionBridge->DATA_CODE_TIME_S_1S) {
        QTableWidgetItem *t = new QTableWidgetItem();
        t->setText(QString::number(value) + "\".000");
        ui->timeTable->setItem(0, 0, t);
    }  else if (code == connectionBridge->DATA_CODE_TIME_S_2S) {
        QTableWidgetItem *t = new QTableWidgetItem();
        t->setText(QString::number(value) + "\".000");
        ui->timeTable->setItem(1, 0, t);
    }  else if (code == connectionBridge->DATA_CODE_TIME_S_3S) {
        QTableWidgetItem *t = new QTableWidgetItem();
        t->setText(QString::number(value) + "\".000");
        ui->timeTable->setItem(2, 0, t);
    }  else if (code == connectionBridge->DATA_CODE_TIME_S_4S) {
        QTableWidgetItem *t = new QTableWidgetItem();
        t->setText(QString::number(value) + "\".000");
        ui->timeTable->setItem(3, 0, t);
    } else if (code == connectionBridge->DATA_CODE_GPS_X) {
        this->gpsX = value;
        this->updateGPSMap();
    } else if (code == connectionBridge->DATA_CODE_GPS_Y) {
        this->gpsY = value;
        this->updateGPSMap();
    }
}

void DashWindow::updateGPSMap() {
    QBitArray dashboardConfiguration = settings->getDashboardConfiguration(); // retrieve setting
    if (dashboardConfiguration.at(4)) {  // there is a map to draw on
        QPixmap *newMap = new QPixmap(this->map);
        QPainter painter(newMap);

        if (settings->hasLightTheme()) {
            painter.setPen(QPen(QBrush(QColor(255, 0, 0)), 10, Qt::SolidLine, Qt::RoundCap));
        } else {
            painter.setPen(QPen(QBrush(QColor(255, 0, 0)), 10, Qt::SolidLine, Qt::RoundCap));
        }
        painter.drawPoint(gpsX / 364 * this->map.width(), gpsY / 142 * this->map.height());  // scale to image
        this->ui->mapLabel->setPixmap(*newMap);
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
    QBitArray dashboardConfiguration = settings->getDashboardConfiguration(); // retrieve setting

    // hide/show widgets
    this->ui->rpmLabel->setHidden(!dashboardConfiguration.at(0));
    this->ui->gearLabel->setHidden(!dashboardConfiguration.at(1));
    this->ui->speedLabel->setHidden(!dashboardConfiguration.at(2));
    this->ui->bpmIndicator->setHidden(!dashboardConfiguration.at(3));
    this->ui->timeTable->setHidden(!dashboardConfiguration.at(4));
    this->ui->mapLabel->setHidden(!dashboardConfiguration.at(4));

    // map
    QString circuitName = settings->getCircuitMap();
    if (circuitName == settings->CIRCUIT_ARAGON) {
        if (settings->hasLightTheme()) {
            this->map = QPixmap(":/circuit/aragon_black").scaled(QSize(141, 141), Qt::KeepAspectRatio);
        } else {
            this->map = QPixmap(":/circuit/aragon_white").scaled(QSize(141, 141), Qt::KeepAspectRatio);
        }
    } else if (circuitName == settings->CIRCUIT_LAGUNA_SECA) {
        if (settings->hasLightTheme()) {
            this->map = QPixmap(":/circuit/lagunaseca_black").scaled(QSize(141, 141), Qt::KeepAspectRatio);
        } else {
            this->map = QPixmap(":/circuit/lagunaseca_white").scaled(QSize(141, 141), Qt::KeepAspectRatio);
        }
    } else if (circuitName == settings->CIRCUIT_MUGELLO) {
        if (settings->hasLightTheme()) {
            this->map = QPixmap(":/circuit/mugello_black").scaled(QSize(141, 141), Qt::KeepAspectRatio);
        } else {
            this->map = QPixmap(":/circuit/mugello_white").scaled(QSize(141, 141), Qt::KeepAspectRatio);
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
