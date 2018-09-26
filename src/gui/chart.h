#ifndef CHART_H
#define CHART_H

#include <limits>
#include <QWidget>


namespace Ui {
class Chart;
}

class Chart : public QWidget
{
    Q_OBJECT

public:
    explicit Chart(QWidget *parent = 0);
    ~Chart();

    int FIELDS_CODES_MIN = 0;  // possible values of set/get methods
    int FIELDS_CODES_AVG = 1;
    int FIELDS_CODES_MAX = 2;
    int FIELDS_CODES_NOW = 3;

    void setTitle(QString title);
    void setPen(QPen pen);

    void setValue(double value);
    double getValue(int code);

private:
    int numPastValues = 0;
    double currentValue;
    double maxValue = std::numeric_limits<double>::min();  // initialization
    double avgValue = 0.0;
    double minValue = std::numeric_limits<double>::max();

    Ui::Chart *ui;

    void updateValues(double value);
};

#endif // CHART_H
