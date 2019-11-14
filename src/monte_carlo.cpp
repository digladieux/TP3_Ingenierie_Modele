/**
 * \file monte_carlo.c
 * \brief Fichier pour l'algorithme de Monte Carlo
 * \author GLADIEUX CUNHA Dimitri
 * \date 17 Octobre 2019
 */

#include "../header/monte_carlo.hpp"
#include "CLHEP/Random/MTwistEngine.h"
#include <exception>
#include <cmath>
/**
 * \fn void experiencesMonteCarlo(const int nb_experiences, const int
 * nb_iterations, char use_random_number_already_generated) \brief Methode
 * effectuant n experiences de Monte Carlo, avec m iterations. On definit si on
 * souhaite utiliser des nombres deja genere ou non. On calcul aussi l'ecart a
 * la moyenne entre les resultats experimentaux du calcul de PI et la valeur
 * theorique de ce dernier \param nb_experiences Le nombre d'experiences que
 * l'on desire \param nb_iterations Le nombre d'iterations que l'on souhaite
 */

MonteCarlo::MonteCarlo(const GenerationStatus& generate_status) : gs(generate_status) {}

void MonteCarlo::recoverStatusMT(int index) {
    this->gs.recoverStatus(index) ;
}

void MonteCarlo::nExperiencesMonteCarlo() {
    unsigned long long int i;
    double average_gap = 0;

    for (i = 0; i < gs.getStatusNumber(); i++) {
        double pi = monteCarlo();
        double tmp = M_PI - pi;
        average_gap += tmp < 0 ? tmp * (-1) : tmp;
        std::cout << "Step n°" << i + 1 << " - Value of Pi : " << pi
                  << std::endl;
        
    }

    average_gap /= gs.getStatusNumber();
    std::cout << "Average Gap : " << average_gap << std::endl;
}

/**
 * \fn double monteCarlo(const int begin, const int end, char
 * use_random_number_already_generated)
 * \brief Fonction effectuant une experience de Monte Carlo, avec m iterations.
 * On definit si on souhaite utiliser des nombres deja genere ou non \param
 * nb_iterations Le nombre d'iterations que l'on souhaite \return La valeur
 * experimentale de PI.
 */
double MonteCarlo::monteCarlo() {
    unsigned long long int count = 0;
    unsigned long long int i = 0;


    for (i = 0; i < gs.getNumbersNumber(); i++) {
        double x = gs.getRandomNumber() ;
        double y = gs.getRandomNumber() ;
        double z = x * x + y * y;
        if (z <= 1) {
            count++;
        }
    }

    return (double)count / gs.getNumbersNumber() * 4;
}