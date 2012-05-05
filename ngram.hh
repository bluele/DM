#ifndef NGRAM_HH
#define NGRAM_HH
#include <vector>
#include <string>
#include <iostream>

/**
 * Ngramでテキストを分解します。
 * UTF8のみ対応
 */

class Ngram {
private:
	unsigned n;

public:
	Ngram();
	Ngram(int); // nを指定して初期化
	~Ngram();
	std::vector<std::string> parse(const char*); // 指定したテキストをパースします
	double search(const char*, const char*);	// 指定したテキストとngramで比較します
};


Ngram::Ngram():n(2u) {}

/*
 * コンストラクタ
 *
 * @param:n NgramのN
 */
Ngram::Ngram(int num){
	// @todo: validation
	this->n = (unsigned)num;
}

/*
 * デストラクタ
 */
Ngram::~Ngram() {}

/*
 * 指定したテキストをNgram分解して配列で返します
 *
 * @param: text: 対象のテキスト
 */
std::vector<std::string> Ngram::parse(const char* text) {
	// あらかじめtokenのサイズを予想して初期化可能 length
	const unsigned length = strlen(text);
	std::vector<std::string> token;
	std::vector<unsigned> char_pos;

	for(unsigned i=0; i < length; i++) {
	  if(!(text[i]&0x80))
	    char_pos.push_back(i); // ascii
	  else if (text[i]&0x40)
	    char_pos.push_back(i); // start of a UTF-8 character byte sequence
	}
	char_pos.push_back(length);
	for(unsigned i=0; i < char_pos.size(); i++){
	    if(i+n < char_pos.size()) {
	    	token.push_back(std::string(text+char_pos[i], text+char_pos[i+n]));
	    }
	}

	return token;
}

/*
 * 第一引数に指定したテキストと類似度を算出します
 *
 */
double Ngram::search(const char* query_one, const char* query_two) {

}

#endif
