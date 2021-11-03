#include <iostream>
#include "Population.h"

const int POPULATION_SIZE = 10;
const int GENE_COUNT = 5;

const char* TARGET = "hello";

void calculateFitness(Population& p);

int main() {
    srand(time(NULL));
    
    Population p = Population(POPULATION_SIZE, GENE_COUNT);

    calculateFitness(p);
    p.iterate();

    std::cout << "--- iteration ---\n";

    calculateFitness(p);

    p.cleanUp();

    return 0;
}

void calculateFitness(Population& p) {
    for(int i = 0; i < POPULATION_SIZE; i++) {
        int fitness = 0;

        const char* data = p.getMemberData(i);
        std::cout << "Member " << i << ": " ;

        for(int j = 0; j < GENE_COUNT; j++) {
            std::cout << data[j];
            if(data[j] == TARGET[j]) {
                fitness++;
            }
        }

        std::cout << " : " << fitness << std::endl;

        p.setFitness(i, fitness);
    }


}