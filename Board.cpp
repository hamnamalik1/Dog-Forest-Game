
#include "Board.hpp"
#include <iostream>
#include "Dog.hpp"
using namespace std;

Board::Board(char diff, bool d){
	level = diff;
	debug = d;
	wallStrength = 6;
	InitAll();
}
Board::Board(bool d){
	level = 'e';
	debug = d;
	wallStrength = 6;
	InitAll();
}
Board::Board(char diff, string name, bool d) {
	level = diff;
	debug = d;
	mydog.name = name;

	wallStrength = 6;
	InitAll();
}
void Board::InitAll() {
	bool keepPlaying = true;


	while (keepPlaying) {
		cout << "What level of difficulty do you want (e, m, or h)?" << endl;
		char c;
		cin >> c;
		level = c;
		startx = rand() % size;
		starty = 0;
		endx = rand() % size;
		endy = size-1;

		mydog.x = startx;
		mydog.y = starty;
		boardConfig();
		addFood();
		addTraps();
		printBoard();
		playGame();

		cout << "Play again? " << endl;
		string s = "no";
		cin>>s;
		if (s == "yes" || s == "Yes" || s == "Y" || s == "y") {
			keepPlaying = true;
			mydog.reset();
		}
		else {
			cout <<"Thanks for playing!" << endl;
			keepPlaying = false;
		}
	}

}


void Board::printBoard() {

	// Print the top border
	std::cout << " ";
	for (int i = 0; i < size; ++i) {
		std::cout << "_ ";
	}
	std::cout << std::endl;

	// Print the rows
	for (int i = 0; i < size; ++i) {
		std::cout << "|";
		for (int j = 0; j < size; ++j) {
			if (board[i][j] == 'T') {
				std::cout << "T ";
			} else if (board[i][j] == 'F') {
				std::cout << "F ";
			} else if (board[i][j] == '|') {
				std::cout << "| ";
			} else if (board[i][j] == '_') {
				std::cout << "_ ";
			} else if (board[i][j] == 'D') {
				std::cout << "D ";
			} else if (board[i][j] == 'E') {
				std::cout << "E->";
			} else {
				std::cout << "  ";
			}
		}
		std::cout << "|" << std::endl; // Right border
	}

	// Print bottom border
	std::cout << " ";
	for (int i = 0; i < size; ++i) {
		std::cout << "_ ";
	}
	std::cout << "|" << std::endl;





mydog.printDog();  // COMMENT THIS IN WHEN YOU Write your Dog class!!

}

void Board::boardConfig() {
        for (int i = 0; i < size; ++i) {
            for (int j = 0; j < size; ++j) {
                board[i][j] = ' ';
            }
        }

        int numWalls = 0;
        int maxWallLength = (level == 1) ? 9 : (level == 2) ? 13 : 16;

        // Randomly place walls
        while (numWalls < 15) {
            bool placed = false;
            while (!placed) {
                int wallOrientation = std::rand() % 2; // 0 for vertical, 1 for horizontal
                int wallPos = (std::rand() % ((size + 1) / 2)) * 2 + 1; // Random odd row/column

                if (wallOrientation == 0) { // Vertical wall
                    if (wallPos >= size) continue; // Skip if out of bounds
                    int wallLength = std::rand() % maxWallLength + 1;
                    wallLength = std::min(wallLength,size); // Emaking sure wallLength does not exceed board size

                    for (int i = 0; i < wallLength; ++i) {
                        if (wallPos + i >= size) break; // Break if out of bounds
                        if (board[wallPos + i][wallPos] == 'D' || board[wallPos + i][wallPos] == 'E') {
                            break; // Skip if start or end is in the wall
                        }
                        board[wallPos + i][wallPos] = '|';
                    }
                    placed = true;
                } else { // Horizontal wall
                    if (wallPos >= size) continue; // Skip if out of bounds
                    int wallLength = std::rand() % maxWallLength + 1;
                    wallLength = std::min(wallLength, size); // Ensure wallLength does not exceed board size

                    for (int i = 0; i < wallLength; ++i) {
                        if (wallPos + i >= size) break; // Break if out of bounds
                        if (board[wallPos][wallPos + i] == 'D' || board[wallPos][wallPos + i] == 'E') {
                            break; // Skip if start or end is in the wall
                        }
                        board[wallPos][wallPos + i] = '_';
                    }
                    placed = true;
                }
                numWalls++;
            }
        }


        int startx = std::rand() % size;
        int starty = 0; // start is in the leftcolumn
        int endx = std::rand() % size;
        int endy = size - 1; //end is in the right column

        // start and end are different and not on the same cell as walls
        while (board[startx][starty] == '|' || board[startx][starty] == '_' ||
               (startx == endx && starty == endy) || board[endx][endy] == '|' || board[endx][endy] == '_') {
            startx = std::rand() % size;
            endx = std::rand() % size;
        }

        board[startx][starty] = 'D';
        board[endx][endy] = 'E';

        // Create an opening space around 'D'
        if (startx > 0) board[startx - 1][starty] = ' ';
        if (startx < size - 1) board[startx + 1][starty] = ' ';
        if (starty > 0) board[startx][starty - 1] = ' ';
        if (starty < size - 1) board[startx][starty + 1] = ' ';

        // Create an opening space around 'E'
        if (endx > 0) board[endx - 1][endy] = ' ';
        if (endx < size - 1) board[endx + 1][endy] = ' ';
        if (endy > 0) board[endx][endy - 1] = ' ';
        if (endy < size - 1) board[endx][endy + 1] = ' ';

}


void Board::addFood() {
	// Determine the number of food items to place based on difficulty level
	int numFood;
	if (level == 'e') {
		numFood = size;        // Easy: size number of food items
	} else if (level == 'm') {
		numFood = size - 2;    // Medium: size - 2 number of food items
	} else if (level == 'h') {
		numFood = size - 4;    // Hard: size - 4 number of food items
	} else {
		numFood = size;        // Default to easy level if the level is invalid
	}

	// Randomly add food around the board
	int placedFood = 0;
	while (placedFood < numFood) {
		int x = std::rand() % size;
		int y = std::rand() % size;

		// Only place food if the square is empty and not occupied by other elements
		if (board[x][y] == ' ' && board[x][y] != 'D' && board[x][y] != 'E' &&
			board[x][y] != 'T' && board[x][y] != 'F' && board[x][y] != '|' && board[x][y] != '_') {
			board[x][y] = 'F'; // Place food
			++placedFood;
			}
	}
}

void Board::addTraps() {
	// Determine the number of traps to place based on difficulty level
	int numTraps;
	if (level == 'e') {
		numTraps = size - 14;  // Easy: size - 14 traps (20 - 14 = 6 traps)
	} else if (level == 'm') {
		numTraps = size - 10;  // Medium: size - 10 traps (20 - 10 = 10 traps)
	} else if (level == 'h') {
		numTraps = size - 6;   // Hard: size - 6 traps (20 - 6 = 14 traps)
	} else {
		numTraps = size - 14;  // Default to easy level if level is invalid
	}

	// Randomly add traps around the board
	int placedTraps = 0;
	while (placedTraps < numTraps) {
		int x = std::rand() % size;
		int y = std::rand() % size;

		// Only place traps if the square is empty and not occupied by other elements
		if (board[x][y] == ' ' && board[x][y] != 'D' && board[x][y] != 'E' &&
			board[x][y] != 'T' && board[x][y] != 'F' && board[x][y] != '|' && board[x][y] != '_') {
			board[x][y] = 'T'; // Place trap
			++placedTraps;
			}
	}
}


bool Board::moveDog(char c) {

	int dogX = -1, dogY = -1;
	for (int i = 0; i < size; ++i) {
		for (int j = 0; j < size; ++j) {
			if (board[i][j] == 'D') {
				dogX = i;
				dogY = j;
				break;
			}
		}
	}
	// Determine new position based on the direction
	int newX = dogX, newY = dogY;
	if (c == 'u') {
		newX = dogX - 1;
	} else if (c == 'd') {
		newX = dogX + 1;
	} else if (c== 'l') {
		newY = dogY - 1;
	} else if (c == 'r') {
		newY = dogY + 1;
	}

	// making sure  the new position is within the bounds of the board
	if (newX < 0 || newX >= size || newY < 0 || newY >= size) {
		std::cout << "Cannot move out of bounds!" << std::endl;
		return true;
	}

	// Check if the new position is the end
	if (board[newX][newY] == 'E') {
		mydog.won();
		return false;  // End the game, since the dog reached the end
	}


	if (board[newX][newY] == '|' || board[newX][newY] == '_') {

		if (mydog.strength >= 6) {
			std::string response;
			std::cout << "Do you want to knock down that wall? (y/n): ";
			std::cin >> response;

			if (response == "y") {
				// Knock down the wall
				board[newX][newY] = ' ';  // Clear the wall
				mydog.changeStrength(-6);  // Decrease strength by 6
				std::cout << "Wall knocked down! Strength decreased by 6."  << " Your current strength is now: "<< mydog.strength<< std::endl;
			} else {
				// User chose not to knock down the wall
				mydog.changeStrength(-1);  // Decrease strength by 1
				std::cout << "Chose not to knock down the wall. Strength decreased by 1." << " Your current strength is now: "<< mydog.strength<< std::endl;
				return true;
			}
		} else {
			std::cout << "Not enough strength to knock down the wall!" << " Your current strength is now: "<< mydog.strength<< std::endl;
			mydog.changeStrength(-1);  // Penalty for trying to move into a wall
			return true;
		}
	}


	if (board[newX][newY] == 'T') {
		int trapPenalty = rand() % 16 + 2;
		mydog.changeStrength(-trapPenalty);
		std::cout << "Hit a trap! Lost " << trapPenalty << " strength." << " Your current strength is now: "<< mydog.strength<< std::endl;

	}


	if (board[newX][newY] == 'F') {
		int foodReward = rand() % 16 + 2;
		mydog.changeStrength(foodReward);
		std::cout << "Found food! Gained " << foodReward << " strength." << " Your current strength is now: "<< mydog.strength<< std::endl;

	}


	mydog.changeStrength(-2);  // Movement cost

	if (mydog.strength <= 0) {
		mydog.die();
		return false;
	}

	board[dogX][dogY] = ' ';  // Clear the old position
	board[newX][newY] = 'D';  // Set the new position
	// Update the dog's position
	mydog.x = newX;
	mydog.y = newY;


	return true;  // Indicate that the move was successful

}


void Board::playGame() {
	bool play = true;
	while (play) {
		cout << "Move (u, d, l, r) "<<endl;
		char c;
		cin >> c;
		play = moveDog(c);
		printBoard();
	}


}


