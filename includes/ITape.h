#ifndef ITAPE_H
#define ITAPE_H

//! \brief Интерфейсный класс устройства хранения данных типа лента
class ITape
{
public:

    enum ErrorCode
    {
        EndOfTape,
        BeginOfTape,
        Success,
        EmptyCell,
    };

    //! \brief Конструктор
    ITape () {};
    //! \brief Деструктор
    virtual ~ITape () {}

    //! \brief Метод передвижения магнитной головки на ячейку вперед
    virtual ErrorCode moveForward () = 0;
    //! \brief Метод передвижения магнитной головки на ячейку назад
    virtual ErrorCode moveBack () = 0;

    //! \brief Метод передвижения магнитной головки в начало ленты
    virtual bool rewindToBegin () = 0;
    //! \brief Метод передвижения магнитной головки в конец ленты
    virtual bool rewindToEnd () = 0;


    //! \brief Чтение данных из текущей позиции
    virtual ErrorCode read (unsigned int &target) = 0;
    //! \brief Запись данных в текущую позицию
    virtual ErrorCode write (unsigned int value) = 0;
};

#endif // ITAPE_H
