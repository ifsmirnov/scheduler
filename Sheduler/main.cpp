#include <QApplication>
#include <QPalette>

#include <iostream>
#include <stdexcept>

#include <src/event.hpp>
#include <src/regularevent.hpp>
#include <src/irregularevent.hpp>
#include <src/day.hpp>
#include <gui/addeventdialog.hpp>
#include <gui/daywidget.hpp>

int main(int argc, char* argv[]) {
    QApplication app(argc, argv);
    QPalette pal = app.palette();

    pal.setColor(QPalette::Window, QColor(Qt::green).lighter());
    app.setPalette(pal);

    Day *day = new Day();
    day->addEvent(new RegularEvent(QTime(10, 0), 10000));
    day->addEvent(new IrregularEvent(QTime(0, 0), 8*60*60));
    day->addEvent(new IrregularEvent(QTime(23, 0), 59*60));

    DayWidget *widget = new DayWidget(day);
    widget->show();

    return app.exec();
}
