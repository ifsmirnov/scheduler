#include <QApplication>

#include <iostream>
#include <stdexcept>

#include <src/event.hpp>
#include <src/regularevent.hpp>

int main(int argc, char* argv[]) {
    QApplication app(argc, argv);

    return app.exec();
}
