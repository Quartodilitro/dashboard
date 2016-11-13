#ifndef INDICATORLABEL_H
#define INDICATORLABEL_H

#include <QWidget>

namespace Ui {
class IndicatorLabel;
}

class IndicatorLabel : public QWidget
{
    Q_OBJECT

public:
    explicit IndicatorLabel(QWidget *parent = 0);
    ~IndicatorLabel();

    void setTitle(QString title);

    void setValue(double value);
    double getValue();

private:
    double currentValue = 0.0;

    Ui::IndicatorLabel *ui;
};

#endif // INDICATORLABEL_H
