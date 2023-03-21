#ifndef SORT_H
#define SORT_H

#include "Tape.h"

//! \brief Класс реализующий сортировку данных на ленте
class Sort
{
public:
    //! \brief Метод осуществляющий сортировку входных данных с входной ленты и записывающий их на выходную
    //! \param input - входная лента
    //! \param output - выходная лента
    //! \param buffer - временный буфер
    //! \return bool - успех выполнения
    bool static doSort (Tape::ptr_t input, Tape::ptr_t output, std::vector <unsigned int> &buffer);
private:
    //! \brief Метод осуществляющий сортировку, в случае если памяти достаточно для одновременной записи всех данных ленты в пямять
    //! \param input - входная лента
    //! \param output - выходная лента
    //! \param buffer - временный буфер
    //! \return bool - успех выполнения
    bool static sortSmall (Tape::ptr_t input, Tape::ptr_t output, std::vector <unsigned int> &buffer);

    //! \brief Метод осуществляющий сортировку, в случае если памяти недостаточно для одновременной записи всех данных ленты в пямять
    //! \param input - входная лента
    //! \param output - выходная лента
    //! \param buffer - временный буфер
    //! \return bool - успех выполнения
    bool static sortBig (Tape::ptr_t input, Tape::ptr_t output, std::vector <unsigned int> &buffer);

    //! \brief Метод осуществзяющий слияние данных с нескольких отсортированных лент в одну с использованием буфера
    //! Буфер позволяет сэкономить на времени чтения данных с ленты при поиске минимального элемента для записи на выходную
    //! ленту, таким образом слияние осуществляется в n чтений, записей и переходов на ячейку, где n это размер итоговой ленты
    //! \param src - Вектор, содержащий отсортированные ленты для слияния
    //! \param startPos - С какой позиции во входном векторе мы берем ленты
    //! \param srcSize - Сколько лент берем с входного вектора
    //! \param dst - Лента на которую записываются данные
    //! \param buffer - Вспомогательный буфер используемый при слиянии
    //! \return bool - успех выполнения
    bool static mergeTapes (std::vector <Tape::ptr_t> &src, unsigned int startPos, unsigned int srcSize, Tape::ptr_t dst, std::vector <unsigned int> &buffer);

    //! \brief Метод сортировки данных в буфере
    //! (Вынесен в отдельный метод в качестве интерфейса для того чтобы заменять используемый алгоритм сортировки,
    //! по сути вызываемый метод, можно было заменой одной строки)
    //! \param buffer - Буфер содержащий данные для сортировки
    //! \param size - сколько элементов из буфера необходимо сортировать (для случаев, когда размер данных меньше буфера)
    void static sort (std::vector <unsigned int> &buffer, unsigned int size);

    //! \brief Метод реализующий быструю сортировку (quickSort)
    //! \param buffer - Буфер содержащий данные для сортировки
    //! \param start - Индекс первого сортируемого элемента в буфере
    //! \param end - Индекс последнего сортируемого элемента в буфере
    void static quickSort (std::vector <unsigned int> &buffer, int start, int end);
};

#endif // SORT_H
