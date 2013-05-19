#ifndef ADDEVENTDIALOG_HPP
#define ADDEVENTDIALOG_HPP

#include <QDialog>
#include <QBoxLayout>
#include <QLabel>
#include <QPushButton>
#include <QTextEdit>
#include <QLineEdit>
#include <QValidator>
#include <QColor>
#include <stdexcept>

#include "src/irregularevent.hpp"
#include "src/dailyschedule.hpp"
#include "src/managers/schedulemanager.hpp"

class AddEventDialog: public QDialog
{
    Q_OBJECT
public:
    explicit AddEventDialog(QDate date,
                            int dayOfWeek = -1,
                            QWidget *parent = 0);

private:
    QLineEdit* hours_;
    QLineEdit* minutes_;
    QLineEdit* duration_;
    QTextEdit* info_;
    QDate date_;
    QColor color_;
    int dayOfWeek_;

signals:
    void addIrregularEvent(QDate date, Event* event);
    void addWeeklyEvent(int dayOfWeek, Event* event);

private slots:
    void addEvent();
};

#endif // ADDEVENTDIALOG_HPP
