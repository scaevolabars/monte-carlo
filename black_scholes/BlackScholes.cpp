//
// Created by serge on 11/25/2021.
//

#include <cmath>
#include <random>
#include <fstream>
#include <string>
#include "BlackScholes.h"

double normalCDF(double x) // Phi(-∞, x) aka N(x)
{
    return std::erfc(-x/std::sqrt(2))/2;
}

void log_path_to_file(const std::string& filename, std::vector<std::vector<double>> &simulations){

    std::ofstream myFile(filename);

    // Send column names to the stream
    for(int j = 0; j < simulations.size(); ++j)
    {
        myFile << "Sim " << j;
        if(j != simulations.size() - 1) myFile << ","; // No comma at end of line
    }
    myFile << "\n";

    // Send data to the stream
    for(int i = 0; i < simulations.at(0).size(); ++i)
    {
        for(int j = 0; j < simulations.size(); ++j)
        {
            myFile << simulations.at(j).at(i);
            if(j != simulations.size() - 1) myFile << ","; // No comma at end of line
        }
        myFile << "\n";
    }

    // Close the file
    myFile.close();
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
    n_steps = 1;
    n_sim = 1;
}

void BlackScholes::SetSimulationParams(const int &steps, const int &sims) {
    if (steps != 0 && sims!=0){
        n_steps = steps;
        n_sim = sims;
    }
}

void BlackScholes::MonteCarloSimulation(){

    std::random_device rd;
    std::mt19937_64 generator(rd());
    std::normal_distribution<> nd(0.0, 1.0);

    double delta_t = (double)ttm / n_steps;
    double sqrt_t = std::sqrt(delta_t);
    double equityPrice = spot;
    std::vector<double> path{};
    std::vector<std::vector<double>> simulations{};

    auto updatePrice = [this, delta_t, sqrt_t](double previousPrice, double norm){

        double price = 0.0;

        double drift = (rf - 0.5*(sigma*sigma)) * delta_t;
        double diffusion = sigma * norm * sqrt_t;
        price = previousPrice * std::exp( drift + diffusion);
        return price;

    };

    for(int i = 0; i != n_sim; ++i){

        equityPrice = spot;
        path.push_back(equityPrice);

        for(int j = 0; j!= n_steps; ++j){

            equityPrice = updatePrice(equityPrice, nd(generator));

            path.push_back(equityPrice);
        }

        call_put_counter(equityPrice);

        simulations.push_back(path);
        path.clear();

    }

    log_path_to_file("D:\\documentarium\\repositories\\monte-carlo\\black_scholes\\sim.csv", simulations);
}

double BlackScholes::PutPriceExact(){
    return strike * normalCDF(-d2()) / std::exp(rf*ttm) - spot*normalCDF(-d1());
}

double BlackScholes::CallPriceExact(){
    return spot*normalCDF(d1()) - strike * normalCDF(d2()) / std::exp(rf*ttm);
}


double BlackScholes::d1() {
    return (std::log(spot/strike) + (rf + (sigma*sigma)*0.5)) * ttm /(sigma * std::sqrt(ttm));
}


double BlackScholes::d2() {
    return d1() - sigma * std::sqrt(ttm);
}

double BlackScholes::call_put_counter(double terminal_value){
    if (terminal_value > strike){
        call_price += terminal_value - strike;
    }
    else if(terminal_value < strike){
        put_price += strike - terminal_value;
    }
}

double BlackScholes::CallPriceSimulation() {
    return call_price/(n_sim * std::exp(rf * ttm));
}

double BlackScholes::PutPriceSimulation() {
    return put_price/(n_sim * std::exp(rf * ttm));
}