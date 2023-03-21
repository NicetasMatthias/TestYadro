#include <iostream>
#include <vector>
#include <unistd.h>
#include <ctime>
#include <chrono>

#include "objects/Settings.h"
#include "objects/Tape.h"
#include "objects/Sort.h"

int main (int argc, char **argv)
{
    char options[ ] = "i:o:v";
    char c;
    char *inFName = nullptr,
            *outFName = nullptr;
    bool verbose = false;
    while ((c = getopt(argc, argv, options)) != -1)
    {
        switch (c)
        {
        case 'i':
            inFName = optarg;
            break;
        case 'o':
            outFName = optarg;
            break;
        case 'v':
            verbose = true;
            std::cout << "Verbose output is defined" << std::endl;
            break;
        case '?':
            std::cout << "Undefined argument: \"" << static_cast<char>(optopt) << "\"" << std::endl;
            break;
        }
    }

    if (inFName == nullptr || outFName == nullptr)
    {
        std::cout << "File names not set" << std::endl;
        return -1;
    }

    if (verbose)
    {
        std::cout << "#FILE NAMES#" << std::endl
                  << "\tInput file name:\t" << inFName << std::endl
                  << "\tOutput file name:\t" << outFName << std::endl;
    }

    Settings::readFromFile ("settings");
    if (!Settings::valid ())
    {
        std::cout << "#ERROR# Settings file read error" << std::endl;
        return -1;
    }

    if (verbose)
    {
        std::cout << "#SETTINGS#" << std::endl
                  << "\tAllowed RAM size:\t" << Settings::N () << " bytes" << std::endl
                  << "\tRewind delay:\t\t" << Settings::rewindDelay () << " mseconds" << std::endl
                  << "\tMove delay:\t\t" << Settings::moveDelay () << " mseconds" << std::endl
                  << "\tRead delay:\t\t" << Settings::readDelay () << " mseconds" << std::endl
                  << "\tWrite delay:\t\t" << Settings::writeDelay () << " mseconds" << std::endl;
    }


    std::vector <unsigned int> mem;
    mem.resize (Settings::N () / 4);

    auto in = std::make_shared <Tape> (std::string (inFName));
    if (!in->valid ())
    {
        std::cout << "Invalid input file" << std::endl;
        return -1;
    }
    auto out = Tape::makeTape (in->size (), std::string (outFName));

    auto t_start = std::chrono::high_resolution_clock::now ();

    if (Sort::doSort (in, out, mem))
    {
        std::cout << "Done" << std::endl;
        if (verbose)
        {
            auto t_end = std::chrono::high_resolution_clock::now ();
            std::cout << "#MEASURES#" << std::endl
                      << "\tNumber of items:\t" << out->size () << std::endl
                      << "\tElapsed time:\t\t" << std::chrono::duration<double, std::milli> (t_end - t_start).count () << " mseconds" << std::endl;
        }
    }
    else
    {
        std::cout << "Error" << std::endl;
    }
    return 0;
}
