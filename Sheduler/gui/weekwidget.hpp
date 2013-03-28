#ifndef WEEKWIDGET_HPP
#define WEEKWIDGET_HPP

#include <QWidget>

class WeekWidget : public QWidget
{
    Q_OBJECT

private:
    std::vector<DayWidget*> dayWidgets;

public:
    WeekWidget(std::vector<DayWidget*> dayWidgets, QWidget *parent = 0);

signals:
    
public slots:
    void paintEvent(QPaintEvent *);
//    QSize sizeHint() const;
    
};

#endif // WEEKWIDGET_HPP
