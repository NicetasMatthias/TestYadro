#ifndef SETTINGS_H
#define SETTINGS_H


class Settings
{
public:
    Settings();

    static bool valid ();

    static int N ();
    static int rewindDelay ();
    static int moveDelay ();

private:
    static bool valid_;
    static int n_;
    void setValid(bool value);
};

#endif // SETTINGS_H
