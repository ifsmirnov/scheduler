#include "daywidget.hpp"

#include <QPainter>
#include <iostream>


DayScheduleWidget::DayScheduleWidget(ScheduleManager *manager,
                                     QDate date,
                                     QCheckBox* showRegular,
                                     QCheckBox* showIrregular,
                                     QWidget *parent) :
    QWidget(parent), manager_(manager), date_(date), showRegular_(showRegular), showIrregular_(showIrregular) {
    connect(showRegular_, SIGNAL(stateChanged(int)), this, SLOT(stateChanged()));
    connect(showIrregular_, SIGNAL(stateChanged(int)), this, SLOT(stateChanged()));
    setMouseTracking(true);
}

void DayScheduleWidget::stateChanged() {
    repaint();
}

QRect DayScheduleWidget::getEventRect(Event *event) const {
    int coeff = 60 * 60 * 24;
    int begin = (double)(QTime(0, 0).secsTo(event->begin())) / coeff * height();
    int len = (double)event->duration() / coeff * height();
    return QRect(rect().left(), begin, rect().width()-1, len);
}

void DayScheduleWidget::paintEvent(QPaintEvent *) {
    QPainter painter(this);

    int letterHeight = 16;
    int letterWidth = 10;
    int coeff = 60 * 60 * 24;

    QVector<Event*> events = manager_->getEvents(date_);
    //QRect timeRect(rect().left(), 0, rect().width() - 1, height() - 1);
    //painter.setPen(Qt::black);
    //painter.setBrush(Qt::white);
    //painter.drawRect(timeRect);
    //for (int hour = 1; hour < 24; hour++) {
        //int h = (double)(QTime(0, 0).secsTo(QTime(hour, 0))) / coeff * height();
        //painter.drawLine(QPoint(rect().left(), h), QPoint(rect().width() - 1, h));

    regularEvents_.clear();
    irregularEvents_.clear();

    for (auto event: events) {
        if (event->isRegular()) {
            regularEvents_.push_back(event);
        } else {
            irregularEvents_.push_back(event);
        }
    }

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

    if (showRegular_->isChecked()) {
        painter.setBrush(QColor(Qt::blue).lighter(150));
        for (auto event: regularEvents_) {
            //std::cout << height() << ' ' << len << std::endl;
            QRect eventRect = getEventRect(event);
            //std::cerr << event->duration() << std::endl;
            painter.drawRect(eventRect);
            //std::cout << eventRect.height() << std::endl;
            painter.setFont(QFont("times", -1, -1, true));
            if (eventRect.height() >= letterHeight  &&  event->info().length() * letterWidth <= eventRect.width()) {
                painter.drawText(eventRect, Qt::AlignLeft, event->info());
            }
        }
    }

    if (showIrregular_->isChecked()) {
        painter.setBrush(QColor(Qt::red).lighter(150));
        for (auto event: irregularEvents_) {
            QRect eventRect = getEventRect(event);
            painter.drawRect(eventRect);
            painter.setFont(QFont("verdana", -1, -1, true));
            if (eventRect.height() >= letterHeight  &&  event->info().length() * letterWidth <= eventRect.width()) {
                painter.drawText(eventRect, Qt::AlignLeft, event->info());
            }
        }
    }
}


void DayScheduleWidget::mouseMoveEvent(QMouseEvent* mouseEvent) {
    QToolTip::hideText();
    QString text = "";
    int minutes = double(mouseEvent->pos().y()) / (height() / double(24 * 60));
    if (showRegular_->isChecked()) {
        for (auto event: regularEvents_) {
            if (getEventRect(event).contains(mouseEvent->pos())) {
                if (!text.length()) {
                    text = QTime(minutes / 60, minutes % 60).toString("hh:mm");
                }
                text += "\n[R] " + event->begin().toString("hh:mm") + " " + event->info();
            }
        }
    }
    if (showIrregular_->isChecked()) {
        for (auto event: irregularEvents_) {
            if (getEventRect(event).contains(mouseEvent->pos())) {
                if (!text.length()) {
                    text = QTime(minutes / 60, minutes % 60).toString("hh:mm");
                }
                text += "\n[I] " + event->begin().toString("hh:mm") + " " + event->info();
            }
        }
    }
    if (text.length() != 0) {
        QToolTip::showText(mouseEvent->globalPos(), text, this);
    }
}

DayWidget::DayWidget(ScheduleManager *manager, QDate date, QWidget *parent) :
    QWidget(parent), manager_(manager), date_(date)
{
    setWindowTitle(date.toString());
    //entire window
    setWindowTitle(date.toString());
    QBoxLayout* dayWidgetLayout = new QBoxLayout(QBoxLayout::TopToBottom, this);
    QLabel* title = new QLabel(date.toString());
    title->setAlignment(Qt::AlignCenter);
    title->setFont(QFont("Courier", 15));

    //draw settings
    QHBoxLayout* drawSettLayout = new QHBoxLayout();
    QLabel* showEvents = new QLabel("Show events: ");
    QCheckBox* showRegularEvents = new QCheckBox("regular");
    QCheckBox* showIrregularEvents = new QCheckBox("irregular");

    showRegularEvents->setChecked(true);
    showIrregularEvents->setChecked(true);
    drawSettLayout->addWidget(showEvents);
    drawSettLayout->addWidget(showRegularEvents);
    drawSettLayout->addWidget(showIrregularEvents);

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
    dayWidgetLayout->addLayout(drawSettLayout);
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
    DayScheduleWidget_ = new DayScheduleWidget(manager_, date, showRegularEvents, showIrregularEvents, this);
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

QSize DayWidget::sizeHint() const {
    return QSize(240, 600);
}

void DayWidget::addEvent() {
    AddEventDialog* eventDialog = new AddEventDialog(date_, this);
    connect(eventDialog, SIGNAL(addIrregularEvent(QDate,Event*)),
            this, SIGNAL(addIrregularEvent(QDate,Event*)));
    eventDialog->show();
    update();
}

