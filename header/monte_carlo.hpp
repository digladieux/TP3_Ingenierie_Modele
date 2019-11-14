/**
 * \file monte_carlo.hpp
 * \brief Fichier d'en tete de monte_carlo.c
 * \author GLADIEUX CUNHA Dimitri
 * \date 17 Octobre 2019
 */

#pragma once
#include "generation_status.hpp"
class MonteCarlo {
  public:
    MonteCarlo(const GenerationStatus& generate_status);
    MonteCarlo(const MonteCarlo&) = delete;
    MonteCarlo(const MonteCarlo&&) = delete;
    void nExperiencesMonteCarlo();
    double monteCarlo();
    void recoverStatusMT(int index);

  private:
    GenerationStatus gs;
};