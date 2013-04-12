#include "gui/weekwidget.hpp"

#include <cstdlib>

WeekWidget::WeekWidget(QDate firstDay, QVector<DailyScheduleSPtr> dailySchedules, QWidget *parent) :
    QWidget(parent), dailySchedules(dailySchedules), firstDay(firstDay)
{
    QDate day = firstDay;
    layout = new QHBoxLayout(this);
    for (int index = 0; index < dailySchedules.size(); ++index, day = day.addDays(1))
    {
        QFrame* frame;
        QVBoxLayout* frameLayout;
        QLabel* dateLabel;
        QFrame* separator;
        DayOfWeek* dayFrame;
        QSizePolicy policy;

        frame = new QFrame();
        frame->setFrameStyle(QFrame::Box);
        if (day.dayOfWeek() >= 6)
        {
            frame->setStyleSheet("QFrame { background-color: #c3a253; }");
        }
        else
        {
            frame->setStyleSheet("QFrame { background-color: #efd334; }");
        }
        frames.push_back(frame);

        frameLayout = new QVBoxLayout(frame);

        dateLabel = new QLabel(day.toString());
        dateLabel->setAlignment(Qt::AlignHCenter);

        policy = dateLabel->sizePolicy();
        policy.setVerticalStretch(0);
        dateLabel->setSizePolicy(policy);

        separator = new QFrame();
        separator->setFrameStyle(QFrame::HLine);

        dayFrame = new DayOfWeek(dailySchedules[index]);
        policy = dayFrame->sizePolicy();
        policy.setVerticalStretch(1);
        dayFrame->setSizePolicy(policy);
        dayFrames.push_back(dayFrame);

        frameLayout->addWidget(dateLabel);
        frameLayout->addWidget(separator);
        frameLayout->addWidget(dayFrame);

        layout->addWidget(frame);
    }

    setMinimumSize(400, 300);
}

void WeekWidget::paintEvent(QPaintEvent* event)
{
    std::cerr << "paintEvent " << rand() << std::endl;
    for (auto frame : frames)
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

DayOfWeek::DayOfWeek(DailyScheduleSPtr dailySchedule, QWidget *parent) :
    QWidget(parent), dailySchedule(dailySchedule)
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
    QVector<Event*> events = dailySchedule->events();
    for (int i = 0; i < events.size(); ++i)
    {
        double begin = QTime(0, 0).secsTo(events[i]->begin()) / secsInDay;
        double end = QTime(0, 0).secsTo(events[i]->end()) / secsInDay;

        int eventX = begin * h;
        int eventHeight = end * h - eventX;

        painter.drawRect(0, eventX, w, eventHeight);
    }
}

QSize DayOfWeek::sizeHint() const
{
    return QSize(100, 240);
}
