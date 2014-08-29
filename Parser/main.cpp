#include <ctime>
#include <string>
#include <vector>
#include <fstream>
#include <iostream>
#include "parse_static.h"
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cout.precision(3);
    fstream fcase;
    fcase.open("test/cases", ios::in);
    string testCaseName;
    StaticParser parser;
    int totalCaseNum = 0, totalPassedNum = 0;
    double totalTime = 0.0;
    while (fcase >> testCaseName) {
        string buffer;
        cout << testCaseName << endl;
        for (string::size_type i = 0; i < testCaseName.length(); ++i) {
            cout << '-';
        }
        cout << endl;
        fstream fin;
        fin.open("test/" + testCaseName + ".in", ios::in | ios::binary);
        vector<string> in;
        while (getline(fin, buffer)) {
            in.push_back(buffer);
        }
        fin.close();

        fstream fout;
        fout.open("test/" + testCaseName + ".out", ios::in | ios::binary);
        vector<string> out;
        while (getline(fout, buffer)) {
            out.push_back(buffer);
        }
        fout.close();

        fstream ftest;
        ftest.open("test/" + testCaseName + ".test", ios::out | ios::binary);
        clock_t beginTime = clock();
        vector<string> test = parser.parseToHtmlList(in);
        clock_t endTime = clock();
        for (auto line : test) {
            ftest << line << '\n';
        }
        ftest.close();

        bool passed = true;
        for (vector<int>::size_type i = 0; i < test.size(); ++i) {
            if (test[i] != out[i]) {
                passed = false;
                cout << "First error at " << i + 1 << ": " << endl;
                cout << "\t" << "Output:  " << test[i] << endl;
                cout << "\t" << "Correct: " << out[i] << endl;
                break;
            }
        }

        ++totalCaseNum;
        double elapsedSecs = double(endTime - beginTime) / CLOCKS_PER_SEC;
        totalTime += double(endTime - beginTime);
        if (passed) {
            ++totalPassedNum;
            cout << "Passed ";
        } else {
            cout << "Failed ";
        }
        cout << fixed << elapsedSecs << endl;

        for (string::size_type i = 0; i < testCaseName.length(); ++i) {
            cout << '-';
        }
        cout << endl;
        cout << endl;
    }
    fcase.close();
    for (int i = 0; i < 79; ++i) {
        cout << '=';
    }
    cout << endl;
    if (totalPassedNum == totalCaseNum) {
        cout << "All " << totalCaseNum << " test cases passed." << endl;
    } else {
        cout << "Total: " << totalCaseNum << endl;
        cout << "Passed: " << totalPassedNum << endl;
        cout << "Failed: " << totalCaseNum - totalPassedNum << endl;
    }
    cout << "Total Seconds: " << fixed << (totalTime / CLOCKS_PER_SEC) << endl;
    return 0;
}
