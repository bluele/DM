#ifndef MARKOV_HH
#define MARKOV_HH
#include <string>
#include <map>
#include <vector>
#include <iostream>
#include <exception>
#include "counter.hh"
#include "util.hh"
#define ENTER std::cout << std::endl

typedef std::map<std::string, TokenCounter> Data;

class Markov {
private:
	Data data;									// 連接語と出現回数を管理
	std::map<std::string, double> score;		// 連接語の頻度を管理
	Util::Random<int> rdm;
public:
	Markov();
	Markov(std::vector<std::string>&);
	virtual ~Markov();
	void build(std::vector<std::string>&);
	std::string predict_next_word(const std::string&);
	std::string generate_sentence(const std::string&, int, std::string);
	std::string join(std::vector<std::string>&, std::string);
	void dump(); 								//DEBUG
};


Markov::Markov() {}

Markov::Markov(std::vector<std::string>& token) {
	this->build(token);
}

Markov::~Markov() {}

/*
 * 指定したtermの配列からマルコフ連鎖を生成します
 */
void Markov::build(std::vector<std::string>& token) {
	std::vector<std::string>::iterator it = token.begin();
	std::vector<std::string>::iterator prev;
	while (it != token.end()) {
		if (data.find(*it) == data.end())
			data.insert(std::make_pair(*it, TokenCounter()));
		prev = it;
		if (++it == token.end())
			break;
		data[*prev].incr(*it);
	}
}

/*
 * 指定した単語の次に続く単語を予測します
 * @TODO: wordよりtermの方がいい
 *
 */
std::string Markov::predict_next_word(const std::string& word) {
	if (data.find(word) == data.end()) // tokenが存在しない
		throw std::exception();
	// TokenCounterから乱数で(上限はsize)取得する。
	return data[word].fetch_word(rdm);
}

/*
 * 指定したテキストを先頭に持つ文章を生成します
 * @TODO prefixが一致しなかった場合
 *
 * @param prefix 文章の先頭文字
 * @param max つなぎ合わせる単語の数
 */
std::string Markov::generate_sentence(const std::string& prefix, int max, std::string separator) {
	int i;
	std::vector<std::string> result;
	std::string current;
	if (max <= 0) // throw
		throw std::exception();
	try {
		current = this->predict_next_word(prefix);
		result.push_back(prefix);
		max -= 1;
	} catch (std::exception& e) {
		current = Util::get_item(this->data.begin(), this->data.end(), this->rdm(1, this->data.size()));
	}
	result.push_back(current);
	for (i=0;i<max;i++) {
		//std::cout << i << std::endl;
		try {
			current = this->predict_next_word(current);
		} catch (std::exception& e) {
			// 連接語が見つからないときはランダムに抽出します
			current = Util::get_item(this->data.begin(), this->data.end(), this->rdm(1, this->data.size()));
		}
		result.push_back(current);
	}
	return this->join(result, separator);
}

/*
 * 第一引数に指定した配列の要素を第二引数に指定した文字列を連結します
 * @TODO 複数のテンプレートを使用したい
 *
 * @param items 連結対象の配列
 * @param separator 連結文字列
 */
std::string Markov::join(std::vector<std::string>& items, std::string separator) {
	std::string sentence;
	std::vector<std::string>::iterator it = items.begin();
	bool is_first = true;
	for (;it!=items.end();it++) {
		if (is_first) {
			is_first = false;
			sentence += *it;
		}
		else
			sentence += separator + *it;
	}
	return sentence;
}

/*
 * DEBUG用
 */
void Markov::dump() {
	Data::iterator it = data.begin();
	for (; it != data.end(); it++) {
		std::cout << "Pref: " << it->first << std::endl;
		it->second.dump();
		ENTER;
	}
}

#endif MARKOV_HH

