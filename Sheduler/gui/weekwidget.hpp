#ifndef WEEKWIDGET_HPP
#define WEEKWIDGET_HPP

#include <QObject>
#include <QWidget>
#include <QLabel>
#include <QDate>
#include <QGridLayout>
#include <src/dailyschedule.hpp>
#include <gui/daywidget.hpp>

class WeekWidget : public QWidget
{
    Q_OBJECT

private:
    QVector<DailyScheduleSPtr> dailySchedules;
    QHBoxLayout* layout;
    QVector<QLabel*> dateLabels;
    QVector<DayWidget*> dayWidgets;
    QDate firstDay;

public:
    WeekWidget(QDate firstDay, QVector<DailyScheduleSPtr> dailySchedules, QWidget *parent = 0);

signals:
    
public slots:
    void paintEvent(QPaintEvent *);
    
};

#endif // WEEKWIDGET_HPP

