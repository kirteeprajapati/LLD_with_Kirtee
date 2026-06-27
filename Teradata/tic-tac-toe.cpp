#include <iostream>
#include <vector>
#include <string>
#include <cmath>

using namespace std;// player, board game Move winningStrategy
class Player{
    int id;
    string name;
    char symbol;
    
    
public:
    Player(int id, string name, char symbol)
        : id(id), name(name), symbol(symbol){}
    
    int getId() const{
        return id;
    }
    
    string getName() const{
        return name;
    }
    
    char getSymbol() const{
        return symbol;
    }
};

class Move{
    int row;
    int col;
    Player* player;
    
public:
    Move(int row, int col, Player* player)
        : row(row), col(col), player(player){}
    
    int getRow() const{
        return row;
    }
    
    int getCol() const{
        return col;
    }
    
    Player* getPlayer() const{
        return player;
    }
};

class Board{
    int size;
    vector<vector<Player*>> grid;

public:
    Board(int n): size(n){
        grid.resize(n, vector<Player*>(n, nullptr));
    }
    
    int getSize() const{
        return size;
    }
    
    bool isValidMove(int row, int col) const{
        if(row<0 || col<0 || row>=size || col>= size) return false;
        return grid[row][col]==nullptr;
    }
    
    bool placeMove(const Move& move){
        int row = move.getRow();
        int col = move.getCol();
        
        if(!isValidMove(row, col)) return false;
        
        grid[row][col]=move.getPlayer();
        return true;
    }
    
    Player* getPlayerAt(int row, int col) const{
        if(row<0 || col<0 || row>=size || col>= size) return nullptr;
        return grid[row][col];
    }
    
    bool isFull() const{
        for(int i=0; i<size; i++){
            for(int j = 0; j<size; j++){
                if(grid[i][j]==nullptr) return false;
            }
        }
        return true;
    }
    
    void printBoard() const{
        for(int i=0; i<size; i++){
            for(int j=0; j<size; j++){
                if(grid[i][j]==nullptr) cout<<". ";
                else cout<< grid[i][j]->getSymbol()<<" ";
            }
            cout<<endl;
        }
    }
};

class WinningStrategy{
    // abstract class as it have 1 or more virtual functions
public:
    virtual bool checkWinner(const Move& move) = 0; 
    // = 0 says "I dont' know how to check the winner my child MUST IMPLEMENT THIS"
    // child classes are allowed to replace my implementations
    // Distructor
    virtual ~WinningStrategy() = default;
};

class NormalWinningStrategy : public WinningStrategy{

private:
    int n;
    vector<int> rows;
    vector<int> cols;
    int diagonal;
    int antidiagonal;
    
public:
    NormalWinningStrategy(int n) 
        : n(n), rows(n,0), cols(n, 0), diagonal(0), antidiagonal(0){}
    
    bool checkWinner(const Move& move) override{
        int row = move.getRow();
        int col = move.getCol();
        
        int value = (move.getPlayer()->getId()== 1) ? 1 : -1;
        
        rows[row]+=value;
        cols[col]+=value;
        if(row==col) diagonal+=value;
        if(row+col == n-1) antidiagonal+=value;
        
        return abs(rows[row])==n || abs(cols[col])==n || abs(diagonal)==n || abs(antidiagonal) == n;
    }
};

class DiagonalWinningStrategy : public WinningStrategy{
private:
    int n;
    int diagonal;
    int antidiagonal;

public:
    DiagonalWinningStrategy(int n) : n(n), diagonal(0), antidiagonal(0){}
    
    bool checkWinner(const Move& move) override{
        int row = move.getRow();
        int col = move.getCol();
        
        int value = move.getPlayer()->getId()==1 ? 1 : -1;
        if(row==col) diagonal+=value;
        if(row+col == n-1) antidiagonal+=value;
        
        return abs(diagonal)==n || abs(antidiagonal)==n;
    }
};

class RowColumnWinningStrategy : public WinningStrategy{
private:
    int n;
    vector<int> rows;
    vector<int> cols;
    
public:
    RowColumnWinningStrategy(int n) : n(n), rows(n,0), cols(n, 0){}
    
    bool checkWinner(const Move& move) override{
        int row = move.getRow();
        int col = move.getCol();
        
        int value = move.getPlayer()->getId() == 1 ? 1 : -1;
        rows[row]+=value;
        cols[col]+=value;
        
        return abs(rows[row])==n || abs(cols[col])==n;
    }
};

class Game{
private:

    Board board;
    vector<Player*> players;
    WinningStrategy* strategy;
    int currentPlayer;

public:

    Game(int boardSize,
         vector<Player*> players,
         WinningStrategy* strategy)
        : board(boardSize),
          players(players),
          strategy(strategy),
          currentPlayer(0)
    {
    }

    bool playMove(int row,int col)
    {
        Player* player = players[currentPlayer];

        Move move(row,col,player);

        // Step 1 : Place Move
        if(!board.placeMove(move))
        {
            cout<<"Invalid Move!\n";
            return false;
        }

        // Step 2 : Print Board
        cout<<"\n";
        board.printBoard();

        // Step 3 : Check Winner
        if(strategy->checkWinner(move))
        {
            cout<<"\nWinner is "
                <<player->getName()
                <<" ("<<player->getSymbol()<<")\n";

            return true;
        }

        // Step 4 : Check Draw
        if(board.isFull())
        {
            cout<<"\nGame Draw!\n";
            return true;
        }

        // Step 5 : Switch Player
        currentPlayer = (currentPlayer + 1) % players.size();

        cout<<"\nNext Turn : "
            <<players[currentPlayer]->getName()
            <<endl;

        return false;
    }
};

int main()
{
    int boardSize = 3;

    Player* p1 = new Player(1,"Kirtee",'X');
    Player* p2 = new Player(2,"GPT",'O');

    vector<Player*> players = {p1,p2};

    WinningStrategy* strategy =
            new NormalWinningStrategy(boardSize);

    Game game(boardSize,players,strategy);
    
    vector<pair<int, int>> moves = {
        {0,0},
        {1,1},
        {0,1},
        {2,2},
        {0,2}
    };

    bool gameOver = false;

    cout<<"Coordinates are 0-indexed.\n";

    for(auto move: moves){
        if(game.playMove(move.first, move.second)){
            gameOver = true;
            break;
        }
    }

    delete strategy;
    delete p1;
    delete p2;
};
