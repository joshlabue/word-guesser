#include "Member.h"
#include <cstdlib>
#include <iostream>

Member::Member() {

}

Member::Member(unsigned int geneCount, const char* data) {
    this->geneCount = geneCount;
    this->data = data;

    fitness = 0;
}

const char* Member::getData() {
    return data;
}

unsigned int Member::getGeneCount() {
    return geneCount;
}

int Member::getFitness() {
    return fitness;
}

void Member::setFitness(int fitness) {
    this->fitness = fitness;
}