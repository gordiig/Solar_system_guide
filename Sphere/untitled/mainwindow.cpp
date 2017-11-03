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

    gr.Ia = ui->Slider_Ia->value();
    gr.Id = ui->Slider_Id->value();
    gr.kd = (double)ui->Slider_kd->value()/100.;
    gr.ka = (double)ui->Slider_ka->value()/100.;

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
        in_dot.read(ui->LineEdit->text().toStdString().c_str());
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

void MainWindow::on_Slider_Id_valueChanged(int value)
{
    gr.Id = value;

    try
    {
        in_dot.camMove(gr);
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
void MainWindow::on_Slider_kd_valueChanged(int value)
{
    if ((ui->Slider_kd->value() + ui->Slider_ka->value()) >= 100)
    {
        tmr.stop();
        ui->Slider_kd->setValue(100 - ui->Slider_ka->value());
        ui->label->setText("Нельзя чтобы коэффициенты световой энергии"
                           " в сумме давали > 100");

        return;
    }


    gr.kd = (double)value/100;
    try
    {
        in_dot.camMove(gr);
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
void MainWindow::on_Slider_ka_valueChanged(int value)
{
    if ((ui->Slider_kd->value() + ui->Slider_ka->value()) >= 100)
    {
        tmr.stop();
        ui->Slider_ka->setValue(100 - ui->Slider_kd->value());
        ui->label->setText("Нельзя чтобы коэффициенты световой энергии"
                           " в сумме давали > 100");

        return;
    }

    gr.ka = (double)value/100;
    try
    {
        in_dot.camMove(gr);
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
void MainWindow::on_Slider_Ia_valueChanged(int value)
{
    gr.Ia = value;

    try
    {
        in_dot.camMove(gr);
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
    InterfaceCommand *caps = nullptr;

    if (key == Qt::Key_W)
    {
        caps = new DzCom(50);
    }
    else if (key == Qt::Key_A)
    {
        caps = new DxCom(-50);
    }
    else if (key == Qt::Key_D)
    {
        caps = new DxCom(50);
    }
    else if (key == Qt::Key_S)
    {
        caps = new DzCom(-50);
    }
    else if (key == Qt::Key_Space)
    {
        caps = new DyCom(-50);
    }
    else if (key == Qt::Key_Control)
    {
        caps = new DyCom(50);
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

