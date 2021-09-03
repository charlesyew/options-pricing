class BSEuropeanOption {
private:

protected:
    double strikePrice; // K
    double spotPrice; // S
    double interestRate; // r
    double dividendRate; //d
    double volatility; // sigma
    int maturityDate; // t
    int purchaseDate; // T 
    int numIntervals; // n
    
public:
    int optionDuration() const;
    double phi(double x);
    double d1(); 
    double d2();

    void info();
    virtual double CallPrice();
    virtual double PutPrice();
    virtual double CallDelta();
    virtual double PutDelta();
    virtual double CallGamma();
    virtual double PutGamma();
    virtual double CallVega(); 
    virtual double PutVega(); 
    virtual double CallTheta(); 
    virtual double PutTheta(); 
    virtual double CallRho(); 
    virtual double PutRho(); 
    virtual double impliedVolatility(); 
    virtual double pExpireITM();

public:
    BSEuropeanOption(); //Constructor
    virtual ~BSEuropeanOption(); //Destructor
};