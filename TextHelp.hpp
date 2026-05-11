#pragma once
#include <iostream>
#include <string>
#include <thread>
#include <chrono>
using namespace std;

/***********
  This code was adapted from:
  Ted Lyngmo
  https://stackoverflow.com/questions/78776920/how-to-make-a-gradual-text-function-in-c
  Accessed: May. 2026
*************/

void slowPrint(string text, int delayMilliseconds = 25) {
    for (int i = 0; i < text.length(); i++) {
        cout << text[i] << flush;
        this_thread::sleep_for(chrono::milliseconds(delayMilliseconds));
    }
}

void slowPrintLine(string text, int delayMilliseconds = 25) {
    slowPrint(text, delayMilliseconds);
    cout << endl;
}
void pauseForPlayer() {
    cout << "\nPress Enter to continue...";
    cin.ignore();
    cin.get();

}