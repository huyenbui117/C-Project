#include <iostream>
#include <cstdlib>
#include <time.h>
#include <limits>
using namespace std;
int secretNumber, scores, guessCount;
int playerSecretNumber, guess, low, high;
char answer;
void init();
int getPlayerSecretNumber();
int getPlayerGuess();
int getComputerGuess(int guess, int &low, int &high, char answer);
void getAnswerFromComputer(int guess, int secretNumber);
char getAnswerFromPlayer(int guess);
void update();
void play(char mode);

int main()
{
    char answer, check, mode;
    do
    {
        system("cls");
        cout << "Select mode?\nPress [p] for Player Guess or [c] for Computer Guess!\nYour selection is: ";
        do
        {
            scanf("%c%c", &mode, &check);
            if ((mode == 'p' || mode == 'c') && check == '\n')
                break;
            else
            {
                cout << "Invalid seclection! \n";
                cin.sync();
            }

        } while (1);
        play(mode);
        cout << "Start a new game? [y] or [n] \n";
        do
        {
            scanf("%c%c", &answer, &check);
            if ((answer == 'y' || answer == 'n') && check == '\n')
                break;
            else
            {
                cout << "Invalid seclection! \n";
                cin.sync();
            }

        } while (1);
    } while (answer == 'y');
    return 0;
}
void init()
{
    scores = 200;
    secretNumber = rand() % 100 + 1;
    guessCount = 0;
    low = 1;
    high = 100;
    guess = 0;
    answer = '0';
}
int getPlayerGuess()
{
    int guess;
    char check;
    do
    {
        cout << "Enter your guess: ";
        if (scanf("%d%c", &guess, &check) != 2 || check != '\n')
        {
            cout << "Invalid guess \n";
        }
        else
        {
            break;
        }
        cin.sync();
    } while (1);
    return guess;
}
void getAnswerFromComputer(int guess, int secretNumber)
{
    if (guess > secretNumber)
        cout << "Too big" << endl;
    else if (guess < secretNumber)
        cout << "Too small" << endl;
    else if (guess == secretNumber)
        cout << "Correct!" << endl;
}
void update()
{
    guessCount++;
    scores -= 10 * guessCount;
    cout << "Score: " << scores << endl;
}

void play(char mode)
{
    srand(time(0));
    init();
    if (mode == 'p')
    {
        do
        {
            guess = getPlayerGuess();
            getAnswerFromComputer(guess, secretNumber);
            update();
            if (scores <= 0 && guess != secretNumber)
            {
                cout << "You lost! \nSecret number is: " << secretNumber << endl;
                break;
            }
        } while (guess != secretNumber);
    }
    else
    {
        getPlayerSecretNumber();
        do
        {
            guess = getComputerGuess(guess, low, high, answer);
            if (guess == 0)
            {
                cout << "Your answers are wrong! Can't find any number matching your requirement \n";
                return;
            }
            answer = getAnswerFromPlayer(guess);
        } while (answer != '=');
        cout << "Your number is: " << guess << endl;
    }
}
int getPlayerSecretNumber()
{
    int secretNumber;
    char check;
    do
    {
        cout << "Enter your secret number from 1 to 100: ";
        if (scanf("%d%c", &secretNumber, &check) != 2 || check != '\n' || secretNumber < 1 || secretNumber > 100)
        {
            cout << "Invalid input \n";
        }
        else
        {
            break;
        }
        cin.sync();
    } while (1);
    return secretNumber;
}
int getComputerGuess(int guess, int &low, int &high, char answer)
{
    if (answer == '>')
        high = guess;
    else if (answer == '<')
        low = guess;
    if (low == high)
        return 0;
    return ((low + high) / 2);
}
char getAnswerFromPlayer(int guess)
{
    char answer;
    cout << "Is " << guess << " your number?" << endl;
    do
    {
        cout << "Enter '>' for too high, '<' for too low, '=' for correct \nYour answer is: ";
        cin >> answer;
        if ((answer != '=') && (answer != '>') && (answer != '<'))
            cout << "Invalid Answer" << endl;
        cin.sync();
    } while ((answer != '=') && (answer != '>') && (answer != '<'));
    return answer;
}
