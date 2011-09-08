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
		bool is_on(Board &board);
};

class Board {
	private:
		int _width;
		int _height;
		vector<string> _board;
		vector<vector<vector<Position> > > _adjacent;
	public:
		Board(int width, int height, string linear_board);
		Board(int width, int height, vector<string> _board);
		void _initialize_adjacent();
		bool operator==(Board &board);
		int width() {return _width; };
		int height() {return _height; };
		vector<string> board() {return _board; };
		void dump();
		bool is_end();
		Board slide(Position &space, Position &target);
		vector<Board> succ();
};

Position::Position(int x, int y) {
	_x = x;
	_y = y;
}

bool Position::is_on(Board &board) {
	int width = board.width();
	int height = board.height();
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
	_initialize_adjacent();
}

void Board::_initialize_adjacent() {
	for(int y = 0; y < _height; y++) {
		vector<vector<Position> > pss;
		for(int x = 0; x < _width; x++) {
			Position u(x, y - 1);
			Position d(x, y + 1);
			Position l(x - 1, y);
			Position r(x + 1, y);
			vector<Position> ps;
			if (u.is_on(*this)) ps.push_back(u);
			if (d.is_on(*this)) ps.push_back(d);
			if (l.is_on(*this)) ps.push_back(l);
			if (r.is_on(*this)) ps.push_back(r);
			pss.push_back(ps);
		}
		_adjacent.push_back(pss);
		pss.clear();
	}
}

bool Board::operator==(Board &board) {
	return _board == board.board();
}

void Board::dump() {
	cout << endl;
	for(vector<string>::iterator i = _board.begin(); i < _board.end(); i++) {
		cout << *i << endl;
	}
	cout << endl;
}

bool Board::is_end() {
	char ch = '0';
	for (int y = 0; y < _height; y++) {
		for (int x = 0; x < _width; x++) {
			ch++;
			if (ch == '9' + 1) ch = 'A';
			if (ch != _board[y][x] && '=' != _board[y][x]) return false;
		}
	}
	return true;
}

Board Board::slide(Position &space, Position &target) {
	vector<string> new_board = _board;
	int x1 = space.x();
	int y1 = space.y();
	int x2 = target.x();
	int y2 = target.y();
	// string tmp = new_board[y1][x1];
	new_board[y1][x1] = _board[y2][x2];
	new_board[y2][x2] = _board[y1][x1];

	return Board(_width, _height, new_board);
}

vector<Board> Board::succ() {
	vector<Board> boards;
	vector<Position> spaces;

	for (int y = 0; y < _height; y++) {
		for (int x = 0; x < _width; x++) {
			if (_board[y][x] == '=') {
				spaces.push_back(Position(x, y));
			}
		}
	}

	for (vector<Position>::iterator space = spaces.begin(); space < spaces.end(); space++) {
		vector<Position> targets = _adjacent[space->y()][space->x()];
		for (vector<Position>::iterator target = targets.begin(); target < targets.end(); target++) {
			boards.push_back(slide(*space, *target));
		}
	}

	return boards;
}

class SlidingPuzzle {
	private:
		vector<Board> _boards;
	public:
		SlidingPuzzle(Board start);
		void solve();
		void solve(vector<Board> boards);
};

SlidingPuzzle::SlidingPuzzle(Board start) {
	_boards.push_back(start);
}

void SlidingPuzzle::solve() {
	return this->solve(_boards);
}

void SlidingPuzzle::solve(vector<Board> boards) {
	vector<Board> next_boards;

	for (vector<Board>::iterator board = boards.begin(); board < boards.end(); board++) {
		vector<Board> succ = board->succ();

		for (vector<Board>::iterator next_board = succ.begin(); next_board < succ.end(); next_board++) {
			bool match = false;
			for (vector<Board>::iterator cmp = _boards.begin(); cmp < _boards.end(); cmp++) {
				if ((*cmp) == (*next_board)) {
					match = true;
					break;
				}
			}
			if (match == false) {
				if (next_board->is_end() == true) {
					cout << _boards.size() << endl;
					next_board->dump();
					return;
				}
				next_boards.push_back(*next_board);
				_boards.push_back(*next_board);
			}
		}
	}

	if (next_boards.size() == 0) {
		return;
	} else {
		cout << _boards.size() << endl;
		return solve(next_boards);
	}
}

int main(int argc, char* []) {
	Board b(3, 3, "86725431=");
	// Board b(3, 3, "=23156478");
	SlidingPuzzle puzzle(b);
	puzzle.solve();
	return 0;
}


