using namespace std;

unordered_map<int,string> mappa_inv;

vector<vector<int>> build(const vector<variables>& rete,const unordered_map<string,int>& map,unordered_map<int,string>& mappa_inv){
	int i=0;
	for(const auto &chiave : map){
		mappa_inv[chiave.second] = chiave.first;
		i++;
     	}
	vector<vector<int>> adj(i);
	for(const auto &ind : rete){
		if(!(ind.genitori.empty())){
			for(const auto &v : ind.genitori){
				adj[map[v]].push_back(map[ind.name]);
			}
		}
	}
	return adj;
}

void stampa(const vector<vector<int>>& dag,const unordered_map<int,string>& map_inv){
	for(auto vint : dag){
		int i=0;
		cout << map_inv.at(vint[i]) << " : ";
		for(auto j : dag[vint[i]]){
			cout << map_inv.at([j]) << "  ";
		}
		cout << endl;
		i++;
	}
}
