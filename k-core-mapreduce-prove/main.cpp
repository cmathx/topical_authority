#include <stdio.h>
#include <vector>
using namespace std;

const int N = 1003;
int n, m;
vector<int> graph[N], est[N];
int core[N];

void print(int *arr, int _beg, int _end){
	for(int i = _beg; i <= _end; ++i){
		printf("%d ", arr[i]);
	}
	printf("\n");
}

void print_detail(){
    printf("--------\n");
    printf("core:\n");
	print(core, 1, n);
}

void init(){
    int md = 0;
	for(int v = 1; v <= n; ++v){
		core[v] = graph[v].size();
		if(md < core[v]) md = core[v];
	}
}

int computeIndex(vector<int> &_est, int u, int k){
    int *count = new int[k + 1];
    for(int i = 1; i <= k; ++i) count[i] = 0;
    for(size_t i = 0; i != graph[u].size(); ++i){
        int v = graph[u][i];
        int j = min(k, _est[i]);
        count[j] += 1;
    }
    for(int i = k; i >= 2; --i) count[i - 1] += count[i];
    int ret = k;
    for(; ret > 1; --ret){
        if(count[ret] >= ret) break;
    }
    return ret;
}

//input data:(u_i, u_j, w_ij)


//key:u
//value:(v, core[v]) est[u][], core[u]
//receive message(u, v, core[v]) to update est[u][], core[u]
//est[u][], core[u]
bool receive(int u, int v_ind, int k){
    bool is_update = false;
    if(k < est[u][v_ind]){
        est[u][v_ind] = k;
        int t = computeIndex(est[u], u, core[u]);
        if(t < core[u]){
            core[u] = t;
            is_update = true;
        }
    }
    return is_update;
}

void process(){
    init();
    print_detail();
    bool is_global_update = true;
    int converge_cnt = 0;
    while(is_global_update){
        is_global_update = false;
        for(int u = 1; u <= n; ++u){
            for(int v_ind = 0; v_ind < graph[u].size(); ++v_ind){
                if(receive(u, v_ind, core[graph[u][v_ind]]))
                    is_global_update = true;
            }
        }
        converge_cnt++;
        print_detail();
    }
    //print_detail();
    printf("converge count = %d\n", converge_cnt);
}

int main()
{
    freopen("in1.txt", "r", stdin);
	scanf("%d%d", &n, &m);
	for(int i = 0; i < m; ++i){
		int from, to;
		scanf("%d%d", &from, &to);
		graph[from].push_back(to);
		graph[to].push_back(from);
		est[from].push_back(INT_MAX);
		est[to].push_back(INT_MAX);
	}
    process();
    return 0;
}
