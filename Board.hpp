//
//  Board.hpp
//  SlidingPuzzleIDA*
//
//  Created by Simona Ivanova on 12.01.21.
//  Copyright © 2021 Simona Ivanova. All rights reserved.
//

#ifndef Board_hpp
#define Board_hpp

#include <stdio.h>
#include <iostream>
using namespace std;

class Board{
public:
    Board(const Board& other){
        doCopy(other);
    }
    Board& operator=(const Board& other){
        if(this!=&other){
            doCopy(other);
        }
        return *this;
    }
    
private:
    //Променлива за размера на дъската.
    int size;
    //Матрицата с елементи.
    int matrix[15][15];
    //Редът, в които се намира празната плочка.
    int zeroRow;
    //Колоната, в която се намира празната плочка.
    int zeroCol;
    
    void doCopy(const Board& other){
        size=other.size;
        for (int i=0;i<size;i++){
            for(int j=0;j<size;j++){
                matrix[i][j]=other.matrix[i][j];
            }
        }
        zeroRow=other.zeroRow;
        zeroCol=other.zeroCol;
    }
};
#endif /* Board_hpp */
