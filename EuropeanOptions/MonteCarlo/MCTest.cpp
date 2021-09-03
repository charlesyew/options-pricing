// MonteCarlo.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>

#include "MonteCarlo.hpp"
#include "BlackScholes.hpp"


using namespace std;

int main()
{
    MCEuropeanOption callOption;
    callOption.strikePrice = 50;
    callOption.spotPrice = 50;
    callOption.interestRate = 0.06;
    callOption.dividendPayment = 0.25;
    callOption.volatility = 0.25;
    callOption.maturityDate = 5;
    callOption.purchaseDate = 0;
    double S_MC = callOption.CallPrice();
    double S_BS = callOption.CallPrice_BS();
    cout << "Call Option Parameters: " << endl;
    cout << "S: " << callOption.spotPrice << "; K: " << callOption.strikePrice << "; r: " << callOption.interestRate << "; q: " << callOption.dividendPayment << "; sigma: " << callOption.volatility << "; T: " << callOption.maturityDate << "; t: " << callOption.purchaseDate << endl;
    cout << "Call Option Price (Monte Carlo): " << S_MC << endl;
    //cout << "Call Option Price(Control Variate): " << callOption.CallPrice_Var() << endl; 
    cout << "Call Option Price (Black Scholes): " << S_BS << endl;
    cout << "Variance: " << S_MC - S_BS << endl;
}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
