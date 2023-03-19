#ifndef SORT_H
#define SORT_H

#include "Tape.h"

class Sort
{
public:
    bool static doSort (Tape::ptr_t input, Tape::ptr_t output, std::vector <unsigned int> &buffer);
private:
    bool static sortSmall (Tape::ptr_t input, Tape::ptr_t output, std::vector <unsigned int> &buffer);
    bool static sortBig (Tape::ptr_t input, Tape::ptr_t output, std::vector <unsigned int> &buffer);

    bool static mergeTapes (std::vector <Tape::ptr_t> &src, unsigned int startPos, unsigned int srcSize, Tape::ptr_t dst, std::vector <unsigned int> &buffer);

    void static sort (std::vector <unsigned int> &buffer, unsigned int size);

    void static quickSort (std::vector <unsigned int> &buffer, int start, int end);
};

#endif // SORT_H
