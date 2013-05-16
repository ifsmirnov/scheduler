#include <gui/eventslist.hpp>

EventsList::EventsList(QDate firstDay, QDate lastDay, ScheduleManager* manager, QWidget* parent) :
    QWidget(parent), manager(manager), lastDay(lastDay), firstDay(firstDay)
{
    QVector< QVector<Event*> > events;

    for (QDate day = firstDay; day <= lastDay; day = day.addDays(1))
    {
        events.push_back(manager->getEvents(day));
    }

    setLayout(new QVBoxLayout(this));

    QLabel* dateLabel = new QLabel(firstDay.toString() + " - " + lastDay.toString());
    layout()->addWidget(dateLabel);

    QFrame* separator = new QFrame();
    separator->setFrameStyle(QFrame::HLine);
    layout()->addWidget(separator);

    QScrollArea* scrollArea = new QScrollArea();
    scrollArea->setLayout(new QVBoxLayout());
    layout()->addWidget(scrollArea);

    QLayout* layout = scrollArea->layout();
    QDate day = firstDay;
    for (int dayIndex = 0; day <= lastDay; dayIndex++, day = day.addDays(1))
    {
        if (events[dayIndex].size() == 0) continue;

        if (dayIndex > 0)
        {
            QFrame* separator = new QFrame();
            separator->setFrameStyle(QFrame::HLine);
            layout->addWidget(separator);
        }

        QLabel* dateLabel = new QLabel("Date: " + day.toString());
        dateLabel->setAlignment(Qt::AlignCenter);
        QSizePolicy policy = dateLabel->sizePolicy();
        policy.setHorizontalStretch(1);
        dateLabel->setSizePolicy(policy);
        layout->addWidget(dateLabel);

        QFrame* separator = new QFrame();
        separator->setFrameStyle(QFrame::HLine);
        layout->addWidget(separator);

        for (int eventIndex = 0; eventIndex < events[dayIndex].size(); ++eventIndex)
        {
            Event* event = events[dayIndex][eventIndex];
            QLabel* eventLabel = new QLabel(event->info() + " (" + event->begin().toString() + ")");
            eventLabel->setAlignment(Qt::AlignCenter);
            QSizePolicy policy = eventLabel->sizePolicy();
            policy.setVerticalStretch(1);
            eventLabel->setSizePolicy(policy);
            layout->addWidget(eventLabel);
        }
    }

/*
    for (int dayNumber = 0; dayNumber < 7; ++dayNumber, day = day.addDays(1))

    {
        QFrame* dayFrame;

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

    setMinimumSize(400, 300);*/
}
