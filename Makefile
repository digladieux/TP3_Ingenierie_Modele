check: ## Clean the quality of the code
	@cppcheck --enable=style -i src/ main/  2> cppcheck.txt 