#ifndef MINDMAPWIDGET_H
#define MINDMAPWIDGET_H


#include "mmnodewidget.h"

#include "mmtextedit.h"

#include <QSettings>
#include <QWidget>
#include <QVector>
#include <QTextEdit>
#include <QPlainTextEdit>
#include <QDir>

class MmWidget : public QWidget
{
    Q_OBJECT
public:
    explicit MmWidget(QSettings &settings, QWidget *parent = 0);
    ~MmWidget();
    void setBackGround(QColor color);
    void setData(MmNodeWidget *node);
    MmNodeWidget* getSelectedNode();
    void editNode();
    void addNode();
    void openMindMap(QString path);


    //Constants
public:
    const int MAX_NODE_WIDTH = 800; //Pixels

signals:

public slots:
    void editAccepted();
    void editRejected();

private:
    MmNodeWidget* load(QDir baseDir);

private:
    QSettings          &m_settings;
    MmNodeWidget             *m_rootNode;
    MmNodeWidget             *m_selectedNode;
    QPen                m_blackPen;
    MmTextEdit          m_editor;
    bool                m_bAddNode;
};

#endif // MINDMAPWIDGET_H
