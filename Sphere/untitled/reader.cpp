#include "reader.h"

/**
 * @brief Reader::Reader -- Конструктор, в который передается имя файла
 * @param name -- Имя файла
 */
Reader::Reader(const char *name)
{
    openFile(name);
}

Reader::~Reader()
{
    closeFile();
}

/**
 * @brief Reader::openFile -- Открытие файла
 * @param name -- Имя файла
 */
void Reader::openFile(const char *name)
{
    closeFile();
    file.open(name);

    if (!file.is_open())
    {
        throw FileOpeningErr("\nReader::Reader(const char *name) in reader.cpp");
    }
}

/**
 * @brief Reader::closeFile -- Закрытие файла
 */
void Reader::closeFile()
{
    if (file.is_open())
    {
        file.clear();
        file.close();
    }
}

/**
 * @brief Reader::resetFile -- Возврат каретки в начало файла и сброс флагов
 */
void Reader::resetFile()
{
    file.clear();
    file.seekg(0);
}

/**
 * @brief Reader::read_dots -- Функция чтения точек из файла .obj
 * @return Массив точек
 */
std::vector<Dot3D<double> > Reader::read_dots()
{
    if (!file.is_open())
    {
        throw FileOpenErr("\nObjReader::read_dots() in reader.cpp");
    }

    std::vector<Dot3D<double>> arr;
    char com;
    char strcom[256];

    file.get(com);

    while ((com != '#') && (!file.eof()))
    {
        if (com == 'v')
        {
            Dot3D<double> tmp;
            file >> tmp.x >> tmp.y >> tmp.z;
            arr.push_back(tmp);
        }
        else
        {
            file.getline(strcom, 256, '\n');
        }

        do
        {
            file.get(com);
        } while (com == '\n');
    }

    return arr;
}

std::vector<Dot2D<double> > Reader::read_texture()
{
    if (!file.is_open())
    {
        throw FileOpenErr("\nObjReader::read_texture() in reader.cpp");
    }

    std::vector<Dot2D<double> > ans;
    char com;
    char strcom[256];

    file.get(com);

    while((com != '#') && (!file.eof()))
    {
        if (com == 'v')
        {
            file.get(com);
            Dot2D<double> tmp;
            file >> tmp.x >> tmp.y;
            ans.push_back(tmp);
        }
        else
        {
            file.getline(strcom, 256, '\n');
        }

        do
        {
            file.get(com);
        } while (com == '\n');
    }

    return ans;
}

/**
 * @brief Reader::read_poly -- Функция чтения полигонов (номера точек, образующих полигоны) из файла .obj
 * @return Массив списков номеров точек
 */
std::vector<std::list<int>> Reader::read_poly()
{
    if (!file.is_open())
    {
        throw FileOpenErr("\nObjReader::read_poly() in reader.cpp");
    }

    std::vector<std::list<int>> arr;
    char com;
    char strcom[256];

    file.get(com);

    while (!file.eof())
    {
        if (com == 'f')
        {
            std::list<int> tmp;
            int in;
            for (int i = 0; i < 3; i++)
            {
                file >> in;
                tmp.push_back(in);
            }

            file.get(com);
            if (com == ' ')
            {
                file >> in;
                tmp.push_back(in);
                file.getline(strcom, 256, '\n');
            }
            arr.push_back(tmp);
        }

        file.get(com);
    }

    return arr;
}

/**
 * @brief Reader::read -- Функция чтения всего объектра из файла .obj
 * @return Объект
 */
Obj Reader::read()
{

    std::vector<Dot3D<double> > points = read_dots();
    std::vector<Dot2D<double> > texture_c = read_texture();
    std::vector<std::list<int> > poly = read_poly();
    Obj tmp(points, texture_c, poly);
    return tmp;
}

/**
 * @brief Reader::read -- Чтение объекта из нового файла
 * @param name -- Имя файла
 * @return Объект
 */
Obj Reader::read(const char *name)
{
    closeFile();
    openFile(name);
    return read();
}

