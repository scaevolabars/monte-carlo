#include <iostream>
#include "BlackScholes.h"




int main(int argc, const char * argv[]) {

    BlackScholes bsm = BlackScholes(300.0, 250.0, 0.03, 0.15, 1.0);

    std::cout << "Call Price:" << bsm.CallPriceExact() << std::endl << "Put Price:"  << bsm.PutPriceExact();

    return 0;
}
