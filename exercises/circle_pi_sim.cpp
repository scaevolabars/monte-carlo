#include <iostream>
#include <chrono>
#include <random>
#include <string>
#include <fstream>

int main ()
{
    std::default_random_engine rng;
    std::random_device rd;
    rng.seed(rd());
    std::uniform_real_distribution<double> uni(0.0, 1.0);

    long hits = 0, N = 0;
    double x, y, distance;
    std::cin >> N;


    std::ofstream outfile ("D:\\documentarium\\repositories\\monte-carlo\\exercises\\coordinates.csv");
    outfile<<"x,y"<<std::endl;
    for(long i = 0; i < N; ++i){
        x = uni(rng);
        y = uni(rng);
        outfile << x << "," << y << std::endl;
        distance = std::sqrt(x*x + y*y);

        if (distance <= 1.0){
            hits++;
        }
    }
    outfile.close();
    std::cout << 4 * double(hits)/double(N);



    return 0;
}