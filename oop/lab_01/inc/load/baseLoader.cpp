#include "baseLoader.hpp"
#include "../base_elems/exceptions.hpp"

BaseLoader::BaseLoader()
{
}

void BaseLoader::open(std::string filename)
{
    if (file.is_open())
        close();

    file.open(filename);
    time_t t_time = time(NULL);
    if (!file)
    {
        throw FileOpenError(ctime(&t_time), __FILE__, typeid(*this).name(), __LINE__);
    }
}

void BaseLoader::close()
{
    if (file.is_open())
        file.close();
}


Point BaseLoader::loadPoint()
{
    Point point;
    double x, y, z;
    if (file >> x >> y >> z)
    {
        point = Point(x, y, z);
    }
    else
    {
        time_t t_time = time(NULL);
        throw FileDataError(ctime(&t_time), __FILE__, typeid(*this).name(), __LINE__);
    }
    return point;
}

Connection BaseLoader::loadConnection()
{
    Connection connection;
    int first, second;
    if (file >> first >> second)
    {
        connection = Connection(first, second);
    }
    else
    {
        time_t t_time = time(NULL);
        throw FileDataError(ctime(&t_time), __FILE__, typeid(*this).name(), __LINE__);
    }
    return connection;
}

Vector<double> BaseLoader::loadAngles()
{
    Vector<double> angles;
    double x, y, z;
    if (file >> x >> y >> z)
    {
        angles = Vector<double>({x, y, z}, 3);
    }
    else
    {
        time_t t_time = time(NULL);
        throw FileDataError(ctime(&t_time), __FILE__, typeid(*this).name(), __LINE__);
    }
    return angles;
}

int BaseLoader::loadAmount()
{
    int amount;
    if (!(file >> amount))
    {
        time_t t_time = time(NULL);
        throw FileDataError(ctime(&t_time), __FILE__, typeid(*this).name(), __LINE__);
    }
    return amount;
}