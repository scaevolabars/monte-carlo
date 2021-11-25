//
// Created by serge on 11/25/2021.
//

#ifndef BLACK_SCHOLES_BLACKSCHOLES_H
#define BLACK_SCHOLES_BLACKSCHOLES_H


enum BSParams{
    ASSET = 1,
    STRIKE = 2,
    RF_RATE = 3,
    VOLATILITY = 4,
    YEARS_TO_MAT = 5,
    STEPS = 6,
    SIMULATIONS = 7,
};

class BlackScholes{
public:
    explicit BlackScholes(const double &asset_price,
                         const double &k_strike,
                         const double &rf_rate,
                         const double &volatility,
                         const double &time_to_maturity);

    void SetSimulationParams(int steps, int sims);

    double CallPriceExact();
    double PutPriceExact();


private:

    double spot;
    double strike;
    double rf;
    double sigma;
    double ttm;
    double n_sim;
    double n_steps;


    double d1();
    double d2();


};
#endif //BLACK_SCHOLES_BLACKSCHOLES_H
