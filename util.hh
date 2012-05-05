#include <string>
#include <iostream>
#include <cstdlib>
#include <ctime>

/*
 * 乱数を生成します
 *
 * @param: start: 乱数の下限
 * @param: end: 乱数の上限
 */
namespace Util{
	template<class T>
	class Random{
	private:
		void init() {
			std::srand((unsigned int)time(NULL));
		}
	public:
		Random() { init(); }
	    T operator()(const T start, const T end) {
			return this->generate(start, end);
	    }
	    // start以上、end以下の乱数を生成します
		T generate(const T start, const T end) {
			return start + rand() % (end-start+1);
		}
	};

	// 指定したmap構造からランダムにキーを取り出します
	template<class T>
	std::string random_choice(T start, T end, int size) {
		Random<int> rdm;
		int i = 1;
		int num = rdm(1, size);
		while (start != end) {
			if (i >= num)
				return start->first;
			i++; start++;
		}
		return end->first;
	}

	template<class T>
	std::string get_item(T start, T end, int num) {
		int i = 1;
		while (start != end) {
			if (i >= num)
				return start->first;
			i++; start++;
		}
		return end->first;
	}

}
