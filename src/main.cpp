#include <iostream>
#include <vector>
#include "objects/Settings.h"
#include "objects/Tape.h"
#include "objects/Sort.h"

#include <random>

using namespace std;

int main()
{
    //    Settings s;

//    auto test = Tape::makeTape (10000, "TestInput");
//    for (auto i = 0; i < 10000; i++)
//    {
//        test->write (std::rand () % 10000);
//        test->moveForward();
//    }

    std::vector <unsigned int> mem;
    //    mem.resize (s.N () / 4);
    mem.resize (1000);

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
