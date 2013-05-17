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
    ScheduleManager* manager;
    QDate day;

public:
    DayOfWeek(QDate day, ScheduleManager* manager, QWidget* parent = 0);

signals:

public slots:
    void paintEvent(QPaintEvent* event);
    QSize sizeHint() const;

};

class WeekWidget : public QWidget
{
    Q_OBJECT

private:
    ScheduleManager* manager;
    QHBoxLayout* layout;
    QVector<DayOfWeek*> dayOfWeekFrames;
    QVector<QFrame*> dayFrames;
    QDate firstDay;

public:
    WeekWidget(QDate firstDay, ScheduleManager* manager, QWidget* parent = 0);

signals:
    
public slots:
    void paintEvent(QPaintEvent* event);
    
};

#endif // WEEKWIDGET_HPP

