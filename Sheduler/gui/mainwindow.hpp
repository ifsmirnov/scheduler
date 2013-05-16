#ifndef MAINWINDOW_HPP
#define MAINWINDOW_HPP
#include <QMainWindow>
#include <QtGui>
#include <QAction>

class MainWindow: public QMainWindow
{
public:
    MainWindow();

private:
    QMenu* fileMenu_;
    QAction* openAct_;
    QAction* saveAct_;

    void createActions();
    void createMenus();

private slots:
    void save();
    void open();
};

#endif // MAINWINDOW_HPP
