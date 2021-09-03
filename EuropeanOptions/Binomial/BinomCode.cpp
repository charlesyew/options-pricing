#define _USE_MATH_DEFINES

#include "Binomial.hpp"
#include "BlackScholes.hpp"

#include <iostream>
#include <cassert>
#include <cfloat>
#include <cmath>
#include <vector>

using namespace std;

BinomEuropeanOption::BinomEuropeanOption(int num) { //Initialize Constructor
    this->strikePrice = 50;
    this->spotPrice = 50;
    this->interestRate = 0.06;
    this->volatility = 0.25;
    this->maturityDate = 5;
    this->purchaseDate = 0;
    this->numIntervals = num;
}

BinomEuropeanOption::~BinomEuropeanOption() {} //Initialize Destructor

void BinomEuropeanOption::info() {
    cout << "Option Parameters: " << endl;
    cout << "S: " << spotPrice << "; K: " << strikePrice << "; r: " << interestRate << "; sigma: " << volatility << "; T: " << maturityDate << "; t: " << purchaseDate << endl;
}

int BinomEuropeanOption::optionDuration() const {
    return maturityDate - purchaseDate;
}

double BinomEuropeanOption::CallPrice() {
    return 0;
}

double BinomEuropeanOption::PutPrice() {
    return 0;
}

double BinomEuropeanOption::CallPrice_BS() {
    BSEuropeanOption BScallOption3;
    //BScallOption3.strikePrice = 50;
    //BScallOption3.spotPrice = 50;
    //BScallOption3.interestRate = 0.06;
    //BScallOption3.dividendRate = 0;
    //BScallOption3.volatility = 0.25;
    //BScallOption3.maturityDate = 5;
    //BScallOption3.purchaseDate = 0;
    return BScallOption3.CallPrice();
}

OptionPriceCRR::OptionPriceCRR(int num) : BinomEuropeanOption(num=1000) {
    double T = optionDuration(); // (T - t) years
    double d_T = T / numIntervals;

    this->jumpUp = exp(volatility * sqrt(d_T));
    this->jumpDown = 1.0 / jumpUp;
    this->jumpProbability = (exp(interestRate * d_T) - jumpDown) / (jumpUp - jumpDown);
}

OptionPriceCRR::~OptionPriceCRR() {}

double OptionPriceCRR::CallPrice() {
    double T = optionDuration(); // (T - t) years
    double d_T = T / numIntervals;

    //forward induction 
    vector<vector<double>> stockTree(numIntervals+1, vector<double>(numIntervals+1));
    for (int i = 0; i <= numIntervals; i++) {
        for (int j = 0; j <= i; j++) {
            stockTree[i][j] = spotPrice * pow(jumpUp, j) * pow(jumpDown, i-j) ;
        }
    }
    //calculate option value at last node
    vector<vector<double>> valueTree(numIntervals + 1, vector<double>(numIntervals + 1));
    for (int j = 0; j <= numIntervals; j++) {
        valueTree[numIntervals][j] = max(stockTree[numIntervals][j] - strikePrice, 0.);
    }

    //backward induction 
    for (int i = numIntervals - 1; i >= 0; i--) {
        for (int j = 0; j <= i; j++) {
            valueTree[i][j] = exp(- interestRate * d_T) * (jumpProbability * valueTree[i+1][j+1] + (1- jumpProbability)*valueTree[i+1][j]);
        }
    }

    double price = valueTree[0][0]; // retrieve the first element of the list
    return price ;
}

double OptionPriceCRR::PutPrice() {
    return 0;
}

OptionPriceJR::OptionPriceJR(int num) : BinomEuropeanOption(num=1000) {
    double T = optionDuration(); // (T - t) years
    double d_T = T / numIntervals;

    this -> jumpUp = exp(volatility * sqrt(d_T));
    this -> jumpDown = 1.0 / jumpUp;
    this -> jumpProbability = 0.5;
}
OptionPriceJR::~OptionPriceJR(){}

double OptionPriceJR::CallPrice() {
    double T = optionDuration(); // (T - t) years
    double d_T = T / numIntervals;

    //forward induction 
    vector<vector<double>> stockTree(numIntervals + 1, vector<double>(numIntervals + 1));
    for (int i = 0; i <= numIntervals; i++) {
        for (int j = 0; j <= i; j++) {
            stockTree[i][j] = spotPrice * pow(jumpUp, j) * pow(jumpDown, i - j);
        }
    }
    //calculate option value at last node
    vector<vector<double>> valueTree(numIntervals + 1, vector<double>(numIntervals + 1));
    for (int j = 0; j <= numIntervals; j++) {
        valueTree[numIntervals][j] = max(stockTree[numIntervals][j] - strikePrice, 0.);
    }

    //backward induction 
    for (int i = numIntervals - 1; i >= 0; i--) {
        for (int j = 0; j <= i; j++) {
            valueTree[i][j] = exp(-interestRate * d_T) * (jumpProbability * valueTree[i + 1][j + 1] + (1 - jumpProbability) * valueTree[i + 1][j]);
        }
    }

    double price = valueTree[0][0]; // retrieve the first element of the list

    return price;
}

double OptionPriceJR::PutPrice() {
    return 0;
}

