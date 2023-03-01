#ifndef ITAPE_H
#define ITAPE_H

//! \brief Интерфейсный класс устройства хранения данных типа лента
class ITape
{
public:
    //! \brief Конструктор
    ITape () {};
    //! \brief Деструктор
    virtual ~ITape () {}

    //! \brief Метод передвижения магнитной головки вперед
    virtual bool moveForward () = 0;
    //! \brief Метод передвижения магнитной головки назад
    virtual bool moveBack () = 0;

    //! \brief Чтение данных из текущей позиции
    virtual bool read (unsigned int &target) = 0;
    //! \brief Запись данных в текущую позицию
    virtual bool write (unsigned int value) = 0;
};

#endif // ITAPE_H
