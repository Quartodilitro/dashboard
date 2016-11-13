#include "indicatorlabel.h"
#include "ui_indicatorlabel.h"


IndicatorLabel::IndicatorLabel(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::IndicatorLabel)
{
    ui->setupUi(this);

    QFont font = QApplication::font();
    font.setPointSize(12);
    font.setBold(true);
    ui->value->setFont(font);
}

IndicatorLabel::~IndicatorLabel()
{
    delete ui;
}

/**
 * @brief IndicatorLabel::setTitle
 * @param title new title for label
 * @return set current title to given one
 */
void IndicatorLabel::setTitle(QString title) {
    ui->label->setText(title);
}

/**
 * @brief IndicatorLabel::setValue
 * @param value double new value
 * @return set current chart value to given one
 */
void IndicatorLabel::setValue(double value) {
    ui->value->setText(QString::number(value));
}

/**
 * @brief IndicatorLabel::getValue get current value of chart
 * @return double current value of chart
 */
double IndicatorLabel::getValue() {
    return currentValue;
}

