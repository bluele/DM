#ifndef COUNTER_HH
#define COUNTER_HH
#include <string>
#include <map>
#include <vector>
#include <iostream>
#include <ctime>
#include <cstdlib>
#include <exception>

class TokenCounter {
private:
	std::map<const std::string, unsigned> child;
	int size;
public:
	TokenCounter();
	~TokenCounter();
	void incr(const std::string);
	void incr(const std::string, int);
	int get_size();
	template<class T>
	std::string fetch_word(T);
	void dump(); //DEBUG
};

TokenCounter::TokenCounter():
		size(0){}

TokenCounter::~TokenCounter() {}

void TokenCounter::incr(const std::string word) {
	this->incr(word, 1);
}

void TokenCounter::incr(const std::string word, int num) {
	// 存在しない場合は初期化
	if (child.find(word) == child.end())
		child.insert(std::make_pair(word, 0));
	size += num;
	child[word] += num;
}

/*
 * 連接語の総数を取得します
 */
int TokenCounter::get_size() {
	return size;
}

/*
 * 乱数を生成して出現頻度で重み付けしてwordを取得します
 */
template<class T>
std::string TokenCounter::fetch_word(T rdm) {
	if (this->get_size() <= 0) // 終端語はthrow
		throw std::exception();
	int num = rdm(1, this->get_size());
	std::map<const std::string, unsigned>::iterator it = child.begin();
	for (; it != child.end(); it++) {
		if (num <= it->second)
			break;
		num -= it->second;
	}
	return it->first;
}

/*
 * DEBUG用
 */
void TokenCounter::dump() {
	std::map<const std::string, unsigned>::iterator it = child.begin();
	for (; it != child.end(); it++) {
		std::cout << it->first << std::endl;
		std::cout << it->second << std::endl;
	}
}

#endif
