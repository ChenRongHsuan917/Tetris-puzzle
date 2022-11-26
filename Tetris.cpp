//1101548 ³¯»T¸©
#pragma GCC optimize("O3")
#include <iostream> 
#include <fstream> 
#include <sstream> 
#include <algorithm> 
#include <string> 
#include <vector> 
using namespace std;

vector< vector< char > >  map;
vector< vector< vector< char > > >  pieces;

void Input(ifstream& inFile);

bool cmp(vector< vector< char > >& p1, vector< vector< char > >& p2);

bool Backtracking();

void DeleteZero(vector<vector<char>>& puzzle);

vector<vector<char>> Rotate(vector<vector<char>>& puzzle);

bool Match(int m, int n, vector<vector<char>>& puzzle);

void PushPuzzle(int i, int j, vector<vector<char>>& puzzle);

void PopPuzzle(int n, int m, vector<vector<char>>& puzzle);

int main(int argc, char* argv[])
{
	/*double Start, End;
	Start = clock();*/

	ios::sync_with_stdio(false);

	ifstream inFile(argv[1], ios::in);
	Input(inFile);
	sort(pieces.begin(), pieces.end(), cmp);
	Backtracking();
	for (auto row : map) {
		for (auto element : row)
			cout << element << " ";
		cout << endl;
	}
	inFile.close();

	/*End = clock();
	cout << endl << (End - Start) / CLOCKS_PER_SEC << " s" << endl;*/
}

void Input(ifstream& inFile)
{
	vector< char > temp_rows;
	string words;
	char chr;
	stringstream ss;
	while (getline(inFile, words)) {

		if (!words.size())
			continue;
		if (words == "x")
			break;

		ss.str("");
		ss.clear();
		ss << words;
		int len = words.size() / 2 + 1;
		temp_rows.clear();
		temp_rows.reserve(len);

		while (ss >> chr) {
			if (chr != '0')
				temp_rows.push_back('.');
			else
				temp_rows.push_back(chr);
		}
		map.push_back(temp_rows);
	}

	vector< vector< char > > temp_pieces;
	while (getline(inFile, words)) {

		if (!words.size())
			continue;

		if (words == "x") {
			DeleteZero(temp_pieces);
			pieces.push_back(temp_pieces);
			temp_pieces.clear();
			continue;
		}
		else if (words == "0")
			break;

		ss.str("");
		ss.clear();
		ss << words;
		int len = words.size() / 2 + 1;
		temp_rows.clear();
		temp_rows.reserve(len);

		while (ss >> chr)
			temp_rows.push_back(chr);

		temp_pieces.push_back(temp_rows);
	}

}

bool cmp(vector< vector< char > >& p1, vector< vector< char > >& p2) {
	int area1 = p1.size() * p1[0].size();
	int area2 = p2.size() * p2[0].size();
	if (area1 < area2)
		return true;
	else if (area1 > area2)
		return false;
	else {
		int c1 = 0, c2 = 0;

		for (auto r1 : p1) {
			for (auto e1 : r1) {
				if (e1 != '0')
					c1++;
			}
		}

		for (auto r2 : p2) {
			for (auto e2 : r2) {
				if (e2 != '0')
					c2++;
			}
		}

		if (c1 < c2)
			return true;
	}
	return false;
}

bool Backtracking()
{
	if (pieces.empty())
		return true;

	vector<vector<char>> temp = pieces.back();
	int rotation = 0, n = 0, m = 0;
	while (rotation < 4) {
		n = 0, m = 0;
		while (n < map.size() - temp.size() + 1) {
			if (Match(n, m, temp)) {
				PushPuzzle(n, m, temp);
				pieces.pop_back();
				Backtracking();
				if (pieces.empty())
					return true;
				else {
					PopPuzzle(n, m, temp);
					pieces.push_back(temp);
				}
			}
			m++;
			if (m > map[0].size() - temp[0].size()) {
				n++;
				m = 0;
			}
		}
		vector<vector<char>> rotate = Rotate(temp);
		if (temp == rotate)
			break;
		else {
			temp = rotate;
			rotation++;
		}
	}
	return false;
}

void DeleteZero(vector<vector<char>>& puzzle)
{
	int r = 0;
	while (r < 4) {
		while (true) {
			if (!puzzle.size())
				return;
			bool check = true;
			for (int i = 0; i < puzzle.back().size(); ++i) {
				if (puzzle.back()[i] != '0') {
					check = false;
					break;
				}
			}
			if (check)
				puzzle.pop_back();
			else
				break;
		}
		puzzle = Rotate(puzzle);
		r++;
	}
	return;
}

vector<vector<char>> Rotate(vector<vector<char>>& puzzle)
{
	int len = puzzle.size();
	vector<char> rotate_row;
	rotate_row.reserve(len);
	vector<vector<char>> rotate_matrix;
	rotate_matrix.reserve(puzzle[0].size());

	for (int j = 0; j < puzzle[0].size(); j++) {
		for (int i = puzzle.size() - 1; i >= 0; i--)
			rotate_row.push_back(puzzle[i][j]);

		rotate_matrix.push_back(rotate_row);
		rotate_row.clear();
		rotate_row.reserve(len);
	}

	return rotate_matrix;
}

bool Match(int n, int m, vector<vector<char>>& puzzle)
{
	int x = 0, y = 0;
	while (x < puzzle.size()) {

		if (puzzle[x][y] != '0') {
			if (map[n + x][m + y] != '.')
				return false;
		}
		y++;
		if (y == puzzle[0].size()) {
			x++;
			y = 0;
		}
	}
	return true;
	/*for (int x = 0; x < puzzle.size(); x++) {
	 for (int y = 0; y < puzzle[0].size(); y++) {
	  if (puzzle[x][y] != "0") {
	   if (map[n + x][m + y] != ".")
		return false;
	  }
	 }
	}
	return true;*/
}

void PushPuzzle(int n, int m, vector<vector<char>>& puzzle)
{
	int x = 0, y = 0;
	while (x < puzzle.size()) {
		if (puzzle[x][y] != '0')
			map[n + x][m + y] = puzzle[x][y];
		y++;
		if (y == puzzle[0].size()) {
			x++;
			y = 0;
		}
	}
	/*for (int x = 0; x < puzzle.size(); x++) {
	 for (int y = 0; y < puzzle[0].size(); y++) {
	  if (puzzle[x][y] != "0")
	   map[n + x][m + y] = puzzle[x][y];
	 }
	}*/
}

void PopPuzzle(int n, int m, vector<vector<char>>& puzzle)
{

	int x = 0, y = 0;
	while (x < puzzle.size()) {
		if (puzzle[x][y] != '0')
			map[n + x][m + y] = '.';
		y++;
		if (y == puzzle[0].size()) {
			x++;
			y = 0;
		}
	}
	return;
	/*for (int x = 0; x < puzzle.size(); x++) {
	 for (int y = 0; y < puzzle[0].size(); y++) {
	  if (puzzle[x][y] != "0")
	   map[n + x][m + y] = ".";
	 }
	}
	return;*/
}