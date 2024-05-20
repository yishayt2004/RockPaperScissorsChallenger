#include <iostream>
#include <fstream>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <chrono>
#include <thread>

using namespace std;

// Enum for choices
enum Choice { ROCK, PAPER, SCISSORS };

// Struct to hold game result data
struct GameResult {
    string playerName;
    int playerWins;
    int computerWins;
};

// Function to get the user's choice with input validation
Choice getUserChoice() {
    char choice;
    cout << "\n\033[1;33mEnter your choice (R for Rock, P for Paper, S for Scissors):\033[0m ";
    cin >> choice;
    choice = toupper(choice); // Convert to uppercase to handle lowercase input

    switch(choice) {
        case 'R': return ROCK;
        case 'P': return PAPER;
        case 'S': return SCISSORS;
        default:
            cout << "\033[1;31mInvalid choice. Please enter R, P, or S.\033[0m" << endl;
            return getUserChoice(); // Recursively call until valid input is provided
    }
}

// Function to generate computer's choice
Choice getComputerChoice() {
    int randomNum = rand() % 3;
    return static_cast<Choice>(randomNum);
}

// Function to display ASCII art for choices
void displayChoice(Choice choice) {
    switch (choice) {
        case ROCK:
            cout << "\n\033[1;36mRock\033[0m" << endl;
            cout << "    _______" << endl;
            cout << "---'   ____)" << endl;
            cout << "      (_____)" << endl;
            cout << "      (_____)" << endl;
            cout << "      (____)" << endl;
            cout << "---.__(___)" << endl;
            break;
        case PAPER:
            cout << "\n\033[1;36mPaper\033[0m" << endl;
            cout << "    _______" << endl;
            cout << "---'   ____)____" << endl;
            cout << "          ______)" << endl;
            cout << "          _______)" << endl;
            cout << "         _______)" << endl;
            cout << "---.__________)" << endl;
            break;
        case SCISSORS:
            cout << "\n\033[1;36mScissors\033[0m" << endl;
            cout << "    _______" << endl;
            cout << "---'   ____)____" << endl;
            cout << "          ______)" << endl;
            cout << "       __________)" << endl;
            cout << "      (____)" << endl;
            cout << "---.__(___)" << endl;
            break;
    }
}

// Function to determine the winner
void determineWinner(const string& playerName, int playerWins, int computerWins) {
    cout << "\n\033[1;35m=============================================\033[0m" << endl;
    if (playerWins > computerWins) {
        cout << "\033[1;32mCongratulations, " << playerName << "! You win the best of three!\033[0m" << endl;
        cout << "🎉🎉🎉 Congratulations! 🎉🎉🎉" << endl;
        cout << "You're on fire, " << playerName << "!" << endl;
    } else {
        cout << "\033[1;31mComputer wins the best of three. Better luck next time, " << playerName << "!\033[0m" << endl;
        cout << "😔😔😔 Oh no! Better luck next time, " << playerName << "!" << endl;
    }
    cout << "\033[1;35m=============================================\033[0m" << endl;
}

// Function to save game results to a vector of GameResult
void saveGameResult(vector<GameResult>& gameResults, const string& playerName, int playerWins, int computerWins) {
    GameResult result = {playerName, playerWins, computerWins};
    gameResults.push_back(result);
}

// Function to output game results to a text file
void outputResultsToFile(const vector<GameResult>& gameResults, const string& playerName) {
    ofstream outputFile(playerName + "_game_results.txt");
    if (outputFile.is_open()) {
        auto now = chrono::system_clock::now();
        time_t currentTime = chrono::system_clock::to_time_t(now);

        outputFile << "Game Results for " << playerName << " - " << ctime(&currentTime) << endl;
        outputFile << "-----------------------------------" << endl;

        int totalRounds = 0;
        int totalPlayerWins = 0;
        int totalComputerWins = 0;

        for (const auto& result : gameResults) {
            totalRounds++;
            totalPlayerWins += result.playerWins;
            totalComputerWins += result.computerWins;

            outputFile << "Round " << totalRounds << ":" << endl;
            outputFile << "Player Wins: " << result.playerWins << endl;
            outputFile << "Computer Wins: " << result.computerWins << endl;

            if (result.playerWins > result.computerWins) {
                outputFile << "Winner: " << playerName << " (+" << (result.playerWins - result.computerWins) << ")" << endl;
            } else if (result.computerWins > result.playerWins) {
                outputFile << "Winner: Computer (+" << (result.computerWins - result.playerWins) << ")" << endl;
            } else {
                outputFile << "It's a tie!" << endl;
            }
            outputFile << "-----------------------------------" << endl;
        }

        outputFile << "Total Rounds Played: " << totalRounds << endl;
        outputFile << "Total Player Wins: " << totalPlayerWins << endl;
        outputFile << "Total Computer Wins: " << totalComputerWins << endl;

        if (totalPlayerWins > totalComputerWins) {
            outputFile << "Overall Winner: " << playerName << " (+" << (totalPlayerWins - totalComputerWins) << ")" << endl;
        } else if (totalComputerWins > totalPlayerWins) {
            outputFile << "Overall Winner: Computer (+" << (totalComputerWins - totalPlayerWins) << ")" << endl;
        } else {
            outputFile << "Overall Result: It's a tie!" << endl;
        }

        outputFile.close();
        cout << "\033[1;33mGame results have been saved to '" << playerName << "_game_results.txt'.\033[0m" << endl;
    } else {
        cout << "\033[1;31mError: Unable to open file to save game results.\033[0m" << endl;
    }
}


int main() {
    string playerName;
    char playAgain;
    vector<GameResult> gameResults;

    srand(time(0)); // Seed the random number generator with current time

    cout << "\033[1;35m=============================================\033[0m" << endl;
    cout << "\033[1;33mWelcome to Rock, Paper, Scissors Game!\033[0m" << endl;
    cout << "\033[1;35m=============================================\033[0m" << endl;

    cout << "\n\033[1;33mEnter your name: \033[0m";
    getline(cin, playerName);

    do {
        Choice userChoice, computerChoice;
        int playerWins = 0;
        int computerWins = 0;

        cout << "\n\033[1;33mWelcome back, " << playerName << "! Let's play Rock, Paper, Scissors!\033[0m" << endl;

        while (playerWins < 2 && computerWins < 2) {
            cout << "\n\033[1;36mRound " << playerWins + computerWins + 1 << "\033[0m" << endl;

            this_thread::sleep_for(chrono::seconds(1));

            userChoice = getUserChoice();
            computerChoice = getComputerChoice();

            cout << playerName << " chose: ";
            displayChoice(userChoice);
            cout << "Computer chose: ";
            displayChoice(computerChoice);

            if ((userChoice == ROCK && computerChoice == SCISSORS) ||
                (userChoice == PAPER && computerChoice == ROCK) ||
                (userChoice == SCISSORS && computerChoice == PAPER)) {
                playerWins++;
            } else if ((computerChoice == ROCK && userChoice == SCISSORS) ||
                       (computerChoice == PAPER && userChoice == ROCK) ||
                       (computerChoice == SCISSORS && userChoice == PAPER)) {
                computerWins++;
            }

            cout << "\n\033[1;33mScore: " << playerName << " " << playerWins << " - " << "Computer " << computerWins << "\033[0m" << endl;
        }

        determineWinner(playerName, playerWins, computerWins);
        saveGameResult(gameResults, playerName, playerWins, computerWins);

        cout << "\n\033[1;33mDo you want to play again? (Y/N): \033[0m";
        cin >> playAgain;
        cin.ignore(); // Ignore the newline character in the input buffer
    } while (playAgain == 'Y' || playAgain == 'y');

    char saveToFile;
    cout << "\n\033[1;33mDo you want to save all game results to a text file? (Y/N): \033[0m";
    cin >> saveToFile;
    if (saveToFile == 'Y' || saveToFile == 'y') {
        outputResultsToFile(gameResults, playerName);
    }

    cout << "\n\033[1;33mThanks for playing, " << playerName << "!\033[0m" << endl;

    return 0;
}
