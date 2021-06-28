#pragma once
class BinomEuropeanOption { //parent class for CRR, JR, EQP, TRG binom pricing strategies
private:

public:
    double strikePrice; // K
    double spotPrice; // S
    double interestRate; // r
    double volatility; // sigma
    int maturityDate; // t
    int purchaseDate; // T
    int numIntervals; // n
    
public:
    
    BinomEuropeanOption(int num); //Constructor
    virtual ~BinomEuropeanOption(); //Destructor

    void info();
    int optionDuration() const;

    double CallPrice_BS();

};

class OptionPriceCRR : public BinomEuropeanOption {

public: 
    double jumpUp; // u
    double jumpDown; // d
    double jumpProbability; // p

    double CallPrice(); 
    double PutPrice();

public:
    OptionPriceCRR(int num) :BinomEuropeanOption(num) {} //Constructor 
    virtual ~OptionPriceCRR(); //Destructor
}; 

class OptionPriceJR : public BinomEuropeanOption {

public:
    double jumpUp; // u
    double jumpDown; // d
    double jumpProbability; // p

    double CallPrice();
    double PutPrice();

public: 
    OptionPriceJR(int num); //Constructor 
    virtual ~OptionPriceJR(); //Destructor

};

