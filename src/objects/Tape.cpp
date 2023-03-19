#include "Tape.h"
#include "Settings.h"

#include <chrono>
#include <thread>
#include <iomanip>
//-- максимальное число, которое может быть записано это UINT_MAX = 4 294 967 295
//-- для простоты навигации по файлу числа будут записываться с ведущими нулями
#define NUMBER_LENGTH 10

Tape::Tape ()
    : valid_ (false)
{}

Tape::Tape (std::string filename)
{
    file.open (filename, std::ios_base::in | std::ios_base::out);
    if (!file.is_open ())
    {
        setValid (false);
        return;
    }
    std::string buff;

    getline (file, buff);
    size_ = atoi (buff.c_str ());
    setValid (true);
}

Tape::~Tape ()
{
    if (valid ())
    {
        file.close ();
    }
}

int Tape::size ()
{
    return size_;
}


ITape::ErrorCode Tape::moveForward ()
{
    file.seekg((NUMBER_LENGTH+1), file.cur);
    if (file.tellg() == (NUMBER_LENGTH + 1) * (size_ + 1))
    {
        file.seekg(-(NUMBER_LENGTH+1), file.cur);
        return Tape::EndOfTape;
    }
    else
    {
        std::this_thread::sleep_for(std::chrono::milliseconds(Settings::moveDelay()));
        return Tape::Success;
    }
}

ITape::ErrorCode Tape::moveBack ()
{
    file.seekg(-(NUMBER_LENGTH+1), file.cur);
    if (file.tellg() == 0)
    {
        file.seekg((NUMBER_LENGTH+1), file.cur);
        return Tape::BeginOfTape;
    }
    else
    {
        std::this_thread::sleep_for(std::chrono::milliseconds(Settings::moveDelay()));
        return Tape::Success;
    }
}

bool Tape::rewindToBegin()
{
    file.seekg((NUMBER_LENGTH+1), file.beg);
    std::this_thread::sleep_for(std::chrono::milliseconds(Settings::rewindDelay()));
    return Tape::Success;
}

bool Tape::rewindToEnd()
{
    file.seekg((NUMBER_LENGTH + 1) * size_, file.beg);
    std::this_thread::sleep_for(std::chrono::milliseconds(Settings::rewindDelay()));
    return Tape::Success;
}

ITape::ErrorCode Tape::read (unsigned int &target)
{
    std::string buff;
    auto ptr = file.tellg();
    getline (file, buff);
    file.seekg (ptr);
    std::this_thread::sleep_for(std::chrono::milliseconds(Settings::readDelay()));
    target = atoi (buff.c_str());
    return Tape::Success;
}

ITape::ErrorCode Tape::write (unsigned int value)
{
    auto tmpPos = file.tellp ();
    file << std::setfill('0') << std::setw(NUMBER_LENGTH) << value;
    file.seekp (tmpPos);
    std::this_thread::sleep_for(std::chrono::milliseconds(Settings::writeDelay()));
    return Tape::Success;
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

    file << std::setfill('0') << std::setw(NUMBER_LENGTH) << size << "\n";
    for (int i = 0; i < size; i ++)
        file << "**********\n";
    file.close();

    return std::make_shared <Tape> (filename);
}

void Tape::setValid (bool value)
{
    valid_ = value;
}
