#include <iostream>
#include <vector>
#include <string>
#include <sstream>

using namespace std;

class Board;

class Position {
	private:
		int _x, _y;
	public:
		Position(int x, int y);
		int x() {return _x;};
		int y() {return _y;};
		bool is_on(Board *board);
};

class Board {
	private:
		int _width;
		int _height;
		vector<string> _board;
		vector<vector<Position> > _adjacent;
	public:
		Board(int width, int height, string linear_board);
		Board(int width, int height, vector<string> _board);
		void _initialize_adjacent();
		int width() {return _width; };
		int height() {return _height; };
		void dump();
};

Position::Position(int x, int y) {
	_x = x;
	_y = y;
}

bool Position::is_on(Board *board) {
	int width = board->width();
	int height = board->height();
	if (_x < 0) return false;
	if (_y < 0) return false;
	if (width - 1 < _x) return false;
	if (height - 1 < _y) return false;
	return true;
}

Board::Board(int width, int height, string linear_board) {
	_width = width;
	_height = height;
	stringstream line;
	for(int i = 0; i < linear_board.length(); i++) {
		if (i % _width == 0) {
			if (i != 0) _board.push_back(line.str());
			line.str("");
		}
		line << linear_board[i];
	}
	_board.push_back(line.str());
	_initialize_adjacent();
}

Board::Board(int width, int height, vector<string> board) {
	_width = width;
	_height = height;
	_board = board;
}

void Board::_initialize_adjacent() {
	for(int y = 0; y < _height; y++) {
		for(int x = 0; x < _width; x++) {
			Position u(x, y - 1);
			Position d(x, y + 1);
			Position l(x - 1, y);
			Position r(x + 1, y);
			vector<Position> ps;
			if (u.is_on(this)) ps.push_back(u);
			if (d.is_on(this)) ps.push_back(d);
			if (l.is_on(this)) ps.push_back(l);
			if (r.is_on(this)) ps.push_back(r);
			_adjacent.push_back(ps);
		}
	}
}

void Board::dump() {
	for(vector<string>::iterator i = _board.begin(); i < _board.end(); i++) {
		cout << *i << endl;
	}
}

int main(int argc, char* []) {
	Board* b = new Board(3, 3, "86725431=");
	b->dump();
	return 0;
}



