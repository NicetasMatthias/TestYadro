#include "Settings.h"

#include <fstream>
#include <sstream>

bool Settings::valid()
{
    return valid_;
}

int Settings::N()
{
    return n_;
}

int Settings::rewindDelay()
{
    return rewindDelay_;
}

int Settings::moveDelay()
{
    return moveDelay_;
}

int Settings::readDelay()
{
    return readDelay_;
}

int Settings::writeDelay()
{
    return writeDelay_;
}

void Settings::readFromFile(std::string fileName)
{
    std::ifstream fs (fileName);
    std::string tmp;
    while (getline (fs,tmp))
    {
        std::stringstream ss (tmp);
        std::string key, value;
        getline (ss, key, '=');
        getline (ss, value, '=');


        if (key.compare("N") == 0)
        {
            n_ = atoi(value.c_str());
            continue;
        }
        if (key.compare("RewindDelay") == 0)
        {
            rewindDelay_ = atoi(value.c_str());
            continue;
        }
        if (key.compare("MoveDelay") == 0)
        {
            moveDelay_ = atoi(value.c_str());
            continue;
        }
        if (key.compare("ReadDelay") == 0)
        {
            readDelay_ = atoi(value.c_str());
            continue;
        }
        if (key.compare("WriteDelay") == 0)
        {
            writeDelay_ = atoi(value.c_str());
            continue;
        }
    }

    if (       n_ == -1
               || rewindDelay_ == -1
               || moveDelay_ == -1
               || readDelay_ == -1
               || writeDelay_ == -1)
    {
        valid_ = false;
    }
    else
    {
        valid_ = true;
    }

}

