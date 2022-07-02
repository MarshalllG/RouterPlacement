#include<iostream>
#include<ctime>
#include<cstdlib>
#include <random>
#include <vector>
using namespace std;

struct point
{
    unsigned x, y; 
};

int Random(int a, int b)
{ 
    static random_device rd;
    static mt19937 gen(rd());
    uniform_int_distribution<int> dis(a,b);
    return dis(gen);
}

vector<vector<char> > CreateGrid (vector<vector<char> > cells)
{
    for (unsigned r = 0; r < cells.size(); r++)
    {
        for (unsigned c = 0; c < cells[r].size(); c++)
        {
            cells[r][c] = '.';
        }
    }
    return cells;
}

void PrintGrid(vector<vector<char> > cells)
{
    for (unsigned r = 0; r < cells.size(); r++)
    {
        for (unsigned c = 0; c < cells[0].size(); c++)
        {
            cout << cells[r][c];
        }
        cout << endl;
    }
}

vector<vector<char> > AddWall(vector<vector<char> > cells, point start, unsigned size, unsigned axis)
{

    unsigned i = start.x;
    unsigned j = start.y;
    if (axis == 0) // Add a row
    {
        while (size > 0)
        {
            cells[i][j] = '#';
            size--;
            j++;
        }
    }
    else if (axis == 1) // Add a column
    {
        while (size > 0)
        {
            cells[i][j] = '#';
            size--;
            i++;
        }
    }
    
    return cells;
}

vector<vector<char> > AddWallInBuilding(vector<vector<char> > cells, unsigned length, unsigned axis)
{
    unsigned r, c, i;

    // Select a point in the building
    do 
    {
        r = Random(0, cells.size()-1);
        c = Random(0, cells[r].size()-1);
    }
    while(cells[r][c] != '.');

    // Print Random Walls
    i = 0;
    while (i < length && r < cells.size() && c < cells[r].size())
    {
        if (cells[r][c] == '.')
            cells[r][c] = '#';

        if (axis == 1)
            c++;
        else
            r++;
        
        i++; 
    }
 
    return cells;
}


vector<vector<char> > PrintSquare(vector<vector<char> > cells)
{
    unsigned rows = cells.size();
    unsigned columns = cells[0].size();

    // Select the wall size
    unsigned wall_size;
    rows > columns ? wall_size = Random(4, columns) : wall_size = Random(4, rows);
    // cout << "Wall size: " << wall_size << endl;

    // Select a good point 
    point start_wall; 
    do
    {
        start_wall.x = Random(0, rows-wall_size);
        start_wall.y = Random(0, columns-wall_size);
    } while (start_wall.x + wall_size > rows-1 && start_wall.x + wall_size < 0 && 
             start_wall.y + wall_size > columns-1 && start_wall.y + wall_size < 0);
    // cout << "Starting from point: (" << start_wall.x << ", " << start_wall.y << ")" << endl;
  
    // Print 2 walls
    cells = AddWall(cells, start_wall, wall_size, 0);
    cells = AddWall(cells, start_wall, wall_size, 1);

    // Print 2 walls
    start_wall.r += wall_size-1;
    cells = AddWall(cells, start_wall, wall_size, 0);
    start_wall.r -= wall_size-1;
    start_wall.c += wall_size-1;
    cells = AddWall(cells, start_wall, wall_size, 1);

    return cells;
}

vector<vector<char> > FillWithLines (vector<vector<char> > cells)
{
    for (unsigned r = 0; r < cells.size(); r++)
    {
        unsigned found = 0;
        for (unsigned c = 0; c < cells[0].size(); c++)
        {
            if (cells[r][c] == '#')
            {
                if (found == 0)
                    found = 1;
                else if (cells[r][c+1] == '.')
                    found = 0;
            }

            if (found == 0 && cells[r][c] != '#')
                cells[r][c] = '-';
        }
    }

    return cells;
}

int main(int argc, char* argv[])
{
    const unsigned DIM = 100;
    const unsigned ROUTER_RANGE = 10;
    const unsigned MAX_BB_PRICE = 5;
    const unsigned MAX_R_PRICE = 100;
    const unsigned BUDGET = 10000;
    unsigned rows, columns, radius, b_price, r_price, budget, r_i, c_i;
    vector<vector<char> > cells;
    point start;
    unsigned w = 0;
    const unsigned MAX_WALLS = 7;
    unsigned walls_to_add = Random(1, MAX_WALLS);

    rows = Random(6, DIM);
    columns = Random(6, DIM);
  
    do
    {
        radius = Random(1, ROUTER_RANGE);
    } while (radius > rows || radius > columns);
       
    b_price = Random(1, MAX_BB_PRICE);
    r_price = Random(5, MAX_R_PRICE);
    budget = Random(1, BUDGET);
    r_i = Random(0, rows-1);
    c_i = Random(0, columns-1);

    cells.resize(rows, vector<char>(columns));

    cout << rows << " " // rows
         << columns << " " // columns
         << radius << endl
         << b_price << " "
         << r_price << " "
         << budget << endl
         << r_i << " " // initial cell row
         << c_i << endl; // initial cell column

    // Add '.'
    cells = CreateGrid(cells);

    // Add '#'
    cells = PrintSquare(cells);

    // Add '-'
    cells = FillWithLines (cells);

    // Add walls in the building
    do
    {
        // Select the wall size
        unsigned wall_size;
        rows > columns ? wall_size = Random(4, columns-1) : wall_size = Random(4, rows-1);

        cells = AddWallInBuilding(cells, wall_size, Random(0,1));
        w++;
    } while(w < walls_to_add);


    /******* PRINT GRID *******/
    PrintGrid(cells);

    return 0;
}


