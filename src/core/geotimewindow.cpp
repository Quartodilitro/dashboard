#include "geotimewindow.h"
#include "ui_geotimewindow.h"

GeoTimeWindow::GeoTimeWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::GeoTimeWindow)
{
    ui->setupUi(this);  // setup  and title
    QFont font = QApplication::font();
    font.setPointSize(15);
    font.setItalic(true);
    ui->title->setFont(font);
    ui->title->setAlignment(Qt::AlignCenter);

    settings = new Settings(QCoreApplication::organizationName(), QCoreApplication::applicationName());  // create settings manager

    ui->leftTabButton->setIcon(QPixmap(":/image/left_black").scaled(QSize(120, 120), Qt::KeepAspectRatio));  // navigation buttons
    QObject::connect(this->ui->leftTabButton, SIGNAL(clicked()), this->parent(), SLOT(changeTabLeft()));
    ui->rightTabButton->setIcon(QPixmap(":/image/right_black").scaled(QSize(120, 120), Qt::KeepAspectRatio));
    QObject::connect(this->ui->rightTabButton, SIGNAL(clicked()), this->parent(), SLOT(changeTabRight()));
}

GeoTimeWindow::~GeoTimeWindow()
{
    delete ui;
}

void GeoTimeWindow::updateSettings() {
    // theme
    if (settings->hasLightTheme()) {
       this->ui->leftTabButton->setIcon(QPixmap(":/image/left_black").scaled(QSize(120, 120), Qt::KeepAspectRatio));
       this->ui->rightTabButton->setIcon(QPixmap(":/image/right_black").scaled(QSize(120, 120), Qt::KeepAspectRatio));
    } else {
        this->ui->leftTabButton->setIcon(QPixmap(":/image/left_white").scaled(QSize(120, 120), Qt::KeepAspectRatio));
        this->ui->rightTabButton->setIcon(QPixmap(":/image/right_white").scaled(QSize(120, 120), Qt::KeepAspectRatio));
    }


    // circuit map
    QString circuitName = settings->getCircuitMap();
    QPixmap map;
    if (circuitName == settings->CIRCUIT_ARAGON) {
        if (settings->hasLightTheme()) {
            map = QPixmap(":/circuit/aragon_black").scaled(QSize(261, 261), Qt::KeepAspectRatio);
        } else {
            map = QPixmap(":/circuit/aragon_white").scaled(QSize(261, 261), Qt::KeepAspectRatio);
        }
    } else if (circuitName == settings->CIRCUIT_LAGUNA_SECA) {
        if (settings->hasLightTheme()) {
            map = QPixmap(":/circuit/lagunaseca_black").scaled(QSize(261, 261), Qt::KeepAspectRatio);
        } else {
            map = QPixmap(":/circuit/lagunaseca_white").scaled(QSize(261, 261), Qt::KeepAspectRatio);
        }
    } else if (circuitName == settings->CIRCUIT_MUGELLO) {
        if (settings->hasLightTheme()) {
            map = QPixmap(":/circuit/mugello_black").scaled(QSize(261, 261), Qt::KeepAspectRatio);
        } else {
            map = QPixmap(":/circuit/mugello_white").scaled(QSize(261, 261), Qt::KeepAspectRatio);
        }
    }
    this->ui->mapLabel->setPixmap(map);
}
