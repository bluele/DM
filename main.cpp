#include "markov.hh"
#include "ngram.hh"
#include <iostream>
#include <vector>
#include <string>

int main(void){
	Ngram gram(2);
	Markov mk;
	std::vector<std::string> token = gram.parse("日本の夏は暑い。");
	mk.build(token);
	std::cout << mk.generate_sentence("日本", 10, "\n") << std::endl;
	return 0;
}
