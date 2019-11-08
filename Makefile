all : exe/question2 

.PHONY : clean help

CREATE_FOLDER_EXE= mkdir -p exe
CREATE_FOLDER_BUILD= mkdir -p build
GENERATE_EXE= $^ -o $@ $(FLAGS)
GENERATE_O= $^ -c -o $@ $(FLAGS)
INCLUDE= -I./Random/include
LIBRARIES= -L./Random/lib ./Random/lib/libCLHEP-Random-2.1.0.0.a
FLAGS= -O2 -msse2 -fpermissive
# FLAGS= -g 

help: ## Display the availables commands
	@grep -E '(^[a-zA-Z_-]+:.*?##.*$$)|(^##)' $(MAKEFILE_LIST) | awk 'BEGIN {FS = ":.*?## "}; {printf "\033[32m%-10s\033[0m %s\n", $$1, $$2}' | sed -e 's/\[32m##/[33m/'

check: ## Clean the quality of the code
	@cppcheck --enable=style -i src/ main/  2> cppcheck.txt 

exe/question2 : build/main_subject.o build/generation_words.o build/monte_carlo.o
	$(CREATE_FOLDER_EXE) && $(CXX) $(GENERATE_EXE) $(LIBRAIRIES)  -pthread

build/main_subject.o : main/main_subject.cpp 
	$(CREATE_FOLDER_BUILD) && $(CXX) $(GENERATE_O) $(INCLUDE) 

build/generation_words.o : src/generation_words.cpp
	$(CREATE_FOLDER_BUILD) && $(CXX) $(GENERATE_O) $(INCLUDE) 

build/monte_carlo.o : src/monte_carlo.cpp
	$(CREATE_FOLDER_BUILD) && $(CXX) $(GENERATE_O) $(INCLUDE) 

exe/question1 : build/test.o
	$(CREATE_FOLDER_EXE) && $(CXX) $(GENERATE_EXE) $(LIBRAIRIES) 

build/test.o : main/test.cc
	$(CREATE_FOLDER_BUILD) && $(CXX) $(GENERATE_O) $(INCLUDE) 

clean :
	rm -rf build/* Status/* exe/* qrngb
