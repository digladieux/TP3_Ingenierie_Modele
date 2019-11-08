/**
 * \file monte_carlo.hpp
 * \brief Fichier d'en tete de monte_carlo.c
 * \author GLADIEUX CUNHA Dimitri
 * \date 17 Octobre 2019
 */

#pragma once

class MonteCarlo {
    public:
        MonteCarlo() = default ;
        // MonteCarlo(const MonteCarlo&) = delete ;
        // MonteCarlo(const MonteCarlo&&) = delete ;
        void nExperiencesMonteCarlo(unsigned long long int nb_iterations, const long long int nb_experiences) const ;
        double monteCarlo(unsigned long long int nb_iterations) const ;
} ;