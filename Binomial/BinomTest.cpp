#include <iostream>

#include "Binomial.hpp"
#include "BlackScholes/cdf.hpp"

using namespace std;

int main()
{
    OptionPriceCRR callOption(10000);
    
    double S_Binom = callOption.CallPrice();
    double S_BS = callOption.CallPrice_BS();
    
    cout << "Call Option Price (Binom): " << S_Binom << endl;
    cout << "Call Option Price (Black Scholes): " << S_BS << endl;
    cout << "Variance: " << S_Binom - S_BS << endl;
}