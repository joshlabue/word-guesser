#pragma once

#include <vector>

#include "Member.h"


class Population {
public:
    /*
    Initialize population object.
    size: number of members in a single generation
    geneCount: the number of genes in a single member of the population
    mutationChance: the chance of a mutation for each gene (0.0 - 1.0)
    */
    Population(unsigned int size, unsigned int geneCount, double mutationChance);

    /*
    Make a new generation of members after supplying the fitness of each member.
    */
    void iterate();

    /*
    Return the data for the member at the given index.
    Used for calculating population externally.
    */
    const char* getMemberData(unsigned int index);

    /*
    Set the fitness of a member at a given index.
    Fitness can be any positive integer.
    */
    void setFitness(unsigned int index, unsigned int fitness);

    /*
    Returns the number of the current generation that the population is on.
    */
    int getGeneration();

    /*
    Free all memory currently occupied child Member objects and their data.
    Should be used before deleting this object to prevent memory leaks.
    */
    void cleanUp();
private:
    std::vector<Member*> members;
    double mutationChance;
    int generation;
    char* randomDNA(unsigned int geneCount);
    char randomGene(char min, char max);
    char randomLetter();
    Member* crossOver(Member* parent1, Member* parent2);
};

