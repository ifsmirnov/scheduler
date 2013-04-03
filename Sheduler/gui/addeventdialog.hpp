#ifndef ADDEVENTDIALOG_HPP
#define ADDEVENTDIALOG_HPP

#include <QDialog>
#include <QBoxLayout>
#include <QLabel>
#include <QPushButton>
#include <QTextEdit>
#include <QLineEdit>
#include <QValidator>
#include "src/irregularevent.hpp"
#include "src/day.hpp"


class AddEventDialog: public QDialog
{
    Q_OBJECT
public:
    explicit AddEventDialog(Event *event, QWidget *parent = 0);

private:
    QLineEdit* hours_;
    QLineEdit* minutes_;
    QLineEdit* duration_;
    QTextEdit* info_;
    Event* event_;

private slots:
    void addEvent();
};

#endif // ADDEVENTDIALOG_HPP
