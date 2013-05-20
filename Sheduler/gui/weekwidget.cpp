#include "gui/weekwidget.hpp"

#include <cstdlib>

WeekWidget::WeekWidget(QDate firstDay, ScheduleManager* manager, QWidget* parent) :
    QWidget(parent), manager(manager), firstDay(firstDay)
{
    QDate day = firstDay;
    layout = new QHBoxLayout(this);
    for (int dayNumber = 0; dayNumber < 7; ++dayNumber, day = day.addDays(1))
    {

        QFrame* dayFrame = new QFrame();
        dayFrame->setFrameStyle(QFrame::Box);
        if (day.dayOfWeek() >= 6)
        {
            dayFrame->setStyleSheet("QFrame { background-color: #c3a253; padding: 1; }");
        }
        else
        {
            dayFrame->setStyleSheet("QFrame { background-color: #efd334; padding: 1; }");
            //dayFrame->layout()->addWidget(dayFrame);
        }
        dayFrame->setMinimumWidth(150);
        dayFrames.push_back(dayFrame);

        QVBoxLayout* frameLayout = new QVBoxLayout();

        QLabel* dateLabel = new QLabel(day.toString());
        dateLabel->setAlignment(Qt::AlignHCenter);

        /*QSizePolicy policy = dateLabel->sizePolicy();
        policy.setVerticalStretch(0);
        dateLabel->setSizePolicy(policy);*/

        //separator = new QFrame();
        //separator->setFrameStyle(QFrame::HLine);

        DayOfWeek* dayOfWeekFrame = new DayOfWeek(day, manager);
        //policy = dayOfWeekFrame->sizePolicy();
        //dayFrame->layout()->addWidget(dayFrame);
        //policy.setVerticalStretch(1);
        //policy.setHorizontalStretch(1);
        //dayOfWeekFrame->setSizePolicy(policy);
        dayOfWeekFrame->setParentWW(this);
        dayOfWeekFrames.push_back(dayOfWeekFrame);

        QScrollArea* dayOfWeekArea = new QScrollArea();
        dayOfWeekArea->setWidget(dayOfWeekFrame);
        dayOfWeekArea->resize(dayOfWeekFrame->size());

        frameLayout->addWidget(dateLabel);
        //frameLayout->addWidget(separator);
        frameLayout->addWidget(dayOfWeekArea);

        dayFrame->setLayout(frameLayout);
        layout->addWidget(dayFrame);
    }

    setMinimumSize(400, 300);
}

void WeekWidget::paintEvent(QPaintEvent*)
{
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

void WeekWidget::closeEvent(QCloseEvent *event)
{
    emit closed();
    QWidget::closeEvent(event);
}

void WeekWidget::callAddEventDialog(int dayOfWeek)
{
    AddEventDialog* addEventDialog = new AddEventDialog(QDate(), dayOfWeek, this);
    connect(addEventDialog, SIGNAL(addWeeklyEvent(int, Event*)), this, SIGNAL(addWeeklyWidget(int,Event*)));
    addEventDialog->show();
}

DayOfWeek::DayOfWeek(QDate day, ScheduleManager* manager, QWidget* parent) :
    QFrame(parent), manager(manager), day(day)
{
    /*setStyleSheet("QFrame { background-color: #ffffff; padding: 1; margin: 1; }");
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
    }*/

}

void DayOfWeek::paintEvent(QPaintEvent *) {
    QPainter painter(this);
    int height;
    QRect eventRect;
    QVector<Event*> events = manager->getEvents(day);
    if (events.size() == 0) {
        height = 50;
        resize(width(), height);
        painter.setPen(Qt::black);
        painter.setBrush(Qt::white);
        eventRect = QRect(0, 0, width() - 1, 49);
        painter.drawRect(eventRect);
        painter.drawText(eventRect, "No events");
    } else {
        height = 50 * events.size();
        resize(width(), height);
        painter.setPen(Qt::black);
        eventRect = QRect(0, 0, width() - 1, 49);
        for (auto event: events) {
            if (event->isRegular()) {
                painter.setBrush(QColor(Qt::blue).lighter());
            } else {
                painter.setBrush(event->color());
            }
            painter.drawRect(eventRect);
            painter.drawText(eventRect, event->info() + " (" + event->begin().toString() + ")");
            eventRect.setTop(eventRect.top() + 50);
            eventRect.setHeight(49);
        }
    }
}

void DayOfWeek::setParentWW(QWidget* parentWidget) {
    parentWW = parentWidget;
}

void DayOfWeek::mousePressEvent(QMouseEvent* )
{
    WeekWidget* parent = dynamic_cast<WeekWidget*>(parentWW);
    parent->callAddEventDialog(day.dayOfWeek() - 1);
}

QSize DayOfWeek::sizeHint() const
{
    //return QWidget::sizeHint();
    return QSize(100, 240);
}
