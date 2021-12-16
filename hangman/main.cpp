#include <iostream>
#include <cstdlib>
#include <limits>
#include <new>
#include <string.h>
#include <windows.h>
#include <time.h>
#include <vector>
#include <fstream>
using namespace std;



void draw();
string chooseSecretWord();
bool getPlayerGuess();
bool gameOver();
void update();
void play();
void printPillar();
void printBar();
void init();

const int manCount=4;
int width, height,stringCount,guessTimeLeft,manCountLeft,guessedWordRightCount;
int *str,*man;
char guess;
string secretWord,guessedWord;



int main(){
    char answer,check;
    srand(time(0));
    do{
        init();
        play();
        cout << "Start a new game? [y] or [n] \n";
        do{
            scanf("%c%c",&answer,&check);
            if ((answer=='y'||answer=='n')&&check=='\n') {
                break;
            }
            else {
                cout<< "Invalid seclection! \n";
                cin.sync();
            }
        }
        while (1);
    }
    while(answer=='y');
    return 0;
}


void printPillar(){
    cout << "#";
}
void printBar(){
    cout << "=";
}
void printString(){
    cout << "|";
}
void printMan(int line, int manCountLeft){
    if (line==1) {
        if (manCountLeft >=1) cout <<" O ";
        else cout << " o ";
    }
    if (line==2) {
        if (manCountLeft >= 4 ) cout << "/|\\";
        else if (manCountLeft >=3 ) cout << "/| ";
        else if (manCountLeft >=2) cout << " | ";
        else cout << "   ";
    }
    if (line==3) {
        if (manCountLeft >=5) cout << " | ";
        else cout << "   ";
    }
    if (line==4) {
        if (manCountLeft>=7) cout << "/ \\";
        else if (manCountLeft>=6) cout << "/  ";
        else cout << "   ";
    }
}
void draw(){
    system("cls");
    for (int i=1; i<= height ; i++ ){
        for(int j=1; j<= width ;j++){
            if (i==1) {
                if (j==1) printPillar();
                else {
                    if (j==width) cout <<endl;
                    else printBar();
                }
            }
            else{
                if (j==1) printPillar();
                else{
                    if (j==width) cout << endl ;
                    else{
                        bool printed=0;
                        for (int k=1;k<=stringCount;k++){

                            if (i==str[k]&&j==width-2) {
                                printString();
                                printed=1;
                            }
                        }
                        for (int k=1;k<=manCount;k++){

                            if (i==man[k]&&j==width-3) {
                                printMan(k, manCountLeft);
                                printed=1;
                                j+=2;
                            }
                        }
                        if (printed == 0) cout << " ";
                    }

                }
            }
        }
    }
    cout << "Secret word: "<< guessedWord<<endl;
    //cout << secretWord<<endl;
}
bool gameOver(){
    if (guessTimeLeft <= 0) return 1;
    return 0;
}
void play(){
    while (!gameOver()){
        draw();
        if (guessedWordRightCount!=secretWord.length()){
            if (!getPlayerGuess()) continue;
            update();
        }
        else {
            update();
            break;
        }

    }
    if (guessTimeLeft > 0) cout <<"Congratulations, you win the game! \n";
    else cout << "Sorry, you lost \nSecret word is: "<<secretWord<<endl;

}
void init(){

    width=20;height=20;stringCount=5;manCountLeft=7;guessTimeLeft=stringCount+manCountLeft;guessedWord="",guessedWordRightCount=0;
    str=new int [stringCount+1];
    for( int i=1;i<=stringCount;i++){
        str[i]=i+1;
    }
    man=new int [manCount+1];
    man[1]=str[stringCount]+1;
    man[2]=man[1]+1;
    man[3]=man[2]+1;
    man[4]=man[3]+1;
    secretWord=chooseSecretWord();
    //secretWord="book";
    for (int i=1; i <= secretWord.length(); i++)
    guessedWord+="-";
}
string chooseSecretWord(){
    ifstream dataInput("data.txt");
    vector <string> wordBank;
    dataInput.is_open();
    string word;
    while (dataInput >> word){
        wordBank.push_back(word);
    }

    dataInput.close();
    int randomIndex=rand()%wordBank.size();
    return wordBank[randomIndex];
}
bool getPlayerGuess(){
    char input,check;
    do {
        cout << "Enter your guess: ";
        if (scanf("%c%c",&input,&check)!=2||check!='\n'||input == '\n'){
            cout << "Invalid guess! \n";
            Sleep(750);
            //cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cin.sync();
            return 0;
        }
        else break;
    }
    while (1);
    guess = input;
    return 1;
}
void update(){
    if (secretWord.find(guess)!=string::npos&&guessedWord.find(guess)==string::npos){
        for (int i=0; i < secretWord.length();i++) {
            if (secretWord[i]==guess) {
                guessedWord[i]=guess;
                guessedWordRightCount++;
            }
        }
    }
    else {
        guessTimeLeft--;
        if (stringCount>1) {
            stringCount--;
            for (int i = 1; i <= manCount;i++){
                man[i]--;
            }
        }
        else {
            manCountLeft --;
        }
    }

}
