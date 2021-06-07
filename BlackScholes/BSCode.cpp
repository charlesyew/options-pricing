#define _USE_MATH_DEFINES

#include "BlackScholes.h"
#include "cdf.h"

#include <cassert>
#include <cfloat>
#include <cmath>
#include <cstdlib>

using namespace std;

double cdf::phi(double x) {
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

double BSEuropeanOption::CallPrice() const {
    double optionDuration = maturityDate - purchaseDate;
    double d1 = (log(spotPrice / strikePrice) + (interestRate + pow(volatility, 2)) * (optionDuration)) / volatility * sqrt(optionDuration);
    double d2 = d1 - volatility * sqrt(optionDuration);

    return spotPrice * exp(-dividendRate * optionDuration) * cdf::phi(d1) - strikePrice * exp(-interestRate * optionDuration) * cdf::phi(d2);
}

double BSEuropeanOption::PutPrice() const {
    double optionDuration = maturityDate - purchaseDate;
    double d1 = (log(spotPrice / strikePrice) + (interestRate + pow(volatility, 2)) * (optionDuration)) / volatility * sqrt(optionDuration);
    double d2 = d1 - volatility * sqrt(optionDuration);


    return strikePrice * exp(-interestRate * optionDuration) * cdf::phi(-d2) - spotPrice * exp(-dividendRate * optionDuration) * cdf::phi(-d1);
}

double BSEuropeanOption::CallDelta() const {
    double optionDuration = maturityDate - purchaseDate;
    double d1 = (log(spotPrice / strikePrice) + (interestRate + pow(volatility, 2)) * (optionDuration)) / volatility * sqrt(optionDuration);

    return exp(-dividendRate * optionDuration) * cdf::phi(d1);
}

double BSEuropeanOption::PutDelta() const {
    double optionDuration = maturityDate - purchaseDate;
    double d1 = (log(spotPrice / strikePrice) + (interestRate + pow(volatility, 2)) * (optionDuration)) / volatility * sqrt(optionDuration);

    return -exp(-dividendRate * optionDuration) * cdf::phi(-d1);
}

double BSEuropeanOption::CallGamma() const {
    double optionDuration = maturityDate - purchaseDate;
    double d1 = (log(spotPrice / strikePrice) + (interestRate + pow(volatility, 2)) * (optionDuration)) / volatility * sqrt(optionDuration);

    return (exp(-dividendRate * optionDuration) * exp(-pow(d1, 2) / 2)) / (spotPrice * volatility * sqrt(optionDuration) * sqrt(2 * M_PI));
}

double BSEuropeanOption::PutGamma() const {
    return BSEuropeanOption::CallGamma();
}

double BSEuropeanOption::CallVega() const {
    double optionDuration = maturityDate - purchaseDate;
    double d1 = (log(spotPrice / strikePrice) + (interestRate + pow(volatility, 2)) * (optionDuration)) / volatility * sqrt(optionDuration);

    return (strikePrice * exp(-dividendRate * optionDuration) * exp(-pow(d1, 2) / 2) * sqrt(optionDuration)) / sqrt(2 * M_PI);
}

double BSEuropeanOption::PutVega() const {
    return BSEuropeanOption::CallVega();
}

double BSEuropeanOption::CallTheta() const {
    double optionDuration = maturityDate - purchaseDate;
    double d1 = (log(spotPrice / strikePrice) + (interestRate + pow(volatility, 2)) * (optionDuration)) / volatility * sqrt(optionDuration);
    double d2 = d1 - volatility * sqrt(optionDuration);

    return -(strikePrice * volatility * exp(-dividendRate * optionDuration) * exp(-pow(d1, 2) / 2)) / 2 * sqrt(2 * M_PI * optionDuration) + dividendRate * spotPrice * exp(-dividendRate * optionDuration) * cdf::phi(d1) - interestRate * strikePrice * exp(-interestRate * optionDuration) * cdf::phi(d2);
}

double BSEuropeanOption::PutTheta() const {
    double optionDuration = maturityDate - purchaseDate;
    double d1 = (log(spotPrice / strikePrice) + (interestRate + pow(volatility, 2)) * (optionDuration)) / volatility * sqrt(optionDuration);
    double d2 = d1 - volatility * sqrt(optionDuration);

    return -(strikePrice * volatility * exp(-dividendRate * optionDuration) * exp(-pow(d1, 2) / 2)) / 2 * sqrt(2 * M_PI * optionDuration) - dividendRate * spotPrice * exp(-dividendRate * optionDuration) * cdf::phi(d1) + interestRate * strikePrice * exp(-interestRate * optionDuration) * cdf::phi(d2);
}

double BSEuropeanOption::CallRho() const {
    double optionDuration = maturityDate - purchaseDate;
    double d1 = (log(spotPrice / strikePrice) + (interestRate + pow(volatility, 2)) * (optionDuration)) / volatility * sqrt(optionDuration);
    double d2 = d1 - volatility * sqrt(optionDuration);

    return strikePrice * optionDuration * exp(-interestRate * optionDuration) * cdf::phi(d2);
}

double BSEuropeanOption::PutRho() const {
    double optionDuration = maturityDate - purchaseDate;
    double d1 = (log(spotPrice / strikePrice) + (interestRate + pow(volatility, 2)) * (optionDuration)) / volatility * sqrt(optionDuration);
    double d2 = d1 - volatility * sqrt(optionDuration);

    return -strikePrice * optionDuration * exp(-interestRate * optionDuration) * cdf::phi(-d2);
}

void BSEuropeanOption::init() {
    //Initialize all default values 
    double strikePrice = 10;
    double spotPrice = 12.86;
    double interestRate = 0.08;
    double volatility = 3.2;
    double maturityDate = 3.5;
    double purchaseDate = 0.2;
}

void BSEuropeanOption::copy(const BSEuropeanOption& o2)
{
    strikePrice = o2.strikePrice;
    spotPrice = o2.spotPrice;
    interestRate = o2.interestRate;
    volatility = o2.volatility;
    maturityDate = o2.maturityDate;
    purchaseDate = o2.purchaseDate;
}

BSEuropeanOption::BSEuropeanOption() //Initiate Constructor
{
    init();
}

BSEuropeanOption::BSEuropeanOption(const BSEuropeanOption& o2)
{ // Copy constructor
    copy(o2);
}

BSEuropeanOption& BSEuropeanOption::operator = (const BSEuropeanOption& opt2)
{ // Assignment operator (deep copy)
    if (this == &opt2) return *this;
    copy(opt2);
    return *this;
}

BSEuropeanOption::~BSEuropeanOption() {} //Initiate Destructor
