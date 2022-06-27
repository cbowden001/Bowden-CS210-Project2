#include "Banking.h"
#include <iostream>

using namespace std;

/**
 * Constructor
 */
Banking::Banking(double investment, double deposit, double interest, unsigned int years) {
    m_investment = investment;
    m_deposit = deposit;
    m_interest = interest;
    m_years = years;
}

/**
 * Accessors and Mutators
 */
double Banking::getInvestment() {
    return m_investment;
}

double Banking::getDeposit() {
    return m_deposit;
}

double Banking::getInterest() {
    return m_interest;
}

unsigned int Banking::getYears() {
    return m_years;
}

void Banking::setInvestment(double investment) {
    m_investment = investment;
}

void Banking::setDeposit(double deposit) {
    m_deposit = deposit;
}

void Banking::setInterest(double interest) {
    m_interest = interest;
}

void Banking::setYears(unsigned int years) {
    m_years = years;
}
