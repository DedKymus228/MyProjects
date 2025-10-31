#include <iostream>
#include <fstream>
#include <windows.h>
#include <thread>
#include <chrono>
#include <conio.h>
using namespace std;


const int width = 10;
const int height = 20;
int posX = 10;
int posY = 1;
int rFig = 1;
bool collision = false;

struct Point {
    int x, y;
} a[4], b[4];

char field[height+2][width+2];
char fieldwf[height+2][width+2];

//figurki
int piece[7][4][2] = {
     {{0,0},{1,0},{0,1},{1,1}}, // cube
     {{0,0},{1,0},{2,0},{3,0}}, // priama
     {{1,0},{2,0},{0,1},{1,1}}, // s
     {{0,1},{1,1},{1,0},{2,0}}, // z
     {{0,0},{1,0},{2,0},{1,1}}, // t
     {{0,0},{1,0},{1,1},{1,2}}, // l
     {{1,0},{1,1},{1,2},{0,2}}  // j
};

// dly mercania
void GoToXY(int x, int y) {
    COORD coord;
    coord.X = x;
    coord.Y = y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}

//for color
void set_color(WORD color) {
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color);
}
const WORD COLOR_GREEN = FOREGROUND_GREEN | FOREGROUND_INTENSITY;
const WORD COLOR_DEFAULT = FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE;


bool colision(Point p[4]) {
    for (int i = 0; i < 4; i++) {
        int x = p[i].x;
        int y = p[i].y;

        if (field[y][x] != ' ') {
            return false;
        }
    }
    return true;
}

// gen figurki
void newFigure() {

    rFig = rand() % 7;


    int startX = (width / 2) - 1;
    int startY = 1;

    for (int i = 0; i < 4; i++) {
        a[i].x = piece[rFig][i][0] + startX;
        a[i].y = piece[rFig][i][1] + startY;
    }


    if (!colision(a)) {
        system("cls");
        cout << "\n\n!!! GAME OVER !!!\n\n";
        Sleep(5000);
        exit(0);
    }
}


void rotate() {
    for (int i = 0; i < 4; i++) b[i] = a[i];


    Point p = a[1];

    for (int i = 0; i < 4; i++) {
        int x = a[i].y - p.y;
        int y = a[i].x - p.x;

        b[i].x = p.x - x;
        b[i].y = p.y + y;
    }

    if (colision(b)) {
        for (int i = 0; i < 4; i++) a[i] = b[i];
    }
}


int main () {

    CONSOLE_CURSOR_INFO cursorInfo;
    GetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &cursorInfo);
    cursorInfo.bVisible = false;
    SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &cursorInfo);



      // gen pole
    for (int y = 0; y < height + 2; y++) {
        for (int x = 0; x < width + 2; x++) {
            if (y == 0 || y == height + 1 || x == 0 || x == width + 1)
                field[y][x] = '#';
            else
                field[y][x] = ' ';
        }
    }

    newFigure();

    int score = 0;

    int timer = 0;
    int gspeed = 200;


    while (true) {

        //control
        int current_gspeed = gspeed;

        if (_kbhit()) {
            char key = _getch();


            for (int i = 0; i < 4; i++) b[i] = a[i];

            if (key == 'a' || key == 'A')
                for (int i = 0; i < 4; i++) b[i].x--;
            if (key == 'd' || key == 'D')
                for (int i = 0; i < 4; i++) b[i].x++;
            if (key == 'w' || key == 'W')
                rotate();
            if (key == 's' || key == 'S')
                current_gspeed = 10;


            if (key == 'a' || key == 'A' || key == 'd' || key == 'D') {
                if (colision(b)) {
                    for (int i = 0; i < 4; i++) a[i] = b[i];
                }
            }
        }


        if (timer > current_gspeed) {


            for (int i = 0; i < 4; i++) b[i] = a[i];
            for (int i = 0; i < 4; i++) b[i].y++;

            if (colision(b)) {

                for (int i = 0; i < 4; i++) a[i] = b[i];
            } else {
                for (int i = 0; i < 4; i++) {
                    field[a[i].y][a[i].x] = 'X';
                }

               //clean line
                int k = height;
                for (int i = height; i > 0; i--) {
                    int count = 0;
                    for (int j = 1; j <= width; j++) {
                        if (field[i][j] == 'X') count++;
                            field[k][j] = field[i][j];
                    }
                    if (count < width) k--;
                }

                newFigure();
            }
            timer = 0;
        }



        // copy pole
        for (int y = 0; y < height + 2; y++) {
            for (int x = 0; x < width + 2; x++) {
                fieldwf[y][x] = field[y][x];
            }
        }

        // draaw figurki in array
        for (int i = 0; i < 4; i++) {
            fieldwf[a[i].y][a[i].x] = 'O';
        }


        GoToXY(0, 0);

        set_color(COLOR_GREEN);
        cout << "  Welcome to MGtetris" << endl;
        set_color(COLOR_DEFAULT);

        //draw pole
        for (int y = 0; y < height + 2; y++) {
            for (int x = 0; x < width + 2; x++) {
                cout << fieldwf[y][x] << " ";
            }
            cout << endl;
        }

        Sleep(10);
        timer += 70;
    }

    return 0;
}