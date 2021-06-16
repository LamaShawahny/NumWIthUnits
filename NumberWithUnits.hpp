#include <iostream>
#include <map>
#include <sstream>
using namespace std;

namespace ariel {
    class NumberWithUnits {
    private:
        double V;
        string U;
        
        static bool map(const NumberWithUnits& NUM1, const NumberWithUnits& NUM2);

    public:
        NumberWithUnits(double a, const string& u);
        static void read_units(ifstream &FILE);

        friend NumberWithUnits operator-(const NumberWithUnits& NUM);
        friend NumberWithUnits operator+(const NumberWithUnits& NUM);
        friend NumberWithUnits operator+(const NumberWithUnits& NUM1, const NumberWithUnits& NUM2);
        friend NumberWithUnits operator-(const NumberWithUnits& NUM1, const NumberWithUnits& NUM2);
        NumberWithUnits& operator++();
        NumberWithUnits operator++(int);
        NumberWithUnits& operator--();
        NumberWithUnits operator--(int);
        NumberWithUnits& operator+=(const NumberWithUnits& NUM2);
        NumberWithUnits& operator-=(const NumberWithUnits& NUM2);
        friend bool operator<(const NumberWithUnits& NUM1, const NumberWithUnits& NUM2);
        friend bool operator>(const NumberWithUnits& NUM1, const NumberWithUnits& NUM2);
        friend bool operator>=(const NumberWithUnits& NUM1, const NumberWithUnits& NUM2);
        friend bool operator<=(const NumberWithUnits& NUM1, const NumberWithUnits& NUM2);
        friend bool operator==(const NumberWithUnits& NUM1, const NumberWithUnits& NUM2);
        friend bool operator!=(const NumberWithUnits& NUM1, const NumberWithUnits& NUM2);
        friend NumberWithUnits operator*(double d, const NumberWithUnits& a);
        friend NumberWithUnits operator*(const NumberWithUnits& a, double d);
        friend ostream& operator<<(ostream& os, const NumberWithUnits& a);
        friend istream& operator>>(istream& s, NumberWithUnits& n);
    };
}