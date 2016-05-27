#include <stdio.h>
#include <vector>
using namespace std;

const int N = 1003;
const int MD = 103;
int n, m;
vector<int> graph[N];
int bin[MD];
int deg[N], pos[N], vert[N];
bool used[N];

void print(int *arr, int beg, int end){
	for(int i = beg; i <= end; ++i){
		printf("%d ", arr[i]);
	}
	printf("\n");
}

void cores(int md){
	for(int d = 0; d <= md; ++d) bin[d] = 0;
	for(int v = 1; v <= n; ++v) bin[deg[v]]++;
	int start = 1;
	for(int d = 0; d <= md; ++d){
		int num = bin[d];
		bin[d] = start;
		start += num;
	}
	for(int v = 1; v <= n; ++v){
		used[v] = false;
		pos[v] = bin[deg[v]];
		vert[pos[v]] = v;
		bin[deg[v]]++;
	}
	for(int d = md; d >= 1; --d) bin[d] = bin[d - 1];
	bin[0] = 1;
	for(int i = 1; i <= n; ++i){
		int v = vert[i];
		used[v] = true;
		for(size_t j = 0; j < graph[v].size(); ++j){
			int u = graph[v][j];
			if(!used[u]){
				used[u] = true;
				if(deg[u] > deg[v]){
					int du = deg[u], pu = pos[u],
						pw = bin[du], w = vert[pw];
					if(u != w){
						pos[u] = pw; vert[pu] = w;
						pos[w] = pu; vert[pw] = u;
					}
					bin[du]++;
					deg[u]--;
				}
			}
		}
	}
}

int main(){
	freopen("in.txt", "r", stdin);
	scanf("%d%d", &n, &m);
	for(int i = 0; i < m; ++i){
		int from, to;
		scanf("%d%d", &from, &to);
		graph[from].push_back(to);
		graph[to].push_back(from);
	}
	int md = 0;
	for(int v = 1; v <= n; ++v){
		deg[v] = graph[v].size();
		if(md < deg[v]) md = deg[v];
	}
	cores(md);
	printf("bin:\n");
	print(bin, 0, md);
	printf("deg:\n");
	print(deg, 1, n);
	printf("pos:\n");
	print(pos, 1, n);
	printf("vert:\n");
	print(vert, 1, n);
	return 0;
}