#ifndef MONTHWIDGET_HPP
#define MONTHWIDGET_HPP

#include <QWidget>
#include <QVector>
#include <QAction>
#include <QDate>

#include "src/managers/schedulemanager.hpp"

class DayOfMonth : public QWidget
{
    Q_OBJECT
public:
    explicit DayOfMonth(ScheduleManager *manager, QDate date, QWidget *parent = 0);
    DayOfMonth(const DayOfMonth& dayOfMonth);
    DayOfMonth operator=(const DayOfMonth& dayOfMonth);

    bool getCovered() const;
    void setCovered(bool value);

    bool getHighlited() const;
    void setHighlited(bool value);

    void setDate(QDate date_);

    void setManager(ScheduleManager *manager_);

public slots:
    void paintEvent(QPaintEvent *);
    void mousePressEvent(QMouseEvent *);
    void mouseMoveEvent(QMouseEvent *);

signals:
    void dayPressed(int);
    void dayCovered(int);

private:
    ScheduleManager *manager;
    QDate date;
    bool covered;
    bool highlited;
};

class MonthWidget : public QWidget
{
    Q_OBJECT
public:
    explicit MonthWidget(ScheduleManager *manager,
                         QDate date,
                         QWidget *parent = 0);
    ~MonthWidget();
    
public slots:
    void setHighlight(QDate date);
    void noHighlight();

    void mouseMoveEvent(QMouseEvent *);

    void dayPressed(int day);
    void dayCovered(int day);

public:
    bool hasHighlight() const;
    void setManager(ScheduleManager *manager_);

signals:
    void dayPressedSignal(QDate date);
    void monthChanged(QDate date);
    void monthChanged();

private:
    void setMonth(QDate date);
    void initActions();

private slots:
    void nextMonth();
    void prevMonth();

private:
    int curYear, curMonth, curDay;
    int coveredDay;
    ScheduleManager *manager;
    
    QVector<DayOfMonth*> days;

    QAction *nextMonthAction;
    QAction *prevMonthAction;
};

#endif // MONTHWIDGET_HPP
