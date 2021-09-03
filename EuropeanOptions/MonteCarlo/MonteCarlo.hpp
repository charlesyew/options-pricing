#pragma once

class MCEuropeanOption {
private: 

protected:
    double strikePrice; // K
    double spotPrice; // S
    double interestRate; // r
    double dividendPayment; // q
    double volatility; // sigma
    int maturityDate; // t
    int purchaseDate; // T
    int numIntervals; // n

public:
    //Constructors
    MCEuropeanOption(); //Constructor
    virtual ~MCEuropeanOption(); //Destructor

    int optionDuration() const;

    double CallPrice();
    double CallPrice2();
    double CallPrice_Var();
    double CallPrice_BS();
};