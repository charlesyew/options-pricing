#pragma once

class BSEuropeanOption {
private:
    void init();
    void copy(const BSEuropeanOption& o2);

public:
    double strikePrice; // K
    double spotPrice; // S
    double interestRate; // r
    double dividendRate; // q
    double volatility; // sigma
    double maturityDate; // t
    double purchaseDate; // T


public:
    //Constructors
    BSEuropeanOption();
    BSEuropeanOption(const BSEuropeanOption& option2);

    //Assignment Operator
    BSEuropeanOption& operator = (const BSEuropeanOption& option2);

    virtual ~BSEuropeanOption(); //Destructor

    double CallPrice() const;
    double CallDelta() const;
    double CallGamma() const;
    double CallVega() const;
    double CallTheta() const;
    double CallRho() const;

    double PutPrice() const;
    double PutDelta() const;
    double PutGamma() const;
    double PutVega() const;
    double PutTheta() const;
    double PutRho() const;
};

