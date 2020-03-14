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

    bool isFull() {
        for (int i = 0; i < 3; i++)
            for (int j = 0; j < 3; j++)
                if (board[i][j] == -1)
                    return false;
        return true;
    }

    Board copyBoard() {
        Board brd;
        for (int i = 0; i < 3; i++)
            for (int j = 0; j < 3; j++)
                brd.board[i][j] = board[i][j];
        return brd;
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
        else if (type == "br") return computerBinaryRandom(board);
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

    Board computerBinaryRandom(Board board) {
        Board brd1 = board.copyBoard();
        Board brd2 = board.copyBoard();
        int left_counter = 0;
        int right_counter = 0;
        int left_i, left_j, right_i, right_j;

        for(;;) {
            left_i = rand() % 3;
            left_j = rand() % 3;
            if (brd1.board[left_i][left_j] == -1) {
                brd1.board[left_i][left_j] = playerNumber;
                break;
            }
        }
        for(;;) {
            right_i = rand() % 3;
            right_j = rand() % 3;
            if (brd2.board[right_i][right_j] == -1) {
                brd2.board[right_i][right_j] = playerNumber;
                break;
            }
        }
        while (brd1.checkWinner() == -1 && !brd1.isFull()) {
            for(;;) {
                int i = rand() % 3;
                int j = rand() % 3;
                if (brd1.board[i][j] == -1) {
                    left_counter++;
                    brd1.board[i][j] = (playerNumber + left_counter) % 2;
                    break;
                }
            }
        }
        while (brd2.checkWinner() == -1 && !brd2.isFull()) {
            for(;;) {
                int i = rand() % 3;
                int j = rand() % 3;
                if (brd2.board[i][j] == -1) {
                    right_counter++;
                    brd2.board[i][j] = (playerNumber + right_counter) % 2;
                    break;
                }
            }
        }
        if (brd2.checkWinner() == playerNumber) {
            board.board[right_i][right_j] = playerNumber;
        }
        else
            board.board[left_i][left_j] = playerNumber;
        return board;
    }

    Board humanMove(Board board) {
        for(;;) {
            int i, j;
            std::cout << "Enter cell position: ";
            std::cin >> i >> j;
            std::cout << std::endl;
            if (i < 1 || i > 3 || j < 1 || j > 3)
                std::cout << "Such cell doesn't exist!" << std::endl;
            else if (board.board[i - 1][j - 1] != -1)
                std::cout << "This cell isn't empty!" << std::endl;
            else {
                board.board[i - 1][j - 1] = playerNumber;
                return board;
            }
        }
    }
};


int main() {
    srand(time(nullptr));

    Board board;
    std::string types[] = {"h", "cr", "br"};
    int flag = 0;

    std::cout << "Tic-Tac-Toe Game" << std::endl;
    std::cout << "Types: ";
    for (const std::string& type: types)
        std::cout << type << " ";
    std::cout << std::endl;
    std::cout << "For human move enter two integers from 1 to 3 (cell coordinates), separated by space.\n" << std::endl;

    std::string type1, type2;
    std::cout << "First player: ";
    std::cin >> type1;
    std::cout << "\n";
    std::cout << "Second player: ";
    std::cin >> type2;
    std::cout << "\n";

    for (const std::string& type: types) {
        if (type1 == type) flag++;
        if (type2 == type) flag++;
    }
    if (flag != 2) {
        std::cout << "Wrong player types!" << std::endl;
        return 1;
    }

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

    if (board.checkWinner() == 1)
        std::cout << "First player won the game!" << std::endl;
    else if (board.checkWinner() == 0)
        std::cout << "Second player won the game!" << std::endl;
    else
        std::cout << "Nobody won the game!" << std::endl;

    return 0;
}
