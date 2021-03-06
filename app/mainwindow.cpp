#include <QFileDialog>
#include <QDirIterator>
#include <QPaintEvent>
#include <QDebug>
#include <QMessageBox>

#include "utils.h"
#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "optionsdialog.h"
#include "exceptions.h"


MmMainWindow::MmMainWindow(QWidget *parent)
    : QMainWindow(parent)
    , m_ui(new Ui::MindForge)
    , m_mindMapWidget(m_settings, this)
{
    m_ui->setupUi(this);

    m_bgColor = m_settings.value(BGCOLOR_KEY, QColor(Qt::white)).value<QColor>();
    m_mindMapWidget.setBackGround(m_bgColor);

    setCentralWidget(&m_mindMapWidget);

    addFonts();
}

void MmMainWindow::addFonts()
{
    QDirIterator it(":/fonts", QDirIterator::Subdirectories);
    while (it.hasNext()) {
        //qDebug() << it.next();
        m_fontDb.addApplicationFont(it.next());
    }

//    foreach(QString s, m_fontDb.families())
//    {
//        qDebug() << s;
//    }
}

MmMainWindow::~MmMainWindow()
{
    safe_delete(m_ui);
}


void MmMainWindow::resizeEvent(QResizeEvent *event) {
    m_mindMapWidget.resize(event->size());
    event->accept();
}

void MmMainWindow::on_actionOptions_triggered()
{
    OptionsDialog od;
    od.exec();
}

void MmMainWindow::openMindMap(QString path)
{
    try {
        m_mindMapWidget.openMindMap(path);
    }
    catch(BadFile &ex) {
        QMessageBox::warning(this, "Could not open mind map.", ex.message());
    }
}

void MmMainWindow::on_actionOpen_triggered()
{
    QString folderPath = QFileDialog::getExistingDirectory(this, "Choose input folder");
    if (!folderPath.isEmpty()) {
        openMindMap(folderPath);
    }
}

void MmMainWindow::on_actionNew_child_node_triggered()
{
    m_mindMapWidget.addNode();
}
