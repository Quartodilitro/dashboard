#include "chart.h"
#include "ui_chart.h"

Chart::Chart(QWidget *parent) : QWidget(parent), ui(new Ui::Chart)
{
    ui->setupUi(this);

    // labels
    QFont font = QApplication::font();
    font.setPointSize(15);
    font.setBold(true);
    ui->max_value->setFont(font);
    ui->avg_value->setFont(font);
    ui->min_value->setFont(font);

    // setup chart (axis, legend ...)
    ui->chart->addGraph();
    ui->chart->xAxis->setTickLabelType(QCPAxis::ltDateTime);
    ui->chart->xAxis->setDateTimeFormat("hh:mm:ss");
    ui->chart->xAxis->setAutoTickStep(false);
    ui->chart->xAxis->setTickStep(2);
    ui->chart->axisRect()->setupFullAxesBox();

    // make left and bottom axes transfer their ranges to right and top axes
    connect(ui->chart->xAxis, SIGNAL(rangeChanged(QCPRange)), ui->chart->xAxis2, SLOT(setRange(QCPRange)));
    connect(ui->chart->yAxis, SIGNAL(rangeChanged(QCPRange)), ui->chart->yAxis2, SLOT(setRange(QCPRange)));
}

Chart::~Chart()
{
    delete ui;
}

/**
 * @brief Chart::setTitle
 * @param title new value for chart title
 */
void Chart::setTitle(QString title) {
    ui->title->setText(title);
}

/**
 * @brief Chart::setPen
 * @param pen new pen of chart
 * @return set new pen as chart's default one
 */
void Chart::setPen(QPen pen) {
    ui->chart->graph(0)->setPen(pen);
}

/**
 * @brief Chart::setValue
 * @param value double new value
 * @return set current chart value to given one
 */
void Chart::setValue(double value) {
    double key = QDateTime::currentDateTime().toMSecsSinceEpoch() / 1000.0;  // seconds
    ui->chart->graph(0)->addData(key, value);
    ui->chart->graph(0)->removeDataBefore(key - 8);  // only 8 points in visible display
    ui->chart->graph(0)->rescaleValueAxis();

    // make key axis range scroll with the data (at a constant range size of 8):
    ui->chart->xAxis->setRange(key + 0.25, 8, Qt::AlignRight);
    ui->chart->replot();

    updateValues(value);
}

/**
 * @brief Chart::getValue
 * @return value corresponding to given field
 */
double Chart::getValue(int code) {
    if (code == 0) {
        return minValue;
    } else if (code == 1) {
        return avgValue;
    }  else if (code == 2) {
        return maxValue;
    } else {
        return  currentValue;
    }
}

/**
 * @brief Chart::updateValues
 * @return update values with current one
 */
void Chart::updateValues(double value) {
    currentValue = value;  // get new value
    minValue = currentValue < minValue ? currentValue : minValue;
    maxValue = currentValue > maxValue ? currentValue : maxValue;
    avgValue = numPastValues * avgValue + currentValue;
    numPastValues += 1;  // update counter on previous values
    avgValue /= numPastValues;

    ui->min_value->setText(QString::number(minValue, 'f', 1));
    ui->avg_value->setText(QString::number(avgValue, 'f', 1));
    ui->max_value->setText(QString::number(maxValue, 'f', 1));
}
