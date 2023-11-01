// Task_Quant_Word.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <map>
#include <thread>
#include <mutex>
#include <sstream>
#include <algorithm>

#include "File_Helper.h"

using namespace std;

void Counting_Word(map<string,int>& result_, vector<string> data_) {
    char arr_symb[] = {'.', ',', ':', '!', '?', '/', '\\', '|', '-', '_','"'};
    map<string, int> middle_result_{};
    for (auto el : data_) {
        istringstream iss(el);
        string word;
        char delimiter = ' ';
        vector<string> line_data{};
        while (getline(iss, word, delimiter)) {
            if (word.size() == 0) {
                continue;
            }
            char last_elem = word[word.size()-1];
            char* result = std::find(std::begin(arr_symb), std::end(arr_symb), last_elem);
            if (result != std::end(arr_symb)) {
                word.pop_back();
            };
            if (word[0] == '"' || word[0] == '\t') {
                word.erase(0, 1);
            }
            line_data.push_back(word);
        }
        for (auto word : line_data) {
            map<string, int>::iterator iter = middle_result_.find(word);
            if (iter == middle_result_.end()) {
                middle_result_.insert(make_pair(word, 1));
            } 
            else {
                iter->second++;
            }
        }
    }

    mutex mtx;
    mtx.lock();
    for (auto pair : middle_result_) {
        map<string, int>::iterator iter = result_.find(pair.first);
        if (iter != result_.end()) {
            iter->second = iter->second + pair.second;
        }
        else {
            result_.insert(pair);
        }
    }
    mtx.unlock();
}

bool Sort_Map(const pair<string, int>& a, const pair<string, int>& b) {
    return a.second > b.second;
}

int main()
{
    map<string, int> result;
    vector<thread> vec_threads;
    File_Helper my_file;

    if (my_file.Get_Status() != 1) {
        return -1;
    }
    
    int n = 20;

    int quantity = my_file.Get_Data().size() / n;
    for (int i = 0; i < quantity; i++) {
        auto vec = my_file.Get_Data();
        vector<string> process_data(vec.begin() + i * n, vec.begin() + (i + 1) * n - 1);
        vec_threads.emplace_back(Counting_Word, ref(result), process_data);
    }

    for (std::thread& t : vec_threads) {
        t.join();
    }

    cout << "All threads have finished." << endl;


    vector<pair<string, int>> sortedPairs(result.begin(), result.end());

    sort(sortedPairs.begin(), sortedPairs.end(), Sort_Map);

    for (const auto& pair : sortedPairs) {
        std::cout << pair.first << " -> " << pair.second << std::endl;
    }

    return 0;
}

