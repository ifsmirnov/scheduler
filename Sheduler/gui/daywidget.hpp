#ifndef DAYWIDGET_HPP
#define DAYWIDGET_HPP

#include <QWidget>
#include <QVector>
#include <QLabel>
#include <QColor>
#include <QPushButton>
#include <QBoxLayout>

#include "src/day.hpp"
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
    explicit DayScheduleWidget(Day* day, QWidget *parent = 0);

public:
    Day* day();

public slots:
    void paintEvent(QPaintEvent *);

private:
    Day *const day_;
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
    explicit DayWidget(Day* day, QWidget *parent = 0);

public:
    Day* day();

public slots:
    void paintEvent(QPaintEvent *);
    QSize sizeHint() const;

private:
    Day *const day_; // pointer is constant, the value is not
    /* I don't know if we may want to change the pointed value
     * while it is displayed. If we want, the signal-slot
     * mapping should be implemented, Day should be Q_OBJECT
     * etc. I haven't decided if we want it yet. */
    DayScheduleWidget* DayScheduleWidget_;

private slots:
    void addEvent();
};




#endif // DAYWIDGET_HPP
