#include <iostream>
#include <vector>
#include <algorithm>
#include <functional>
#include <cstdlib>
#include <cstring>
#include "hex.h"
#define K 2000
using namespace std;
typedef pair<int, int> pii;

const int maxn = 11;

bool board[maxn][maxn];
bool mystep[maxn][maxn];
int n;

struct Compare {
    bool operator() (const pii &lhs, const pii &rhs) {
        if (lhs.first != rhs.first)
        	return (lhs.first > rhs.first);
        else return (lhs.second > rhs.second);
    }
};
struct Compare2{
    bool operator() (const pii &lhs, const pii &rhs) {
        if (lhs.first != rhs.first)
        	return (lhs.first < rhs.first);
        else return (lhs.second < rhs.second);
    }
};

bool updownadj(int rc, int cc){
	if (rc > 0){
		if (mystep[rc - 1][cc] == true)
			return true;
	}
	if (rc > 0 && cc < n - 1){
		if (mystep[rc - 1][cc + 1] == true)
			return true;
	}
	if (rc < n - 1){
		if (mystep[rc + 1][cc] == true)
			return true;
	}
	if (rc < n - 1 && cc > 0){
		if (mystep[rc + 1][cc - 1] == true)
			return true;
	}
	if (cc > 0){
		if (mystep[rc][cc - 1] == true)
			return true;
	}
	if (cc < n - 1){
		if (mystep[rc][cc + 1] == true)
			return true;
	}
	return false;
}

void printmystep(){
	for (int i = 0; i < n; i++){
		for (int j = 0; j < n; j++)
			printf("%d", mystep[i][j]);
		printf("\n");
	}
	printf("\n");
}

bool visit(bool visited[maxn][maxn], int row, int col){
	visited[row][col] = 1;
	if (row == n - 1)
		return true;
	if (col > 0 && mystep[row + 1][col - 1] == 1)
		if (!visited[row + 1][col - 1] && visit(visited, row + 1, col - 1))
			return true;
	if (mystep[row + 1][col] == 1)
		if (!visited[row + 1][col] && visit(visited, row + 1, col))
			return true;
	if (col > 0 && mystep[row][col - 1] == 1)
		if (!visited[row][col - 1] && visit(visited, row, col - 1))
			return true;
	if (col < n - 1 && mystep[row][col + 1] == 1)
		if (!visited[row][col + 1] && visit(visited, row, col + 1))
			return true;
	return false;
}

bool testwin(){
	bool visited[maxn][maxn] = {{0}};
	for (int i = 0; i < n; i++){
		if (mystep[0][i] == 1){
			if (visit(visited, 0, i)){
				return true;
			}
		}
	}
	return false;
}

int testwinnum(int row, int col){
	bool mystep_init[maxn][maxn];
	bool board_init[maxn][maxn];
	for (int i = 0; i < n; i++){
		for (int j = 0; j < n; j++){
			mystep_init[i][j] = mystep[i][j];
			board_init[i][j] = board[i][j];
		}
	}

	int testnum = K;
	int winnum = 0;
	while(testnum != 0){
		testnum--;
		bool nowplay = 1;
		for (int i = 0; i < n; i++){
			for (int j = 0; j < n; j++){
				mystep[i][j] = mystep_init[i][j];
				board[i][j] = board_init[i][j];
			}
		}
		mystep[row][col] = board[row][col] = 1;

		vector<pii> unused;
		for (int i = 0; i < n; i++){
			for (int j = 0; j < n; j++){
				if (board[i][j] == 0)
					unused.push_back({i, j});
			}
		}

		random_shuffle(unused.begin(), unused.end());

		while (!unused.empty()){
			pii tryp = unused.back();
			unused.pop_back();
			if (nowplay == 0){
				mystep[tryp.first][tryp.second] = 1;
				board[tryp.first][tryp.second] = 1;
				nowplay = 1;
			}
			else{
				board[tryp.first][tryp.second] = 1;
				nowplay = 0;
			}
		}

		if (testwin() == 1){
			winnum++;
		}
	}

	for (int i = 0; i < n; i++){
		for (int j = 0; j < n; j++){
			mystep[i][j] = mystep_init[i][j];
			board[i][j] = board_init[i][j];
		}
	}

	return winnum;
}
void init(int _n) {
    n = _n;
    memset(board, 0, sizeof board);
    memset(mystep, 0, sizeof mystep);
    srand(12345);
}
pii decide(pii p) {
    if (p == make_pair(-1, -1)){
    	if (n % 2 == 1){
    		board[n / 2][n / 2] = true;
    		mystep[n / 2][n / 2] = true;
    		return make_pair(n / 2, n / 2);
    	}
    	else{
    		board[n / 2 - 1][n / 2] = true;
    		mystep[n / 2 - 1][n / 2] = true;
    		return make_pair(n / 2 - 1, n / 2);
    	}
    }
    board[p.first][p.second] = true;

    vector<pii> unused;
    for (int i = 0; i < n; ++i)
        for (int j = 0; j < n; ++j)
            if (!board[i][j])
                unused.push_back({i, j});
    
    int canmove = unused.size();
    pii result = make_pair(-1, -1);
    int max_winnum = -1;
    for (int i = 0; i < canmove; i++){
    	pii tryp = unused[i];
    	if (updownadj(tryp.first, tryp.second)){
    		int winnum = testwinnum(tryp.first, tryp.second);
    		if (winnum > max_winnum){
    			result = tryp;
    			max_winnum = winnum;
    		}
    	}
    }

    if (result == make_pair(-1, -1)){
    	result = unused[rand() % unused.size()];
    }
    
    board[result.first][result.second] = true;
    mystep[result.first][result.second] = true;

    return result;
}
