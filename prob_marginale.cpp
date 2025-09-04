using namespace std;

//construzione della struttura dati per aiutarmi trovare il cpt

struct dettagli{
	int card_valori;
	vector<int> cardinalita_val_par;
	vector<int> stride_parent;
	vector<int> quale_parent;
};


vector<dettagli> creo_parenti(const vector<variabile>& rete,unordered_map<string,int>& name_id){

	vector<dettagli> ip;
	ip.resize(rete.size());

	for(int i=0;i<ip.size();i++){

		ip[i].card_valori = rete[i].tipi.size();
		if(!(rete[i].genitori.empty())){
			int j=0;


			for(auto x : rete[i].genitori){

				ip[i].quale_parent.push_back(name_id.at(x));
				ip[i].cardinalita_val_par.push_back(rete[name_id[x]].tipi.size());
				j++;
			}
		}

		else if(rete[i].genitori.empty()){
			ip[i].quale_parent.clear();
			ip[i].cardinalita_val_par.clear();
		}

		ip[i].stride_parent.resize(ip[i].quale_parent.size());

		for(int k=0;k<ip[i].stride_parent.size();k++){

			ip[i].stride_parent[k] = (k == 0 ? 1 : ip[i].stride_parent[k-1] * ip[i].cardinalita_val_par[k-1]);
		}
	}

	return ip;
}

int righe(int ind,const vector<dettagli>& cardi,const vector<int>& a){

	int riga=0;
	const auto& par = cardi[ind].quale_parent;
	const auto& str = cardi[ind].stride_parent;

	int v;
	for(int i=0;i<cardi[ind].stride_parent.size();i++){
		riga += a[par[i]] * str[i];
	}
	return riga;
}

bool controllo(const vector<dettagli>& par,vector<int>& assig,int fissato,const vector<int>& topo,const vector<int>& topo_pos){

	int stop = topo_pos[fissato];         // posizione di fissato nella LISTA
    // Itera sulle POSIZIONI < stop, mappando al nodo corrispondente
	for (int p = 0; p < stop; ++p) {
        int j = topo[p];                  // 'j' è ora l'id del nodo da incrementare
        if (j == fissato) continue;
        if (++assig[j] < par[j].card_valori) return true;
        assig[j] = 0;
    }
    return false;
}

double prob_esatta(int ind,const vector<dettagli>& cardi,const vector<int>& a,const vector<variabile>& rete){

	if(!(rete[ind].genitori.empty())){
		int r = righe(ind,cardi,a);
		return rete[ind].cpt[r][a[ind]];
	}
	else if(rete[ind].genitori.empty()){
		return rete[ind].cpt[0][a[ind]];
	}
	return 0;
}

double joint_probability(const vector<variabile>& bay,const vector<int>& ass,const vector<dettagli>& info_parenti,const vector<int>& topo){
	double ris = 1;
	for(int x : topo){
		ris *= prob_esatta(x,info_parenti,ass,bay);
	}
	return ris;
}

double probabilita_marginale(const vector<variabile>& bayes,
                             const vector<int>& topo,
                             const vector<dettagli>& cardi,
                             const string& name,
                             const string& val)
{
    int idx = -1, val_idx = -1;
    for (size_t i = 0; i < bayes.size(); ++i) {
        if (bayes[i].name == name) {
            idx = static_cast<int>(i);
            for (size_t t = 0; t < bayes[i].tipi.size(); ++t) {
                if (bayes[i].tipi[t] == val) { val_idx = static_cast<int>(t); break; }
            }
            break;
        }
    }
    if (idx < 0 || val_idx < 0) return 0.0;

// prob_marginale.cpp (pezzo già presente, ora coerente con A)
	vector<int> topo_pos = build_topo_pos(topo);
	int stop = topo_pos[idx];

	vector<int> topo_pref;
	topo_pref.reserve(stop + 1);
	for (int p = 0; p <= stop; ++p) topo_pref.push_back(topo[p]); // nodi corretti

	vector<int> assig(bayes.size(), 0);
	assig[idx] = val_idx;

	double somma = 0.0;
	do {
	    somma += joint_probability(bayes, assig, cardi, topo_pref); // moltiplica sui nodi giusti
	} while (controllo(cardi, assig, idx, topo, topo_pos));

	return somma;
}

void marginale(const vector<variabile>& b,const vector<int>& topologico,const vector<dettagli>& cardinalita){

	string n;
	string v;

	for(int i=0;i<b.size();i++){
		n = b[i].name;
		int j=0;
		while(j < b[i].tipi.size()){
			v = b[i].tipi[j];
			cout << "P(" << n << "= " << v << ")" << " = " << probabilita_marginale(b,topologico,cardinalita,n,v);
			cout << endl;
			j++;
		}
	}
}
