#include "gui/weekwidget.hpp"

WeekWidget::WeekWidget(QDate firstDay, QVector<DailyScheduleSPtr> dailySchedules, QWidget *parent) :
    QWidget(parent), dailySchedules(dailySchedules), firstDay(firstDay)
{
    layout = new QHBoxLayout(this);
    for (int index = 0; index < dailySchedules.size(); ++index)
    {
        QFrame* frame = new QFrame();
        QVBoxLayout* frameLayout = new QVBoxLayout(frame);
        frame->setFrameStyle(QFrame::Box);

        QLabel* label = new QLabel("Date");
        dateLabels.push_back(label);

        layout->addWidget(frame);
        frameLayout->addWidget(label);
        QFrame* separator = new QFrame();
        separator->setFrameStyle(QFrame::HLine);
        frameLayout->addWidget(separator);
        frameLayout->addWidget(new QLabel("Day widget"));
    }

    setMinimumSize(400, 300);
}

void WeekWidget::paintEvent(QPaintEvent *)
{

}
