#ifndef RANDOMINRANGE_HPP
#define RANDOMINRANGE_HPP

#include <random>

/*
 * Classe pour générer un nombre aléatoire entre low et high
 * ( question de simplicité ... )
 * 
 * ASKME: Baptiste FAMCHON
 */

class RandomInRange { 
    std::mt19937 rng;
public:
    RandomInRange() : rng(std::random_device()()) {}
    int operator()(int low, int high) { 
        std::uniform_int_distribution<int> uni(low, high);
        return uni(rng);
    }
};

#endif
