#include "mainwindow.hpp"

MainWindow::MainWindow()
{
    createActions();
    createMenus();
}


void MainWindow::createActions() {
    saveAct_ = new QAction(tr("&Save"), this);
    saveAct_->setShortcut(QKeySequence::Save);
    saveAct_->setStatusTip("Save current calendar to file");
    connect(saveAct_, SIGNAL(triggered()), this, SLOT(save()));

    openAct_ = new QAction(tr("&Open"), this);
    openAct_->setShortcut(QKeySequence::Open);
    openAct_->setStatusTip("Open calendar file");
    connect(openAct_, SIGNAL(triggered()), this, SLOT(open()));
}


void MainWindow::createMenus() {
    fileMenu_ = menuBar()->addMenu(tr("&File"));
    fileMenu_->addAction(openAct_);
    fileMenu_->addAction(saveAct_);
}
