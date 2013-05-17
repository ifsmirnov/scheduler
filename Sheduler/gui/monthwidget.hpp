#ifndef MONTHWIDGET_HPP
#define MONTHWIDGET_HPP

#include <QWidget>
#include <QVector>
#include <QDate>

#include "src/managers/schedulemanager.hpp"

class DayOfMonth : public QWidget
{
    Q_OBJECT
public:
    explicit DayOfMonth(ScheduleManager *manager, QDate date, QWidget *parent = 0);
    DayOfMonth(const DayOfMonth& dayOfMonth);
    DayOfMonth operator=(const DayOfMonth& dayOfMonth);

public slots:
    void paintEvent(QPaintEvent *);

private:
    ScheduleManager *manager;
    QDate date;
};

class MonthWidget : public QWidget
{
    Q_OBJECT
public:
    explicit MonthWidget(ScheduleManager *manager,
                         QDate date,
                         QWidget *parent = 0);
    ~MonthWidget();
    
signals:
    
public slots:
    void setHighlight(QDate date);
    void noHighlight();

public:

private:
    int curYear, curMonth, curDay;
    ScheduleManager *manager;
    
    QVector<DayOfMonth*> days;
};

#endif // MONTHWIDGET_HPP
