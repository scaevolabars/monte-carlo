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

    void SetSimulationParams(const int &steps, const int &sims);
    void MonteCarloSimulation();

    double CallPriceExact();
    double PutPriceExact();
    double CallPriceSimulation();
    double PutPriceSimulation();


private:

    double spot;
    double strike;
    double rf;
    double sigma;
    double ttm;
    int n_sim{};
    int n_steps{};
    double call_price = 0;
    double put_price = 0;


    double d1();
    double d2();
    double call_put_counter(double terminal_value);


};
#endif //BLACK_SCHOLES_BLACKSCHOLES_H
