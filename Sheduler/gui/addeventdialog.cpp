#include "addeventdialog.hpp"

AddEventDialog::AddEventDialog(DailyScheduleSPtr &day, QWidget *parent):
    QDialog(parent), day_(day)
{
    setWindowTitle("Add Event");

    //the entire dialog
    QBoxLayout* eventDialogLayout = new QBoxLayout(QBoxLayout::TopToBottom, this);

    QBoxLayout* eventStartLayout = new QBoxLayout(QBoxLayout::LeftToRight);
    QBoxLayout* eventDuration = new QBoxLayout(QBoxLayout::LeftToRight);
    QLabel* infoLabel = new QLabel("Event Info");
    info_ = new QTextEdit();
    QPushButton* addEventButton = new QPushButton("Add");

    eventDialogLayout->addLayout(eventStartLayout);
    eventDialogLayout->addLayout(eventDuration);
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
    Event* event = new IrregularEvent();
    try {
        event->setBegin(QTime(hours_->text().toInt(), minutes_->text().toInt()));
        event->setDuration(duration_->text().toInt() * 60);
        event->setInfo(info_->toPlainText());
        day_->addEvent(event);
        close();
    } catch(std::invalid_argument ex) {
        delete event;
    }
}
