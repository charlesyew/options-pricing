#pragma once

class BSEuropeanOption {
private:
    double strikePrice; // K
    double spotPrice; // S
    double interestRate; // r
    double dividendRate; // q
    double volatility; // sigma
    double maturityDate; // t
    double purchaseDate; // T

public:
    BSEuropeanOption(); //Constructor
    virtual ~BSEuropeanOption(); //Destructor

public:
    double optionDuration();
    double d1();
    double d2();

    double CallPrice();
    double CallDelta();
    double CallGamma();
    double CallVega();
    double CallTheta();
    double CallRho();

    double PutPrice();
    double PutDelta();
    double PutGamma();
    double PutVega();
    double PutTheta();
    double PutRho();

    double impliedVolatility();
    double pExpireITM();

};

class cdf {
public:
    static double phi(double x);
};

