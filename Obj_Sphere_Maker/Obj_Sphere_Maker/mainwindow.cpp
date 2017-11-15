#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    file_dir = "/Users/gordiig/Desktop/";
    ui->tabWidget->setTabText(0, "Sphere");
    ui->tabWidget->setTabText(1, "Ring");
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_Start_Button_clicked()
{
    if (ui->tabWidget->currentIndex() == 0)
    {
        double radius = ui->Radius_SpinBox->value();
        int n = ui->mer_SpinBox->value();
        int m = ui->par_SpinBox->value() + 1;

        if ((m % 2) == 1)
        {
            ui->Err_Label->setText("Ошибка!\nНеверно указано количество параллелей!");
            return;
        }

        out_file.open((file_dir + "new.obj").toStdString());

        vWriter(n, m, radius);
        fWriter(n+1, m);
    }
    else if (ui->tabWidget->currentIndex() == 1)
    {
        double inner_radius = ui->Spin_Ring_Inner_Radius->value();
        double outer_radius = ui->Spin_Ring_Outer_Radius->value();
        int poly_num = ui->SpinRingPolys->value();

        if (inner_radius >= outer_radius)
        {
            ui->Err_Label->setText("Ошибка!\nНеверно указаны внешний и внутренний радиусы кольца!");
            return;
        }

        out_file.open((file_dir + "ring.obj").toStdString());

        ringVWriter(inner_radius, outer_radius, poly_num);
        ringFWriter(poly_num);
    }

    out_file.close();
    ui->Err_Label->setText("Создание файла прошло успешно!");
}


void MainWindow::vWriter(const int n, const int m, const double r)
{
    double alpha = (double)360/(double)n * M_PI/(double)180;    // Round circle angle
    double beta = (double)180/(double)m * M_PI/(double)180;     // Upper semi-circle angle
    double x = 0;
    double y = 0;
    double z = 0;
    int count = 0;

    std::string vt;

    // Экватор
    for (int i = 0; i <= n; i++)
    {
        x = roundToN(r * cos(alpha*i));
        z = roundToN(r * sin(alpha*i));
        count++;
        out_file << "v " << x << " " << y << " " << z << "\n";

        vt = vt + "vt " + std::to_string(roundToN(alpha*i/2/M_PI)) + " 0.5\n";
    }

    // Широты/долготы (в т.ч. и полюса (последняя итерация цикла))
    for (int i = 1; i <= (m/2); i++)
    {
        x = r * cos(i*beta); // Это же и новый радиус
        y = r * sin(i*beta);

        std::vector<Dot> dots;
        std::vector<Dot> tex;
        for (int j = 0; j <= n; j++)
        {
            Dot circle;
            circle.x = roundToN(x * cos(alpha*j));
            circle.y = roundToN(y);
            circle.z = roundToN(x * sin(alpha*j));
            count += 2;
            out_file << "v " << circle.x << " " << circle.y << " "
                     << circle.z << "\n";
            dots.push_back(circle);

            Dot texx;
            texx.x = roundToN(j * alpha/2/M_PI);
            texx.y = roundToN((i*beta + (M_PI/2))/M_PI);
            vt = vt + "vt " + std::to_string(texx.x) + " " + std::to_string(texx.y) + "\n";
            tex.push_back(texx);
        }
        for (int j = 0; j < dots.size(); j++)
        {
            out_file << "v " << dots[j].x << " " << -dots[j].y << " "
                     << dots[j].z << "\n";
            vt = vt + "vt " + std::to_string(tex[j].x) + " " + std::to_string(roundToN(1-tex[j].y)) + "\n";
        }
    }

    vt = vt + "# " + std::to_string(count) + "dots\n";
    out_file << "# " << count << " dots \n";
    out_file << "\n" << vt << "\n";
}

void MainWindow::fWriter(const int n, const int m)
{
    out_file << "\no Sphere \n";
    int dots_num = n + m*n; // Экватор + остальное
    int poly_cnt = 0;

    // Связанные с экватором
    for (int i = 0; i < n; i++)
    {
        int j = (i == n-1) ? (0) : (i+1);
        out_file << "f " << n+i+1 << " " << n+j+1 << " "
                 << j+1 << " " << i+1 << "\n";
        out_file << "f " << i+1 << " " << j+1 << " "
                 << n+n+j+1 << " " << n+n+i+1 << "\n";
        poly_cnt += 2;
    }

    // Остальные
    int i_up_line = 1;
    for (int i = 0; i < m/2 - 1; i++)
    {
        for (int j = 0; j < n; j++)
        {
            int k = (j == n-1) ? (0) : (j+1);

            out_file << "f " << n*(i_up_line+2)+j+1 << " " << n*(i_up_line+2)+k+1 << " "
                     << n*i_up_line+k+1 << " " << n*i_up_line+j+1 << "\n";
            out_file << "f " << n*(i_up_line+1)+j+1 << " " << n*(i_up_line+1)+k+1 << " "
                     << n*(i_up_line+3)+k+1 << " " << n*(i_up_line+3)+j+1 << "\n";
            poly_cnt += 2;
        }
        i_up_line += 2;
    }

    /*
    // Полюсные
    for (int i = 0; i < n; i++)
    {
        int j = (i == n-1) ? (0) : (i+1);

        out_file << "f " << dots_num - 2-n+i + 1 << " " << dots_num - 2-n+j + 1 << " "
                 << dots_num << "\n";
        out_file << "f " << dots_num - 2-2*n+j + 1 << " " << dots_num - 2-2*n+i + 1 << " "
                 << dots_num-1 << "\n";
        poly_cnt += 2;
    }
    */

    out_file << "# " << poly_cnt << " polygons\n";
}

void MainWindow::ringVWriter(const double in_r, const double out_r, const int p_num)
{
    std::string vt;
    int count = 0;
    double alpha = ((double)360 / (double)p_num) * M_PI/180;
    double y = 0;
    double x = in_r;
    double z = 0;

    for (int k = 0; k < 2; k++)
    {
        x = in_r;
        z = 0;
        alpha *= -1;
        for (int i = 0; i <= p_num; i++)
        {
            x = roundToN(in_r * cos(alpha*i));
            z = roundToN(in_r * sin(alpha*i));
            out_file << "v " << x << " " << y << " " << z << "\n";

            if (alpha < 0)
            {
                vt = vt + "vt " + std::to_string(1 + (alpha*i)/2/M_PI) + " 1\n";
            }
            else
            {
                vt = vt + "vt " + std::to_string((alpha*i)/2/M_PI) + " 1\n";
            }

            count++;
        }

        x = out_r;
        z = 0;
        for (int i = 0; i <= p_num; i++)
        {
            x = roundToN(out_r * cos(alpha*i));
            z = roundToN(out_r * sin(alpha*i));
            out_file << "v " << x << " " << y << " " << z << "\n";

            if (alpha < 0)
            {
                vt = vt + "vt " + std::to_string(1 + (alpha*i)/2/M_PI) + " 1\n";
            }
            else
            {
                vt = vt + "vt " + std::to_string((alpha*i)/2/M_PI) + " 1\n";
            }

            count++;
        }
    }

    vt = vt + "# " + std::to_string(count) + "dots\n";
    out_file << "# " << count << " dots \n";
    out_file << "\n" << vt << "\n";
}

void MainWindow::ringFWriter(const int p_num)
{
    out_file << "\no Ring \n";

    int cnt = 0;
    int point_num = p_num + 1;

    for (int i = 0; i < p_num; i++)
    {
        out_file << "f " << i+1 << " " << i+point_num+1 << " "
                 << i+point_num+1+1 << " " << i+1+1 << "\n";

        out_file << "f " << i+1+point_num*2 << " " << i+point_num+1+point_num*2 << " "
                 << i+point_num+1+1+point_num*2 << " " << i+1+1+point_num*2 << "\n";
        cnt += 2;
    }



    out_file << "# " << cnt << " polygons\n";
}

void MainWindow::on_Dir_Button_clicked()
{
    file_dir = QFileDialog::getExistingDirectory(this, "Сохранить в:");
    if (file_dir.isEmpty())
    {
        file_dir = "/Users/gordiig/Desktop/new.obj";
    }
    else
    {
        file_dir += "/new.obj";
    }
}

double MainWindow::roundToN(double num, int n)
{
    double ans = fabs(num);
    double sign = (num >= 0) ? (1) : (-1);

    ans = round(ans * 10*n);
    if (ans == 0)
    {
        return 0;
    }

    ans = (double)ans / (double)(10.*n);
    return sign*ans;
}
