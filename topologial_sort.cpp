// topologial_sort.cpp
#include <algorithm>

using namespace std;

// DFS che costruisce l'ordine topologico (push su fine visita)
static void DFS_list(const vector<vector<int>>& dag,
                     int u,
                     vector<char>& vis,
                     vector<int>& order)
{
    vis[u] = 1;
    for (int v : dag[u]) {
        if (!vis[v]) DFS_list(dag, v, vis, order);
    }
    order.push_back(u);  // push dopo i figli
}

// Restituisce la lista dei nodi in ordine topologico
vector<int> topo_sort(const vector<vector<int>>& dag) {
    int n = (int)dag.size();
    vector<char> vis(n, 0);
    vector<int> order;
    order.reserve(n);

    for (int s = 0; s < n; ++s) {
        if (!vis[s]) DFS_list(dag, s, vis, order);
    }

    reverse(order.begin(), order.end()); // ottieni ordine corretto
    return order; // esempio: [nodo1, nodo2, nodo3, ...]
}

// Costruisce la mappa nodo -> posizione nell’ordinamento topologico
vector<int> build_topo_pos(const vector<int>& topo_list) {
    vector<int> pos(topo_list.size());
    for (int i = 0; i < (int)topo_list.size(); ++i) {
        pos[topo_list[i]] = i;
    }
    return pos;
}
