#define _USE_MATH_DEFINES

#include "Binomial.hpp"
#include "BlackScholes/cdf.hpp"
#include "BlackScholes/BlackScholes.hpp"

#include <iostream>
#include <cassert>
#include <cfloat>
#include <cmath>

using namespace std;

BinomEuropeanOption::BinomEuropeanOption(int num) {
    this->strikePrice = 50;
    this->spotPrice = 50;
    this->interestRate = 0.06;
    this->volatility = 0.25;
    this->maturityDate = 5;
    this->purchaseDate = 0;
    this->numIntervals = num;

}//Initialize Constructor

BinomEuropeanOption::~BinomEuropeanOption() {} //Initialize Destructor

void BinomEuropeanOption::info() {
    cout << "Option Parameters: " << endl;
    cout << "S: " << spotPrice << "; K: " << strikePrice << "; r: " << interestRate << "; sigma: " << volatility << "; T: " << maturityDate << "; t: " << purchaseDate << endl;
}

int BinomEuropeanOption::optionDuration() const {
    return maturityDate - purchaseDate;
}

OptionPriceCRR::OptionPriceCRR(int num) {
    numIntervals = num;
    double R1 = (interestRate - 0.5 * spotPrice * spotPrice) * strikePrice;
    double R2 = spotPrice * sqrt(strikePrice);

    this -> jumpUp = exp(R1 + R2);
    this -> jumpDown = exp(R1 - R2);
    this -> jumpProbability = 0.5;
}

OptionPriceCRR::~OptionPriceCRR() {}

double OptionPriceCRR::CallPrice() {
    double discounting = exp(-interestRate * strikePrice);
    return 0;
}

double OptionPriceCRR::PutPrice() {
    return 0;
}

OptionPriceJR::OptionPriceJR(int num){
    numIntervals = num;
    double T = optionDuration(); // (T - t) years
    double d_T = T / numIntervals;

    this -> jumpUp = exp(volatility * sqrt(d_T));
    this -> jumpDown = 1.0 / jumpUp;
    this -> jumpProbability = 0.5;
}
OptionPriceJR::~OptionPriceJR(){}

double OptionPriceJR::CallPrice() {
    double T = optionDuration(); // (T - t) years

    //forward induction 
    double* sArr = new double[numIntervals + 1];
    for (int i = 0; i <= numIntervals; ++i) {
        sArr[i] = spotPrice * pow(jumpUp, 2 * i - numIntervals) - strikePrice;
        if (sArr[i] < 0) sArr[i] = 0;
    }

    //backward induction 
    for (int j = numIntervals; j >= 0; --j) {
        for (int i = 0; i <= j; ++i) {
            sArr[i] = jumpProbability * sArr[i] + (1 - jumpProbability) * sArr[i + 1];
        }
    }
       
    double price = sArr[0]; // retrieve the first element of the list
    delete[] sArr;
    price *= exp(-interestRate * T);

    return price;
}

double OptionPriceJR::PutPrice() {
    return 0;
}

double BinomEuropeanOption::CallPrice_BS() {
    BSEuropeanOption BScallOption2;
    BScallOption2.strikePrice = 50;
    BScallOption2.spotPrice = 50;
    BScallOption2.interestRate = 0.06;
    BScallOption2.dividendRate = 0;
    BScallOption2.volatility = 0.25;
    BScallOption2.maturityDate = 5;
    BScallOption2.purchaseDate = 0;
    double BS_s = BScallOption2.CallPrice();
    return BS_s;
}