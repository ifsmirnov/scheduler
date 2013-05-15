#ifndef DAYWIDGET_HPP
#define DAYWIDGET_HPP

#include <QWidget>
#include <QVector>
#include <QLabel>
#include <QColor>
#include <QPushButton>
#include <QBoxLayout>
#include <QDate>
#include <QFrame>
#include <QToolTip>
#include <QCheckBox>
#include <QMouseEvent>

#include "src/managers/schedulemanager.hpp"
#include "src/event.hpp"
#include "gui/addeventdialog.hpp"


/**
 * @brief The DayScheduleWidget class
 *
 * This is a subwidget of DayWidget class
 * paints the rectangle scheme of the events during the day.
 *
 * @
 */
class DayScheduleWidget : public QWidget
{
    Q_OBJECT

public:
    explicit DayScheduleWidget(ScheduleManager *manager,
                               QDate date_,
                               QCheckBox* showRegular,
                               QCheckBox* showIrregular,
                               QWidget *parent = 0);

public slots:
    void paintEvent(QPaintEvent *);
    void stateChanged();
    void mouseMoveEvent(QMouseEvent *);

private:
    ScheduleManager *manager_;
    QDate date_;
    QCheckBox* showRegular_;
    QCheckBox* showIrregular_;
    QVector<Event*> regularEvents_;
    QVector<Event*> irregularEvents_;

    QRect getEventRect(Event*) const;
};


/**
 * @brief The DayWidget class
 *
 * This class handles a Day* pointer and displays the contents of pointed
 * object on the screen. Regular events are drawed as green rectangles,
 * and irregular are a bit smaller red ones.
 *
 * @
 */
class DayWidget : public QWidget
{
    Q_OBJECT
public:
    explicit DayWidget(ScheduleManager *manager, QDate date, QWidget *parent = 0);

public:

public slots:
    void paintEvent(QPaintEvent *);
    QSize sizeHint() const;

signals:
    void addRegularEvent(QDate date, Event *event);
    void addWeeklyEvent(int dayOfWeek, Event *event);

private:
    ScheduleManager *manager_;
    DayScheduleWidget* DayScheduleWidget_;

private slots:
    void addEvent();
};




#endif // DAYWIDGET_HPP
