#include "mainwindow.hpp"

MainWindow::MainWindow(Calendar* calendar, QWidget* parent):
    QMainWindow(parent), calendar_(calendar)
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


void MainWindow::save() {
    QString fileName = QFileDialog::getSaveFileName(this, tr("Open Calendar"), QDir::currentPath(), tr("XML (*.xml);;All files (*.*)"));
    if(!fileName.isNull()) {
        QDomDocument doc;
        calendar_->serialize(doc);
        QFile file(fileName);
        QTextStream stream(&file);
        stream << doc.toString();
        file.close();
    }
}


void MainWindow::open() {
    QString fileName = QFileDialog::getOpenFileName(this, tr("Open Calendar"), QDir::currentPath(), tr("XML (*.xml);;All files (*.*)"));
    if (!fileName.isNull()) {
        QFile file(fileName);
        QDomDocument doc;
        doc.setContent(&file);
        file.close();
        Calendar* cal = Calendar::deserialize(doc.toElement());
        delete calendar_;
        calendar_ = cal;
    }
}
