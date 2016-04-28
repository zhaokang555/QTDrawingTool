#include "mainwindow.h"
#include <QMenuBar>
#include <QMenu>
#include <QToolBar>
#include <QActionGroup>
#include <QFileDialog>
#include <QMessageBox>
#include <QFile>
#include <QTextStream>
#include <QIODevice>
#include <QDebug>
#include <QPoint>
#include "circle.h"
#include "line.h"
#include "rect.h"
#include <QPainter>
#include <QPrinter>
#include <QPrintDialog>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    // 1. 初始化所有的菜单栏，工具栏，Group，Action
    initMenusToolBarsAndActionGroups();
    initAllActions();

    // 2. 添加状态栏
    statusBar();

    // 3. 创建画布对象，居中
    paintWidget = new PaintWidget(this);
    setCentralWidget(paintWidget);

    // 4. 连接
    connectAllThings();
}

// 初始化Menu, ToolBar和QActionGroup
void MainWindow::initMenusToolBarsAndActionGroups()
{
    this->fileMenu = menuBar()->addMenu(tr("&File"));
    this->drawMenu = menuBar()->addMenu(tr("&Draw"));
    this->editMenu = menuBar()->addMenu(tr("&Edit"));

    this->fileToolBar = this->addToolBar(tr("&File"));
    this->drawToolBar = this->addToolBar(tr("&Draw"));
    this->editToolBar = this->addToolBar(tr("&Edit"));

    this->group = new QActionGroup(this);
}

// 初始化所有的Action
void MainWindow::initAllActions()
{
    // 打开Action
    this->openAction = new QAction(tr("&Open"), this);
    openAction->setToolTip(tr("Open a file."));
    openAction->setStatusTip(tr("Open a file."));
    fileMenu->addAction(openAction);
    fileToolBar->addAction(openAction);

    // 保存Action
    this->saveAction = new QAction(tr("&Save"), this);
    saveAction->setToolTip(tr("Save this file."));
    saveAction->setStatusTip(tr("Save this file."));
    fileMenu->addAction(saveAction);
    fileToolBar->addAction(saveAction);

    // 打印Action
    this->printAction = new QAction(tr("&Print"), this);
    printAction->setToolTip(tr("Print to ( *.oxps  *.xps ) file."));
    printAction->setStatusTip(tr("Print to ( *.oxps  *.xps ) file."));
    fileMenu->addAction(printAction);
    fileToolBar->addAction(printAction);

    // 画线Action
    this->drawLineAction = new QAction(tr("&Line"), this);
    drawLineAction->setToolTip(tr("Draw a line."));
    drawLineAction->setStatusTip(tr("Draw a line."));
    drawLineAction->setCheckable(true);
    drawLineAction->setChecked(true);
    group->addAction(drawLineAction);
    drawToolBar->addAction(drawLineAction);
    drawMenu->addAction(drawLineAction);

    // 画矩形Action
    this->drawRectAction = new QAction(tr("&Rectangle"), this);
    drawRectAction->setToolTip(tr("Draw a rectangle."));
    drawRectAction->setStatusTip(tr("Draw a rectangle."));
    drawRectAction->setCheckable(true);
    group->addAction(drawRectAction);
    drawToolBar->addAction(drawRectAction);
    drawMenu->addAction(drawRectAction);

    // 画圆Action
    this->drawCircleAction = new QAction(tr("&Circle"), this);
    drawCircleAction->setToolTip(tr("Draw a circle."));
    drawCircleAction->setStatusTip(tr("Draw a circle."));
    drawCircleAction->setCheckable(true);
    group->addAction(drawCircleAction);
    drawToolBar->addAction(drawCircleAction);
    drawMenu->addAction(drawCircleAction);

    // 撤销Action
    this->undoAction = new QAction(tr("&Undo"), this);
    undoAction->setToolTip(tr("Undo last shape."));
    undoAction->setStatusTip(tr("Undo last shape."));
    editMenu->addAction(undoAction);
    editToolBar->addAction(undoAction);

    // 清空Action
    this->clearAllAction = new QAction(tr("&Clear All"), this);
    clearAllAction->setToolTip(tr("Clear all shapes."));
    clearAllAction->setStatusTip(tr("Clear all shapes."));
    editMenu->addAction(clearAllAction);
    editToolBar->addAction(clearAllAction);
}

// connect所有的函数
void MainWindow::connectAllThings()
{
    // 连接两个File Action
    connect(saveAction, SIGNAL(triggered()),
            this, SLOT(save()));
    connect(openAction, SIGNAL(triggered()),
            this, SLOT(open()));
    connect(printAction, SIGNAL(triggered()),
            this, SLOT(print()));

    // 连接三个Draw Action
    connect(drawLineAction, SIGNAL(triggered()),
            this, SLOT(drawLineActionTriggered()));
    connect(drawRectAction, SIGNAL(triggered()),
            this, SLOT(drawRectActionTriggered()));
    connect(drawCircleAction, SIGNAL(triggered()),
            this, SLOT(drawCircleActionTriggered()));

    // 连接两个Edit Action
    connect(clearAllAction, SIGNAL(triggered()),
            paintWidget, SLOT(clearAll()));
    connect(undoAction, SIGNAL(triggered()),
            paintWidget, SLOT(undo()));

    // 连接 MainWindow发出的changeCurrentShape信号
    // 与 paintWidget的setCurrentShape槽
    connect(this, SIGNAL(changeCurrentShape(Shape::Code)),
            paintWidget, SLOT(setCurrentShape(Shape::Code)));
}

void MainWindow::drawLineActionTriggered()
{
    emit changeCurrentShape(Shape::Line);
}

void MainWindow::drawRectActionTriggered()
{
    emit changeCurrentShape(Shape::Rect);
}

void MainWindow::drawCircleActionTriggered()
{
    emit changeCurrentShape(Shape::Circle);
}

/*
 *  QFileDialog Class Reference
    QString	getExistingDirectory ( QWidget * parent = 0, const QString & caption = QString(), const QString & dir = QString(), Options options = ShowDirsOnly )
    QString	getOpenFileName ( QWidget * parent = 0, const QString & caption = QString(), const QString & dir = QString(), const QString & filter = QString(), QString * selectedFilter = 0, Options options = 0 )
    QStringList	getOpenFileNames ( QWidget * parent = 0, const QString & caption = QString(), const QString & dir = QString(), const QString & filter = QString(), QString * selectedFilter = 0, Options options = 0 )
    QString	getSaveFileName ( QWidget * parent = 0, const QString & caption = QString(), const QString & dir = QString(), const QString & filter = QString(), QString * selectedFilter = 0, Options options = 0 )
 */
void MainWindow::open()
{
    // 1. 获取文件路径来打开文件，并检验文件是否打开。否则直接return
    QString fileName = QFileDialog::getOpenFileName(this, tr("Open File"),
                                                    ".", tr("dat Files (*.dat)"));
    QFile file(fileName);
    if (!file.open(QIODevice::ReadOnly)) {
        QMessageBox::warning(NULL, tr("Warning"), tr("File not opened"));
        return;
    }

    // 2. 清空数据列表
    paintWidget->shapeList.clear();

    // 3. 创建一个QtextStream对象来操纵file
    QTextStream in(&file);

    // 4. 当QtextStream对象没有到末尾时，循环
    while (! in.atEnd())
    {
        // 4.1 取得文件中的shapeName, 存入s中
        QString s;
        in >> s;
//        qDebug() << s;
        if (s == "")
            break;

        // 4.2 根据文件中shapeName的值，决定创建Shape的哪一种子对象。然后把newShape指向新创建的对象
        Shape * newShape;
        if (s == "Circle")
            newShape = new Circle(this->paintWidget);
        else if (s == "Rect")
            newShape = new Rect(this->paintWidget);
        else if (s == "Line")
            newShape = new Line(this->paintWidget);

        // 4.3 获取文件中的四个坐标值，存入新创建的Shape的子对象中
        int sx, sy, ex, ey;
        in >> sx >> sy >> ex >> ey;
//        qDebug() << sx << sy << ex << ey;
        newShape->setStart(QPoint(sx, sy));
        newShape->setEnd(QPoint(ex, ey));

        // 4.4 把创建好的Shape的子对象添加到数据列表中
        paintWidget->shapeList.append(newShape);
    }

    // 5. 刷新画布，显示出上一步添加的所有新数据。关闭文件
    paintWidget->update();
    file.close();
}

void MainWindow::save()
{
    // 1. 获取文件路径来打开文件，并检验文件是否打开。否则直接return
    QString fileName = QFileDialog::getSaveFileName(this, tr("Save File"),
                                                    ".", tr("dat Files (*.dat)"));
    QFile file(fileName);
    if (!file.open(QIODevice::WriteOnly)) {
        QMessageBox::warning(NULL, tr("Warning"), tr("File not saved!"));
        return;
    }

    // 2. 创建一个QtextStream对象来操纵file
    QTextStream out(&file);

    // 3. 通过循环，把数据列表中的每一个Shape对象的各项属性都写入文件中。关闭文件
    foreach (Shape *shape, paintWidget->shapeList)
    {
        // windows下换行是\r\n，unix下换行是\n，如果在行末只添加\n, 在windows下用记事本打开此文件时会丢失换行符，所以在行末添加\r\n
        out << shape->shapeName         << "\r\n"
            << shape->getStart().x()    << "\r\n"
            << shape->getStart().y()    << "\r\n"
            << shape->getEnd().x()      << "\r\n"
            << shape->getEnd().y()      << "\r\n";
    }
    file.close();
}

void MainWindow::print()
{
    QPrinter printer;
    QPainter painter;
    painter.begin(&printer);
    double xscale = printer.pageRect().width()/double(this->paintWidget->width());
    double yscale = printer.pageRect().height()/double(this->paintWidget->height());
    double scale = qMin(xscale, yscale);
    painter.translate(printer.paperRect().x() + printer.pageRect().width()/2,
                      printer.paperRect().y() + printer.pageRect().height()/2);
    painter.scale(scale, scale);
    painter.translate(-width()/2, -height()/2);

    this->paintWidget->render(&painter);
}
