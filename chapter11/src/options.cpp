#include <cmath>
#include <algorithm>
#include <vector>
#include <iostream>

int main(){

    // Option strike price, K
    double K;

    // Option expiry, T

    // Stock price at time T, S_T
    double S;
    
    // Call options give right to buy: payoff, C_T, is max(S_T - K, 0)
    double C = std::max(S - K, 0.0);

    // Put options give right to sell: payoff, P_T, is max(K - S_T, 0)
    double P = std::max(K - S, 0.0);
    // Payoff is never negative because the option doesn't have to be exercised

    // C_T - P_T = max(S_T - K, 0) - max(K - S_T, 0) = S_T - K

}