using namespace std;

void DFS(const vector<vector<int>>& dag,
                     int u,
                     vector<bool>& vis,
                     vector<int>& order,int *conta)
{
    vis[u] = true;
    for (int v : dag[u]) {
        if (!vis[v]) DFS(dag, v, vis, order,conta);
    }
	order[u] = *conta;
	(*conta)--;
}

vector<int> topo_sort(const vector<vector<int>>& dag) {
    int n = dag.size();
    vector<bool> vis(n);
    vector<int> order(n);

	int contatore = n-1;

	for(auto k : vis){
		k = false;
	}

    for (int s = 0; s<n; s++) {
        if (!vis[s]) DFS(dag, s, vis, order,&contatore);
    }
    return order;
}

vector<int> build_topo_pos(const vector<int>& topo_list) {
    vector<int> pos(topo_list.size());
    for (int i = 0; i < topo_list.size(); ++i) {
        pos[topo_list[i]] = i;
    }
    return pos;
}
