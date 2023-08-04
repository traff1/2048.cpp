#include <iostream>
#include <vector>
#include <windows.h>
#include <string>
#include <math.h>
#include <conio.h>

using namespace std;

void set_cursor(int x = 0, int y = 0){
        HANDLE handle = nullptr;
        COORD coordinates;
        handle = GetStdHandle(STD_OUTPUT_HANDLE);
        coordinates.X = x;
        coordinates.Y = y;
        SetConsoleCursorPosition(handle, coordinates);
}

void color(int color_num){
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(hConsole, color_num);
}


class Map {

private:
    vector<vector<int>> map;

public:

    int size;
    Map(int size){
        this->size = size;
        resetMap();
    }

    void resetMap(){
        for(size_t i = 0; i < size; i++){
            vector<int> row;
            for(size_t j = 0; j < size; j++){
                row.push_back(0);
            }
            map.push_back(row);
        }
    }

    void setValue(int y, int x, int val){ map[y][x] = val; }
    int getValue(int y, int x){ return map.at(y).at(x); }

    int SpawnValue() {
        int count = 0;
        int i = rand() % size; int j = rand() % size;
        while (getValue(i, j) != 0){
            if(count == size*size){
                return 0;
            }
            i = rand()%size;
            j=rand() % size;
            count++;
        }
        int tmp = rand()%101;
        if(tmp > 10) { setValue(i, j, 2); return 2;}
        else { setValue(i, j, 4); return 4;}
    }

    int moveLeft() {
        int plusScore = 0;
        for(size_t i = 0; i < size; i++){
            for(size_t j = 0; j < size; j++){
                if (getValue(i, j) > 0){
                    int x = j;
                    while (x > 0)
                    {
                        if(getValue(i, x-1) == 0 ) { setValue(i, x-1, getValue(i, x)); setValue(i, x, 0); }
                        else if(getValue(i, x-1) == getValue(i, x)){
                            int tmpVal = ((getValue(i, x))*2);
                            setValue(i, x-1, tmpVal);
                            setValue(i, x, 0);
                            plusScore += tmpVal;
                            break;
                        }
                        x--;
                    }
                }
            }
        }
        return plusScore;
    }

    int moveRight(){
        int plusScore = 0;
        for(size_t i = 0; i < size; i++){
            for(size_t j = 0; j < size; j++){
                if(getValue(i, j) > 0){
                    int x = j;
                    while (x < size-1){
                        if(getValue(i, x+1) == 0) { setValue(i, x+1, getValue(i, x)); setValue(i, x, 0); }
                        else if (getValue(i, x+1) == getValue(i, x)) {
                            int tmpValue = ((getValue(i, x))*2);
                            setValue(i, x+1, tmpValue);
                            setValue(i, x, 0);
                            plusScore += tmpValue;
                            break;
                        }
                        x++;
                    }
                }
            }
        }
        return plusScore;
    }

    int moveUp(){
        int plusScore = 0;
        for(size_t i = 0; i < size; i++){
            for(size_t j = 0; j < size; j++){
                if(getValue(i, j) > 0) {
                    int y = i;
                    while (y > 0){
                        if(getValue(y-1, j)==0){ setValue(y-1, j, getValue(y, j)); setValue(y, j, 0); }
                        else if (getValue(y, j) == getValue(y-1, j)) {
                            int tmpValue = ((getValue(y, j))*2);
                            setValue(y-1, j, tmpValue);
                            setValue(y, j, 0);
                            plusScore += tmpValue;
                            break;
                        }
                        y--;
                    }

                }
            }
        }
        return plusScore;
    }

    int moveDown(){
        int plusScore = 0;
        for(size_t i = 0; i < size-1; i++){
            for(size_t j = 0; j < size; j++){
                if(getValue(i, j) > 0){
                    int y = i;
                    while (y < size-1)
                    {
                        if(getValue(y+1, j) == 0){ setValue(y+1, j, getValue(y, j)); setValue(y, j, 0); }
                        else if (getValue(y+1, j) == getValue(y, j)){
                            int tmpValue = ((getValue(y, j))*2);
                            setValue(y+1, j, tmpValue);
                            setValue(y, j, 0);
                            plusScore += tmpValue;
                            break;
                        }
                        y++;
                    }

                }
            }
        }
        return plusScore;
    }

    bool operator != (Map &otherMap) {
        if(this->size != otherMap.size) return true;

        for(size_t i = 0; i < size; i++){
            for(size_t j = 0; j < size; j++){
                if (this->getValue(i, j) != otherMap.getValue(i, j)) {
					return true;
				}
            }
        }
        return false;
    }

    int ValColor(int val){
        switch(val) {
            case 0:
                return 15;
            case 2:
                return 15;
           case 4:
                return 14;
            case 8:
                return 14;
            case 16:
                return 13;
            case 32:
                return 13;
            case 64:
                return 12;
            case 128:
                return 12;
            case 256:
                return 11;
            case 512:
                return 11;
            case 1024:
                return 10;
            case 2048:
                return 10;
            case 4096:
                return  9;
        }
        return 0;
    }

    void MapItems(int size){
        int y = ((size*2)+1);
        int x = ((size*7)+1);
        int x_f = 0;
        int y_f = 0;
        for(size_t i = 0; i < y; i++){
            for(size_t j = 0; j < x; j++){
                color(3);
                if (i == 0 && j == 0) {color(5); cout<<'/'; continue;}
                if (i == 0 && j == x -1) { color(5); char sym = '\\'; cout<<sym; continue;}
                if (i == y-1 && j == 0) { color(5); char sym = '\\'; cout<<sym; continue;}
                if (i == y-1 && j == x -1) { color(5); cout<<'/'<<endl; continue;}
                if (j % 7 == 0) { color(6); cout<<'|'; continue;}
                if (i % 2 == 0) { color(2); cout<<'-';  continue;}
                if(i%2 != 0 && (j-2)%7 == 0) {
                    while (y_f < size)
                    {
                        if(x_f >= size){
                            x_f = 0;
                            y_f++;
                            if((getValue(y_f, x_f)/10) >= 1){
                                j+=1;
                            }
                            if (getValue(y_f, x_f)/100 >= 1){
                                j+=1;
                            }
                            if (getValue(y_f, x_f)/1000 >= 1){
                                j+=1;
                            }
                            color(ValColor(getValue(y_f, x_f)));
                            cout<<getValue(y_f, x_f);
                            x_f++;
                            break;
                        } else {
                            if(getValue(y_f, x_f)/10 >= 1){
                                j+=1;
                            }
                            if (getValue(y_f, x_f)/100 >= 1){
                                j+=1;
                            }
                            if (getValue(y_f, x_f)/1000 >= 1){
                                j+=1;
                            }
                            color(ValColor(getValue(y_f, x_f)));
                            cout<<getValue(y_f, x_f);
                            x_f++;
                            break;
                        }
                    }
                    continue;
                }
                cout<<" ";
            }
            cout<<endl;
        }
    }

    void print(){
        set_cursor();
        MapItems(size);

    }
};

class Game{
private:
    Map* map;
public:
    int score = 0;
    int size;
    int Max = 0;
    bool GameOver = false;
    bool Won = false;
    bool exit = false;

    Game(int size){
        this->size = size;
        GameOver = false;
        Max = 0;
        score = 0;
        map = new Map(size);


        map->SpawnValue();
        map->SpawnValue();
    }

    void getAct(){
        while (true)
        {
            bool pressedKey = false;
            if(GetAsyncKeyState(VK_LEFT) & 0x8000 != 0 ){ score += map->moveLeft();
            pressedKey = true; map->SpawnValue(); break;}
            else if (GetAsyncKeyState(VK_RIGHT) & 0x8000 != 0 ) { score += map->moveRight();
            pressedKey = true; map->SpawnValue(); break;}
            else if (GetAsyncKeyState(VK_UP) & 0x8000 != 0 ) { score += map->moveUp();
            pressedKey = true; map->SpawnValue(); break;}
            else if (GetAsyncKeyState(VK_DOWN) & 0x8000 != 0 ) { score += map->moveDown();
            pressedKey = true; map->SpawnValue(); break;}

        }
    }

    bool checkWon() {
        for(size_t i = 0; i < size; i++){
            for(size_t j = 0; j < size; j++){
                int val;
                val = map->getValue(i, j);
                if(val > Max) {
                    Max = val;
                    if (Max >= 2048 ) { return true; }
                }

            }
        }
        return false;
    }


    bool checkGameOver() {

		bool checker = false;

		Map othMap = *map;

		othMap.moveLeft();
		if (*map != othMap) {
			checker = true;
		}

		if (!checker) {
			othMap = *map;
			othMap.moveRight();
			if (*map != othMap) {
				checker = true;
			}
		}

		if (!checker) {
			othMap = *map;
			othMap.moveUp();
			if (*map != othMap) {
				checker = true;
			}
		}

		if (!checker) {
			othMap = *map;
			othMap.moveDown();
			if (*map != othMap) {
				checker = true;
			}
		}

		if (checker == false) {
			return true;
		}

        return false;
	}

    void showScore(int score, int size) {
        color(11);
        cout << "Score: " << score;
        color(0);
    }

    bool GetChoice(){
        while (true)
        {
            if(GetAsyncKeyState(0x59) & 0x8000 != 0 ){ cout<<"y"; Sleep(1000); return true; }
            else if(GetAsyncKeyState(0x4E) & 0x8000 != 0) { cout<<"n"; Sleep(1000); return false; }
        }
        return false;
    }


    void run(){
        while (true)
        {
            system("cls");
            map->print();
            showScore(score, size);
            if (checkWon()) {
                color(6);
                cout<<endl<<"You got 2048! Do you want to restart? (y/n): ";
                break;
            }
            else if (checkGameOver()) {
                color(4);
                cout<<endl<<"You lost! Do you want to restart? (y/n): ";
                break;
            };
            getAct();
        }
        bool c = GetChoice();
        if (c) {

            for(size_t i = 0; i < size; i++){
                for(size_t j = 0; j < size; j++){
                    map->setValue(i, j, 0);
                }
            }
            score = 0;
            Max = 0;
            Won = false;
            GameOver = false;
            map->SpawnValue();
            map->SpawnValue();
            run();
        }
        else {
            system("cls");
            exit;
        }

    }
};

int main(int argc, char* argv[] ){
    system("cls");
    int size = 2;
    Game game(size);
    game.run();
    return 0;
}
