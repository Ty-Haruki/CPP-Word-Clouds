#pragma once
#include <string>

using namespace std;

class WordCount {
private:
	string mWord;
	int mCount;
public:
	WordCount(){};
	WordCount(string word);

	string getWord() const;
	int getCount() const;

	void setCount(int count);

	void incrementCount();

};