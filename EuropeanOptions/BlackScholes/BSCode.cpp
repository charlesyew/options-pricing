#define _USE_MATH_DEFINES

#include "BlackScholes.hpp"

#include <cassert>
#include <cfloat>
#include <cmath>
#include <cstdlib>
#include <iostream>

using namespace std;

BSEuropeanOption::BSEuropeanOption() {  //Initialize Constructor
    this->strikePrice = 50;
    this->spotPrice = 49;
    this->interestRate = 0.05;
    this->dividendRate = 0; 
    this->volatility = 0.20;
    this->maturityDate = 0.3846;
    this->purchaseDate = 0;
}

BSEuropeanOption::~BSEuropeanOption() {} //Initialize Destructor

double BSEuropeanOption::phi(double x) {
    // constants
    double a1 = 0.254829592;
    double a2 = -0.284496736;
    double a3 = 1.421413741;
    double a4 = -1.453152027;
    double a5 = 1.061405429;
    double p = 0.3275911;

    // Save the sign of x
    int sign = 1;
    if (x < 0)
        sign = -1;
    x = fabs(x) / sqrt(2.0);

    // A&S formula 7.1.26
    double t = 1.0 / (1.0 + p * x);
    double y = 1.0 - (((((a5 * t + a4) * t) + a3) * t + a2) * t + a1) * t * exp(-x * x);

    return 0.5 * (1.0 + sign * y);
}

void BSEuropeanOption::info() {
    cout << "Option Parameters: " << endl;
    cout << "S: " << spotPrice << "; K: " << strikePrice << "; r: " << interestRate << "; sigma: " << volatility << "; T: " << maturityDate << "; t: " << purchaseDate << endl;
}

double BSEuropeanOption::optionDuration() const {
    return maturityDate - purchaseDate;
}

double BSEuropeanOption::d1() {
    return (log(spotPrice / strikePrice) + (interestRate - dividendRate + pow(volatility, 2) / 2) * (optionDuration())) / (volatility * sqrt(optionDuration()));
}


double BSEuropeanOption::d2() {
    return (log(spotPrice / strikePrice) + (interestRate - dividendRate - pow(volatility, 2) / 2) * (optionDuration())) / (volatility * sqrt(optionDuration()));
}

double BSEuropeanOption::CallPrice() {
    return spotPrice * exp(-dividendRate * optionDuration()) * BSEuropeanOption::phi(d1()) - strikePrice * exp(-interestRate * optionDuration()) * BSEuropeanOption::phi(d2());
}

double BSEuropeanOption::PutPrice() {
    return strikePrice * exp(-interestRate * optionDuration()) * BSEuropeanOption::phi(-d2()) - spotPrice * exp(-dividendRate * optionDuration()) * BSEuropeanOption::phi(-d1());
}

double BSEuropeanOption::CallDelta() {
    return exp(-dividendRate * optionDuration()) * BSEuropeanOption::phi(d1());
}

double BSEuropeanOption::PutDelta() {
    return -exp(-dividendRate * optionDuration()) * BSEuropeanOption::phi(-d1());
}

double BSEuropeanOption::CallGamma() {
    return (exp(-dividendRate * optionDuration()) * exp(-pow(d1(), 2) / 2)) / (spotPrice * volatility * sqrt(optionDuration()) * sqrt(2 * M_PI));
}

double BSEuropeanOption::PutGamma() {
    return BSEuropeanOption::CallGamma();
}

double BSEuropeanOption::CallVega() {
    return (strikePrice * exp(-dividendRate * optionDuration()) * exp(-pow(d1(), 2) / 2) * sqrt(optionDuration())) / sqrt(2 * M_PI);
}

double BSEuropeanOption::PutVega() {
    return BSEuropeanOption::CallVega();
}

double BSEuropeanOption::CallTheta() {
    return -(strikePrice * volatility * exp(-dividendRate * optionDuration()) * exp(-pow(d1(), 2) / 2)) / 2 * sqrt(2 * M_PI * optionDuration()) + dividendRate * spotPrice * exp(-dividendRate * optionDuration()) * BSEuropeanOption::phi(d1()) - interestRate * strikePrice * exp(-interestRate * optionDuration()) * BSEuropeanOption::phi(d2());
}

double BSEuropeanOption::PutTheta() {
    return -(strikePrice * volatility * exp(-dividendRate * optionDuration()) * exp(-pow(d1(), 2) / 2)) / 2 * sqrt(2 * M_PI * optionDuration()) - dividendRate * spotPrice * exp(-dividendRate * optionDuration()) * BSEuropeanOption::phi(d1()) + interestRate * strikePrice * exp(-interestRate * optionDuration()) * BSEuropeanOption::phi(d2());
}

double BSEuropeanOption::CallRho() {
    return strikePrice * optionDuration() * exp(-interestRate * optionDuration()) * BSEuropeanOption::phi(d2());
}

double BSEuropeanOption::PutRho() {
    return -strikePrice * optionDuration() * exp(-interestRate * optionDuration()) * BSEuropeanOption::phi(-d2());
}

double BSEuropeanOption::impliedVolatility() {
    return BSEuropeanOption::phi(d1());
}

double BSEuropeanOption::pExpireITM() {
    return BSEuropeanOption::phi(d1());
}
