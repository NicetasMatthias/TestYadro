#include <iostream>
#include <vector>
#include "objects/Settings.h"
#include "objects/Tape.h"
#include "objects/Sort.h"

#include <random>


int main (int argc, char **argv)
{
    Settings::readFromFile ("settings");
    if (!Settings::valid ())
    {
        std::cout << "Settings file read error" << std::endl;
        return -1;
    }

//    auto test = Tape::makeTape (100, "TestInput");
//    for (auto i = 0; i < 100; i++)
//    {
//        test->write (std::rand () % 10000);
//        test->moveForward();
//    }
//    return 0;

    std::vector <unsigned int> mem;
    mem.resize (Settings::N () / 4);

    std::string inTapeName, outTapeName;

    inTapeName = "TestInput";
    outTapeName = "TestOutput";
    auto in = std::make_shared <Tape> (inTapeName);
    auto out = Tape::makeTape (in->size (), outTapeName);

    if (Sort::doSort (in, out, mem))
        std::cout << "Done" << std::endl;
    else
        std::cout << "Error" << std::endl;
    return 0;
}
