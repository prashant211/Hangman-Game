#include <iostream>
#include <vector>
#include <fstream>
#include <string>
#include <time.h>
using namespace std;
void Message(string message, bool printTop = true, bool printBottom = true)//IT WILL PRINT ALL THE MESSAGES AND DESIGN
{
    if (printTop)
    {
        cout << "+---------------------------------+" << endl;
        cout << "|";
        system("Color 9");
    }
    else
    {
        cout << "|";
    }
    bool front = true;
    for (int i = message.length(); i < 33; i++)
    {
        if (front)
        {
            message = " " + message;
        }
        else
        {
            message = message + " ";
        }
        front = !front;
    }
    cout << message.c_str();
 
    if (printBottom)
    {
        cout << "|" << endl;
        cout << "+---------------------------------+" << endl;
    }
    else
    {
        cout << "|" << endl;
    }
}
void Hangman(int guessCount = 0)//IT WILL PRINT HANGMAN
{
    if (guessCount >= 1)
        Message("|", false, false);
    else
        Message("", false, false);
 
    if (guessCount >= 2)
        Message("|", false, false);
    else
        Message("", false, false);
 
    if (guessCount >= 3)
        Message("O", false, false);
    else
        Message("", false, false);
 
    if (guessCount == 4)
        Message("/  ", false, false);
    
    if (guessCount == 5)
        Message("/| ", false, false);
 
    if (guessCount >= 6)
        Message("/|\\", false, false);
    else
        Message("", false, false);
 
    if (guessCount >= 7)
        Message("|", false, false);
    else
        Message("", false, false);
 
    if (guessCount == 8)
        Message("/", false, false);
 
    if (guessCount >= 9)
        Message("/ \\", false, false);
    else
        Message("", false, false);
}
void Letters(string input, char from, char to)//IT WILL PRINT THE LETTERS FROM A TO Z
{
    string s;
    for (char i = from; i <= to; i++)
    {
        if (input.find(i) == string::npos)
        {
            s += i;
            s += " ";
        }
        else
            s += "  ";
    }
    Message(s, false, false);
}
void AvailableLetters(string taken)//IT WILL PRINT THE AVAILABLE LETTERS TO GUESS THE WORD
{
    Message("Available letters");
    Letters(taken, 'A', 'M');
    Letters(taken, 'N', 'Z');
}
bool CheckWin(string word, string guessed)//IT WILL CHECK THE POISSIBILITY OF THE WIN
{
    bool won = true;
    string s;
    for (int i = 0; i < word.length(); i++)
    {
        if (guessed.find(word[i]) == string::npos)
        {
            won = false;
            s += "_ ";
        }
        else
        {
            s += word[i];
            s += " ";
        }
    }
    Message(s, false);
    return won;
}
string RandomWord(string path)//IT WILL CHOOSE THE RANDOM WORD FORM FILE
{
    int lineCount = 0;
    string word;
    vector<string> v;
    ifstream reader(path);
    if (reader.is_open())
    {
        while (std::getline(reader, word))
            v.push_back(word);
 
        int randomLine = rand() % v.size();
 
        word = v.at(randomLine);
        reader.close();
    }
    return word;
}
int TriesLeft(string word, string guessed)//IT WILL CHECK HOW MANY TRIES ARE LEFT
{
    int error = 0;
    for (int i = 0; i < guessed.length(); i++)
    {
        if (word.find(guessed[i]) == string::npos)
            error++;
    }
    return error;
}
int main()//MAIN FUNCTION
{
    srand(time(0));
    string guesses;
    string wordToGuess;
    wordToGuess = RandomWord("words.txt");
    int tries = 0;
    bool win = false;
    do
    {
        system("cls"); 
        Message("WELCOME TO HANGMAN GAME");
        Hangman(tries);
        AvailableLetters(guesses);
        Message("Guess the word");
        win = CheckWin(wordToGuess, guesses);
 
        if (win)
            break;
 
        char x;
        cout << ">"; cin >> x;
 
        if (guesses.find(x) == string::npos)
            guesses += x;
 
        tries = TriesLeft(wordToGuess, guesses);
 
    } while (tries < 10);
 
    if (win)
        Message("YOU WON!");
    else
        Message("GAME OVER");
 
    system("pause"); 
    getchar();
    return 0;
}