#pragma once

class GenerationsWords {
    public :
        GenerationsWords(char* dico) ;
        const char* generateWord(short int word_size) const;
    private :
        char * dictionnary ;
};