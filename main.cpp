#include <iostream>
#include <utility>
#include <ctime>


class Board {
public:
    int board[3][3] = {{-1, -1, -1}, {-1, -1, -1}, {-1, -1, -1}};

    void printBoard() {
        for (int i = 0; i < 3; i++) {
            for (int j = 0; j < 3; j++){
                switch(board[i][j]) {
                    case -1: std::cout << "|_"; break;
                    case 0: std::cout << "|O"; break;
                    case 1: std::cout << "|X"; break;
                }
            }
            std::cout << "|" << std::endl;
        }
        std::cout << "\n";
    }

    int checkWinner() {
        // row matches
        for (int i = 0; i < 3; i++)
            if (board[i][0] == board[i][1] && board[i][0] == board[i][2])
                return board[i][0];
        // column matches
        for (int i = 0; i < 3; i++)
            if (board[0][i] == board[1][i] && board[0][i] == board[2][i])
                return board[0][i];
        // diagonal matches
        if ( (board[0][0] == board[1][1] && board[0][0] == board[2][2]) \
        || (board[2][0] == board[1][1] && board[2][0] == board[0][2]) )
            return board[1][1];
        return -1;
    }
};

class Player {
public:
    Player(std::string s, int num) {
        type = std::move(s);
        playerNumber = num;
    }

    Board makeMove(Board board) {
        if (type == "h") return humanMove(board);
        else if (type == "cr") return computerRandom(board);
        return board;
    }

private:
    std::string type;
    int playerNumber;

    Board computerRandom(Board board) {
        for(;;) {
            int i = rand() % 3;
            int j = rand() % 3;
            if (board.board[i][j] == -1) {
                board.board[i][j] = playerNumber;
                return board;
            }
        }
    }

    Board humanMove(Board board) {
        for(;;) {
            int i, j;
            std::cout << "Enter cell position: ";
            std::cin >> i >> j;
            std::cout << std::endl;
            if (i < 0 || i > 2 || j < 0 || j > 2)
                std::cout << "Such cell doesn't exist!" << std::endl;
            else if (board.board[i][j] != -1)
                std::cout << "This cell isn't empty!" << std::endl;
            else {
                board.board[i][j] = playerNumber;
                return board;
            }
        }
    }
};


int main() {
    srand(time(nullptr));

    Board board;

    std::string type1, type2;
    std::cout << "First player: ";
    std::cin >> type1;
    std::cout << "\n";
    std::cout << "Second player: ";
    std::cin >> type2;
    std::cout << "\n";

    Player player1 = Player(type1, 1);
    Player player2 = Player(type2, 0);

    int moveCounter = 0;
    for(;;) {
        board = player1.makeMove(board);
        std::cout << "First player board:" << std::endl;
        board.printBoard();
        moveCounter++;
        if (board.checkWinner() != -1 || moveCounter == 9) break;

        board = player2.makeMove(board);
        std::cout << "Second player board:" << std::endl;
        board.printBoard();
        moveCounter++;
        if (board.checkWinner() != -1 || moveCounter == 9) break;
    }

    return 0;
}
