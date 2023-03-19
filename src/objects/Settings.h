#ifndef SETTINGS_H
#define SETTINGS_H

#include <string>

class Settings
{
public:
    static bool valid ();
    static int N ();
    static int rewindDelay ();
    static int moveDelay ();
    static int readDelay ();
    static int writeDelay ();
    static void readFromFile (std::string fileName);

private:
    static inline bool valid_ = false;
    static inline int n_ = -1;
    static inline int rewindDelay_ = -1;
    static inline int moveDelay_ = -1;
    static inline int readDelay_ = -1;
    static inline int writeDelay_ = -1;
};

#endif // SETTINGS_H
