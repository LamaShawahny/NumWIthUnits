#include "NumberWithUnits.hpp"
#include <iostream>
#include <map>
#include <fstream>   
#include <sstream>   
#include <algorithm> 
using namespace std;

const double epsilon = 0.001;
static map<string,map<string,double>> UnitsContaner;

namespace ariel
{
    NumberWithUnits::NumberWithUnits(double val, const string& unit)
    {
        if (UnitsContaner.count(unit)==0)
        {
            throw
            invalid_argument("Illegal units!");
        }
        else{
             V = val;
            U = unit;
        }
    };

    void convert(string u1,string u2)
    {
        for (auto &map : UnitsContaner[u2])
        {
            double val = UnitsContaner[u1][u2] * map.second;
            UnitsContaner[u1][map.first] = val;
            UnitsContaner[map.first][u1] = 1 / val;
        }
    }

    void NumberWithUnits::read_units(std::ifstream &FILE)
    {
        string u1, u2, c;
        double v1=0, v2=0;

        while (FILE >> v1 >> u1 >> c >> v2 >> u2)
        {
            UnitsContaner[u1][u2] = v2;
            UnitsContaner[u2][u1] = 1 / v2;
            convert(u1, u2);
            convert(u2, u1);
        }
    }

    NumberWithUnits operator-(const NumberWithUnits &NUM)
    {
        NumberWithUnits N(-NUM.V, NUM.U);
        return N;
    }

    NumberWithUnits operator+(const NumberWithUnits &NUM)
    {
        return NUM;
    }

    NumberWithUnits operator+(const NumberWithUnits &NUM1, const NumberWithUnits &NUM2)
    {
        if (UnitsContaner.count(NUM1.U) != 0 &&UnitsContaner[NUM1.U].count(NUM2.U) != 0)
        {
            return NumberWithUnits(NUM1.V + NUM2.V * UnitsContaner[NUM2.U][NUM1.U], NUM1.U);
        }
        throw invalid_argument("!!!!");
    }

    NumberWithUnits operator-(const NumberWithUnits &NUM1, const NumberWithUnits &NUM2)
    {
      
        if (UnitsContaner.count(NUM1.U) != 0 &&UnitsContaner[NUM1.U].count(NUM2.U) != 0)
        {
            return NumberWithUnits(NUM1.V - NUM2.V * UnitsContaner[NUM2.U][NUM1.U], NUM1.U);
        }
        throw invalid_argument("!!!!");
    }

    NumberWithUnits &NumberWithUnits::operator+=(const NumberWithUnits &NUM2)
    {
        if (UnitsContaner.count(this->U) != 0 &&UnitsContaner[this->U].count(NUM2.U) != 0)
        {
            this->V += NUM2.V * UnitsContaner[NUM2.U][this->U];
            return *this;
        }
        throw invalid_argument("!!!!");
    }
    NumberWithUnits &NumberWithUnits::operator-=(const NumberWithUnits &NUM2)
    {
        if (UnitsContaner.count(this->U) != 0 &&UnitsContaner[this->U].count(NUM2.U) != 0)
        {
             this->V -= NUM2.V * UnitsContaner[NUM2.U][this->U];
            return *this;
        }
        throw invalid_argument("not same unit");
    }

    bool operator<(const NumberWithUnits &NUM1, const NumberWithUnits &NUM2)
    {
        if (!(UnitsContaner.count(NUM1.U) != 0 &&UnitsContaner[NUM1.U].count(NUM2.U) != 0))
        {
            throw invalid_argument("not same unit");
        }
        double NUM2_new_amount = NUM2.V * UnitsContaner[NUM2.U][NUM1.U];
        return (NUM1.V < NUM2_new_amount);
    }

    bool operator>(const NumberWithUnits &NUM1, const NumberWithUnits &NUM2)
    {
        return NUM2 < NUM1;
    }

    bool operator>=(const NumberWithUnits &NUM1, const NumberWithUnits &NUM2)
    {
        return !(NUM1 < NUM2);
    }

    bool operator<=(const NumberWithUnits &NUM1, const NumberWithUnits &NUM2)
    {
        return !(NUM2 < NUM1);
    }

    bool operator==(const NumberWithUnits &NUM1, const NumberWithUnits &NUM2)
    {
        if (!(UnitsContaner.count(NUM1.U) != 0 &&UnitsContaner[NUM1.U].count(NUM2.U) != 0))
        {
            throw invalid_argument("!!!");
        }
        double NUM2_new_amount = NUM2.V * UnitsContaner[NUM2.U][NUM1.U];
            return (NUM1.V - NUM2_new_amount <= epsilon &&NUM1.V - NUM2_new_amount>=-1*epsilon);
    }

    bool operator!=(const NumberWithUnits &NUM1, const NumberWithUnits &NUM2)
    {return !(NUM1 == NUM2);}

   
    NumberWithUnits NumberWithUnits::operator++(int) 
    {
        NumberWithUnits th = *this;
        this->V++;
        return th;
    }
    NumberWithUnits &NumberWithUnits::operator++() 
    {
        this->V++;
        return *this;
    }
    NumberWithUnits &NumberWithUnits::operator--() 
    {
        this->V--;
        return *this;
    }
    NumberWithUnits NumberWithUnits::operator--(int) 
    {
        NumberWithUnits th = *this;
        this->V--;
        return th;
    }

    NumberWithUnits operator*(double d, const NumberWithUnits &a)
    {
        return a*d;
    }

    NumberWithUnits operator*(const NumberWithUnits &a, double d)
    {
        NumberWithUnits num{d * a.V, a.U};
        return num;
    }

    ostream &operator<<(ostream &os, const NumberWithUnits &a)
    {
        os << a.V << "[" << a.U << "]";
        return os;
    }

    istream &operator>>(istream &os, NumberWithUnits &n)
    {
        char CH ='a';
        string str;
        double NUM = 0;
        os >> NUM >> CH >> str >> CH;
        if (str.at(str.length() - 1) == ']'){str.pop_back();}
        if(UnitsContaner.count(str) != 0){
            n.V = NUM;
            n.U = str;
            return os;
        }
        throw invalid_argument("!!!!");
    }
}