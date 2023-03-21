#ifndef SETTINGS_H
#define SETTINGS_H

#include <string>

//! \brief Класс параметров выполнения алгоритма
class Settings
{
public:
    //! \brief Валидность настроек
    static bool valid ();
    //! \brief Размер буфера
    static int N ();
    //! \brief Задержка перемотки в начало\конец
    static int rewindDelay ();
    //! \brief Задержка перемещения на ячейку
    static int moveDelay ();
    //! \brief Задержка чтения
    static int readDelay ();
    //! \brief Задержка записи
    static int writeDelay ();
    //! \brief Метод чтения настроек с файла
    static void readFromFile (std::string fileName);

private:
    //! \brief Валидность настроек
    static inline bool valid_ = false;
    //! \brief Размер буфера
    static inline int n_ = -1;
    //! \brief Задержка перемотки в начало\конец
    static inline int rewindDelay_ = -1;
    //! \brief Задержка перемещения на ячейку
    static inline int moveDelay_ = -1;
    //! \brief Задержка чтения
    static inline int readDelay_ = -1;
    //! \brief Задержка записи
    static inline int writeDelay_ = -1;
};

#endif // SETTINGS_H
