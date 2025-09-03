using namespace std;

//construzione della struttura dati per aiutarmi

struct dettagli{
	int card_valori;
	vector<int> cardinalita_val_par;
	vector<int> stride_parent;
	vector<int> quale_parent;
};


vectro<dettagli> creo_parenti(const vector<variabile>& rete,unordered_map<string,int>& name_id){

	vector<dettagli> ip;
	ip.resize(rete.size());

	for(int i=0;i<ip.size();i++){
		ip[i].card_valori = rete[i].valori.size();
		if(!(rete[i].genitori.empty()){
			int j=0;
			for(auto x : rete.genitori[i]){
				ip.quale_parent.resize(j+1);
				ip.cardinalita_val_par.resize(j+1);
				ip.quale_parent.push_back(rete[name_id[x]]);
				ip.cardinalita_val_par.push_back(rete[name_id[x]].valori.size());

				j++;
			}
		}
		else if(rete[i].genitori.empty()){
			ip[i].quale_parent.clear();
			ip[i].cardinalita_val_par.clear();
		}
		ip[i].stride_parent.resize(ip[i].quale_parent.size());
		for(int k=0;k<ip[i].stride_parent.size();k++){
			ip[i].stride_parent[k] = (k == 0 ? 1 : ip[i].stride_parent[k-1] * ip[i].cardinalita_parent[k-1];
		}
	}
	return ip;
}

int righe(int ind,const vector<dettagli>& cardi,const vector<int>& a){
	int riga=0;
	const auto& par = cardi[ind].parents;
	const auto& str = cardi[ind].stride_parents;

	int v;
	for(int i=0;i<cardi[ind].stride_parent.size();i++){
		riga += assing[par[i]] * str[i];
	}
	return riga;
}


double probabilita_marginale(const vector<variabile>& bayes,int topo[],const vector<dettagli>& cardi,string name,string val)
{
	vector<int> assing;
	assing.resize(cardi.size());

	for(int i=0;i<assing.size();i++) assing[i] = 0;

	double risultato = 0;

	do{
		risultato += joint_probability(cardi,assig);

	}while(controllo(cardi,assing);
	
	return risutato;

}

double prob_esatta(int ind,const vector<dettagli>& cardi,const vector<int>& a,const vector<variabile>& rete){
	int r = righe(ind,cardi,a);
	return rete[i].cpt[r][a[i]];
}

bool controllo(const vector<dettagli>& par,vector<int> assig){

	for(int j=0;j<assig.size();j++){
		if(++assig[j]<par[j].car_valori) return true;
		assig[j] = 0;
	}
	return false;
}

double joint_probability(const vector<variabile>& bay,const vector<int>& ass,const vector<dettagli>& info_parenti,const int topo[]){
	double ris = 1;
	for(int x : topo){
		ris *= prob_esatta(x,info_parenti,ass,rete);
	}
	return ris;
}

void marginale(const vector<variabile>& b){

	string n;
	string v;

	for(int i=0;i<b.size();i++){
		n = b[i].name;
		int j=0;
		while(j < b[i].valori.size()){
			v = b[i].valori[j];
			cout << "P(" << n << "= " << v << ")" << " = " << probabilita_marginale(b,topologico,cardinalita,n,v);
			cout << endl;
			j++;
		}
	}
}
