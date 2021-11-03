#pragma once

class Member {
public:
    Member();
    Member(unsigned int geneCount, const char* data);
    const char* getData();
    unsigned int getGeneCount();
    void setFitness(int fitness);
    int getFitness();

private:
    const char* data;
    int fitness;
    unsigned int geneCount;
};