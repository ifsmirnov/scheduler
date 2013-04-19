#include "daywidget.hpp"

#include <QPainter>
#include <iostream>


DayScheduleWidget::DayScheduleWidget(DailyScheduleSPtr &day, QWidget *parent) :
    QWidget(parent), day_(day) {
}

void DayScheduleWidget::paintEvent(QPaintEvent *) {
    QPainter painter(this);

    int coeff = 60 * 60 * 24;

    QVector<Event*> events = day()->events();

    for (int hour = 0; hour < 24; hour++) {
        int begin = (double)(QTime(0, 0).secsTo(QTime(hour, 0))) / coeff * height();
        int len = (double)(60*60) / coeff * height();
        if (begin % 2 == 1) {
            begin--;
            len++;
        }
        if (len % 2 == 1  &&  hour != 23) {
            len++;
        }
        QRect hourRect(rect().left(), begin, rect().width()-1, len);
        painter.setPen(Qt::black);
        painter.setBrush(Qt::white);
        painter.drawRect(hourRect);
    }

    for (auto event: events) {
        int begin = (double)(QTime(0, 0).secsTo(event->begin())) / coeff * height();
        int len = (double)event->duration() / coeff * height();
        //std::cout << height() << ' ' << len << std::endl;
        QRect eventRect(rect().left(), begin, rect().width()-1, len);
        if (event->isRegular()) {
            painter.setBrush(QColor(Qt::blue).lighter(150));
        } else {
            painter.setBrush(QColor(Qt::red).lighter(150));
        }
        //std::cerr << event->duration() << std::endl;
        painter.drawRect(eventRect);
    }
}

DailyScheduleSPtr DayScheduleWidget::day() {
    return day_;
}



DayWidget::DayWidget(DailyScheduleSPtr day, QDate date, QWidget *parent) :
    QWidget(parent), day_(day)
{
    setWindowTitle(date.toString());
    //entire window
    setWindowTitle(date.toString());
    QBoxLayout* dayWidgetLayout = new QBoxLayout(QBoxLayout::TopToBottom, this);
    QLabel* title = new QLabel(date.toString());
    title->setAlignment(Qt::AlignCenter);
    title->setFont(QFont("Courier", 15));

    //labels + events
    QFrame* timeLineFrame = new QFrame();
    QBoxLayout* timeLineLayout = new QBoxLayout(QBoxLayout::LeftToRight);
    QPalette pal = timeLineFrame->palette();

    timeLineFrame->setFrameStyle(QFrame::Box | QFrame::Sunken);
    timeLineFrame->setLayout(timeLineLayout);
    //pal.setColor( backgroundRole(), );

    //buttons at the bottom of window
    QBoxLayout* menuLineLayout = new QBoxLayout(QBoxLayout::RightToLeft);

    dayWidgetLayout->addWidget(title);
    dayWidgetLayout->addWidget(timeLineFrame);
    dayWidgetLayout->addLayout(menuLineLayout);

    //bottom menu
    QPushButton* exitButton = new QPushButton(QString("Exit"));
    QPushButton* addEventButton = new QPushButton(QString("Add Event"));

    menuLineLayout->addWidget(exitButton);
    menuLineLayout->addWidget(addEventButton);
    exitButton->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
    addEventButton->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);

    connect(addEventButton, SIGNAL(clicked()), this, SLOT(addEvent()));
    connect(exitButton, SIGNAL(clicked()), this, SLOT(close()));

    //timeLine
    QBoxLayout* hoursLabelsLayout = new QBoxLayout(QBoxLayout::TopToBottom);
    DayScheduleWidget_ = new DayScheduleWidget(day_, this);
    //DayScheduleWidget_->setSizePolicy(QSizePolicy::Minimum, QSizePolicy::Minimum);

    timeLineLayout->addLayout(hoursLabelsLayout);
    timeLineLayout->addWidget(DayScheduleWidget_, 1);

    for (int hour = 0; hour < 24; hour++) {
        hoursLabelsLayout->addWidget(new QLabel(QTime(hour, 0).toString("hh:mm")), 1);
    }
    setLayout(dayWidgetLayout);
}

void DayWidget::paintEvent(QPaintEvent *) {
}

DailyScheduleSPtr DayWidget::day() {
    return day_;
}

QSize DayWidget::sizeHint() const {
    return QSize(240, 600);
}

void DayWidget::addEvent() {
    AddEventDialog* eventDialog = new AddEventDialog(day_, this);
    eventDialog->show();
    update();
}

