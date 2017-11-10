#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),
    gr(im)
{
    ui->setupUi(this);

    im = MyDisplay(ui->graphicsView->width()-2, ui->graphicsView->height()-2,
                QImage::Format_ARGB32);
    scene = new QGraphicsScene(ui->graphicsView);
    ui->graphicsView->setScene(scene);

    tmr.setInterval(33);
    connect(&tmr, SIGNAL(timeout()), this, SLOT(tmrTick()));

    ui->graphicsView->grabMouse();

    im.fill(Qt::black);
    on_ButOpen_clicked();

    /*
    try
    {
        in_dot.read("new.obj");
        in_dot.draw(gr);
        scene->clear();
        scene->addPixmap(QPixmap::fromImage(im));
        ui->label->setText(QString("Все в норме!"));
    }
    catch(BaseErr& err)
    {
        ui->label->setText(QString(err.what()));
    }
    */
}

MainWindow::~MainWindow()
{
    tmr.stop();
    delete scene;
    delete ui;
}

void MainWindow::on_ButOpen_clicked()
{
    try
    {
        std::string dir = "/Users/gordiig/Desktop/Cur_Sem/Un_CourseProject_Graph/Sphere/Contents/";
        dir += ui->LineEdit->text().toStdString();
        in_dot.read(dir.c_str());
        in_dot.draw(gr);
        scene->clear();
        scene->addPixmap(QPixmap::fromImage(im));

        if (!tmr.isActive())
        {
            tmr.start();
        }
    }
    catch(BaseErr& err)
    {
        tmr.stop();
        ui->label->setText(QString(err.what()));
    }
}

void MainWindow::tmrTick()
{
    try
    {
        in_dot.planetMove(gr);
        scene->clear();
        scene->addPixmap(QPixmap::fromImage(im));
    }
    catch(BaseErr& err)
    {
        ui->label->setText(QString(err.what()));
    }
}

void MainWindow::keyPressEvent(QKeyEvent *event)
{
    int key = event->key();
    double d = 5000;
    InterfaceCommand *caps = nullptr;

    if (key == Qt::Key_W)
    {
        caps = new DzCom(d);
    }
    else if (key == Qt::Key_A)
    {
        caps = new DxCom(-d);
    }
    else if (key == Qt::Key_D)
    {
        caps = new DxCom(d);
    }
    else if (key == Qt::Key_S)
    {
        caps = new DzCom(-d);
    }
    else if (key == Qt::Key_Space)
    {
        caps = new DyCom(-d);
    }
    else if (key == Qt::Key_Control)
    {
        caps = new DyCom(d);
    }

    try
    {
        in_dot.camMove(gr, caps);
        scene->clear();
        scene->addPixmap(QPixmap::fromImage(im));

        if (!tmr.isActive())
        {
            tmr.start();
        }
    }
    catch(BaseErr& err)
    {
        tmr.stop();
        ui->label->setText(QString(err.what()));
    }

    if (caps)
    {
        delete caps;
    }

}

void MainWindow::mousePressEvent(QMouseEvent *event)
{
    if (event->button() == Qt::LeftButton)
    {
        last_x = event->pos().x();
        last_y = event->pos().y();
    }
}
void MainWindow::mouseMoveEvent(QMouseEvent *event)
{
    double dx = (event->pos().x() - last_x) * MOUSE_SENS;
    last_x = event->pos().x();

    double dy = (event->pos().y() - last_y) * MOUSE_SENS;
    last_y = event->pos().y();

    InterfaceCommand *caps = new DyAngCom(dx);
    InterfaceCommand *caps2 = new DxAngCom(-dy);

    try
    {
        in_dot.camMove(gr, caps);
        in_dot.camMove(gr, caps2);
        scene->clear();
        scene->addPixmap(QPixmap::fromImage(im));

        if (!tmr.isActive())
        {
            tmr.start();
        }
    }
    catch(BaseErr& err)
    {
        tmr.stop();
        ui->label->setText(QString(err.what()));
    }

    delete caps;
    delete caps2;
}

void MainWindow::on_LineEdit_returnPressed()
{
    on_ButOpen_clicked();
}

