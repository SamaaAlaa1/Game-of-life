#include <iostream>
#include <thread>
#include <chrono>
#include <cstdlib>
using namespace std;

class Universe
{
private:
    int row, col;
    bool** arr1;
    bool** arr2;

public:
    Universe(int r, int c) : row(r), col(c) {
        arr1 = new bool*[row];
        arr2 = new bool*[row];
        for (int i = 0; i < row; ++i) {
            arr1[i] = new bool[col]{false};
            arr2[i] = new bool[col]{false};
        }
    }
    ~Universe() {
        for (int i = 0; i < row; ++i) {
            delete[] arr1[i];
            delete[] arr2[i];
        }
        delete[] arr1;
        delete[] arr2;
    }
    void reset()
    {
        for (int i = 0; i < row; ++i)
        {
            for (int j = 0; j < col; ++j)
            {
                arr1[i][j] = false;
            }
        }
    }
    void intial()
    {
        cout << "Choose how to intialize: " << endl;
        cout << "1.Choose the pattern \n2.Default pattern \n3.Random pattern\nEnter your choice:";
        char choice;
        cin >> choice;
        if (choice == '1')
        {
            inputPattern();
        }
        else if (choice == '2')
        {
            defaultPattern();
        }
        else if (choice == '3')
        {
            randomPattern();
        }
        else
        {
            cout << "Invalid choice. Using default pattern.\n";
            defaultPattern();
        }
    }
    void inputPattern()
{
    reset();
    cout << "Enter the number of alive cells: ";
    int numAliveCells;
    cin >> numAliveCells;

    cout << "Enter the coordinates of each alive cell in the form 'row col' (e.g., '2 3' for row 2, column 3):\n";
    for (int i = 0; i < numAliveCells; ++i)
    {
        int r, c;
        cout << "Enter coordinates of alive cell " << i + 1 << ": ";
        cin >> r >> c;

        if (r >= 0 && r < row && c >= 0 && c < col)
        {
            arr1[r][c] = true;
        }
        else
        {
            cout << "Invalid cell out of bounds.\n";
            --i;  
        }
    }
}

    void defaultPattern()
    {
        reset();
        arr1[1][2] = true;
        arr1[2][3] = true;
        arr1[3][1] = true;
        arr1[3][2] = true;
        arr1[3][3] = true;
    }
    void randomPattern()
    {
        reset();
        for (int i = 0; i < row; ++i)
        {
            for (int j = 0; j < col; ++j)
            {
                arr1[i][j] = (rand() % 2 == 0);
            }
        }
    }
    void display(int gen) 
    {
        system("cls");
        cout << "Generation " << gen+1 << ":" << endl;
        for (int i = 0; i < row; ++i)
        {
            for (int j = 0; j < col; ++j)
            {
                cout << (arr1[i][j] ? "#" : "-");
            }
            cout << "\n";
        }
    }
    int count_neighbors(int x, int y)
{
    int count = 0;
    for (int dx = -1; dx <= 1; ++dx)
    {
        for (int dy = -1; dy <= 1; ++dy)
        {
            if (dx == 0 && dy == 0)
                continue;
            int nx = x + dx;  
            int ny = y + dy; 
            if (nx >= 0 && nx < row && ny >= 0 && ny < col && arr1[nx][ny])
            {
                ++count;
            }
        }
    }
    
    return count;
}
    void next_generation()
    {
        for (int i = 0; i < row; ++i)
        {
            for (int j = 0; j < col; ++j)
            {
                int aliveNeighbors = count_neighbors(i, j);
                if (arr1[i][j])
                {
                    arr2[i][j] = (aliveNeighbors == 2 || aliveNeighbors == 3);
                }
                else
                {
                    arr2[i][j] = (aliveNeighbors == 3);
                }
            }
        }

        for (int i = 0; i < row; ++i)
        {
            for (int j = 0; j < col; ++j)
            {
                arr1[i][j] = arr2[i][j];
            }
        }
    }
    void run(int generations, int delayMilliseconds = 500) {
        for (int gen = 0; gen < generations; ++gen) {
            display(gen);
            next_generation();
            this_thread::sleep_for(chrono::milliseconds(delayMilliseconds));
            
        }
    }

};
int main()
{
    const int rows = 20;
    const int cols = 40;
    int generations;

    Universe universe(rows, cols);
    universe.intial();
    cout << "Enter number of generations: ";
    cin >> generations;
    universe.run(generations);
    return 0;
}