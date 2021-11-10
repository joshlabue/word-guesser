#include <iostream>
#include <cstring>

#include "Population.h"

const int POPULATION_SIZE = 10000;
const double MUTATION_CHANCE = .1 / 100;

const char* TARGET = "she sells sea shells by the sea shore";
const int GENE_COUNT = strlen(TARGET);

bool done = false;

void calculateFitness(Population& p);

int main() {
    srand(time(NULL));
    
    Population p = Population(POPULATION_SIZE, GENE_COUNT, MUTATION_CHANCE);

    calculateFitness(p);
    p.iterate();

    while(!done) {
        calculateFitness(p);
        p.iterate();
    }


    p.cleanUp();

    return 0;
}

void calculateFitness(Population& p) {
    double fitnessSum = 0;
    const char* bestMember;
    int bestFitness = 0;

    for(int i = 0; i < POPULATION_SIZE; i++) {
        int fitness = 0;

        const char* data = p.getMemberData(i);

        for(int j = 0; j < GENE_COUNT; j++) {
            if(data[j] == TARGET[j]) {
                fitness++;
            }

        }

        p.setFitness(i, fitness);
        fitnessSum += fitness;

        if(fitness > bestFitness) {
            bestFitness = fitness;
            bestMember = data;
        }

        if(fitness == GENE_COUNT) {
            done = true;
        }
    }

    std::cout << "Generation " << p.getGeneration() << " | ";
    std::cout << "Average fitness: " << (fitnessSum / (double)POPULATION_SIZE) / GENE_COUNT << " | Fittest member: ";

    for(int i = 0; i < GENE_COUNT; i++) {
        std::cout << bestMember[i];
    }
    std::cout << " (" << (double)bestFitness / GENE_COUNT << ")" << std::endl;
}