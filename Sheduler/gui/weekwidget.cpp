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
            dayFrame->setStyleSheet("QFrame { background-color: #c3a253; padding: 1; }");
        }
        else
        {
            dayFrame->setStyleSheet("QFrame { background-color: #efd334; padding: 1; }");
        }
        dayFrame->setMinimumWidth(150);
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
        policy.setHorizontalStretch(1);
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
    QFrame(parent), manager(manager), day(day)
{
    setStyleSheet("QFrame { background-color: #ffffff; padding: 1; margin: 1; }");
    setFrameStyle(QFrame::Plain);

    setLayout(new QVBoxLayout(this));

    if (manager->getEvents(day).size() == 0)
    {
        QLabel* noEventLabel = new QLabel("No events");
        noEventLabel->setAlignment(Qt::AlignCenter);
        QSizePolicy policy = noEventLabel->sizePolicy();
        policy.setVerticalStretch(1);
        policy.setHorizontalStretch(1);
        noEventLabel->setSizePolicy(policy);
        layout()->addWidget(noEventLabel);
    }
    else
    {
        QVector<Event*> events = manager->getEvents(day);
        for (int eventIndex = 0; eventIndex < events.size(); ++eventIndex)
        {
            Event* event = events[eventIndex];
            QLabel* eventLabel = new QLabel(event->info() + " (" + event->begin().toString() + ")");// + " - " + event->end().toString() + ")"
            eventLabel->setAlignment(Qt::AlignCenter);
            QSizePolicy policy = eventLabel->sizePolicy();
            policy.setVerticalStretch(1);
            policy.setHorizontalStretch(1);
            eventLabel->setSizePolicy(policy);
            layout()->addWidget(eventLabel);

            if (eventIndex + 1 < events.size())
            {
                QFrame* separator = new QFrame();
                separator->setFrameStyle(QFrame::HLine);
                layout()->addWidget(separator);
            }
        }
    }
}

void DayOfWeek::paintEvent(QPaintEvent* event)
{
}

QSize DayOfWeek::sizeHint() const
{
    return QWidget::sizeHint();
    //return QSize(100, 240);
}
