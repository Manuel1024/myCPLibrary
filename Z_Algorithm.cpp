/*
    Z_Algorithm:
    文字列が与えられたときに 各i(i = 0, 1, ..., |s|-1)について
    sとs[i:]の最長共通部分接頭辞(LCP)の長さを記録した配列をつくる
    戻り値のvectorは vec[i] := sとs[i:]のLCPの長さ vec[0] = |s|
*/
#include <iostream>
#include <vector>
#include <string>
using namespace std;

vector<int> Z_Algorithm(const string &s){
    vector<int> a(s.size());
    a[0] = s.size();
    int i = 1, j = 0;
    while(i < s.size()){
        while(i+j < s.size() && s[j] == s[i+j]) ++j;
        a[i] = j;
        if(j == 0){
            ++i; continue;
        }
        int k = 1;
        while(i+k < s.size() && k+a[k] < j){
            a[i+k] = a[k], ++k;
        }
        i += k; j -= k;
    }
    return a;
}

// Library Checker String Z Algorithm
int main(){
    string s;
    cin >> s;
    auto a = Z_Algorithm(s);
    for(int i = 0; i < s.size(); i++){
        if(i != 0) cout << " ";
        cout << a[i];
    }
    cout << endl;
    return 0;
}