#include <iostream>

#include "Binomial.hpp"
#include "BlackScholes.hpp"

using namespace std;

int main()
{
    
    OptionPriceCRR option1(1000000);
    OptionPriceJR option2(1000000);

    BinomEuropeanOption* baseOption[] = {&option1, &option2};

    double S_CRR = baseOption[0] -> CallPrice();
    double S_JR = baseOption[1]->CallPrice();
    /*double S_Binom = callOption.CallPrice();*/
    double S_BS = baseOption[0] -> CallPrice_BS();
    
    baseOption[0] -> info();
    cout << "Call Option Price (Black Scholes): " << S_BS << endl;
    cout << "Call Option Price (CRR Binom): " << S_CRR << endl;
    cout << "Variance: " << S_CRR - S_BS << endl;
    cout << "Call Option Price (JR Binom): " << S_JR << endl;
    cout << "Variance: " << S_JR - S_BS << endl;
}