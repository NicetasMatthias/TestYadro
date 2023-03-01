#ifndef TAPE_H
#define TAPE_H

#include <ITape.h>
#include <fstream>
#include <string>
#include <memory>
#include <vector>

struct Element
{
    unsigned int data_ {0};
    bool used_ {false};
};


//! \brief Класс реализации интерфейса устройства хранения данных типа лента
//!
class Tape : public ITape
{
public:
    using ptr_t = std::shared_ptr <Tape>;

    //! \brief Конструктор без параметров
    //!     (нельзя использовать в данной реализации, т.к. нужно имя файла)
    Tape ();

    //! \brief Конструктор с параметром std::string
    //! \param filename имя файла используемого в качестве ленты
    Tape (std::string filename);

    //! \brief Деструктор
    ~Tape ();

    //! \brief Метод передвижения магнитной головки вперед
    //! \return bool
    //!     true - удалось передвинуть головку
    //!     false - не удалось передвинуть головку
    bool moveForward () override;

    //! \brief Метод передвижения магнитной головки назад
    //! \return bool
    //!     true - удалось передвинуть головку
    //!     false - не удалось передвинуть головку
    bool moveBack () override;

    //! \brief Чтение данных из текущей позиции
    //! \param target - ссылка на переменную для записи результата
    //! \return bool
    //!     true - данные прочитаны
    //!     false - данные не прочитаны (либо не валидна вся лента, либо в текущей ячейке нет данных)
    bool read (unsigned int &target) override;

    //! \brief Запись данных в текущую позицию
    //! \param value - данные для записи в ячейку
    //! \return bool
    //!     true - данные записаны
    //!     false - данные не записаны (лента не валидна)
    bool write (unsigned int value) override;

    //! \brief Метод определения валидности ленты
    //! \return bool
    //!     true - лента валидна, можно работать
    //!     false - лента не валидна, нельзя работать
    bool valid ();

    //! \brief Статический метод создания пустого объекта класса Tape
    //! \param size - размер "ленты"
    //! \param filename - имя файла хранящего "ленту"
    //! \return std::shared_pointer на объект класса Tape
    static ptr_t makeTape (unsigned int size, std::string filename);

protected:
    //! \brief Метод установки валидности ленты
    //! \param value - устанавливаемое значение
    void setValid (bool value);

    //! \brief Переменная отображающая валидность ленты
    bool valid_ {false};

    std::vector <Element> tapeData_;
    std::string filename_;
    unsigned int currPos_;
};

#endif // TAPE_H
