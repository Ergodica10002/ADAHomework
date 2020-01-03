#include <iostream>
#include <vector>
#include <math.h>
#define MAXN 210000
enum color{white = 0, gray = 1, black = 2};
#define NDEBUG
#define MAXK 550	//for not use too much memory
#define Table_size 1073741824	//for hash
using namespace std;
vector <int> reach[MAXN];
vector <int> adlist[MAXN];
int color[MAXN] = {0};	//for DFS
int myhash(int num){	//hash function
	double c = 0.618;
	int h = floor(Table_size * (num * c - floor(num * c)));
	return h;
}
void printgraph(int N){
	for (int i = 1; i <= N; i++){
		printf("%d ", i);
		if (adlist[i].size() != 0){
			for (int j = 0; j < adlist[i].size(); j++)
				printf("%d ", adlist[i][j]);
		}
		printf("\n");
	}
	return;
}
void printreach(int N){
	printf("reach\n");
	for (int i = 1; i <= N; i++){
		printf("%d :\n", i);
		vector<int>::iterator it = reach[i].begin();
		while (it != reach[i].end()){
			printf("%d ", *it);
			it++;
		}
		printf("\n");
	}
}
void initreach(int N){
	for (int i = 1; i <= N; i++){
		reach[i].push_back(i);
	}

	return;
}
void Combinehash(int v1, int v2){	//combine two sets, the result set must have size < MAXK
	vector<int>::iterator i1 = reach[v1].begin();
	vector<int>::iterator i2 = reach[v2].begin();
	vector<int> newvec;
	if (*i1 > *i2)
		newvec.push_back(*i2);
	else
		newvec.push_back(*i1);
	int count = MAXK;

	while((i1 != reach[v1].end() || i2 != reach[v2].end())){
		if (count < 0)
			break;
		if (i1 == reach[v1].end()){
			if (newvec.back() != *i2){
				newvec.push_back(*i2);
				count--;
			}
			i2++;
		}
		else if (i2 == reach[v2].end()){
			if (newvec.back() != *i1){
				newvec.push_back(*i1);
				count--;
			}
			i1++;
		}
		else{
			if (*i1 > *i2){
				if (newvec.size() != 0 && newvec.back() != *i2){
					newvec.push_back(*i2);
					count--;
				}
				i2++;
			}
			else{
				if (newvec.size() != 0 && newvec.back() != *i1){
					newvec.push_back(*i1);
					count--;
				}
				i1++;
			}
		}
	}
	vector <int>::iterator it = newvec.begin();
	reach[v1].assign(newvec.begin(), newvec.end());
	return;
}
void DFSv(int v){
	color[v] = gray;
	int size = adlist[v].size();
	for (int i = 0; i < size; i++){
		if (color[adlist[v][i]] == white)
			DFSv(adlist[v][i]);
		Combinehash(v, adlist[v][i]);
	}
	color[v] = black;
	return;
}
float Jaccard(int q1, int q2){	
	int internum = 0;
	int unionnum = 0;
	vector<int>::iterator i1 = reach[q1].begin();
	vector<int>::iterator i2 = reach[q2].begin();
	while(i1 != reach[q1].end() || i2 != reach[q2].end()){
		if (i1 == reach[q1].end()){
			unionnum++;
			i2++;
		}
		else if (i2 == reach[q2].end()){
			unionnum++;
			i1++;
		}
		else{
			if (*i1 > *i2){
				unionnum++;
				i2++;
			}
			else if (*i1 < *i2){
				unionnum++;
				i1++;
			}
			else{
				*i1++;
				*i2++;
				unionnum++;
				internum++;
			}
		}
	}
	if (unionnum > MAXK)
		unionnum = MAXK;
	double f = (double)internum / (double)unionnum;
	return f;

}
int main(){
	int N, M, Q;
	scanf("%d%d%d", &N, &M, &Q);
	for (int i = 0; i < M; i++){
		int u, v;
		scanf("%d%d", &u, &v);
		adlist[u].push_back(v);
	}

	initreach(N);
	for (int i = 1; i <= N; i++){
		if (color[i] == white){
			DFSv(i);
		}
	}

#ifndef NDEBUG
	printgraph(N);
	printreach(N);
#endif

	for(int i = 0; i < Q; i++){
		int q1, q2;
		scanf("%d%d", &q1, &q2);
		double f = Jaccard(q1, q2);
		printf("%lf\n", f);
	}

	return 0;
}