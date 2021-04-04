//
//  main.cpp
//  SlidingPuzzleIDA*
//
//  Created by Simona Ivanova on 12.01.21.
//  Copyright © 2021 Simona Ivanova. All rights reserved.
//

#include <iostream>
#include <cmath>
#include <iomanip>
#include <limits>
#include <vector>
#include<list>
using namespace std;

class Board{
public:
    Board(){
        size=0;
    }
    Board(const Board& other){
        doCopy(other);
    }
    Board& operator=(const Board& other){
        if(this!=&other){
            doCopy(other);
        }
        return *this;
    }
    
    int getDigitSize() const{
        return(countDigitN(size));
    }
    
    void read(){
        int n;
        cout<<"Enter value for n: ";
        cin>>n;
        size=n;
        int zRow,zCol;
        do{
            cout<<"Enter row of zero: ";
            cin>>zRow;
        }while(zRow<=0 || zRow>size);
        do{
        cout<<"Enter col of zero: ";
        cin>>zCol;
        }while(zCol<=0 || zCol>size);
        zeroRow=zRow;
        zeroCol=zCol;
        int max=(size*size)-1;
        bool alreadyEnteredThisValue[max];
        for(int i=1;i<=max;i++){
            alreadyEnteredThisValue[i]=false;
        }
        for (int i=0;i<size;i++){
            for (int j=0;j<size;j++){
                if(i==zeroRow-1 && j==zeroCol-1){
                    matrix[i][j]=0;
                }
                else{
                    int number;
                    do{
                        cout<<"Enter value for: ["<<i+1<<";"<<j+1<<"]= ";
                        cin>>number;
                    }while(number<=0 || number>max || alreadyEnteredThisValue[number]==true);
                    matrix[i][j]=number;
                    alreadyEnteredThisValue[number]=true;
                }
            }
        }
    }
    
    void print() const{
        for (int i=0;i<size;i++){
            for(int j=0;j<size;j++){
                cout<<setw(countDigitN((size*size)-1))<<matrix[i][j]<<" |";
            }
            cout<<endl;
        }
        cout<<endl;
    }
    
    int getManhatanDistance() const{
        Board goalState;
        goalState.size=size;
        goalState.zeroRow=size-1;
        goalState.zeroCol=size-1;
        int number=1;
        for(int i=0;i<goalState.size;i++){
            for(int j=0;j<goalState.size;j++){
                if(i==goalState.zeroRow && j==goalState.zeroCol){
                    goalState.matrix[i][j]=0;
                }
                else{
                    goalState.matrix[i][j]=number;
                    number++;
                }
            }
        }
        //goalState.print();
        int sum=0;
        for(int i=0;i<size;i++){
            for(int j=0;j<size;j++){
                int currentNumber=matrix[i][j];
                if(currentNumber!=0){
                    int goalXCurrentNumber, goalYCurrentNumber;
                        for(int k=0;k<size;k++){
                            for(int l=0;l<size;l++){
                                if(goalState.matrix[k][l]==currentNumber){
                                    goalXCurrentNumber=k;
                                    goalYCurrentNumber=l;
                                }
                            }
                        }
                        int distance= abs(i-goalXCurrentNumber)+abs(j-goalYCurrentNumber);
                        sum += distance;
                        //cout<<"Distance of number "<<currentNumber<<" of it's goal state is "<<distance<<"."<<endl;
                }
            }
        }
        return sum;
    }
    
    bool isSovable()const{
        bool canSolve=false;
        //Ako size e nechetno
        if(!isEven(size) && isEven(countInversion())){
            canSolve=true;
        }
        else if(isEven(size)){
            int rowFromBottom=size-(zeroRow-1);
            if(isEven(rowFromBottom) && !isEven(countInversion())){
                canSolve=true;
            }
            else if(!isEven(rowFromBottom) && isEven(countInversion())){
                canSolve=true;
            }
        }
        return canSolve;
    }
    
    bool operator==(const Board& other)const{
        if(size!=other.size){
            return false;
        }
        else{
            for(int i=0;i<size;i++){
                for(int j=0;j<size;j++){
                    if(matrix[i][j]!=other.matrix[i][j]){
                        return false;
                    }
                }
            }
        }
        return true;
    }
    
    bool isGoal()const{
        Board goalState;
        goalState.size=size;
        goalState.zeroRow=size-1;
        goalState.zeroCol=size-1;
        int number=1;
        for(int i=0;i<goalState.size;i++){
            for(int j=0;j<goalState.size;j++){
                if(i==goalState.zeroRow && j==goalState.zeroCol){
                    goalState.matrix[i][j]=0;
                }
                else{
                    goalState.matrix[i][j]=number;
                    number++;
                }
            }
        }
        if(*this==goalState){
            return true;
        }
        else{
            return false;
        }
    }
    
    bool haveLeftNeighbor() const{
        if(zeroCol<size){
            return true;
        }
        else{
            return false;
        }
    }
    
    bool haveRightNeighbor() const{
        if(zeroCol-1>0){
            return true;
        }
        else{
            return false;
        }
    }
    
    bool haveUpNeighbor()const{
        if(zeroRow<size){
            return true;
        }
        else{
            return false;
        }
    }
    
    bool haveDownNeighbor() const{
         if(zeroRow-1>0){
             return true;
         }
         else{
             return false;
         }
    }
    
    Board makeLeftNeighbor() const{
        Board left;
        if(haveLeftNeighbor()){
            left.zeroRow=zeroRow;
            left.zeroCol=zeroCol+1;
            left.size=size;
            for(int i=0;i<size;i++){
                for(int j=0;j<size;j++){
                    if(i==left.zeroRow-1 && j==left.zeroCol-1){
                        left.matrix[i][j]=0;
                    }
                    else{
                        if(i==zeroRow-1 && j==zeroCol-1){
                            left.matrix[i][j]=matrix[zeroRow-1][zeroCol+1-1];
                        }
                        else{
                            left.matrix[i][j]=matrix[i][j];
                        }
                    }
                }
            }
        }
        else{
            cout<<"Can make move to left."<<endl;
        }
        return left;
    }
    
    Board makeRightNeighbor() const{
        Board right;
        if(zeroCol-1>0){
            right.zeroRow=zeroRow;
            right.zeroCol=zeroCol-1;
            right.size=size;
            for(int i=0;i<size;i++){
                for(int j=0;j<size;j++){
                    if(i==right.zeroRow-1 && j==right.zeroCol-1){
                        right.matrix[i][j]=0;
                    }
                    else{
                        if(i==zeroRow-1 && j==zeroCol-1){
                            right.matrix[i][j]=matrix[zeroRow-1][zeroCol-1-1];
                        }
                        else{
                            right.matrix[i][j]=matrix[i][j];
                        }
                    }
                }
            }
        }
        else{
            cout<<"Can make move to right."<<endl;
        }
        return right;
    }
    
    Board makeUpNeighbor() const{
           Board up;
           if(zeroRow<size){
               up.zeroRow=zeroRow+1;
               up.zeroCol=zeroCol;
               up.size=size;
               for(int i=0;i<size;i++){
                   for(int j=0;j<size;j++){
                       if(i==up.zeroRow-1 && j==up.zeroCol-1){
                           up.matrix[i][j]=0;
                       }
                       else{
                           if(i==zeroRow-1 && j==zeroCol-1){
                               up.matrix[i][j]=matrix[zeroRow-1+1][zeroCol-1];
                           }
                           else{
                               up.matrix[i][j]=matrix[i][j];
                           }
                       }
                   }
               }
           }
           else{
               cout<<"Can make move to up."<<endl;
           }
           return up;
       }
    
        Board makeDownNeighbor() const{
            Board down;
            if(zeroRow-1>0){
                down.zeroRow=zeroRow-1;
                down.zeroCol=zeroCol;
                down.size=size;
                for(int i=0;i<size;i++){
                    for(int j=0;j<size;j++){
                        if(i==down.zeroRow-1 && j==down.zeroCol-1){
                            down.matrix[i][j]=0;
                        }
                        else{
                            if(i==zeroRow-1 && j==zeroCol-1){
                                down.matrix[i][j]=matrix[zeroRow-1-1][zeroCol-1];
                            }
                            else{
                                down.matrix[i][j]=matrix[i][j];
                            }
                        }
                    }
                }
            }
            else{
                cout<<"Can make move to down."<<endl;
            }
            return down;
        }
    
    vector<Board> childBoard() {
        vector<Board> result;
        if(haveLeftNeighbor()){
            result.push_back(makeLeftNeighbor());
        }
        if(haveRightNeighbor()){
            result.push_back(makeRightNeighbor());
        }
        if(haveUpNeighbor()){
            result.push_back(makeUpNeighbor());
        }
        if(haveDownNeighbor()){
            result.push_back(makeDownNeighbor());
        }
        return result;
    }
    
    string boardLikeString() const{
        string result="";
        for(int i=0;i<size;i++){
            for(int j=0;j<size;j++){
                char temp=matrix[i][j]+48;
                result+=temp;
            }
        }
        return result;
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
    
    int countDigitN(int n) const{
        int countDigit=0;
        while(n>0){
            countDigit++;
            n/=10;
        }
        return countDigit;
    }
    
    int countInversion() const{
        int makeNewArr[(size*size)-1];
        int index=0;
        for(int i=0;i<size;i++){
            for(int j=0;j<size;j++){
                if(matrix[i][j]!=0){
                    makeNewArr[index]=matrix[i][j];
                    index++;
                }
            }
        }
        
        int inversion=0;
        for(int i=0;i<(size*size)-2;i++){
            for(int j=i+1;j<(size*size)-1;j++){
                if(makeNewArr[i]>makeNewArr[j]){
                    inversion++;
                }
            }
        }
        //cout<<"Number of inversion: "<<inversion<<endl;
        return inversion;
    }
    
    bool isEven(int n) const{
        if(n%2==0){
            return true;
        }
        else{
            return false;
        }
    }
};

bool contain(vector<Board> children,const Board& b){
    bool have=false;
    for (int i=0;i<children.size();i++){
        if(children[i]==b){
            have=true;
        }
    }
    return have;
}

int search(vector<Board> moves,int g,int bound){
    Board current=moves[moves.size()-1];
    
    int f=g+current.getManhatanDistance();
    if(f>bound){
        return f;
    }
    if(current.isGoal()){
        cout<<"Lenght: "<<g<<endl;
        cout<<endl;
        for(int i=0;i<moves.size()-1;i++){
            moves[i].print();
            if(moves[i].haveLeftNeighbor() && moves[i+1]==moves[i].makeLeftNeighbor()){
                cout<<"LEFT"<<endl;
            }
            else if(moves[i].haveRightNeighbor() && moves[i+1]==moves[i].makeRightNeighbor()){
                cout<<"RIGHT"<<endl;
            }
            else if(moves[i].haveUpNeighbor() && moves[i+1]==moves[i].makeUpNeighbor()){
                cout<<"UP"<<endl;
            }
            else if(moves[i].haveDownNeighbor() && moves[i+1]==moves[i].makeDownNeighbor()){
                cout<<"DOWN"<<endl;
            }
        }
        moves[moves.size()-1].print();
        return 0;
    }
    int min=1000;
    vector<Board> children=current.childBoard();
    for(int i=0;i<children.size();i++){
        if(!contain(moves, children[i])){
            moves.push_back(children[i]);
            int temp=search(moves,g+1,bound);
            if(temp==0){
                return 0;
            }
            if(temp<min){
                min=temp;
            }
            moves.pop_back();
        }
    }
    return min;
}

vector<Board> idaStar(const Board& b){
    int bound=b.getManhatanDistance();
    vector<Board> moves;
    //vector<Board> other;
    moves.push_back(b);
    do{
        int temp=search(moves,0,bound);
        if(temp==0){
            return moves;
        }
        bound=temp;
    }while(bound!=1000);
    return {};
}
int main() {
    
    Board b;
    b.read();
    //b.print();

    idaStar(b);
    return 0;
}
