#include <SFML/Graphics.hpp>
#include <vector>
#include <string>
#include <sstream>
#include <iomanip>
#include <chrono>
#include <thread>
#include <math.h>

#include <stdio.h>

std::string ASSETSPATH = "bin/assets/";
int clicked = 0;
int dead = 0;

int revealed;
void countRevealed();

#include "Face.hpp"
#include "Button.hpp"
#include "MineCounter.hpp"

MineCounter *mineCounter;

#include "Tile.hpp"
#include "Timer.hpp"

const float WINDOW_WIDTH = 500.f;
const float WINDOW_HEIGHT = 500.f;
float windowWidth = WINDOW_WIDTH;
float windowHeight = WINDOW_HEIGHT;

std::vector<std::vector<Tile*>> tileMap;

int mode = 0;

void countRevealed(){
    int x=0;
    for (int i = 0; i<tileMap.size(); i++){
        for (int j = 0; j<tileMap[0].size(); j++){
            if (!tileMap[i][j]->hidden && tileMap[i][j]->value != '#') ++x;
        }
    }

    //printf("x:\t%d\n\n", x);

    revealed = tileMap.size()*tileMap[0].size() - x;

}

int checkAround(std::vector<std::vector<Tile*>> tileMap, int row, int col){
    int count = 0;

    //printf("Checking Around!!\n");

    for (int i = row-1; i<row+2; i++){
        for (int j = col-1; j<col+2; j++){
            if (0<=i && i < tileMap.size() && 0<=j && j < tileMap[0].size()){
                //printf("row: %d ; col: %d\n", i, j);
                if (tileMap[i][j]->value == '#') ++count;
            }
        }
    }

    return count;
}

void openAroundSub(std::vector<std::vector<Tile*>> tileMap, int x, int y){
    tileMap[x][y]->value = '-';
    for (int i = x-1; i<x+2; i++){
        for (int j = y-1; j<y+2; j++){
            if (0<=i && i < tileMap.size() && 0<=j && j < tileMap[0].size()){
                //printf("row: %d ; col: %d\n", i, j);
                
                tileMap[i][j]->show();
                if (tileMap[i][j]->value == '0') openAroundSub(tileMap, i, j);
            }
        }
    }
}
void openAround(std::vector<std::vector<Tile*>> tileMap, int x, int y){
    if (tileMap[x][y]->value == '#' && !tileMap[x][y]->hidden){
        dead = 1;
        return;
    }
    if (tileMap[x][y]->value != '0' || tileMap[x][y]->hidden) return;
    openAroundSub(tileMap, x, y);
    for (int i = 0; i<tileMap.size(); i++){
        for (int j = 0; j<tileMap[0].size(); j++){
            if (tileMap[i][j]->value == '-')
                tileMap[i][j]->update('0');
        }
    }
}


int main(){    
    srand (time(NULL));

    auto timerA = std::chrono::high_resolution_clock::now();
    int waitingDec = 0;

    sf::RenderWindow window(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "Minesweeper!");

    window.setPosition(sf::Vector2i(sf::VideoMode::getDesktopMode().width/2-windowWidth/2, sf::VideoMode::getDesktopMode().height/2-windowHeight/2));

    float buttonWidth = windowWidth/3+50;
    float buttonHeight = 80;
    float buttonGap = 25;

    int windowOffsetTop = 75;
    int windowOffsetBottom = 40;
    int windowOffsetSides = 40;

    int rows=0, columns=0;
    int mines=0;

    int nextMode = 0;

    Face *Emote;

    Timer *Stopper;


    Button BTNEasy(windowWidth/2-buttonWidth/2, 100, buttonWidth, buttonHeight, "Easy", &mode, 1);
    Button BTNMedium(windowWidth/2-buttonWidth/2, 100+buttonGap+buttonHeight, buttonWidth, buttonHeight, "Medium", &mode, 2);
    Button BTNHard(windowWidth/2-buttonWidth/2, 100+2*(buttonGap+buttonHeight), buttonWidth, buttonHeight, "Hard", &mode, 3);

    BTNEasy.setColors(sf::Color(200, 200, 200), sf::Color(150, 150, 150), sf::Color(150, 150, 150), sf::Color(80, 80, 80));
    BTNEasy.setBorderSize(-3.f);
    BTNMedium.setColors(sf::Color(200, 200, 200), sf::Color(150, 150, 150), sf::Color(150, 150, 150), sf::Color(80, 80, 80));
    BTNMedium.setBorderSize(-3.f);
    BTNHard.setColors(sf::Color(200, 200, 200), sf::Color(150, 150, 150), sf::Color(150, 150, 150), sf::Color(80, 80, 80));
    BTNHard.setBorderSize(-3.f);

    sf::Cursor cursor;
    if (cursor.loadFromSystem(sf::Cursor::Cross))
        window.setMouseCursor(cursor);

    while (window.isOpen()){
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
            
             if (event.type == sf::Event::Resized){
                // update the view to the new size of the window
                sf::FloatRect visibleArea(0, 0, event.size.width, event.size.height);
                window.setView(sf::View(visibleArea));
            }
        }

        if (nextMode){
            mode = nextMode;
            nextMode = 0;
        }

        window.clear(sf::Color(222, 222, 222));

        if (!mode){
            BTNEasy.draw(&window);
            BTNMedium.draw(&window);
            BTNHard.draw(&window);
        }else{
            switch (mode){
                case 1:
                    rows = columns = 8;
                    mines=9;
                    break;
                case 2:
                    rows = columns = 16;
                    mines=40;
                    break;
                case 3:
                    rows = 30;
                    columns = 16;
                    mines=99;
                    break;
                default:
                    exit(1);
                    break;
            }


            // create tiles
            // execute once
            if (tileMap.empty()){
                for (int i = 0; i<rows; i++){
                    tileMap.push_back(std::vector<Tile*>());
                    for (int j = 0; j<columns; j++){
                        tileMap[i].push_back(new Tile(windowOffsetSides+30.f*(float)i+2.f*(float)i, windowOffsetTop+30.f*(float)j+2.f*(float)j, &Emote));
                        tileMap[i][j]->update('0');
                    }
                }

                windowHeight = windowOffsetTop+windowOffsetBottom+(columns*(30+2));
                windowWidth = windowOffsetSides*2+(rows*(30+2));
                

                window.setSize(sf::Vector2u(windowWidth, windowHeight));
                window.setPosition(sf::Vector2i(sf::VideoMode::getDesktopMode().width/2-windowWidth/2, sf::VideoMode::getDesktopMode().height/2-windowHeight/2));

                int temp = 0;
                int tempRow, tempCol;
                while (temp<mines){
                    tempRow = rand() % rows;
                    tempCol = rand() % columns;

                    if (tileMap[tempRow][tempCol]->value != '#'){
                        tileMap[tempRow][tempCol]->update('#');
                        ++temp;
                    }
                }

                for (int i = 0; i<rows; i++){
                    for (int j = 0; j<columns; j++){
                        if (tileMap[i][j]->value != '#')
                            tileMap[i][j]->update('0' + checkAround(tileMap, i, j));
                    }
                }
                
                Stopper = new Timer(windowWidth-windowOffsetSides-75, 20, 75, 31);
                Stopper->reset();
                Stopper->stop();

                mineCounter = new MineCounter(windowOffsetSides, 20, 75, 31);
                mineCounter->setMines(mines);

                countRevealed();

                Emote = new Face(windowWidth/2-32/2, 20, 32, 32, &dead);

            }


            if (!dead && revealed-mines == 0){
                dead = 5;
            }

            if (clicked && !dead){
                if(!Stopper->running) Stopper->start();
                for (int r = 0; r<rows; r++){
                    for (int c = 0; c<columns; c++){
                        openAround(tileMap, r, c);
                    }
                }

                clicked = 0;
            }


            if (dead){
                
                Stopper->stop();

                int timePassed = std::chrono::duration_cast<std::chrono::microseconds>(std::chrono::high_resolution_clock::now() - timerA).count() / 100'000;
                if (dead == 1){
                    timerA = std::chrono::high_resolution_clock::now();

                    for (int r = 0; r<rows; r++){
                        for (int c = 0; c<columns; c++){
                            if (tileMap[r][c]->value == '#'){
                                tileMap[r][c]->hidden = 0;
                            }
                        }
                    }
                    
                    //printf("dead stage 1 complete\n");
                    dead = 2;
                    waitingDec = 5;

                    Emote->setMood(2);
                }
                if (dead==2){
                    if (timePassed >= waitingDec){
                        for (int r = 0; r<rows; r++){
                            for (int c = 0; c<columns; c++){
                                if (tileMap[r][c]->value == '#'){
                                    sf::Color tileCurColor = tileMap[r][c]->getColor();
                                    if (tileCurColor != sf::Color(180, 0, 0)){
                                        if (tileCurColor.r - 15 >= 180){
                                            tileCurColor.r -= 15;
                                        }else{
                                            tileCurColor.r = 220;
                                        }

                                        if (tileCurColor.g - 30 >= 0){
                                            tileCurColor.g -= 30;
                                        }else{
                                            tileCurColor.g = 0;
                                        }

                                        if (tileCurColor.b - 30 >= 0){
                                            tileCurColor.b -= 30;
                                        }else{
                                            tileCurColor.b = 0;
                                        }
                                        tileMap[r][c]->setColor(tileCurColor);
                                    }else{
                                        dead = 3;
                                    }
                                }
                            }
                        }
                        waitingDec+=1;
                    }
                }
                if (dead==3){
                    //printf("stage 1\n");
                    for (int i = 0; i<rows; i++){
                        for (int j = 0; j<columns; j++){
                            delete tileMap[i][j];
                        }
                    }
                    //printf("stage 2\n");
                    windowWidth = WINDOW_WIDTH;
                    windowHeight = WINDOW_HEIGHT;
                    window.setSize(sf::Vector2u(windowWidth, windowHeight));
                    window.setPosition(sf::Vector2i(sf::VideoMode::getDesktopMode().width/2-windowWidth/2, sf::VideoMode::getDesktopMode().height/2-windowHeight/2));
                    //printf("stage 3\n");
                    mode = 0;
                    dead = 0;
                    tileMap.clear();
                    delete Stopper;
                    delete mineCounter;
                    delete Emote;
                }
                if (dead == 5){
                    Stopper->stop();
                    Emote->setMood(3);
                }

                if (dead == 6){
                    nextMode = mode;
                    dead = 3;
                }
            }

            if (mode){

                Stopper->draw(&window);
                mineCounter->draw(&window);
                Emote->draw(&window);

                if (Emote->getMood() == 1) Emote->setMood(0);

                for (int i = 0; i<rows; i++){
                    for (int j = 0; j<columns; j++){
                        tileMap[i][j]->draw(&window);
                    }
                }

                //printf("%d\n", revealed - mines);
            }
        }

        window.display();
    }

    return 0;
} 