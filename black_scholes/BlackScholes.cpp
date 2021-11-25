//
// Created by serge on 11/25/2021.
//

#include <cmath>
#include "BlackScholes.h"

double normalCDF(double x) // Phi(-∞, x) aka N(x)
{
    return std::erfc(-x/std::sqrt(2))/2;
}


BlackScholes::BlackScholes(const double &asset_price,
                         const double &k_strike,
                         const double &rf_rate,
                         const double &volatility,
                         const double &time_to_maturity){

    spot = asset_price;
    strike = k_strike;
    rf = rf_rate;
    sigma = volatility;
    ttm = time_to_maturity;
}

void BlackScholes::SetSimulationParams(int steps, int sims) {
    n_steps = steps;
    n_sim = sims;
}

double BlackScholes::PutPriceExact(){
    return strike * normalCDF(-d2()) / std::exp(rf*ttm) - spot*normalCDF(-d1());

}

double BlackScholes::CallPriceExact(){

    return spot*normalCDF(d1()) - strike * normalCDF(d2()) / std::exp(rf*ttm);

}


double BlackScholes::d1() {
    return (std::log(spot/strike) + (rf + (sigma*sigma)/2.0)) * ttm /(sigma * std::sqrt(ttm));
}


double BlackScholes::d2() {
    return d1() - sigma * std::sqrt(ttm);
}