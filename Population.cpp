#include "Population.h"
#include <iostream>
#include <array>

Population::Population(unsigned int size, unsigned int geneCount, double mutationChance)
{
    this->members = std::vector<Member*>();    
    for(int i = 0; i < size; i++)
    {
        char* randGene = randomDNA(geneCount);
        members.push_back(new Member(geneCount, randGene));        
    }

    this->mutationChance = mutationChance;
    this->generation = 0;
}

void Population::cleanUp() {
    for(int i = 0; i < members.size(); i++) {
        const char* oldGene = members[i]->getData();
        delete[] oldGene;
        delete members[i];
    }
}

void Population::iterate() {
    std::vector<Member*> matingPool = std::vector<Member*>();

    for(int i = 0; i < members.size(); i++) { // for each member
        for(int j = 0; j < members[i]->getFitness(); j++) { // and for each "point" of fitness the member has
            matingPool.push_back(members[i]);
        }
    }

    std::vector<Member*> newMembers = std::vector<Member*>();

    while(matingPool.size() < 2) { // if there aren't enough members just use two from the last pool and let mutation do the work
        matingPool.push_back(members[0]);
        matingPool.push_back(members[1]);
    }

    for(int i = 0; i < members.size(); i++) {
        int parentAIndex = rand() % matingPool.size();
        int parentBIndex = rand() % matingPool.size();

        Member* parentA = matingPool[parentAIndex];
        Member* parentB = matingPool[parentBIndex];

        Member* child = crossOver(parentA, parentB);

        newMembers.push_back(child);
    }       

    // get rid of old members

    for(int i = 0; i < members.size(); i++) {
        const char* memberData = members[i]->getData();
        delete[] memberData;
        delete members[i];
    }

    members = newMembers;

    generation++;

}

const char* Population::getMemberData(unsigned int index) {
    return members[index]->getData();
}

void Population::setFitness(unsigned int index, unsigned int fitness) {
    members[index]->setFitness(fitness);
}

char* Population::randomDNA(unsigned int geneCount) {
    char* gene = new char[geneCount];

    for(int i = 0; i < geneCount; i++) {
        gene[i] = randomLetter();
    }
    return gene;
}

char Population::randomLetter() {

    /**
     * slightly hacky approach to generate either a letter or a space.
     * can pick any of the 26 letters in the alphabet, but also a 27th character.
     * this character (encoded version unrelated) is replaced with a space if it is drawn
     */

    char letter = randomGene('a', 'z' + 1);
    if(letter == 'z' + 1) letter = ' ';

    return letter;
}

char Population::randomGene(char min, char max) {
    // pick a random number from (and including) min to max        
    return rand() % (max - min + 1) + min;
}

int Population::getGeneration() {
    return generation;
}

Member* Population::crossOver(Member* parent1, Member* parent2) {
        const char* genesA = parent1->getData();
        const char* genesB = parent2->getData();

        char* newGeneData = new char[parent1->getGeneCount()];

        for(int i = 0; i < parent1->getGeneCount(); i++) {
            if(rand() % 2 == 0) { // 50% chance for either parent's gene to be selected
                newGeneData[i] = genesA[i];
            }
            else {
                newGeneData[i] = genesB[i];
            }

            double random = (double)rand() / (double)RAND_MAX;
            if(random < mutationChance) { 
                newGeneData[i] = randomLetter();
            }
        }

        return new Member(parent1->getGeneCount(), newGeneData);
}