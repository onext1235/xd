// GRA_gra.cpp : Ten plik zawiera funkcję „main”. W nim rozpoczyna się i kończy wykonywanie programu.
//
#include <iostream>
#include <string>
#include <vector>
#include <cstdlib>
#include <tuple>
#include <algorithm>
#include <cassert>
#include <random>
#include <conio.h>
#include <stdio.h>

using std::cout, std::cin, std::endl;
using std::string;
using Dac = std::vector<char>;
using Mac = std::vector<Dac>;

void ekran(Mac & m, int counter);
void points(Mac& m);
void enemies(Mac& m);
void wall(Mac& m);
int x(char ruch, int col);
int y(char ruch, int row);
int RNG();

int height = 20;
int width = 20;
int win_condition = 10;

int main()
{
    Mac m(height, Dac(width, '.'));
    m[0][0] = 'O';
    points(m);
    wall(m);
    enemies(m);
    
    char ruch;

    int row = 0;
    int col = 0;
    int counter = 0;
    int timer = 0;

    

    while(1)
    {
        ekran(m, counter);
        
        ruch = _getch();
        
        if (timer == 7)
        {
            enemies(m);
            timer = 0;
        }
        timer++;
        m[row][col] = '.';
        row = y(ruch, row);
        col = x(ruch, col);

        if (m[row][col] == '$')
            if (counter == win_condition - 1)
            {
                m[row][col] = 'O';
                counter++;
                ekran(m, counter);
                cout << "You WIN!" << endl;
                return 0;
            }
            else
                counter++;
        else if (m[row][col] == 'X')
        {
            cout << "You Lose!" << endl;
            return 0;
        }
        else if (m[row][col] == '#')
        {
            if (ruch == 'w')
                ruch = 's';
            else if(ruch == 'a')
                ruch = 'd';
            else if(ruch == 's')
                ruch = 'w';
            else if(ruch == 'd')
                ruch = 'a';
            row = y(ruch, row);
            col = x(ruch, col);
        }
        
        m[row][col] = 'O'; 
        
    }
    
    return 0;

}


int RNG()
{
    std::random_device rd;
    std::mt19937 mtRandomEngine(rd());
    std::uniform_int_distribution uni_distr(0, height - 1);
    std::vector< int >	random_decimals;
    std::generate_n(back_inserter(random_decimals), 1, [&]() { return uni_distr(mtRandomEngine); });
    return random_decimals[0];
}

void enemies(Mac& m)
{
    int rng_1;
    int rng_2;
    int counter = 3;
    for (int i = 0; i < counter; i++)
    {
        rng_1 = RNG();
        rng_2 = RNG();
        if (m[rng_1][rng_2] == '.')
            m[rng_1][rng_2] = 'X';
        else
            counter++;
    }
}

void points(Mac& m)
{
    int rng_1;
    int rng_2;
    int counter = win_condition;
    for (int i = 0; i < counter; i++)
    {
        rng_1 = RNG();
        rng_2 = RNG();
        if (m[rng_1][rng_2] == '.')
            m[rng_1][rng_2] = '$';
        else
            counter++;
    }
}

void wall(Mac& m)
{
    int rng_1;
    int rng_2;
    int counter = 10;
    for (int i = 0; i < counter; i++)
    {
        rng_1 = RNG();
        rng_2 = RNG();
        if (m[rng_1][rng_2] == '.')
            m[rng_1][rng_2] = '#';
        else
            counter++;
    }
}

int x(char ruch, int col)
{
    if (ruch == 'a')
        {
        if (col == 0)
            col = width - 1;
        else
            col = col - 1;
        }
    else if (ruch == 'd')
    {
        if (col == width - 1)
            col = 0;
        else
            col = col + 1;
    }
    return col;
}

int y(char ruch, int row)
{
    if (ruch == 'w')
    {
        if (row == 0)
            row = height - 1;
        else
            row = row - 1;
    }
    else if (ruch == 's')
    {
        if (row == height - 1)
            row = 0;
        else
            row = row + 1;
    }
    return row;
}

void ekran(Mac& m,int counter)
{
    system("cls");
    for (int r = 0; r < m.size(); r++)
    {
        for (int c = 0; c < m[0].size(); c++)
            cout << m[r][c] << " ";
        cout << endl;
    }
    cout << "Score: " << counter << endl;
}