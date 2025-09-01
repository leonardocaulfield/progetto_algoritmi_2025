using namespace std;

void DFS(const vector<vector<int>>& dag,vector<int>& ord,int u,bool v[],int *cont);

vector<int> topo_sort(const vector<vector<int>>& dag){

	vector<int> ordinato;
	int n = dag.size();
	bool v[n];
	ordinato.resize(n);

	for(int i=0;i<n;i++) v[i] = false;

	int contatore = n-1;

	for(int s=0;s< n;s++){
		if(!(v[s])){
			DFS(dag,ordinato,s,v,&contatore);
		}
	}
	return ordinato;
}

void DFS(const vector<vector<int>>& dag,vector<int>& ord,int u,bool v[],int *cont){

	v[u] = true;
	for(auto x : dag[u])
	{
		auto k = x;
		if(!(v[k])){
			DFS(dag,ord,k,v,cont);
		}
	}
	ord[u] = *cont;
	(*cont)--;
}

void stampavet(const vector<int>& vet){

	cout << endl;
	cout << "[";

	for(auto i : vet){
		cout << i << " , ";
	}

	cout << "]";
	cout << endl;

}
