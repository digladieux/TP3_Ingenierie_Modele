#pragma once

class GenerationsWords {
    public :
        explicit GenerationsWords(char* dico) ;
        const char* generateWord(short int word_size) const;
    private :
        char * dictionnary ;
};