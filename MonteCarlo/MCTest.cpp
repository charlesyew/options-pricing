// MonteCarlo.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>

#include "MonteCarlo.hpp"
#include "BlackScholes/cdf.hpp"

using namespace std;

int main()
{
    MCEuropeanOption callOption;
    callOption.strikePrice = 100;
    callOption.spotPrice = 128;
    callOption.interestRate = 0.12/365;
    callOption.dividendRate = 0.08;
    callOption.volatility = 0.08;
    callOption.maturityDate = 365;
    callOption.purchaseDate = 30;
    cout << "Call Option Parameters: " << endl;
    cout << "S: " << callOption.spotPrice << "; K: " << callOption.strikePrice << "; r: " << callOption.interestRate << "; q: " << callOption.dividendRate << "; sigma: " << callOption.volatility << "; T: " << callOption.maturityDate << "; t: " << callOption.purchaseDate << endl;
    cout << "Call Option Price: " << callOption.CallPrice() << endl; // Analytical Price: 29.367
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
