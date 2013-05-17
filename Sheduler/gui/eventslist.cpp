#include <gui/eventslist.hpp>

EventsList::EventsList(QDate firstDay, QDate lastDay, ScheduleManager* manager, QWidget* parent) :
    QWidget(parent), manager(manager), firstDay(firstDay), lastDay(lastDay)
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
}
