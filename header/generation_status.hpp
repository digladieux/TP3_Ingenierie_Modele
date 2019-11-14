#pragma once
#include "../Random/CLHEP/Random/MTwistEngine.h"

class GenerationStatus {
    public:

        GenerationStatus(int status_nb, long long int numbers_nb) ;
        GenerationStatus(GenerationStatus&&) = delete ;
        GenerationStatus(const GenerationStatus& gs) ;

        void generateStatus(bool save_number) ;
        void recoverStatus(int index) ;
        bool checkStatus() ;

        void setValues(int status_nb, unsigned long long int numbers_nb, bool save_number) ;
        unsigned int getStatusNumber() const;
        unsigned long long int getNumbersNumber() const;
        double getRandomNumber() ;

    private:
        
        CLHEP::MTwistEngine mercenneTwister ;
        unsigned int status_number ;
        unsigned long long int numbers_number ; 
        int index_status ;
        bool numbers_saved ;
        bool status_generated ;
};