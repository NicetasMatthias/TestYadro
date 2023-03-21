#include "Sort.h"

bool Sort::doSort(Tape::ptr_t input, Tape::ptr_t output, std::vector<unsigned int> &buffer)
{
    if (buffer.size () >= input->size ())
    {
        return sortSmall (input, output, buffer);
    }
    else
    {
        //-- дописать описание
        return sortBig (input, output, buffer);
    }
}

bool Sort::sortSmall(Tape::ptr_t input, Tape::ptr_t output, std::vector<unsigned int> &buffer)
{
    for (int i = 0; i < input->size (); i ++)
    {
        unsigned int tmp;
        if (input->read (tmp) != Tape::Success)
            return false; //-- Ошибка при чтении

        buffer.at (i) = tmp;
        input->moveForward ();
    }

    sort (buffer, input->size ());


    for (int i = 0; i < output->size (); i ++)
    {
        if (output->write (buffer.at (i)) != Tape::Success)
            return false; //-- Ошибка при записи

        output->moveForward ();
    }
    return true;
}



bool Sort::sortBig(Tape::ptr_t input, Tape::ptr_t output, std::vector<unsigned int> &buffer)
{
    bool flag = true;
    std::vector <std::vector <Tape::ptr_t>> tmpTapes;
    std::vector <Tape::ptr_t> firstLayer;
    tmpTapes.push_back (firstLayer);
    while (flag)
    {
        int usedBuffSize = buffer.size();

        //-- Считываем с ленты сколько влезает в память
        for (int i = 0; i < buffer.size (); i ++)
        {
            unsigned int tmp;
            if (input->read (tmp) != Tape::Success)
                return false; //-- Ошибка при чтении

            buffer.at (i) = tmp;
            if (input->moveForward () == Tape::EndOfTape)
            {
                usedBuffSize = i + 1;
                flag = false;
                break;
            }
        }

        //-- Сортируем то что считали
        sort (buffer, usedBuffSize);
        //-- Записываем на временную ленту
        tmpTapes.at(0).push_back (Tape::makeTape (usedBuffSize, "tmpTape_0_" + std::to_string(tmpTapes.at(0).size ())));
        for (int i = 0; i < usedBuffSize; i++)
        {
            if (tmpTapes.at(0).back ()->write (buffer.at (i)) != Tape::Success)
                return false; //-- Ошибка при записи

            tmpTapes.at(0).back ()->moveForward ();
        }

        tmpTapes.at(0).back ()->rewindToBegin ();

    }

    //-- Выполняем слияние промежуточных лент
    while (tmpTapes.back ().size () > buffer.size ())
    {
        std::vector <Tape::ptr_t> mergedTapesLayer;
        bool flag = true;
        for (unsigned int tmpStartPoint = 0; flag; tmpStartPoint += buffer.size ())
        {
            unsigned int mergedTapesNumber;
            if (tmpStartPoint + buffer.size () < tmpTapes.back ().size ())
            {
                mergedTapesNumber = buffer.size ();
            }
            else
            {
                flag = false;
                mergedTapesNumber = tmpTapes.back ().size () - tmpStartPoint;
            }
            unsigned int mergedSize = 0;
            for (unsigned int i = tmpStartPoint; i < tmpStartPoint + mergedTapesNumber; i ++)
            {
                mergedSize += tmpTapes.back ().at (i)->size ();
            }
            auto mergedTape = Tape::makeTape (mergedSize, "tmpTape_" + std::to_string (tmpTapes.size ()) + "_" + std::to_string (mergedTapesLayer.size ()));
            if (mergeTapes (tmpTapes.back (), tmpStartPoint, mergedTapesNumber, mergedTape, buffer))
                mergedTapesLayer.push_back (mergedTape);
            else return false;
        }
        tmpTapes.push_back (mergedTapesLayer);
    }

    //-- Выполняем слияние в выходную ленту
    return mergeTapes (tmpTapes.back (), 0, tmpTapes.back ().size (), output, buffer);
}

bool Sort::mergeTapes(std::vector<Tape::ptr_t> &src, unsigned int startPos, unsigned int srcSize, Tape::ptr_t dst, std::vector<unsigned int> &buffer)
{
    for (unsigned int i = 0; i < srcSize; i ++)
    {
        unsigned int tmp;
        if (src.at (startPos + i)->read(tmp) == Tape::Success)
            buffer.at (i) = tmp;
        else return false;
    }
    unsigned int usedTapes = srcSize;
    while (usedTapes > 0)
    {
        //-- Ищем минимальный элемент
        unsigned int minInd = 0;
        for (unsigned int i = 1; i < usedTapes; i ++)
        {
            if (buffer.at (i) < buffer.at (minInd))
                minInd = i;
        }
        dst->write (buffer.at (minInd));
        dst->moveForward ();

        switch (src.at (startPos + minInd)->moveForward())
        {
        case Tape::Success:
            unsigned int tmp;
            src.at (startPos + minInd)->read(tmp);
            buffer.at (minInd) = tmp;
            break;
        case Tape::EndOfTape:
            //-- Если лента закончилась то мы исключаем ее из следующих проходов
            std::swap (buffer.at (minInd), buffer.at (usedTapes - 1));
            std::swap (src.at (startPos + minInd), src.at (startPos + usedTapes - 1));
            usedTapes--;
            break;
        default:
            return false;
        }

    }

    dst->rewindToBegin ();
    return true;
}

void Sort::sort(std::vector<unsigned int> &buffer, unsigned int size)
{
    quickSort (buffer, 0, size - 1);
    return;
}

void Sort::quickSort(std::vector<unsigned int> &buffer, int start, int end)
{
    if (start >= end) return;

    unsigned int pivot = buffer.at (start);

    int count = 0;
    for (int i = start + 1; i <= end; i++)
    {
        if (buffer.at (i) <= pivot)
            count++;
    }

    std::swap (buffer.at (start), buffer.at (start + count));

    int i = start, j = end;

    int pivotIndex = start + count;
    while (i < pivotIndex && j > pivotIndex)
    {
        while (buffer.at (i) <= pivot) {
            i++;
        }

        while (buffer.at (j) > pivot) {
            j--;
        }

        if (i < pivotIndex && j > pivotIndex) {
            std::swap (buffer.at (i++), buffer.at (j--));
        }
    }

    quickSort (buffer, start, pivotIndex-1);
    quickSort (buffer, pivotIndex+1, end);

}
