//Ethan McCrary
//Assignment 8
//This program creates word clouds
#include <iostream>
#include <fstream>
#include <string>
#include <ctime>
#include <cstdlib>
#include <vector>
#include <tuple>
#include "WordCount.h"

using namespace std;

string cleanWord(string word, bool filterStopWords, vector<string> stopWords);
vector<string> readStopWords();
void output(const vector<WordCount> & wordCounts, const string filename, const int minFontSize, const int maxFontSize, const int minCount);

vector<string> readStopWords() {
	vector<string> stopWords;
	ifstream input;

	input.open("stopwords.txt");
	string word;
	while (input) {
		input >> word;
		stopWords.push_back(word);
	}
	input.close();

	return stopWords;
}

string cleanWord(string word, bool filterStopWords, vector<string> stopWords) {
	string cleanedWord;
	for (int i = 0; i < word.length(); i++) {
		word[i] = tolower(word[i]);												 //http://www.cplusplus.com/forum/beginner/25649/
		if (!ispunct(word[i]) && word[i] != '\n' && word[i] != '\t') {			 //http://www.cplusplus.com/forum/general/5555/
			cleanedWord += word[i];
		}
	}

	if (filterStopWords == true) {
		bool clean = true;
		for (int i = 0; i < stopWords.size(); i++) {
			if (cleanedWord == stopWords[i]) {
				clean = false;
			}
		}
		if (clean) {
			return cleanedWord;
		}
		else {
			return "";
		}
	}
	else {
		return cleanedWord;
	}
}

int linearSearch(vector<WordCount> wordCounts) {
	int maxCount = 0;
	for (int i = 0; wordCounts[i].getCount() > maxCount; i++) {
		if (wordCounts[i].getCount() > maxCount) {
			maxCount = wordCounts[i].getCount();
		}
	}
	return maxCount;
}

void WordBubblesort(vector<WordCount> &wordCounts, int sortType) {
	bool swapped = true;
	int j = 0;
	WordCount tmp;
	if (sortType == 1) {
		while (swapped) {
			swapped = false;
			j++;
			for (int i = 0; i < wordCounts.size() - j - 1; i++) {
				if (wordCounts[i].getWord() > wordCounts[i + 1].getWord()) {
					tmp = wordCounts[i];
					wordCounts[i] = wordCounts[i + 1];
					wordCounts[i + 1] = tmp;
					swapped = true;
				}
			}
		}
	}
	else if (sortType == 2) {
		while (swapped) {
			swapped = false;
			j++;
			for (int i = 0; i < wordCounts.size() - j - 1; i++) {
				if (wordCounts[i].getCount() > wordCounts[i + 1].getCount()) {
					tmp = wordCounts[i];
					wordCounts[i] = wordCounts[i + 1];
					wordCounts[i + 1] = tmp;
					swapped = true;
				}
			}
		}
	}
}

ostream & operator<<(ostream &out, const WordCount &word) {
	out << word.getWord() << endl;
	return out;
}

void output(const vector<WordCount> & wordCounts, const string filename, const int minFontSize, const int maxFontSize, const int minCount) {
	int maxCount = linearSearch(wordCounts);
	ofstream output;

	output.open("cloud.html");

	output << "<html>" << endl;
	output << "<head>" << endl;
	output << "<title> Word Cloud </title>" << endl;
	output << "</head>" << endl;
	output << "<h1 style='text-align:center;'> Word Cloud for " << filename + ".txt" << "</h1>" << endl;
	output << "<div style='background-color: #000000; margin: 10px 50px; text-align:center;'>" << endl;
	for (int i = 0; i != wordCounts.size(); i++) {
		if (wordCounts[i].getCount() >= minCount) {
			output << "<span style='font-size: " << ((wordCounts[i].getCount() / maxCount) * maxFontSize) + minFontSize << "; color: rgb(" << rand() % (156) + 100 << "," << rand() % (156) + 100 << "," << rand() % (156) + 100 << ")' >" << wordCounts[i] << "</span>" << endl;
		}
	}
	output << "</div>" << endl;
	output << "</body>" << endl;
	output << "</html>" << endl;

	output.close();
}

int main() {
	cout << "__________________________________" << endl;
	cout << "|        Ethan McCrary's       v.|" << endl;
	cout << "|      Word Cloud Generator    1 |" << endl;
	cout << "|________________________________|" << endl << endl;
	cout << "----------------------------------" << endl << endl;

	srand(time(NULL));
	string filename;
	int maxFontSize;
	int minFontSize;
	char filter;
	bool filterStopWords;
	int minWordCount;
	int sortType = 0;
	vector<WordCount> wordCounts;
	vector<string> stopWords = readStopWords();


	cout << "Enter the filename to process: ";
	cin >> filename;

	do {
		cout << "Max font size: ";
		cin >> maxFontSize;
		if (maxFontSize <= 0) {
			cout << "ERROR: max font size must be greater than 0." << endl;
		}
	} while (maxFontSize <= 0);

	do {
		cout << "Min font size: ";
		cin >> minFontSize;
		if (minFontSize >= maxFontSize) {
			cout << "ERROR: min font size cannot be greater than or equal to max font size." << endl;
		}
		if (minFontSize <= 0) {
			cout << "ERROR: min font size must be greater than 0." << endl;
		}
	} while (minFontSize >= maxFontSize || minFontSize <= 0);

	cout << "Filter stop words (Y/N): ";
	cin >> filter;

	do {
		cout << "Min word count: ";
		cin >> minWordCount;
		if (minWordCount < 0) {
			cout << "ERROR: minimum word count must be greater than or equal to 0." << endl;
		}
	} while (minWordCount < 0);

	cout << "Sort by 1) word or 2) count: ";
	cin >> sortType;

	if (filter == 'Y') {
		filterStopWords = true;
	}
	else if (filter == 'N') {
		filterStopWords = false;
	}

	ifstream input;
	input.open(filename + ".txt");
	string word;

	if (!input) {
		cout << "File did not open" << endl;
		system("pause");
		exit(-1);
	}

	while (input) {
		input >> word;
		word = cleanWord(word, filterStopWords, stopWords);
		if (word.length() > 0) {
			bool found = false;
			for (int i = 1; i < wordCounts.size(); i++) {
				if (word == wordCounts[i].getWord()) {
					wordCounts[i].incrementCount();
					found = true;
				}
			}
			if (!found) {
				WordCount wc(word);
				wordCounts.push_back(wc);
			}
		}
	}
	input.close();



	cout << "Words" << endl;

	for (int i = 0; i < wordCounts.size(); i++) {
		cout << wordCounts[i] << " ";
	}

	cout << "-------------------------------------\n";

	WordBubblesort(wordCounts, sortType);

	cout << "Words" << endl;
	for (int i = 0; i < wordCounts.size(); i++) {
		if (wordCounts[i].getCount() >= minWordCount) {
			cout << wordCounts[i].getCount() << " : " << wordCounts[i].getWord() << endl;
		}
	}

	output(wordCounts, filename, minFontSize, maxFontSize, minWordCount);

	system("pause");
}