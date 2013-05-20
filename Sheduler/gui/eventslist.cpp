#include <gui/eventslist.hpp>

ListWidget::ListWidget(QDate firstDay, QDate lastDay, ScheduleManager *manager, QWidget *parent) :
    QWidget(parent), manager(manager), firstDay(firstDay), lastDay(lastDay)
{
}


void ListWidget::paintEvent(QPaintEvent *) {
    int height = 1;
    for (QDate day = firstDay; day <= lastDay; day = day.addDays(1))
    {
        QVector <Event*> events = manager->getEvents(day);
        if (events.size()) {
            height += 20 * (events.size() + 1);
        }
    }
    resize(this->width(), height);

    QPainter painter (this);
    QRect textRect(rect().left(), rect().top(), rect().width() - 1, 19);

    for (QDate day = firstDay; day <= lastDay; day = day.addDays(1))
    {
        QVector <Event*> events = manager->getEvents(day);
        if (events.size()) {
            painter.setBrush(Qt::white);
            painter.setPen(Qt::black);
            painter.drawRect(textRect);
            painter.drawText(textRect, "  Date: " + day.toString());
            textRect.setTop(textRect.top() + 20);
            textRect.setHeight(19);
            for (auto event: events) {
                if (event->isRegular()) {
                    painter.setBrush(QColor(Qt::blue).lighter());
                } else {
                    painter.setBrush(event->color());
                }
                painter.drawRect(textRect);
                painter.drawText(textRect, Qt::AlignCenter, event->info() + " (" + event->begin().toString() + ")");
                textRect.setTop(textRect.top() + 20);
                textRect.setHeight(19);
            }
        }
    }
}

QSize ListWidget::sizeHint() const {
    return QSize(height() - 50, width() - 250);
}

EventsList::EventsList(QDate firstDay, QDate lastDay, ScheduleManager* manager, QWidget* parent) :
    QWidget(parent), manager(manager), firstDay(firstDay), lastDay(lastDay)
{


    QVBoxLayout* eventListLayout = new QVBoxLayout();

    QLabel* dateLabel = new QLabel(firstDay.toString() + " - " + lastDay.toString());
    eventListLayout->addWidget(dateLabel);

    QFrame* separator = new QFrame();
    separator->setFrameStyle(QFrame::HLine);
    eventListLayout->addWidget(separator);

    QScrollArea* scrollArea = new QScrollArea();
    list = new ListWidget(firstDay, lastDay, manager);
    //eventListLayout->addWidget(list);

    scrollArea->setWidget(list);
    eventListLayout->addWidget(scrollArea);


    setLayout(eventListLayout);
}

void ListWidget::setManager(ScheduleManager *value)
{
    manager = value;
}

void EventsList::setManager(ScheduleManager *value)
{
    manager = value;
    list->setManager(value);
}
