#include "addeventdialog.hpp"
#include <iostream>

AddEventDialog::AddEventDialog(QDate date, int dayOfWeek, QWidget *parent):
    QDialog(parent), date_(date), dayOfWeek_(dayOfWeek)
{
    setWindowTitle("Add Event");
    //the entire dialog
    QBoxLayout* eventDialogLayout = new QBoxLayout(QBoxLayout::TopToBottom, this);

    QBoxLayout* eventStartLayout = new QBoxLayout(QBoxLayout::LeftToRight);
    QBoxLayout* eventDuration = new QBoxLayout(QBoxLayout::LeftToRight);
    QBoxLayout* eventColor = NULL;
    QLabel* infoLabel = new QLabel("Event Info");
    info_ = new QTextEdit();
    QPushButton* addEventButton = new QPushButton("Add");


    if (!date.isNull()) {
        eventColor = new QBoxLayout(QBoxLayout::LeftToRight);
        QLabel* colorLabel = new QLabel("Color:");
        initColorPicker();
        eventColor->addWidget(colorLabel, 0, Qt::AlignLeft);
        eventColor->addWidget(colorPicker_, 0, Qt::AlignRight);
    }

    eventDialogLayout->addLayout(eventStartLayout);
    eventDialogLayout->addLayout(eventDuration);
    if (!date.isNull()) {
        eventDialogLayout->addLayout(eventColor);
    }
    eventDialogLayout->addWidget(infoLabel);
    eventDialogLayout->addWidget(info_, 1);
    eventDialogLayout->addWidget(addEventButton, 0, Qt::AlignRight);


    //start info getter
    QLabel* startLabel = new QLabel("Starts at: ");
    hours_ = new QLineEdit();
    QLabel* colonLabel = new QLabel(":");
    minutes_ = new QLineEdit();

    hours_->setValidator(new QIntValidator(0, 23, this));
    hours_->setMaxLength(2);
    minutes_->setValidator(new QIntValidator(0, 59, this));
    hours_->setMaxLength(2);
    minutes_->setMaxLength(2);

    eventStartLayout->addWidget(startLabel, 1);
    eventStartLayout->addWidget(hours_);
    eventStartLayout->addWidget(colonLabel);
    eventStartLayout->addWidget(minutes_);


    //duration info
    QLabel* durationLabel = new QLabel("Duration (min): ");
    duration_ = new QLineEdit();

    duration_->setValidator(new QIntValidator(1, 24 * 60, this));
    eventDuration->addWidget(durationLabel, 1);
    eventDuration->addWidget(duration_);

    addEventButton->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
    connect(addEventButton, SIGNAL(clicked()), this, SLOT(addEvent()));


    setLayout(eventDialogLayout);
}

void AddEventDialog::addEvent() {
    Event* event;
    if (!date_.isNull()) {
        event = new IrregularEvent();
    } else {
        event = new RegularEvent();
    }
    try {
        event->setBegin(QTime(hours_->text().toInt(), minutes_->text().toInt()));
        event->setDuration(duration_->text().toInt() * 60);
        event->setInfo(info_->toPlainText());
        if (!date_.isNull()) {
            int index = colorPicker_->currentIndex();
            event->setColor(colors_[index / 2].lighter(150 * (index % 2)));
            emit addIrregularEvent(date_, event);
        } else {
            emit addWeeklyEvent(dayOfWeek_, event);
        }
        close();
    } catch(std::invalid_argument ex) {
        delete event;
    }
}

void AddEventDialog::initColorPicker() {
    colorPicker_ = new QComboBox();
    colors_.push_back(Qt::red);
    colors_.push_back(Qt::green);
    colors_.push_back(Qt::blue);
    colors_.push_back(Qt::yellow);

    for (auto color: colors_) {
        QPixmap pixmap(20, 20);
        pixmap.fill(color);
        colorPicker_->addItem(QIcon(pixmap), "");
        pixmap.fill(color.lighter(150));
        colorPicker_->addItem(QIcon(pixmap), "");
    }
}
