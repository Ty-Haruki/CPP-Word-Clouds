#include "WordCount.h"

WordCount::WordCount(string word) {
	mWord = word;
	mCount = 1;
}

string WordCount::getWord() const{
	return mWord;
}

int WordCount::getCount() const {
	return mCount;
}

void WordCount::setCount(int count){
	mCount = count;
}

void WordCount::incrementCount(){
	mCount++;
}