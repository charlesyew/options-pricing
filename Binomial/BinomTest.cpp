#include <iostream>

#include "Binomial.hpp"
#include "BSFormula.hpp"

using namespace std;

int main()
{
    BinomEuropeanOption* baseOption;
    OptionPriceJR callOption(1000);
    baseOption = &callOption; 

    double S_Binom = baseOption -> CallPrice();
    /*double S_Binom = callOption.CallPrice();*/
    double S_BS = baseOption -> CallPrice_BS();
    
    baseOption -> info();
    cout << "Call Option Price (Binom): " << S_Binom << endl;
    cout << "Call Option Price (Black Scholes): " << S_BS << endl;
    /*cout << "Variance: " << S_Binom - S_BS << endl;*/
}