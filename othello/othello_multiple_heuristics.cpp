
#include<iostream>
#include<cstring>
#include<vector>
#include <algorithm>
#include<limits.h>
#pragma warning(disable : 4996)
using namespace std;

struct Coor {
	char r, c;
};
class Board {
public:
	char grid[8][8];
	vector<Coor>available_grid;
	//00 01 02 03 04 05 06 07
	//10 11 12 13 14 15 16 17	 
	//...
	//11 is Aa,etc

	//Player 1 uses dark pieces and Player 2 uses light pieces.
	// X (for dark pieces), and O (for light pieces).
	/* 0 ~7 denote the eight directions, i.e.上 up, 右上 up - right, 右 right, 右下 down - right,
	下 down, 左下 down - left, 左 left, and 左上 up - left.
	*/
	Board() {
		
	}
	
	Board(const char*s) {
		//walls
		
		for (int i = 0; i < 8; i++) {
			grid[0][i] = 'w';
			grid[7][i] = 'w';
			grid[i][0] = 'w';
			grid[i][7] = 'w';
		}
		int pen = 0;
		for (int i = 1; i <= 6; i++)
			for (int j = 1; j <= 6; j++) {
				grid[i][j] = s[pen];
				if (s[pen] == '+') {
					Coor c; c.r = i; c.c = j;
					available_grid.push_back(c);
				}
				pen++;
			}
	}
	void copy(Board *b, vector<Coor>v) {
		available_grid = v;
	
		memcpy(grid, b->grid, 64 * sizeof(char));
	}
	char get_grid_by_character(char r, char c) {
		int my_r = r - 64, my_c = c - 96;
		return grid[my_r][my_c];
	}
	char get_grid_by_int(int r, int c) {

		return grid[r][c];
	}
	void updateGrid_by_int(int r, int c, char x) {
		grid[r][c] = x;
		vector<Coor>::iterator it_i;
		for (it_i = available_grid.begin(); it_i != available_grid.end(); ++it_i) {
			if ((*it_i).r == r && (*it_i).c == c) {
				available_grid.erase(it_i);
				break;
			}
		}
		
	}
}; 
void my_advance(int dir, int *r, int*c) {
	switch (dir)
	{
	case 0:
		*r -= 1;
		break;
	case 1:*c += 1; *r -= 1; break;
	case 2: *c += 1; break;
	case 3: *c += 1; *r += 1; break;
	case 4: *r += 1; break;
	case 5: *c -= 1; *r += 1; break;
	case 6: *c -= 1; break;
	case 7: *c -= 1; *r -= 1; break;
	default:
		break;
	}
}


int countFlipPieces(Board* b, int color, int r_in, int c_in, int dir) {/*gameboard, the player's color, a grid, a direction*/
	if (b->get_grid_by_int(r_in, c_in) != '+')return 0;
	char me = 'O', opponent = 'X';
	if (color == 1) { me = 'X'; opponent = 'O'; }

	int r, c;
	r = r_in; c = c_in;
	int flipCount = 0;
	char where_me_at;
	
	while (true) {
		my_advance(dir, &r, &c);
		
		where_me_at = b->get_grid_by_int(r, c);
		
		if (where_me_at == opponent) {
			flipCount += 1; continue;
		}
		else if (where_me_at == me)return flipCount;
		else if (where_me_at == 'w') {
			return 0;
		}
		else if (where_me_at == '+') {
			return 0;
		}
	}
	return flipCount;

}
bool isValidMove(Board* b, int player, int r, int c) {
	if (b->get_grid_by_int(r, c) != '+')return false;
	for (int dir = 0; dir < 8; dir++) {
		if (countFlipPieces(b, player, r, c, dir) > 0)return true;
	}return false;
}

void get_char_coor(int r, int c, char* coor) {
	coor[0] = r + 64;
	coor[1] = c + 96;
	coor[2] = '\0';
}
bool passTurn(Board* b, int player) {
	for (unsigned int i = 0; i < b->available_grid.size(); i++) {
		int r=b->available_grid[i].r, c= b->available_grid[i].c;
		if (b->get_grid_by_int(r, c) == '+' && isValidMove(b, player, r, c))return false;

	}
	
	return true;
}int countColorPieces(Board *b, int targetColor) {
	char target = 'O';
	if (targetColor == 1)target = 'X';
	int count = 0;
	for (int i = 1; i <= 6; i++)
		for (int j = 1; j <= 6; j++) {
			if (b->get_grid_by_int(i, j) == target)count++;
		}
	return count;
}

bool gameover(Board* b) {
	return passTurn(b, 1) && passTurn(b, 2);
}


void visualize(Board*b) {
	cout << '-';
	char c = 'a';
	for (int i = 1; i < 7; i++) {
		cout << c; c += 1;
	}
	cout << '\n';
	c = 'A';
	for (int i = 1; i <= 6; i++) {
		cout << c;
		for (int j = 1; j <= 6; j++) {
			cout << b->get_grid_by_int(i,j);

		}
		c += 1;
		cout << endl;
	}
}
void get_coordinates(int *r, int*c, const char *input) {
	*r = input[0] - 64;
	*c = input[1] - 96;
}
const int SQUARE_SCORE[8][8] = {
		{0,0,0,0,0,0,0,0}	,
		{0,100 , -10 , 8  , 8  , -10 ,  100,0},
		{0,-10 , -25 , -4 , -4 , -25 , -10,0 },
		{0,6   ,  -4 ,  0 ,   0, -4 ,  6  ,0},
		{0,6   ,  -4 ,  0 ,   0, -4 ,  6  ,0},
		{0,-10 , -25 ,  -4, -4 , -25 , -10 ,0},
		{0,100 , -10 , 8  , 8  , -10 ,  100,0},
		{0,0,0,0,0,0,0,0} };
int placement_heuristic(Board*b, int player) {
	char player_c='X', oplayer_c='O';
	int opponent = 1;
	if (player == 1) { opponent = 2; player_c = 'O', oplayer_c = 'X';
	}

	int myW = 0;
	int opW = 0;

	for (int i = 1; i < 7; i++) {
		for (int j = 1; j < 7; j++) {
			if (b->get_grid_by_int(i,j) == player_c) myW += SQUARE_SCORE[i][j];
			if (b->get_grid_by_int(i, j) == oplayer_c) opW += SQUARE_SCORE[i][j];
		}
	}

	return myW - opW;
}
int pieces_heuristic(Board* b, int player) {
	int opponent = 1;
	if (player == 1)opponent = 2;
	int mySC = countColorPieces(b, player), opSC = countColorPieces(b, opponent);
	return 100 * (mySC - opSC) / (mySC + opSC + 1);
}
int mobility_heuristc(Board* b, int player) {
	int opponent = 1;
	if (player == 1)opponent = 2;

	int myMoveCount=0, opMoveCount=0;
	vector<Coor>::iterator it_i;
	for (it_i = b->available_grid.begin(); it_i != b->available_grid.end(); ++it_i) {
		int r = (*it_i).r, c = (*it_i).c;
		if (isValidMove(b, player, r, c))myMoveCount++;
		if (isValidMove(b, opponent, r, c))opMoveCount++;
	}


	return 100 * (myMoveCount - opMoveCount) / (myMoveCount + opMoveCount + 1);
}
int cornerGrab_heuristic(Board* b, int player) {
	
	if (isValidMove(b,player,1,1) )return 1;
	if (isValidMove(b, player, 1, 6))return 2;
	if (isValidMove(b, player,6, 1))return 3;
	if (isValidMove(b, player, 6, 6))return 4;
	

	return 0;
}
class Point {
public:
	int r, c;
	Point(int i, int j) {
		r = i; c = j;
	}
};
int getFrontierSquares(Board* b, int player) {

	vector<Point*> frontiers ;

	char player_c = 'X', oplayer_c = 'O';
	int opponent = 1;
	if (player == 1) {
		opponent = 2; player_c = 'O', oplayer_c = 'X';
	}

	for (int i = 1; i < 7; i++) {
		for (int j = 1; j < 7; j++) {
			if (b->get_grid_by_int(i,j) == oplayer_c) {

				vector<Point*> possiblefrontiers;

				//check 8 directions

				//up
				if (i > 1 && b->get_grid_by_int(i - 1, j) == '+') possiblefrontiers.push_back(new Point(i - 1, j));
				//down
				if (i < 6 && b->get_grid_by_int(i + 1,j) == '+') possiblefrontiers.push_back(new Point(i + 1, j));
				//right
				if (j < 6 && b->get_grid_by_int(i,j + 1) == '+') possiblefrontiers.push_back(new Point(i, j + 1));
				//left
				if (j > 1 && b->get_grid_by_int(i,j - 1) == '+') possiblefrontiers.push_back(new Point(i, j - 1));
				//up-left
				if (i > 1&& j > 1 && b->get_grid_by_int(i - 1,j - 1) == '+') possiblefrontiers.push_back(new Point(i - 1, j - 1));
				//up-right
				if (i > 1 && j < 6 && b->get_grid_by_int(i - 1,j + 1) == '+') possiblefrontiers.push_back(new Point(i - 1, j + 1));
				//down-left
				if (i < 6 && j>1 && b->get_grid_by_int(i + 1,j - 1) =='+') possiblefrontiers.push_back(new Point(i + 1, j - 1));
				//down-right
				if (i < 6 && j < 6 && b->get_grid_by_int(i + 1,j + 1) == '+') possiblefrontiers.push_back(new Point(i + 1, j + 1));

				//remove duplicates
				vector<Point*>::iterator it_i;
				for (it_i = possiblefrontiers.begin(); it_i != possiblefrontiers.end(); ++it_i) {
					bool redundant = false;
					vector<Point*>::iterator it_i_frontiers;
					for (it_i_frontiers = frontiers.begin(); it_i_frontiers != frontiers.end(); ++it_i_frontiers) {
						if((*it_i)->r== (*it_i_frontiers)->r&&
							(*it_i)->c == (*it_i_frontiers)->c){
							redundant = true;
							break;
						}
					}
					if (!redundant) frontiers.push_back(*it_i);
				}
				possiblefrontiers.clear();
			}
		}
	}
	int size = frontiers.size();
	frontiers.clear();

	return size;
}
int Frontier_heuristcs(Board* b, int player) {
	int opponent = 1;
	if (player == 1)opponent = 2;

	int myF = getFrontierSquares(b, player);
	int opF = getFrontierSquares(b, opponent);

	return 100 * (myF - opF) / (myF + opF + 1);
}
int h_score(Board* b, int player, int depth) {
	double pieces_w = 0, mobility_w = 0;
	int remain = b->available_grid.size();
	if (remain < 10)					{pieces_w = 2; mobility_w = 0;}
	else if (remain >= 10 && remain < 14) { pieces_w = 1.8, mobility_w = 0.1; }
	else if (remain >= 14 && remain < 18) {pieces_w = 1.4, mobility_w = 0.2;}
	else if (remain >= 18 && remain < 24) { pieces_w = 1.3, mobility_w = 0.3; }
	else if (remain >= 24 && remain < 30){pieces_w = 1.2, mobility_w = 0.4;}
	else								{pieces_w = 1, mobility_w = 0.5;}
	return
		//placement_heuristic(b, player)+	
		pieces_w * pieces_heuristic(b, player)+
		mobility_w * mobility_heuristc(b, player) +
		0.5*Frontier_heuristcs(b, player);
}
void  flipPieces(Board*new_board, Board*org_board, int color, int R, int C) {
	int r_in = R; int c_in = C;
	new_board->copy(org_board, org_board->available_grid);
	if (org_board->get_grid_by_int(r_in, c_in) != '+')return;
	if (!isValidMove(org_board, color, r_in, c_in))return;
	char me = 'O', opponent = 'X';
	if (color == 1) { me = 'X'; opponent = 'O'; }

	int r = r_in, c = c_in;
	new_board->updateGrid_by_int(r, c, me);
	for (int dir = 0; dir < 8; dir++) {
		int steps = countFlipPieces(org_board, color, r, c, dir);
		for (int j = 0; j < steps; j++) {
			my_advance(dir, &r, &c);
			if (org_board->get_grid_by_int(r, c) == opponent)
				new_board->updateGrid_by_int(r, c, me);
		}
		r = r_in;   c = c_in;
	}
}
int minimax(Board* b, int depth, bool isMax,  int max_player_num,int min_player_num, int alpha, int beta, int* chosen_r, int* chosen_c, bool is_top_level) {


	int value; 
	if (depth == 0 || gameover(b))
		return h_score(b, max_player_num,depth);
	if (isMax) {
		value = INT_MIN;
		if (passTurn(b, max_player_num)) {
			return minimax(b, depth - 1, false, max_player_num, min_player_num, alpha,beta ,chosen_r, chosen_c, false);
		}
		//vector<Coor> vec = b->available_grid;
		//std::random_shuffle(vec.begin(), vec.end());
		//vector<Coor>::iterator it_i;
		for (int i=b->available_grid.size()-1; i >=0; --i) {
			int r = (b->available_grid[i]).r, c = (b->available_grid[i]).c;
			if (isValidMove(b,max_player_num,r,c) ){
				Board* child = new Board();
				child->copy(b, b->available_grid);
				flipPieces(child, b, max_player_num, r,c);
			
				int minimax_value = minimax(child, depth - 1, false, max_player_num,min_player_num,  alpha,  beta ,chosen_r, chosen_c, false);
				/*debug 
				if (is_top_level) { 
							cout << '(' << r << ',' << c << ')' << minimax_value << endl; }
							*/
				if (value < minimax_value) {
					if (is_top_level) {
						*chosen_r = r; *chosen_c = c;
					}
					value = minimax_value;
				}delete child;
				if (alpha < value)alpha = value;
				if (beta <= alpha)break;		

			}
		}
		return value;
	}
	else //min player
	{
		value = INT_MAX;
		
		if (passTurn(b, min_player_num)) {
			return minimax(b, depth - 1, true, max_player_num, min_player_num, alpha, beta,chosen_r, chosen_c, false);
		}
		//vector<Coor> vec = b->available_grid;
		//std::random_shuffle(vec.begin(), vec.end());
		vector<Coor>::iterator it_i;
		for (it_i =b->available_grid.begin(); it_i !=b->available_grid.end(); ++it_i) {
			int r = (*it_i).r, c = (*it_i).c;
			if (isValidMove(b, min_player_num, r, c)) {

				Board* child = new Board();
				child->copy(b, b->available_grid);

				flipPieces(child, b, min_player_num, r, c);
				int minimax_value = minimax(child, depth - 1, true, max_player_num, min_player_num, alpha, beta, chosen_r, chosen_c, false);
				if (value > minimax_value) {
					if (is_top_level) {
						*chosen_r = r; *chosen_c = c;
					}
					value = minimax_value;
				}delete child;
				if (beta > value)beta = value;
				if (beta <= alpha)break;
			}
		}
		return value;
	}
}
int main() {
	/*char input[200];
	char s[37];

	
	int step; cin >> step;
	while (step--) {
		
		cin >> s;
		
		int player,depth; cin >> player;
		
		char coor[3];
	
		cin >> depth;
		
		Board* b = new Board(s);
		visualize(b);
		int max_player = 1, min_player = 2;
		if (player == 2) {
			max_player = 2, min_player = 1;
		}
		int r, c;
		minimax(b, depth, true, max_player, min_player, INT_MIN, INT_MAX, &r, &c, true);
		get_char_coor(r, c, coor);
		cout << coor<<'\n';
		delete b;
		
	}

	*/

	
	char s[37];


	int color;
	while (cin >> s >> color) {
		Board* b = new Board(s);
		
		//visualize(b);
		int max_player = 1, min_player = 2;
		if (color == 2) {
			max_player = 2, min_player = 1;
		}
		int r, c;
		int corner = cornerGrab_heuristic(b, max_player);
		if (corner!=0) {
			if (corner == 1)cout << "Aa";
			else if (corner == 2)cout << "Af";
			else if (corner == 3)cout << "Fa";
			else cout << "FF";
			cout << endl; continue;
		}
		Board* nb = new Board();
		//visualize(b);
		nb->copy(b,b->available_grid);
		int oppCorner= cornerGrab_heuristic(nb, min_player);
		if (oppCorner) {
			vector<Coor>::iterator it_i;
			int flag = 0;
			for (it_i = b->available_grid.begin(); it_i != b->available_grid.end(); ++it_i) {
				int r = (*it_i).r, c = (*it_i).c;
				
				if (isValidMove(b, max_player, r, c)) {
					Board* child = new Board();
					child->copy(b, b->available_grid); flipPieces(child, b, max_player, r, c);
					int oppCorner_1 = cornerGrab_heuristic(child, min_player);
					if (oppCorner_1!=oppCorner){
						char coor[3];
						get_char_coor(r, c, coor);
						cout << coor << '\n'; flag = 1; break;
					}delete child;
				}
			}
			if (flag)continue;
		}
		delete nb;
		int depth;
		if (b->available_grid.size() > 15)depth = 7;
		else depth = 8;
		minimax(b,depth, true, max_player, min_player, INT_MIN, INT_MAX, &r, &c, true);
		char coor[3]; 
		get_char_coor(r, c, coor);
		cout << coor << '\n';
		delete b;

	}
	return 0;
}