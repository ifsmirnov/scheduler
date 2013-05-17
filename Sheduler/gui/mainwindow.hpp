#ifndef MAINWINDOW_HPP
#define MAINWINDOW_HPP
#include <QMainWindow>
#include <QtGui>
#include <QAction>
#include <QFileDialog>
#include <QFile>
#include <QDomDocument>
#include <src/calendar/calendar.hpp>

#include <iostream>

#include "gui/calendarwidget.hpp"

class MainWindow: public QMainWindow
{
    Q_OBJECT
public:
    explicit MainWindow(Calendar* calendar,
                        QWidget* parent = 0);

private slots:
    void save();
    void open();

private:
    QMenu* fileMenu_;
    QAction* openAct_;
    QAction* saveAct_;
    Calendar* calendar_;

    CalendarWidget *calendarWidget;



    void createActions();
    void createMenus();
};

#endif // MAINWINDOW_HPP
