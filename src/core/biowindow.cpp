#include <stdexcept>
#include <QPen>

#include "biowindow.h"


BioWindow::BioWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::BioWindow)
{
    ui->setupUi(this);  // setup and title
    QFont font = QApplication::font();
    font.setPointSize(12);
    font.setItalic(true);
    ui->title->setFont(font);
    ui->title->setAlignment(Qt::AlignCenter);

    connectionBridge = new ConnectionBridge();
    settings = new Settings(QCoreApplication::organizationName(), QCoreApplication::applicationName());  // create settings manager

    ui->chart_0->setTitle(QString::fromUtf8("Oxygen level (O2)"));  // labels and charts
    ui->chart_0->setPen(QPen(Qt::blue));
    ui->chart_1->setTitle(QString::fromUtf8("Heart beat (BPM)"));
    ui->chart_1->setPen(QPen(Qt::red));

    ui->indicator_0->setTitle(QString::fromUtf8("Body temp."));
    ui->indicator_1->setTitle(QString::fromUtf8("BPM"));
    ui->indicator_2->setTitle(QString::fromUtf8("Oxygen"));

    QObject::connect(this->ui->leftTabButton, SIGNAL(clicked()), this->parent(), SLOT(changeTabLeft()));  // navigation button
    QObject::connect(this->ui->rightTabButton, SIGNAL(clicked()), this->parent(), SLOT(changeTabRight()));
}

BioWindow::~BioWindow()
{
    delete ui;
}

/**
 * @brief BioWindow::setValue
 * @param value new value to set
 * @param code which label to set value of
 */
void BioWindow::setValue(int value, int code) {
    if (code == connectionBridge->DATA_CODE_TEMPERATURE_BODY) {
        ui->indicator_0->setValue(value);
    } else if (code == connectionBridge->DATA_CODE_BPM) {
        ui->indicator_1->setValue(value);
        ui->chart_1->setValue(value);
    } else if (code == connectionBridge->DATA_CODE_O2) {
        ui->indicator_2->setValue(value);
        ui->chart_0->setValue(value);
    }
}

void BioWindow::updateSettings() {
    // theme
    if (settings->hasLightTheme()) {
       this->ui->leftTabButton->setIcon(QPixmap(":/image/left_black").scaled(QSize(120, 120), Qt::KeepAspectRatio));
       this->ui->rightTabButton->setIcon(QPixmap(":/image/right_black").scaled(QSize(120, 120), Qt::KeepAspectRatio));
    } else {
        this->ui->leftTabButton->setIcon(QPixmap(":/image/left_white").scaled(QSize(120, 120), Qt::KeepAspectRatio));
        this->ui->rightTabButton->setIcon(QPixmap(":/image/right_white").scaled(QSize(120, 120), Qt::KeepAspectRatio));
    }
}
