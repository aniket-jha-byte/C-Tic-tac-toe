#include <bits/stdc++.h>
using namespace std;

/* Macros used to represent the state of each square */
#define EMPTY 0
#define CIRCLE 1
#define CROSS 2

/* Creating array to generate random entries by computer */
int C_entry[9] = {1, 2, 3, 4, 5, 6, 7, 8, 9};
int t;

/* Initialize the game board by setting all nine squares to EMPTY and shuffling the array for mark by computer using rand() */
void initGameBoard(int gameBoard[3][3]) {
    srand(time(0));
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            gameBoard[i][j] = EMPTY;
        }
    }
    for (int j = 8; j >= 0; j--) {
        int random = rand() % (j + 1);
        int temp = C_entry[j];
        C_entry[j] = C_entry[random];
        C_entry[random] = temp;
    }
    t = 0;
}

/* Function to print the gameboard */
void printGameBoard(int gameBoard[3][3]) {
    cout << endl;
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            if (gameBoard[i][j] == EMPTY) { /* Checks if entry is empty, then print the location of that position */
                if (i == 0)
                    cout << "|" << j + 1 << "|";
                else if (i == 1)
                    cout << "|" << 3 + j + 1 << "|";
                else
                    cout << "|" << 6 + j + 1 << "|";
            } else if (gameBoard[i][j] == CIRCLE) /* Checks if entry at the location is circle, then print O in place of it */
                cout << "|O|";
            else if (gameBoard[i][j] == CROSS) /* Checks if entry at the location is cross, then print X in place of it */
                cout << "|X|";
        }
        cout << endl;
    }
    cout << endl;
}

/* Function to save the game in a text file */
int saveGame(int gameBoard[3][3], int numOfHumanPlayers, int currentPlayer) {
    ofstream file("game.txt");
    if (!file.is_open()) {
        return 0;
    }
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            file << gameBoard[i][j] << " ";
        }
    }
    file << numOfHumanPlayers << " ";
    file << currentPlayer << " ";
    file.close();
    return 1;
}

/* Function to open the last saved */
int loadGame(int gameBoard[3][3], int *numOfHumanPlayers, int *currentPlayer) {
    ifstream file("game.txt");
    if (!file.is_open()) {
        return 0;
    }
    int data;
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            if (file >> data)
                gameBoard[i][j] = data;
        }
    }
    if (file >> data)
        *numOfHumanPlayers = data;
    if (file >> data)
        *currentPlayer = data;
    file.close();
    return 1;
}

/* Function to mark the entry by human player */
int placeMarkByHumanPlayer(int gameBoard[3][3], int mark, int numOfHumanPlayers, int currentPlayer, int t) {
    int move;
again:
    cin >> move;
    if (move == 0) { // Checking if move == 0 i.e. if user is trying to save the game
        if (t == 1) { // for checking if user is trying to save a single, not tournament
            int status = saveGame(gameBoard, numOfHumanPlayers, currentPlayer); // calling function to save the game
            cout << "\nSaving game...\n";
            if (status == 1) {
                cout << "Game Saved Successfully.\n";
            }
        } else {
            cout << "\n\nInvalid entry !! Enter again-"; // if user is trying to save game in tournament, then going back to again
            goto again;
        }
        return 1;
    }
    if (move > 9) {
        cout << "\n\nInvalid entry !! Enter again-"; // if user is trying to mark an entry greater than 9
        goto again;
    } else if (gameBoard[(move - 1) / 3][(move - 1) % 3] != EMPTY) // checking if the entry taken up by the user is already occupied
    {
        cout << "Invalid entry!! Enter again -"; // if already occupied, going to again
        goto again;
    } else
        gameBoard[(move - 1) / 3][(move - 1) % 3] = mark; // else marking the position int the gameboard
    return 0;
}

/* Function to mark the entry by computer */
void placeMarkByComputerPlayer(int gameBoard[3][3], int mark) {
    while (gameBoard[(C_entry[t] - 1) / 3][(C_entry[t] - 1) % 3] != EMPTY && t < 9) // getting the number from the array C_entry randomly
    {
        t++;
    }
    gameBoard[(C_entry[t] - 1) / 3][(C_entry[t] - 1) % 3] = mark; // Marking the position in the gameboard
}

/* Return 1 if there is a winner in the game, otherwise return 0 */
/* Note: the winner is the current player indicated in main() */
int hasWinner(int gameBoard[3][3]) {
    int count;
    for (int i = 0; i < 3; i++) {
        if (gameBoard[i][0] != EMPTY) { /* check if there is any winner in the any of the column */
            int check = gameBoard[i][0];
            count = 1;
            for (int j = 1; j < 3; j++) {
                if (check == gameBoard[i][j]) {
                    count++;
                    if (count == 3) {
                        return 1;
                    }
                } else
                    break;
            }
        }
    }

    for (int i = 0; i < 3; i++) {
        if (gameBoard[0][i] != EMPTY) { /* check if there is any winner in the any of the row */
            int check = gameBoard[0][i];
            count = 1;
            for (int j = 1; j < 3; j++) {
                if (check == gameBoard[j][i]) {
                    count++;
                    if (count == 3) {
                        return 1;
                    }
                } else
                    break;
            }
        }
    }
    /* check if winner is there in any of the diagonal */
    if ((gameBoard[0][0] != EMPTY && ((gameBoard[0][0] == gameBoard[1][1]) && (gameBoard[1][1] == gameBoard[2][2]))) ||
        (gameBoard[0][2] != EMPTY && ((gameBoard[0][2] == gameBoard[1][1]) && (gameBoard[1][1] == gameBoard[2][0])))) {
        return 1;
    }
    return 0;
}

/* Return 1 if the game board is full, otherwise return 0 */
int isFull(int gameBoard[3][3]) {
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            if (gameBoard[i][j] == EMPTY)
                return 0;
        }
    }
    return 1;
}

/* Function for game of two players */
int two_player(int gameBoard[3][3], int currentPlayer, int t) {
    printGameBoard(gameBoard);
    int gameEnds = 0;
    while (gameEnds == 0) { // work till game game doesn't end, i.e. either there is a winner or the grid is full
        cout << "Player " << currentPlayer << ", please place your mark [1-9]:\n";
        int mark;
        if (currentPlayer == 1)
            mark = CIRCLE;
        else
            mark = CROSS;
        int status = placeMarkByHumanPlayer(gameBoard, mark, 2, currentPlayer, t); // status is 1 when user had saved the game else it will be 0
        if (status == 1) {
            int choice;
            cout << "\nDo you still want to play? (Enter 1 for YES and 2 for NO)\n"; // asking if he further wants to play
            cout << "Enter your choice [1/2]: ";
            cin >> choice;
            if (choice == 2) {
                exit(1);
            }
        }
        printGameBoard(gameBoard);
        if (hasWinner(gameBoard)) { // checking for thw winner
            gameEnds = 1; // if winner is there, then game is ended
            cout << "Player " << currentPlayer << " wins! Congratulations!\n";
            return currentPlayer; // returns which player is the winner
        }
        if (isFull(gameBoard) && !hasWinner(gameBoard)) { // if gameboard is full and no winner is there,
            gameEnds = 1; // then, game is declared to be drawn
            cout << "The game has drawn!\n";
        }
        if (status != 1) { // if game has not ended, the current player is changed
            if (currentPlayer == 1)
                currentPlayer = 2;
            else
                currentPlayer = 1;
        }
    }
    return 0;
}

/* Function for game of single player */
void one_player(int gameBoard[3][3], int currentPlayer, int t) {
    printGameBoard(gameBoard);
    int mark;
    int gameEnds = 0;
    while (gameEnds == 0) { // work till game game doesn't end, i.e. either there is a winner or the grid is full
        if (currentPlayer == 1)
            mark = CIRCLE;
        else
            mark = CROSS;
        int status = 0;
        if (currentPlayer == 1) {
            cout << "Player 1, please place your mark [1-9]:\n";
            status = placeMarkByHumanPlayer(gameBoard, mark, 1, currentPlayer, t); // status is 1 when user had saved the game else it will be 0
            if (status == 1) {
                int choice;
                cout << "\nDo you still want to play? (Enter 1 for YES and 2 for NO)\n"; // asking if he further wants to play
                cout << "Enter your choice [1/2]: ";
                cin >> choice;
                if (choice == 2)
                    exit(1);
            }
        } else {
            cout << "Computer places the mark:\n";
            placeMarkByComputerPlayer(gameBoard, mark); // calling function for marking my computer
        }
        printGameBoard(gameBoard);
        if (hasWinner(gameBoard)) { // checking for thw winner
            gameEnds = 1; // if winner is there, then game is ended
            if (currentPlayer == 1)
                cout << "You wins! Congratulations!\n";
            else
                cout << "Computer wins!\n";
        }
        if (isFull(gameBoard) && !hasWinner(gameBoard)) { // if gameboard is full and no winner is there,
            gameEnds = 1; // then, game is declared to be drawn
            cout << "The game is drawn !!";
        }

        if (status != 1) { // if game has not ended, the current player is changed
            if (currentPlayer == 1)
                currentPlayer = 2;
            else
                currentPlayer = 1;
        }
    }
}

int main() {
    /* Guidelines for the game */
    cout << "\n*********************************************************************************************\n";
    cout << "\t\t\t\tWelcome to the Classical Tic-Tac-Toe game ";
    cout << "\n*********************************************************************************************\n";
    cout << "Guidelines to play the game - \n";
    cout << "1. Tic-Tac-Toe can be played between two players or one player and computer.\n";
    cout << "2. You can play a single round of Tic-Tac-Toe or you can play the The Tic-Tac-Toe Tournament, but the tournament cannot be played against the computer.\n";
    cout << "3. The game can be saved at any time and can later be loaded from the last saved stage, but remember tournaments cannot be saved.\n";
    cout << "4. To save the game at any time, enter 0.\n";
    cout << "\n*********************************************************************************************\n";

    int gameBoard[3][3];
    int numOfHumanPlayers, currentPlayer;
    int choice, kind = 0;
start:
    initGameBoard(gameBoard); //calling function to intialise the gameboard
    cout << "\n\t\t\t\t\tTic-Tac-Toe Menu\n";
    cout << "1. New game\n";
    cout << "2. Load previous game\n";
    cout << "Enter your choice [1/2]: ";
    cin >> choice;
    cout << "\n*********************************************************************************************\n";
    if (choice == 1) { // if new game is selected, then asking for the mode i.e., the no. of human players
    newgame:
        initGameBoard(gameBoard);
        cout << "\n\nHow many human players [1-2]?\n";
        cin >> numOfHumanPlayers;

        currentPlayer = 1;
        if (numOfHumanPlayers == 1) {
            int p;
            one_player(gameBoard, currentPlayer, 1); // if numOfHumanPlayers is 1, calling one_player()
            cout << "\n\nDo you want to play again[Enter 1 for Yes,0 for No] :";
            cin >> p;
            if (p == 1)
                goto start;
            else
                exit(1);
        } else if (numOfHumanPlayers == 2) {
            cout << "Do you want to play a single round or a tournament? (Enter 1 for a single round, 2 for a tournament)\n";
            cout << "Enter your choice [1/2]: ";
            cin >> kind;
            if (kind == 1) {
                int p;
                two_player(gameBoard, currentPlayer, 1); // if numOfHumanPlayers is 2, calling two_player()
                cout << "\n\nDo you want to play again[Enter 1 for Yes,0 for No] :";
                cin >> p;
                if (p == 1)
                    goto start;
                else
                    exit(1);
            } else {
                int numRound, currRound = 1;
                int p1Score = 0, p2Score = 0;
                cout << "\n*********************************************************************************************\n";
                cout << "\n\t\t\t\tWelcome to the Tic-Tac-Toe Tournament\n";
                cout << "\n*********************************************************************************************\n";
                cout << "\nHow many rounds do you want to play in the tournament?\n";
                cin >> numRound;
                /* Scorecard for the game */
                while (currRound <= numRound) {
                    cout << "\n*********************************************************************************************\n";
                    cout << "\n\t\t\t\t\t    Total Rounds : " << numRound << "\n\t\t\t\t\t    Current Round: " << currRound << "\n";
                    cout << "\n*********************************************************************************************\n";
                    cout << "\t\t\t\t\t\tScore\t\t\t\t\t\n";
                    cout << "\n\t\t\t\t\t    Player 1 : " << p1Score << "\n\t\t\t\t\t    Player 2 : " << p2Score << "\n";
                    cout << "\n*********************************************************************************************\n";
                    int winner = two_player(gameBoard, currentPlayer, 2); // getting winner of a match
                    initGameBoard(gameBoard);
                    if (winner == 1) {
                        p1Score++; // Updating the scorecard
                    } else if (winner == 2) {
                        p2Score++;
                    }
                    currRound++;
                }
                /* Printing the scorecard */

                if (p1Score > p2Score) {
                    cout << "\n*********************************************************************************************\n";
                    cout << "\n\t\t\tCongratulations! Player 1 wins the Tic-Tac-Toe Tournament!\n";
                    cout << "\n*********************************************************************************************\n";
                } else if (p2Score > p1Score) {
                    cout << "\n*********************************************************************************************\n";
                    cout << "\n\t\t\tCongratulations! Player 2 wins the Tic-Tac-Toe Tournament!\n";
                    cout << "\n*********************************************************************************************\n";
                } else {
                    cout << "\nThe tournament is tied !!";
                    cout << "\nDo you want to play one more match to declare the winner [Yes-1 and No-0] :";
                    int t;
                    cin >> t;
                    if (t == 1) {
                        int winner = two_player(gameBoard, currentPlayer, 2);
                        if (winner == 1) {
                            cout << "\n*********************************************************************************************\n";
                            cout << "\n\t\t\tCongratulations! Player 1 wins the Tic-Tac-Toe Tournament!\n";
                            cout << "\n*********************************************************************************************\n";
                        } else if (winner == 2) {
                            cout << "\n*********************************************************************************************\n";
                            cout << "\n\t\t\tCongratulations! Player 2 wins the Tic-Tac-Toe Tournament!\n";
                            cout << "\n*********************************************************************************************\n";
                        } else {
                            cout << "\n*********************************************************************************************\n";
                            cout << "\n\t\t\t\t\tThe Tic-Tac-Toe Tournament has tied!\n";
                            cout << "\n*********************************************************************************************\n";
                        }
                    }
                }
                int p;
                cout << "\n\nDo you want to play again[Enter 1 for Yes,0 for No] :";
                cin >> p;
                if (p == 1)
                    goto start;
                else
                    exit(1);
            }
        }
    } else {
        /* if user selected a saved game */
        int status = loadGame(gameBoard, &numOfHumanPlayers, &currentPlayer);
        if (status == 0) { /* if status is 0, then no saved game is there */
            cout << "\n Cannot load game right now as there is no saved game !!\n Starting a new game !!";
            goto newgame;
        }
        if (numOfHumanPlayers == 1) { // if saved game is of one player, calling for one_player
            one_player(gameBoard, currentPlayer, 1);
        } else if (numOfHumanPlayers == 2) { // if saved game is of two player, calling for two_player
            two_player(gameBoard, currentPlayer, 1);
        }
        int p;
        cout << "\n\nDo you want to play again[Enter 1 for Yes,0 for No] :";
        cin >> p;
        if (p == 1)
            goto start;
        else
            exit(1);
    }

    return 0;
}
