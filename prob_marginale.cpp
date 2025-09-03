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

bool controllo(const vector<dettagli>& par,vector<int>& assig);

double prob_esatta(int ind,const vector<dettagli>& cardi,const vector<int>& a,const vector<variabile>& rete){
	int r = righe(ind,cardi,a);
	return rete[ind].cpt[r][a[ind]];
}

double joint_probability(const vector<variabile>& bay,const vector<int>& ass,const vector<dettagli>& info_parenti,const vector<int>& topo){
	double ris = 1;
	for(int x : topo){
		ris *= prob_esatta(x,info_parenti,ass,bay);
	}
	return ris;
}

double probabilita_marginale(const vector<variabile>& bayes,const vector<int>& topo,const vector<dettagli>& cardi,string name,string val)
{
	vector<int> assing;
	assing.resize(cardi.size());

	for(int i=0;i<assing.size();i++) assing[i] = 0;

	double risultato = 0;

	do{
		risultato += joint_probability(bayes,assing,cardi,topo);

	}while(controllo(cardi,assing));
	
	return risultato;
}


bool controllo(const vector<dettagli>& par,vector<int>& assig){

	for(int j=0;j<assig.size();j++){
		if(++assig[j]<par[j].card_valori) return true;
		assig[j] = 0;
	}
	return false;
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
