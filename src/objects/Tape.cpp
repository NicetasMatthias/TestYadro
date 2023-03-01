#include "Tape.h"

Tape::Tape ()
    : valid_ (false)
{}

Tape::Tape (std::string filename)
    : filename_ (filename)
    , currPos_ (0)
{
    std::ifstream file (filename_);
    if (!file.is_open ())
    {
        setValid (false);
        return;
    }
    std::string buff;

    getline (file, buff);
    unsigned int size = atoi (buff.c_str ());
    tapeData_.resize (size);

    while (getline (file, buff))
    {
        if (buff.find ("*") == std::string::npos)
        {
            tapeData_.at (currPos_).data_ = atoi (buff.c_str ());
            tapeData_.at (currPos_).used_ = true;
        }
        else
        {
            tapeData_.at (currPos_).used_ = false;
        }

    }

    setValid (true);
}

Tape::~Tape ()
{
    if (valid ())
    {
        std::ofstream file (filename_);
        file << tapeData_.size () << std::endl;
        for (const auto &iter : tapeData_)
        {
            if (iter.used_)
            {
                file << iter.data_ << std::endl;
            }
            else
            {
                file << "*" << std::endl;
            }
        }
        file.close ();
    }
}

bool Tape::moveForward ()
{
    if (!valid ()) return false;

    if (currPos_ == tapeData_.size () - 1)
    {
        //если каретка находится на последней ячейке
        return false;
    }
    else
    {
        currPos_++;
        return true;
    }
}

bool Tape::moveBack ()
{
    if (!valid ()) return false;

    if (currPos_ == 0)
    {
        //если каретка находится на пераой ячейке
        return false;
    }
    else
    {
        currPos_++;
        return true;
    }
}

bool Tape::read (unsigned int &target)
{
    if (!valid ()) return false;

    if (tapeData_.at (currPos_).used_)
    {
        target = tapeData_.at (currPos_).data_;
        return true;
    }
    else
    {
        return false;
    }
}

bool Tape::write (unsigned int value)
{
    if (!valid ()) return false;

    tapeData_.at (currPos_).data_ = value;
    tapeData_.at (currPos_).used_ = true;
    return true;
}

bool Tape::valid ()
{
    return valid_;
}

Tape::ptr_t Tape::makeTape(unsigned int size, std::string filename)
{
    std::ofstream file (filename);
    if (!file.is_open ())
    {
        return nullptr;
    }

    file << size;
    file.close();

    return std::make_shared <Tape> (filename);
}

void Tape::setValid (bool value)
{
    valid_ = value;
}
