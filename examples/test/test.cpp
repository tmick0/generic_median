#include <iostream>
#include <cstdlib>

#include "MedianFilter.h"

int main(int argc, char **argv)
{

    MedianFilter<int, 7> f;
    
    for(int i = 0; i < 1000; i++){
        int s = rand() % 100;
        f.addSample(s);

        std::cout << f.getMedian() << std::endl;
    }
    
    return 0;

}
