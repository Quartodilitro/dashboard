#include <QPainter>

#include "geotimewindow.h"
#include "ui_geotimewindow.h"

GeoTimeWindow::GeoTimeWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::GeoTimeWindow)
{
    ui->setupUi(this);  // setup  and title
    QFont font = QApplication::font();
    font.setPointSize(12);
    font.setItalic(true);
    ui->title->setFont(font);
    ui->title->setAlignment(Qt::AlignCenter);
    ui->timeTable->setFrameStyle(QFrame::NoFrame);

    settings = new Settings(QCoreApplication::organizationName(), QCoreApplication::applicationName());  // create settings manager
    connectionBridge = new ConnectionBridge();

    ui->leftTabButton->setIcon(QPixmap(":/image/left_black").scaled(QSize(120, 120), Qt::KeepAspectRatio));  // navigation buttons
    QObject::connect(this->ui->leftTabButton, SIGNAL(clicked()), this->parent(), SLOT(changeTabLeft()));
    ui->rightTabButton->setIcon(QPixmap(":/image/right_black").scaled(QSize(120, 120), Qt::KeepAspectRatio));
    QObject::connect(this->ui->rightTabButton, SIGNAL(clicked()), this->parent(), SLOT(changeTabRight()));
}

GeoTimeWindow::~GeoTimeWindow()
{
    delete ui;
}

void GeoTimeWindow::setValue(double value, int code) {
    if (code == connectionBridge->DATA_CODE_TIME_S_1S) {
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

void GeoTimeWindow::updateGPSMap() {
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



void GeoTimeWindow::updateSettings() {
    // circuit map
    QString circuitName = settings->getCircuitMap();
    if (circuitName == settings->CIRCUIT_ARAGON) {
        if (settings->hasLightTheme()) {
            this->map = QPixmap(":/circuit/aragon_black").scaled(QSize(261, 261), Qt::KeepAspectRatio);
        } else {
            this->map = QPixmap(":/circuit/aragon_white").scaled(QSize(261, 261), Qt::KeepAspectRatio);
        }
    } else if (circuitName == settings->CIRCUIT_LAGUNA_SECA) {
        if (settings->hasLightTheme()) {
            this->map = QPixmap(":/circuit/lagunaseca_black").scaled(QSize(261, 261), Qt::KeepAspectRatio);
        } else {
            this->map = QPixmap(":/circuit/lagunaseca_white").scaled(QSize(261, 261), Qt::KeepAspectRatio);
        }
    } else if (circuitName == settings->CIRCUIT_MUGELLO) {
        if (settings->hasLightTheme()) {
            this->map = QPixmap(":/circuit/mugello_black").scaled(QSize(261, 261), Qt::KeepAspectRatio);
        } else {
            this->map = QPixmap(":/circuit/mugello_white").scaled(QSize(261, 261), Qt::KeepAspectRatio);
        }
    }
    this->ui->mapLabel->setPixmap(map);

    // theme
    if (settings->hasLightTheme()) {
       this->ui->leftTabButton->setIcon(QPixmap(":/image/left_black").scaled(QSize(120, 120), Qt::KeepAspectRatio));
       this->ui->rightTabButton->setIcon(QPixmap(":/image/right_black").scaled(QSize(120, 120), Qt::KeepAspectRatio));
    } else {
        this->ui->leftTabButton->setIcon(QPixmap(":/image/left_white").scaled(QSize(120, 120), Qt::KeepAspectRatio));
        this->ui->rightTabButton->setIcon(QPixmap(":/image/right_white").scaled(QSize(120, 120), Qt::KeepAspectRatio));
    }
}
