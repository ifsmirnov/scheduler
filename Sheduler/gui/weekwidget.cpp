#include "gui/weekwidget.hpp"

#include <cstdlib>

WeekWidget::WeekWidget(QDate firstDay, ScheduleManager* manager, QWidget* parent) :
    QWidget(parent), manager(manager), firstDay(firstDay)
{
    QDate day = firstDay;
    layout = new QHBoxLayout(this);
    for (int dayNumber = 0; dayNumber < 7; ++dayNumber, day = day.addDays(1))
    {
        QFrame* dayFrame;
        QVBoxLayout* frameLayout;
        QLabel* dateLabel;
        QFrame* separator;
        DayOfWeek* dayOfWeekFrame;
        QSizePolicy policy;

        dayFrame = new QFrame();
        dayFrame->setFrameStyle(QFrame::Box);
        if (day.dayOfWeek() >= 6)
        {
            dayFrame->setStyleSheet("QFrame { background-color: #c3a253; }");
        }
        else
        {
            dayFrame->setStyleSheet("QFrame { background-color: #efd334; }");
        }
        dayFrames.push_back(dayFrame);

        frameLayout = new QVBoxLayout(dayFrame);

        dateLabel = new QLabel(day.toString());
        dateLabel->setAlignment(Qt::AlignHCenter);

        policy = dateLabel->sizePolicy();
        policy.setVerticalStretch(0);
        dateLabel->setSizePolicy(policy);

        separator = new QFrame();
        separator->setFrameStyle(QFrame::HLine);

        dayOfWeekFrame = new DayOfWeek(day, manager);
        policy = dayOfWeekFrame->sizePolicy();
        policy.setVerticalStretch(1);
        dayOfWeekFrame->setSizePolicy(policy);
        dayOfWeekFrames.push_back(dayOfWeekFrame);

        frameLayout->addWidget(dateLabel);
        frameLayout->addWidget(separator);
        frameLayout->addWidget(dayOfWeekFrame);

        layout->addWidget(dayFrame);
    }

    setMinimumSize(400, 300);
}

void WeekWidget::paintEvent(QPaintEvent* event)
{
    std::cerr << "paintEvent " << rand() << std::endl;
    for (auto frame : dayFrames)
    {
        if (frame->underMouse())
        {
            frame->setFrameShadow(QFrame::Plain);
        }
        else
        {
            frame->setFrameShadow(QFrame::Raised);
        }
    }
}

DayOfWeek::DayOfWeek(QDate day, ScheduleManager* manager, QWidget* parent) :
    QWidget(parent), manager(manager)
{
    setMinimumWidth(100);
}

void DayOfWeek::paintEvent(QPaintEvent* event)
{
    QPainter painter(this);

    painter.setBrush(Qt::white);
    painter.setPen(Qt::black);

    int w = width() - 1;
    int h = height() - 1;

    painter.drawRect(0, 0, w, h);
    double secsInDay = 24 * 60 * 60;

    painter.setBrush(QBrush(QColor(180, 180, 180)));
    QVector<Event*> events = manager->getEvents(day);
    QVector<int> eventsYPositions;
    if (events.size() > 0)
    {
        for (int eventIndex = 0; eventIndex <= events.size(); ++eventIndex)
        {
            eventsYPositions.push_back((eventIndex * h) / events.size());
        }
    }

    for (int eventIndex = 0; eventIndex < events.size(); ++eventIndex)
    {
        int eventY = eventsYPositions[eventIndex];
        int eventHeight = eventsYPositions[eventIndex + 1] - eventY;

        painter.drawRect(0, eventY, w, eventHeight);
    }
}

QSize DayOfWeek::sizeHint() const
{
    return QSize(100, 240);
}
