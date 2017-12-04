#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),
    gr(im)
{
    ui->setupUi(this);

    im = MyDisplay(ui->graphicsView->width()-2, ui->graphicsView->height()-2,
                QImage::Format_RGB32);
    scene = new QGraphicsScene(ui->graphicsView);
    ui->graphicsView->setScene(scene);

    tmr.setInterval(33);
    connect(&tmr, SIGNAL(timeout()), this, SLOT(tmrTick()));

    ui->graphicsView->grabMouse();

    im.fill(Qt::black);
    tmr.start();
    //on_ButOpen_clicked();

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
        //dir += "poly.obj";
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

    if (key == Qt::Key_0)
    {
        in_dot.camChange(0);
        return;
    }
    else if (key == Qt::Key_1 || key == Qt::Key_F1)
    {
        in_dot.camChange(1);
        if (key == Qt::Key_F1)
            system("open ../../../../Contents/infos/pdfs/mercury.pdf");
        return;
    }
    else if (key == Qt::Key_2 || key == Qt::Key_F2)
    {
        in_dot.camChange(2);
        if (key == Qt::Key_F2)
            system("open ../../../../Contents/infos/pdfs/venus.pdf");
        return;
    }
    else if (key == Qt::Key_3 || key == Qt::Key_F3)
    {
        in_dot.camChange(3);
        if (key == Qt::Key_F3)
            system("open ../../../../Contents/infos/pdfs/earth.pdf");
        return;
    }
    else if (key == Qt::Key_4 || key == Qt::Key_F4)
    {
        in_dot.camChange(4);
        if (key == Qt::Key_F4)
            system("open ../../../../Contents/infos/pdfs/mars.pdf");
        return;
    }
    else if (key == Qt::Key_5 || key == Qt::Key_F5)
    {
        in_dot.camChange(5);
        if (key == Qt::Key_F5)
            system("open ../../../../Contents/infos/pdfs/jupiter.pdf");
        return;
    }
    else if (key == Qt::Key_6 || key == Qt::Key_F6)
    {
        in_dot.camChange(6);
        if (key == Qt::Key_F6)
            system("open ../../../../Contents/infos/pdfs/saturn.pdf");
        return;
    }
    else if (key == Qt::Key_7 || key == Qt::Key_F7)
    {
        in_dot.camChange(7);
        if (key == Qt::Key_F7)
            system("open ../../../../Contents/infos/pdfs/uranus.pdf");
        return;
    }
    else if (key == Qt::Key_8 || key == Qt::Key_F8)
    {
        in_dot.camChange(8);
        if (key == Qt::Key_F8)
            system("open ../../../../Contents/infos/pdfs/neptune.pdf");
        return;
    }
    else if (key == Qt::Key_W)
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
    else if (key == Qt::Key_P)
    {
        in_dot.painterChange();
    }
    else if (key == Qt::Key_N)
    {
        in_dot.modelChange(normal);
    }
    else if (key == Qt::Key_M)
    {
        in_dot.modelChange(medium);
    }
    else if (key == Qt::Key_B)
    {
        in_dot.modelChange(bad);
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

