using namespace std;

unordered_map<int,string> id_name;

vector<vector<int>> build(const vector<variabile>& rete,const unordered_map<string,int>& name_id,unordered_map<int,string>& id_name){
	int i=0;
	for(const auto &chiave : map){
		mappa_inv[chiave.second] = chiave.first;
		i++;
     	}
	vector<vector<int>> adj(i);
	for(const auto &ind : rete){
		if(!(ind.genitori.empty())){
			for(const auto &v : ind.genitori){
				adj.at(map.at(v)).push_back(map.at(ind.name));
			}
		}
	}
	return adj;
}

void stampa(const vector<vector<int>>& dag,const unordered_map<int,string>& id_name){
    for (size_t u = 0; u < dag.size(); u++) {
        cout << map_inv.at(u) << " ---> ";
        if (dag[u].empty()) {
            cout << "vuoto" << endl;
            continue;
        }
        for (int v : dag[u]) cout << map_inv.at(v) << "  ";
        cout << endl;
    }
}
