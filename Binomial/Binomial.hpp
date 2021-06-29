#pragma once
class BinomEuropeanOption { //parent class for CRR, JR, EQP, TRG binom pricing strategies
private:

protected:
    double strikePrice; // K
    double spotPrice; // S
    double interestRate; // r
    double volatility; // sigma
    int maturityDate; // t
    int purchaseDate; // T
    int numIntervals; // n
    
public:
    void info();
    int optionDuration() const;
    virtual double CallPrice();
    double CallPrice_BS();

public: 
    BinomEuropeanOption(int num); //Constructor
    virtual ~BinomEuropeanOption(); //Destructor
};

class OptionPriceCRR : public BinomEuropeanOption {

private: 
    double jumpUp; // u
    double jumpDown; // d
    double jumpProbability; // p

public: 
    double CallPrice(); 
    double PutPrice();

public:
    OptionPriceCRR(int num); //Constructor 
    ~OptionPriceCRR(); //Destructor
}; 

class OptionPriceJR : public BinomEuropeanOption {

private:
    double jumpUp; // u
    double jumpDown; // d
    double jumpProbability; // p

public: 
    double CallPrice();
    double PutPrice();

public: 
    OptionPriceJR(int num); //Constructor 
    ~OptionPriceJR(); //Destructor

};

