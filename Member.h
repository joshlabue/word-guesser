#pragma once

class Member {
public:
    Member();
    Member(unsigned int geneCount, const char* data);
    const char* getData();
    unsigned int getGeneCount();
    void setFitness(double fitness);
    double getFitness();

private:
    const char* data;
    double fitness;
    unsigned int geneCount;
};