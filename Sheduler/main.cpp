#include <QApplication>

#include <iostream>
#include <stdexcept>

#include <src/event.hpp>
#include <src/regularevent.hpp>
#include <src/irregularevent.hpp>
#include <src/day.hpp>
#include <gui/daywidget.hpp>

int main(int argc, char* argv[]) {
    QApplication app(argc, argv);

    Day *day = new Day();
    day->addEvent(new RegularEvent(QTime(10, 0), 10000));
    day->addEvent(new IrregularEvent(QTime(0, 0), 8*60*60));
    day->addEvent(new IrregularEvent(QTime(23, 0), 59*60));

    DayWidget *dayWidget = new DayWidget(day);
    dayWidget->show();

    return app.exec();
}
