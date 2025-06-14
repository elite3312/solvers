﻿#include<iostream>
#include<cstring>
#include<cmath>
#include <queue>
#include <vector>
#pragma warning(disable : 4996)
using namespace std;
int compare(char a, int b) {/*b<a return -1, a=b return 0*/
	if (a == '\0')return -1;
	if (a == '0')return -1;
	if (a >= 65) {
		if (a - 55 == b)return 0;
		else if (a - 55 > b)return -1;
		else return 1;
	}
	else {
		if (a - 48 == b)return 0;
		else if (a - 48 > b)return -1;
		else return 1;
	}
}
struct dataNode {
	char s[17]; // choose whatever representation of a state you like, such as a string or a Ndim × Ndim array)
	int g, h, f; // g: so-far cost; h: estimated cost to goal; f = g + h
	int action, entry_time; dataNode *parent;
	// this state is generated by applying which action to which parent state
};
bool solvability(char*s) {
	struct orderedPair { int a; int b; };
	vector <orderedPair>vect;
	int N = strlen(s);
	int n = sqrt(strlen(s));
	int pairCount = 0;
	for (int j = 1; j < N; j++) {
		char*p = s;
		while (compare(*p, j) != 0)p++;
		while (1) {
			p++;
			if (*p == '\0')break;
			if (compare(*p, j) > 0) {
				orderedPair pair;
				pair.a = j;
				if (*p >= 65)
					pair.b = *p - 55;
				else
					pair.b = *p - 48;
				int existFlag = 0;
				for (std::vector<orderedPair>::iterator it = vect.begin(); it != vect.end(); ++it)
				{
					if (((*it).a == pair.a && (*it).b == pair.b) ||
						((*it).a == pair.b && (*it).b == pair.a)) {
						existFlag = 1; break;
					}
				}
				if (existFlag)continue;
				else {
					vect.push_back(pair); pairCount++;
				}
			}
		}
	}
	if (n % 2 == 1) {
		if (pairCount % 2 == 0)return true;
		else return false;

	}
	else {
		int zeroPos = 0;
		char*p = s;
		while (*p != '0') {
			p++; zeroPos++;
		}
		int zeroRow = zeroPos / n;
		if ((zeroRow + pairCount) % 2 == 0)return true;
		else return false;
	}
	vect.clear();
	return false;
}
void get_successor(const char*p,char* up, char * down, char *left, char*right) {
	int r = 0, c = 0, row, col;
	int matrices[30][30]; 
	int N = strlen(p);
	int n = sqrt(N);
	for (; r < n; r++)
		for (c = 0; c < n; c++) {
			if (*p == '\0')break;

			if (*p <= '9') {
				if (*p == '0') { row = r; col = c; }
				matrices[r][c] = *p - 48;
			}
			else matrices[r][c] = *p - 55;
			p++;
		}
	int possible_moves = 0;
	char s1[30], s2[30], s3[30], s4[30];
	int flag[4] = { 0,0,0,0 }, j;
	if (row - 1 >= 0) {
		possible_moves++;
		int temp;
		temp = matrices[row - 1][col];
		matrices[row - 1][col] = matrices[row][col];
		matrices[row][col] = temp;
		flag[0] = 1;
		j = 0;
		for (r = 0; r < n; r++)
			for (c = 0; c < n; c++)
			{
				if (matrices[r][c] <= 9) {
					s1[j] = matrices[r][c] + 48;
				}
				else
					s1[j] = matrices[r][c] + 55;
				j++;
			}
		s1[j] = '\0';
		strcpy(up, s1);
		temp = matrices[row - 1][col];
		matrices[row - 1][col] = matrices[row][col];
		matrices[row][col] = temp;
	}
	if (row + 1 <= 3) {
		possible_moves++;
		int temp;
		temp = matrices[row + 1][col];
		matrices[row + 1][col] = matrices[row][col];
		matrices[row][col] = temp;
		flag[1] = 1;
		j = 0;
		for (r = 0; r < n; r++)
			for (c = 0; c < n; c++)
			{
				if (matrices[r][c] <= 9) {
					s2[j] = matrices[r][c] + 48;
				}
				else
					s2[j] = matrices[r][c] + 55;
				j++;
			}
		s2[j] = '\0';
		strcpy(down, s2);
		temp = matrices[row + 1][col];
		matrices[row + 1][col] = matrices[row][col];
		matrices[row][col] = temp;
	}
	if (col - 1 >= 0) {
		possible_moves++;
		int temp;
		temp = matrices[row][col - 1];
		matrices[row][col - 1] = matrices[row][col];
		matrices[row][col] = temp;
		flag[2] = 1;
		j = 0;
		for (r = 0; r < n; r++)
			for (c = 0; c < n; c++)
			{
				if (matrices[r][c] <= 9) {
					s3[j] = matrices[r][c] + 48;
				}
				else
					s3[j] = matrices[r][c] + 55;
				j++;
			}
		s3[j] = '\0';
		strcpy(left, s3);
		temp = matrices[row][col - 1];
		matrices[row][col - 1] = matrices[row][col];
		matrices[row][col] = temp;
	}
	if (col + 1 <= 3) {
		possible_moves++;
		int temp;
		temp = matrices[row][col + 1];
		matrices[row][col + 1] = matrices[row][col];
		matrices[row][col] = temp;
		flag[3] = 1;
		j = 0;
		for (r = 0; r < n; r++)
			for (c = 0; c < n; c++)
			{
				if (matrices[r][c] <= 9) {
					s4[j] = matrices[r][c] + 48;
				}
				else
					s4[j] = matrices[r][c] + 55;
				j++;
			}
		s4[j] = '\0';
		strcpy(right, s4);
		temp = matrices[row][col + 1];
		matrices[row][col + 1] = matrices[row][col];
		matrices[row][col] = temp;
	}
}

struct custom_compare {
	bool operator()(const struct dataNode * a, const struct dataNode *  b) {
		int a_priority = (*a).g + (*a).h;
		int b_priority = (*b).g + (*b).h;
		if (a_priority > b_priority)return true;
		else if (a_priority < b_priority)return false;
		else {
			if (a->entry_time > b->entry_time)return true;
			else return false;
		}
	}

};
int manhattan_dist(char*p) {
	int N = strlen(p);
	int n = sqrt(N);
	
	int r = 0, c = 0, row, col;
	int matrices[30][30];
	for (r = 0; r < n; r++)
		for (c = 0; c < n; c++) {
			if (*p == '\0')break;

			if (*p <= '9') {
				if (*p == '0') { row = r; col = c; }
				matrices[r][c] = *p - 48;
			}
			else matrices[r][c] = *p - 55;
			p++;
		}
	int goal_num = 1, i = 0, manhatan_dist = 0;
	while (goal_num < 16) {
		i = 0;
		int  goal_r, goal_c;/*find ideal goal pos*/
		for (r = 0; r < n; r++) {
			int break_flag = 0;
			for (c = 0; c < n; c++) {
				goal_r = r; goal_c = c;
				if (i == goal_num) {
					break_flag = 1; break;
				}
				i++;
			}if (break_flag)break;
		}
		int goal_r_actual = 0, goal_c_actual = 0;
		for (r = 0; r < n; r++) {
			int break_flag = 0;
			for (c = 0; c < n; c++) {
				goal_r_actual = r; goal_c_actual = c;
				if (matrices[r][c] == goal_num) {
					break_flag = 1; break;
				}

			}
			if (break_flag)break;
		}
		manhatan_dist += abs(goal_r_actual - goal_r) + abs(goal_c_actual - goal_c);
		goal_num++;
	}
	return manhatan_dist;
}
int main() {
	char s[30];
	const char* goal = "0123456789ABCDEF";
	cin.getline(s, 30, '\n');
	strtok(s, "\r\n?");
	if (strcmp(s, "0123456789ABCDEF") == 0){cout << "It is the goal state." << endl;
		return 0;
	}
	int g_score = 0, h_score = 0;
	if (solvability(s) == false) {
		cout << "No solution!!" << endl; return 0;
	}


	
	struct dataNode * mynode; struct dataNode *  newnode; struct dataNode* final = NULL;
	
	int nextStateCount;
	char nextState[4][17];
	char nextAction[4];
	mynode = new dataNode();
	strcpy((*mynode).s, s);
	(*mynode).g = 0;
	(*mynode).h = manhattan_dist(s);
	(*mynode).f = (*mynode).g +( *mynode).h;
	(*mynode).parent = NULL;
	priority_queue<dataNode*,vector<dataNode*>,custom_compare> q;
	q.push(mynode); int entry_time = 0;
	while (q.empty() != true) {
		mynode = q.top();
		q.pop();
		if (strcmp((*mynode).s, goal) == 0) {
			final = mynode; break;
		}
		nextState[0][0] = 'n';
		nextState[1][0] = 'n';
		nextState[2][0] = 'n';
		nextState[3][0] = 'n';
		get_successor((*mynode).s, nextState[0], nextState[1],
			nextState[2], nextState[3]);
		for (int i = 0; i < 4; i++) {
			if (nextState[i][0] != 'n') {
				newnode = new dataNode();
				strcpy((*newnode).s, nextState[i]);
				(*newnode).action = i;
				(*newnode).g = (*mynode).g + 1;
				(*newnode).h = manhattan_dist(nextState[i]);
				(*newnode).f = (*newnode).g + (*newnode).h;
				(*newnode).parent = mynode;
				newnode->entry_time = entry_time++;
				q.push(newnode);
			}
		}
	}
	if (final == NULL)cout << "No solution!!";
	else {
		int stack[1000], top = -1;
		while (final->parent) {
			top++;
			if (final->action == 0)stack[top] = 0;
			else if (final->action == 1)stack[top] = 1;
			else if (final->action == 2)stack[top] = 2;
			else stack[top] = 3;
			
			final = final->parent;
		}
		for (int i = top; i > -1; i--) {
			if (stack[i] == 0)cout << "move 0 to up\n";
			else if (stack[i]== 1)cout << "move 0 to down\n";
			else if (stack[i] == 2)cout << "move 0 to left\n";
			else cout << "move 0 to right\n";
		}
	}
	
	return 0;

}

