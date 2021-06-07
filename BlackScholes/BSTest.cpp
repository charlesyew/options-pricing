// BlackScholes.cpp : This file contains the 'main' function. Program execution begins and ends there.
//
#define _USE_MATH_DEFINES

#include "BlackScholes.h"
#include "cdf.h"

#include <iostream>

using namespace std;

int main()
{
    BSEuropeanOption callOption;
    callOption.strikePrice = 100;
    callOption.spotPrice = 128;
    callOption.interestRate = 0.12;
    callOption.dividendRate = 0.08;
    callOption.volatility = 0.8;
    callOption.maturityDate = 0.5;
    callOption.purchaseDate = 0.1;
    cout << "Call Option Parameters: " << endl;
    cout << "S: " << callOption.spotPrice << "; K: " << callOption.strikePrice << "; r: " << callOption.interestRate << "; q: " << callOption.dividendRate << "; sigma: " << callOption.volatility << "; T: " << callOption.maturityDate << "; t: " << callOption.purchaseDate << endl;
    cout << "Call Option Price: " << callOption.CallPrice() << endl;
    cout << "Call Option Greeks: " << endl;
    cout << "Delta: " << callOption.CallDelta() << endl;
    cout << "Gamma: " << callOption.CallGamma() << endl;
    cout << "Vega: " << callOption.CallVega() << endl;
    cout << "Theta: " << callOption.CallTheta() << endl;
    cout << "Rho: " << callOption.CallRho() << endl;

    BSEuropeanOption putOption;
    putOption.strikePrice = 100;
    putOption.spotPrice = 128;
    putOption.interestRate = 0.12;
    putOption.dividendRate = 0.08;
    putOption.volatility = 0.8;
    putOption.maturityDate = 0.5;
    putOption.purchaseDate = 0.1;
    cout << "Put Option Parameters: " << endl;
    cout << "S: " << putOption.spotPrice << "; K: " << putOption.strikePrice << "; r: " << putOption.interestRate << "; q: " << putOption.dividendRate << "; sigma: " << putOption.volatility << "; T: " << putOption.maturityDate << "; t: " << putOption.purchaseDate << endl;
    cout << "Put Option Price: " << putOption.PutPrice() << endl;
    cout << "Put Option Greeks: " << endl;
    cout << "Delta: " << putOption.PutDelta() << endl;
    cout << "Gamma: " << putOption.PutGamma() << endl;
    cout << "Vega: " << putOption.PutVega() << endl;
    cout << "Theta: " << putOption.PutTheta() << endl;
    cout << "Rho: " << putOption.PutRho() << endl;

    system("pause>0");
}
