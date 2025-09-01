using namespace std;

vector<int> topo_sort(const vector<vector<int>>& dag){

	vector<int> ordinato;
	int n = size(dag);
	bool v[n];
	ordinato.resize(n);

	for(int i=0;i<n;i++) v[i] = false;

	contatore = n-1;

	for(int s=0;s< n;s++){
		if(!(v[s])){
			DFS(...)
		}
	}
}

void DFS(){

	v[u] = true;
	for(int x : dag[u])
	{
		auto k = x;
		if(!(v[k])){
			DFS(...)
		}
	}
	ordinato[u] = contatore;
	contatore--;
}
