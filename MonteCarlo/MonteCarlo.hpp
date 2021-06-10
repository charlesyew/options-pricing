#pragma once

class MCEuropeanOption {
private: 
	void init(); 
    void copy(const MCEuropeanOption& o2);
    struct List {
        double S; 
    };

public: 
    double strikePrice; // K
    double spotPrice; // S
    double interestRate; // r
    double dividendRate; // q
    double volatility; // sigma
    int maturityDate; // t
    int purchaseDate; // T

public:
    //Constructors
    MCEuropeanOption();
    MCEuropeanOption(const MCEuropeanOption& option2);

    //Assignment Operator
    MCEuropeanOption& operator = (const MCEuropeanOption& option2);

    virtual ~MCEuropeanOption(); //Destructor

    int optionDuration() const;

    double CallPrice();

};