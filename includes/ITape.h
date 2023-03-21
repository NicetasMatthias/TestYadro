#ifndef ITAPE_H
#define ITAPE_H

#include <memory>

//! \brief Интерфейсный класс устройства хранения данных типа лента
class ITape
{
public:

    using ptr_t = std::shared_ptr <ITape>;
    enum ErrorCode
    {
        EndOfTape,
        BeginOfTape,
        Success,
        EmptyCell,
        InvalidTape,
    };

    //! \brief Конструктор
    ITape () {};
    //! \brief Деструктор
    virtual ~ITape () {};

    //! \brief Метод возвращающий размер ленты
    virtual int size () = 0;

    //! \brief Метод передвижения магнитной головки на ячейку вперед
    virtual ErrorCode moveForward () = 0;

    //! \brief Метод передвижения магнитной головки на ячейку назад
    virtual ErrorCode moveBack () = 0;

    //! \brief Метод передвижения магнитной головки в начало ленты
    virtual ErrorCode rewindToBegin () = 0;

    //! \brief Метод передвижения магнитной головки в конец ленты
    virtual ErrorCode rewindToEnd () = 0;

    //! \brief Чтение данных из текущей позиции
    virtual ErrorCode read (unsigned int &target) = 0;

    //! \brief Запись данных в текущую позицию
    virtual ErrorCode write (unsigned int value) = 0;
};

#endif // ITAPE_H
