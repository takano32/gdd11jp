#include <iostream>
#include <vector>
#include <string>

using namespace std;

class Board {
	private:
		vector<string> board;
	public:
	Board(int width, int height, string linear_board);
};

Board::Board(int width, int height, string linear_board) {
	for(int i = 0; i < linear_board.length(); i++) {
	}
}

int main(int argc, char* []) {
	Board* b = new Board(3, 3, "86725431=");
	return 0;
}



