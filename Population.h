#pragma once

#include <vector>

#include "Member.h"


class Population {
public:
    /*
    Initialize population object.
    size: number of members in a single generation
    geneCount: the number of genes in a single member of the population
    */
    Population(unsigned int size, unsigned int geneCount);

    /*
    Make a new generation of members after supplying the fitness of each member.
    */
    void iterate();

    /*
    Return the data for the member at the given index.
    Used for calculating population externally.
    */
    const char* getMemberData(unsigned int index);

    void setFitness(unsigned int index, double fitness);

    /*
    Free all memory currently occupied child Member objects and their data.
    Should be used before deleting this object to prevent memory leaks.
    */
    void cleanUp();
private:
    std::vector<Member*> members;
    char* randomGene(unsigned int geneCount, char min, char max);
};

