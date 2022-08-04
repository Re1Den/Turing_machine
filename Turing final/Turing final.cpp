#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <stdlib.h> // stoi
#include <windows.h> // sleep
#include <iomanip>

using namespace std;

struct TTuring
{
    string CurrentState, NextState;
    char CurrentSymbol, NextSymbol, Direction;
};

int Instructions();
void Read(vector<TTuring>& states, string& tape, int& HeadPostion);
void Run(vector<TTuring> states, string tape, int HeadPosition);
string Pointer(string tape, int HeadPosition);
int SpeedUp(string tape, int HeadPosition);

int main()
{
    vector<TTuring> states;
    string tape;
    int HeadPosition;

    Instructions();
    Read(states, tape, HeadPosition);
    Run(states, tape, HeadPosition);

    return 0;
}

void Read(vector<TTuring>& states, string& tape, int& HeadPosition)
{
    TTuring temp;
    string read;
    bool head = true;

    string f_name;
    cout << '\n' << "Enter the file name: ";
    cin >> f_name;
    ifstream fin;
    fin.open(f_name);

    while (!fin.eof())
    {

        getline(fin, read, '\n');
        if (!read.empty())
        {
            if (tape.empty()) // Read tape
                tape = read;

            else if (head) // Read head position 
            {
                HeadPosition = stoi(read);
                head = false;
            }
            else
            {
                string z; // Next state
                string y = read.substr(0, read.find(' ')); // Current state
                read.erase(0, y.length() + 1); // Removes current state from string
                if (read[read.length() - 1] != ' ') // Checks if there is space at the end of the string or 
                    z = read.substr(6, read.find('\n'));
                else
                    z = read.substr(6, read.find(' '));

                read.erase(5, z.find('\n'));


                for (int i = 0; i < read.length(); i++)
                    if (read[i] == ' ')
                        read.erase(i, 1);

                temp.CurrentState = y;
                temp.CurrentSymbol = read[0];
                temp.NextSymbol = read[1];
                temp.Direction = read[2];
                temp.NextState = z;

                states.push_back(temp);
            }
        }
    }

    fin.close();
}

void Run(vector<TTuring> states, string tape, int HeadPosition)
{

    HeadPosition--;
    string mode = "0";
    bool loop = true, speedup = true;

    while (loop)
    {
        for (int i = 0; i < states.size(); i++)
        {
            if (GetAsyncKeyState(VK_ESCAPE)) // To terminate
            {
                cout << '\n' << "Programe has beenn terminated" << '\n';
                exit(0);
            }

            if (GetAsyncKeyState(VK_SPACE)) // To pause
            {
                cout << '\n' << "Programe has beenn paused" << '\n';
                system("pause");
            }

            if (states[i].CurrentState == mode && states[i].CurrentSymbol == tape[HeadPosition])
            {
                tape[HeadPosition] = states[i].NextSymbol;
                mode = states[i].NextState;

                if (states[i].Direction == 'R')
                    HeadPosition++;

                else if (states[i].Direction == 'L')
                    HeadPosition--;

                else // Wrong direction input
                {
                    cout << '\n' << "Halted. Wrong direction input '" << states[i].Direction << "' in state '" << states[i].CurrentState << "'." << '\n' << '\n';
                    loop = false;
                    break;
                }

                if (HeadPosition == -1) // Range -1
                {
                    tape.insert(0, " ");
                    HeadPosition++;
                }

                if (HeadPosition == tape.size()) // Range size()+1
                {
                    tape.insert(tape.size(), " ");
                    HeadPosition--;
                }

                if (GetAsyncKeyState(VK_UP)) // Speed up
                {
                    speedup = false;
                    system("CLS");
                    cout << "This might take for a while..." << '\n';
                }

                if (speedup)
                {
                    system("CLS");
                    cout << tape << '\n';
                    cout << Pointer(tape, HeadPosition);
                }

                break;
            }
            else if (i == states.size() - 1) // No rule for position - HALT
            {
                cout << '\n' << "Halted. No rule for state '" << mode << "' and symbol '" << tape[HeadPosition] << "'.";
                loop = false;
            }
        }
    }

    
    if (speedup == false)
        SpeedUp(tape, HeadPosition);

}

string Pointer(string tape, int HeadPosition)
{
    string cursor(tape.size(), ' ');
    cursor[HeadPosition] = '^';
    Sleep(20);

    return cursor;
}

int Instructions()
{
    cout << setw(20) << "MENU" << '\n' << '\n';
    cout << "Press 'esc' key to terminate program" << '\n';
    cout << "Press 'space bar' key to pause program" << '\n';
    cout << "Press 'UP ARROW key' key to speeed up program (Doesn't work with infinite loops)" << '\n';

    return 0;
}

int SpeedUp(string tape, int HeadPosition)
{
    cout << '\n' << tape << '\n' << Pointer(tape, HeadPosition);
    return 0;
}
