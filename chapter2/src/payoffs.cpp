#include <memory>
#include <iostream>

class Payoff{
public:
    virtual double operator()(double S) const = 0;
};

class CallPayoff : public Payoff{
public:
    CallPayoff(double strike) { K = strike; }
    double operator()(double S) const { return std::max<double>(S - K, 0); }

private:
    double K;
};

class PutPayoff : public Payoff{
public:
    PutPayoff(double strike) { K = strike; }
    double operator()(double S) const { return std::max<double>(K - S, 0); }
    
private:
    double K;
};

class PayoffFactory{
public:
    PayoffFactory(const PayoffFactory& factory) = delete;
    PayoffFactory& operator=(const PayoffFactory& factory) = delete;

    PayoffFactory() = default;
    virtual ~PayoffFactory() = default;

    virtual std::shared_ptr<Payoff> createPayoff(double K) = 0;
};

class CallPayoffFactory : public PayoffFactory{
public:
    CallPayoffFactory(const CallPayoffFactory& factory) = delete;
    CallPayoffFactory& operator=(const CallPayoffFactory& factory) = delete;

    CallPayoffFactory() = default;
    virtual ~CallPayoffFactory() = default;

    virtual std::shared_ptr<Payoff> createPayoff(double K){ return std::shared_ptr<Payoff>(new CallPayoff(K)); }
};

class PutPayoffFactory : public PayoffFactory{
public:
    PutPayoffFactory(const PutPayoffFactory& factory) = delete;
    PutPayoffFactory& operator=(const PutPayoffFactory& factory) = delete;

    PutPayoffFactory() = default;
    virtual ~PutPayoffFactory() = default;

    virtual std::shared_ptr<Payoff> createPayoff(double K){ return std::shared_ptr<Payoff>(new PutPayoff(K)); }
};

int main(){
    int choice;
    std::cout << "1: Call\n" << "2: Put\n" << ": ";
    std::cin >> choice;

    std::unique_ptr<PayoffFactory> factory;
    if (choice == 1){
        factory.reset(new CallPayoffFactory());
    } else{
        factory.reset(new PutPayoffFactory());
    }

    double K = 100.0;
    std::shared_ptr<Payoff> payoff = factory->createPayoff(K);

    double S = 90.0;
    std::cout << "Payoff: " << (*payoff)(S) << "\n";

    return 0;
}