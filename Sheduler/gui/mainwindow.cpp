#include "mainwindow.hpp"

MainWindow::MainWindow(Calendar* calendar, QWidget* parent):
    QMainWindow(parent), calendar_(calendar)
{
    createActions();
    createMenus();

    calendarWidget = new CalendarWidget(QDate::currentDate(), calendar, this);
    setCentralWidget(calendarWidget);
    calendarWidget->show();
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
        QDomElement element = calendar_->serialize(doc);
        doc.appendChild(element);
        std::cerr << "Filename = " << fileName.toStdString() << std::endl;
        QFile file(fileName);
        file.open(QIODevice::WriteOnly | QIODevice::Text);
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
        Calendar* cal = Calendar::deserialize(doc.firstChildElement("calendar"));
        delete calendar_;
        calendar_ = cal;
        calendarWidget->setCalendar(calendar_);
    }
}
