#include <iostream>
#include <windows.h>
#include <string>
#include <ctime>

using namespace std;

class TimeC
{

public:
    TimeC() : year(2020)
    {
        const time_t t = time(NULL);
        tm *gtm = localtime(&t);
        month = gtm->tm_mon + 1;
        day = gtm->tm_mday;
        hour = gtm->tm_hour;
        minute = gtm->tm_min;
        second = gtm->tm_sec;

        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_GREEN | FOREGROUND_INTENSITY);
    }

    TimeC operator++()
    {
        ++second;
        if (second >= 60)
        {
            second = 0;
            ++minute;
            if (minute >= 60)
            {
                minute = 0;
                ++hour;
                if (hour >= 24)
                {
                    hour = 0;
                    ++day;
                    if (day > getDaysInMonth(year, month))
                    {
                        day = 1;
                        ++month;
                        if (month > 12)
                        {
                            month = 1;
                            ++year;
                        }
                    }
                }
            }
        }

        return *this;
    }

    void display()
    {
        string m = to_string(month);
        string d = to_string(day);
        string h = to_string(hour);
        string n = to_string(minute);
        string s = to_string(second);

        if (month < 10)
        {
            m = "0" + m;
        }

        if (day < 10)
        {
            d = "0" + d;
        }

        if (hour < 10)
        {
            h = "0" + h;
        }

        if (minute < 10)
        {
            n = "0" + n;
        }

        if (second < 10)
        {
            s = "0" + s;
        }

        printf("系统时间：%4d/%s/%s %s:%s:%s\r", year, m.c_str(), d.c_str(), h.c_str(), n.c_str(), s.c_str());
    }

private:
    int year, month, day, hour, minute, second;
    int getDaysInMonth(int y, int m)
    {
        int d, day[] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};

        if (2 == m)
        {
            d = (((0 == y % 4) && (0 != y % 100) || (0 == y % 400)) ? 29 : 28);
        }
        else
        {
            d = day[m - 1];
        }

        return d;
    }
};

int main()
{
    TimeC t;
    do
    {
        ++t;
        t.display();
        Sleep(1000);
    } while (true);

    return 0;
}
