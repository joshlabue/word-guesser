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
    for(int i = 0; i < members.size(); i++) {
        const char* oldGene = members[i]->getData();
        delete[] oldGene;
        delete members[i];
    }
}

void Population::iterate() {
    // const char* oldGene = members[0]->getData();
    // int gc = members[0]->getGeneCount();

    // delete[] oldGene;
    // delete members[0];

    // members[0] = new Member(gc, randomGene(gc, 'a', 'z'));
 
    int fitnessSum = 0;
    std::vector<int> matingPool = std::vector<int>();

    for(int i = 0; i < members.size(); i++) { // for each member
        int fitness = members[i]->getFitness(); 
        fitnessSum += fitness; // add its fitness to the sum
        for(int j = 0; j < fitness; j++) { // and for each "point" of fitness the member has
            matingPool.push_back(i); // add an instance of its index to the mating pool
        }
    }

    // should do something in the event that nothing has a fitness greater than zero
    // maybe generate a new set of random members?

    std::vector<Member*> newMembers = std::vector<Member*>();

    if(matingPool.size() < 2) {
        for(int i = 0; i < members.size(); i++) {
            char* randGene = randomGene(members[0]->getGeneCount(), 'a', 'z');
            newMembers.push_back(new Member(members[0]->getGeneCount(), randGene));        
        }
    }
    else {
        for(int i = 0; i < members.size(); i++) {
            int parentAPoolIndex = (int)rand() % matingPool.size();
            int parentBPoolIndex = (int)rand() % matingPool.size();

            int parentAIndex = matingPool[parentAPoolIndex];
            int parentBIndex = matingPool[parentBPoolIndex];

            Member* parentA = members[parentAIndex];
            Member* parentB = members[parentBIndex];

            const char* genesA = parentA->getData();
            const char* genesB = parentB->getData();

            char* newGeneData = new char[parentA->getGeneCount()];

            for(int geneIndex = 0; geneIndex < parentA->getGeneCount(); geneIndex++) {
                // 50% chance for either parent's gene to be selected
                if(rand() % 2 == 0) {
                    newGeneData[geneIndex] = genesA[geneIndex];
                }
                else {
                    newGeneData[geneIndex] = genesB[geneIndex];
                }
            }

            newMembers.push_back(new Member(parentA->getGeneCount(), newGeneData));
        }        
    }


    // get rid of old members

    for(int i = 0; i < members.size(); i++) {
        const char* oldGene = members[i]->getData();
        delete[] oldGene;
        delete members[i];
    }

    members = newMembers;

}

const char* Population::getMemberData(unsigned int index) {
    return members[index]->getData();
}

void Population::setFitness(unsigned int index, int fitness) {
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