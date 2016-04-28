#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "shape.h"
#include "paintwidget.h"

class QActionGroup;

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = 0);

signals:
    void changeCurrentShape(Shape::Code newShape);

private:
    PaintWidget *paintWidget;

    QMenu *fileMenu;
    QToolBar *fileToolBar;
    QAction *saveAction;
    QAction *openAction;
    QAction *printAction;

    QMenu *drawMenu;
    QToolBar *drawToolBar;
    QAction *drawLineAction;
    QAction *drawRectAction;
    QAction *drawCircleAction;

    QMenu *editMenu;
    QToolBar *editToolBar;
    QAction *undoAction;
    QAction *clearAllAction;

    QActionGroup *group;

    void initMenusToolBarsAndActionGroups();
    void initAllActions();
    void connectAllThings();

private slots:
    void drawLineActionTriggered();
    void drawRectActionTriggered();
    void drawCircleActionTriggered();

    void open();
    void save();
    void print();
};

#endif // MAINWINDOW_H
