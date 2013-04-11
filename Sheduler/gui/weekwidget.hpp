#ifndef WEEKWIDGET_HPP
#define WEEKWIDGET_HPP

#include <QObject>
#include <QWidget>
#include <QLabel>
#include <QDate>
#include <QTime>
#include <QPainter>
#include <QGridLayout>
#include <iostream>
#include <src/dailyschedule.hpp>
#include <src/event.hpp>
#include <gui/daywidget.hpp>

class DayOfWeek : public QWidget
{
    Q_OBJECT

private:
    DailyScheduleSPtr dailySchedule;

public:
    DayOfWeek(DailyScheduleSPtr dailySchedule, QWidget *parent = 0);

signals:

public slots:
    void paintEvent(QPaintEvent *);
    QSize sizeHint() const;

};

class WeekWidget : public QWidget
{
    Q_OBJECT

private:
    QVector<DailyScheduleSPtr> dailySchedules;
    QHBoxLayout* layout;
    QVector<DayOfWeek*> dayFrames;
    QVector<QFrame*> frames;
    QDate firstDay;

public:
    WeekWidget(QDate firstDay, QVector<DailyScheduleSPtr> dailySchedules, QWidget *parent = 0);

signals:
    
public slots:
    void paintEvent(QPaintEvent *);    
    
};

#endif // WEEKWIDGET_HPP

