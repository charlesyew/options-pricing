#define _USE_MATH_DEFINES

#include "MonteCarlo.hpp"
#include "BSFormula.hpp"

#include <cassert>
#include <cfloat>
#include <cmath>
#include <cstdlib>
#include <limits>
#include <random>
#include <utility>
#include <algorithm>  

using namespace std;

double gaussianRV() { // Doesn't work
    double x = 0.0;
    double y = 0.0;
    double euclid_sq = 0.0;

    // Continue generating two uniform random variables
    // until the square of their "euclidean distance" 
    // is less than unity
    do {
        x = 2.0 * rand() / static_cast<double>(RAND_MAX) - 1;
        y = 2.0 * rand() / static_cast<double>(RAND_MAX) - 1;
        euclid_sq = x * x + y * y;
    } while (euclid_sq >= 1.0);

    return x * sqrt(-2 * log(euclid_sq) / euclid_sq);
}

double rand_normal(double mean, double stddev) {
    std::random_device rd; // random device class instance, source of 'true' randomness for initializing random seed    
    std::mt19937 eng(rd()); // Mersenne twister PRNG, initialized with seed from previous random device instance
    std::normal_distribution<double> normal(mean, stddev); // instance of class std::normal_distribution with specific mean and stddev
    double Z = normal(eng); // get random number with normal distribution using eng as random source
    return Z;
}

int MCEuropeanOption::optionDuration() const {
    return maturityDate - purchaseDate;
}

double MCEuropeanOption::CallPrice() { // Boyle (1977)
    const int m = 10000; // # of trials
    const int n = 200; 
    const double T = optionDuration(); // (T - t) years
    double d_T = T / n;

    double Q = 0.0; 
    

    for (int i = 0; i < m; ++i) {
        vector<double> S;
        S.push_back(spotPrice); 
        for (int j = 1; j < n; ++j) {
            double Z = rand_normal(0, 1);
            double S_t = S.back() * exp((interestRate - pow(volatility, 2) / 2) * d_T + volatility * Z * sqrt(d_T));
            S.push_back(S_t);
            //if (S_t > dividendPayment) {
            //    S.push_back(S_t - dividendPayment);
            //}
            //else {
            //    break;
            //}
            
        }
        double payoff = S.back() - strikePrice;
        Q += std::max(payoff,0.0);
    }

    double MC_S = exp(-interestRate * T) * Q / m;

    return MC_S;
}

double MCEuropeanOption::CallPrice2() {
    int m = 10000; // # of trials
    double T = optionDuration(); // (T - t) years
    double S_adj = spotPrice * exp((interestRate - pow(volatility, 2) / 2) * T);
    double S_T = 0.0;
    double payoff_sum = 0.0;

    for (int i = 0; i < m; ++i) {
        double Z = rand_normal(0,1);
        S_T =  S_adj * exp( volatility * Z * sqrt(T));
        payoff_sum += std::max(S_T - strikePrice, 0.0);
    }

    double MC_S = exp(-interestRate * T) * (payoff_sum / static_cast<double>(m));
    return MC_S;
}

double MCEuropeanOption::CallPrice_Var() {
    BSEuropeanOption BScallOption;
    BScallOption.strikePrice = 50;
    BScallOption.spotPrice = 50;
    BScallOption.interestRate = 0.06;
    BScallOption.dividendRate = 0;
    BScallOption.volatility = sqrt(0.025);
    BScallOption.maturityDate = 5;
    BScallOption.purchaseDate = 0;
    double BS_S = BScallOption.CallPrice();

    const int m = 10000; // # of trials
    const int n = 1000;
    const double T = optionDuration(); // (T - t) days
    const double d_T = T / n;

    double Q = 0.0;
    double q = 0.0;

    for (int i = 0; i < m; ++i) {
        vector<double> S;
        vector<double> s; 
        S.push_back(spotPrice);
        s.push_back(spotPrice);
        for (int j = 1; j < n; ++j) {
            double Z = rand_normal(0, 1);
            double S_t = S.back() * exp((interestRate - pow(volatility, 2) / 2) * d_T + volatility * Z * sqrt(d_T));
            S.push_back(S_t);
            //if (S_t > dividendPayment) {
            //    S.push_back(S_t - dividendPayment);
            //}
            //else {
            //    break;
            //}
            double s_t = s.back() * exp((interestRate - pow(volatility, 2) / 2) * d_T + volatility * Z * sqrt(d_T));
            s.push_back(s_t);
        }

        double Payoff = S.back() - strikePrice;
        if (Payoff < 0.0) Payoff = 0.0;
        Q += Payoff;

        double payoff = s.back() - strikePrice; 
        if (payoff < 0.0) payoff = 0.0;
        q += payoff;
    }
    double MC_S = exp(-interestRate * n) * Q / m;
    double MC_s = exp(-interestRate * n) * q / m;
    return BS_S + MC_S - MC_s;
}

double MCEuropeanOption::CallPrice_BS() {
    BSEuropeanOption BScallOption2;
    BScallOption2.strikePrice = 50;
    BScallOption2.spotPrice = 50;
    BScallOption2.interestRate = 0.06;
    BScallOption2.dividendRate = 0;
    BScallOption2.volatility = 0.25;
    BScallOption2.maturityDate = 5;
    BScallOption2.purchaseDate = 0;
    double BS_s = BScallOption2.CallPrice();

    return BS_s ;
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