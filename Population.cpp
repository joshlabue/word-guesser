#include "Population.h"
#include <iostream>
#include <array>
// #include <cmath>

Population::Population(unsigned int size, unsigned int geneCount)
{
    this->members = std::vector<Member*>();    
    for(int i = 0; i < size; i++)
    {
        char* randGene = randomGene(geneCount, 'a', 'z');
        members.push_back(new Member(geneCount, randGene));        
    }
}

void Population::cleanUp() {
    for(int i = 0; i < members.size(); i++)
    {
        const char* oldGene = members[i]->getData();
        delete[] oldGene;
        delete members[i];
    }
}

void Population::iterate() {
    const char* oldGene = members[0]->getData();
    int gc = members[0]->getGeneCount();

    delete[] oldGene;
    delete members[0];

    members[0] = new Member(gc, randomGene(gc, 'a', 'z'));
}

const char* Population::getMemberData(unsigned int index) {
    return members[index]->getData();
}

void Population::setFitness(unsigned int index, double fitness) {
    members[index]->setFitness(fitness);
}

char* Population::randomGene(unsigned int size, char min, char max) {
    char* gene = new char[size];
    // char* gene = (char*) malloc(size * sizeof(char));
    for(int i = 0; i < size; i++) {

        // pick a random number from (and including) min to max        
        char randChar = rand() % (max - min + 1) + min;
        gene[i] = randChar;
    }
    return gene;
}