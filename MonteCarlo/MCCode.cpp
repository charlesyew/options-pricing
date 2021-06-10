#define _USE_MATH_DEFINES

#include "MonteCarlo.hpp"
#include "BlackScholes/cdf.hpp"

#include <cassert>
#include <cfloat>
#include <cmath>
#include <cstdlib>
#include <limits>
#include <random>
#include <utility>

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

std::pair<double, double> gaussianRV(double mu, double sigma)
{
    constexpr double epsilon = std::numeric_limits<double>::epsilon();
    constexpr double two_pi = 2.0 * M_PI;

    //initialize the random uniform number generator (runif) in a range 0 to 1
    static std::mt19937 rng(std::random_device{}()); // Standard mersenne_twister_engine seeded with rd()
    static std::uniform_real_distribution<> runif(0.0, 1.0);

    //create two random numbers, make sure u1 is greater than epsilon
    double u1, u2;
    do
    {
        u1 = runif(rng);
        u2 = runif(rng);
    } while (u1 <= epsilon);

    //compute z0 and z1
    auto mag = sigma * sqrt(-2.0 * log(u1));
    auto z0 = mag * cos(two_pi * u2) + mu;
    auto z1 = mag * sin(two_pi * u2) + mu;

    return std::make_pair(z0, z1);
}

int MCEuropeanOption::optionDuration() const {
    return maturityDate - purchaseDate;
}


double MCEuropeanOption::CallPrice() { // Boyle (1977)
    const int m = 10000; // # of trials
    const int n = optionDuration(); // (T - t) days

    double Q = 0.0; 
    

    for (int i = 0; i < m; ++i) {
        vector<int> S;
        S.push_back(spotPrice); 
        for (int j = 1; j < n; ++j) {
            double S_t = S.back() * exp(interestRate - pow(volatility, 2) / 2 + volatility * gaussianRV(0, 1).first);
            S.push_back(S_t);
        }
        double payoff = S.back() - strikePrice;
        if (payoff < 0.0) payoff = 0.0;

        Q += payoff;
    }

    return exp(-interestRate * optionDuration()) * Q / m;
}

void MCEuropeanOption::init() {
    //Initialize all default values 
    double strikePrice = 10;
    double spotPrice = 12.86;
    double interestRate = 0.08;
    double volatility = 3.2;
    double maturityDate = 3.5;
    double purchaseDate = 0.2;
}

void MCEuropeanOption::copy(const MCEuropeanOption& o2)
{
    strikePrice = o2.strikePrice;
    spotPrice = o2.spotPrice;
    interestRate = o2.interestRate;
    volatility = o2.volatility;
    maturityDate = o2.maturityDate;
    purchaseDate = o2.purchaseDate;
}

MCEuropeanOption::MCEuropeanOption() //Initiate Constructor
{
    init();
}

MCEuropeanOption::MCEuropeanOption(const MCEuropeanOption& o2)
{ // Copy constructor
    copy(o2);
}

MCEuropeanOption& MCEuropeanOption::operator = (const MCEuropeanOption& opt2)
{ // Assignment operator (deep copy)
    if (this == &opt2) return *this;
    copy(opt2);
    return *this;
}

MCEuropeanOption::~MCEuropeanOption() {} //Initiate Destructor