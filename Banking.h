#ifndef BANKING_H
#define BANKING_H

#include <string>
using namespace std;

class Banking {

public:
    //FIXME: add t_ 
    Banking(double investment = 0.0, double deposit = 0.0, double interest = 0.0, unsigned int years = 0);

    double getInvestment();
    double getDeposit();
    double getInterest();
    unsigned int getYears();

    void setInvestment(double);
    void setDeposit(double);
    void setInterest(double);
    void setYears(unsigned int);

private:
    double m_investment;
    double m_deposit;
    double m_interest;
    unsigned int m_years;
};

#endif