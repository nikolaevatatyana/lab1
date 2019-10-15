#pragma once
#include "pch.h"
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <list>
#include <map>

typedef std::pair<std::string, long int> pair;

class Word {
public:
	Word() {
		int Counter = 0;
	};
	~Word() {};
	std::list<std::string> gettext();
	void parsetext(std::list<std::string> lines_);
	void parseline(std::string& line);
	std::vector<pair> sortV(std::map<std::string, long int> map);
	void push_csv_();

	std::ifstream inputFile;
	std::ofstream outputFile;
private:
	std::map<std::string, long int> words;
	std::list<std::string> lines;
	long int Count;

 };
 
 CPP
 #include "pch.h"
#include "lab1booop.h"
#include <iostream>
#include <fstream>
#include<string>
#include <vector>
#include <list>
#include <map>
#include <cctype>
#include <algorithm>


std::list<std::string> Word::gettext()
{
	for (std::string line; std::getline(inputFile, line); )
	{
		lines.push_back(line);
	}
	return lines;
}

void Word::parsetext(std::list<std::string> lines)
{
	for (std::string& line : lines)
	{
		parseline(line);
	}
}

void Word::parseline(std::string& line)
{
	std::string buf;

	for (char& c : line) {
		if (std::isalnum(static_cast<unsigned char>(c))) {
			buf.push_back(c);
		}
		else {
			std::map<std::string, long int>::iterator it = words.find(buf);
			if (!buf.empty()) {
				if (it != words.end()) {
					it->second++;
					Count++;
					buf.clear();
				}
				else {
					words[buf] = 1;
					Count++;
					buf.clear();
				}
			}
			else {
				continue;
			}
		}
	}
}

std::vector<pair> Word::sortV(std::map<std::string, long int> map)
{
	std::vector<pair> vec;

	std::copy(map.begin(), map.end(), std::back_inserter<std::vector<pair>>(vec));

	std::sort(vec.begin(), vec.end(), [](const pair& l, const pair& r) {
		if (l.second != r.second)
			return l.second > r.second;
		return l.first > r.first;
		});

	return vec;
}

void Word::push_csv_()
{
	for (auto const& pair : Word::sortV(words))
	{
		outputFile << pair.first << "," << pair.second << ","
			<< ((float)pair.second / (float)Count) * 100 << std::endl;
	}
}

int main(int argc, char** argv ) {
	Word w;

	w.inputFile.open("input_eng.txt");
	w.outputFile.open("output_eng.csv");

	if (!w.inputFile)
	{
		std::cout << "File 1 opening failed\n";
		return EXIT_FAILURE;
	}
	if (!w.outputFile)
	{
		std::cout << "File 2 opening failed\n";
		return EXIT_FAILURE;
	}

	w.parsetext(w.gettext());

}
