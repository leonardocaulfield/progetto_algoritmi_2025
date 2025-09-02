using namespace std;

/*
double joint_probability(const vector<variable>& bay,vector<string,string>& assig){
	return 
}

double marginale(const vector<variable>& bayes,string nome,string valore,int topo[],const unordered_map id_to_name,const unordered_map name_to_id){

	vector<string,string> assigment;
	int k=0;
	for(int i=0;(topo[i]!=name_to_id[nome]) && i<topo.size();i++){
		assigment.resize(i+1);
		assigment[i].push_back({ id_to_name[topo[i]], rete[topo[i]].valore[k] });
	}

	double risultato;
//INDIVIDUO GLI ELEMENTI DEL CPT
	

	for(int i=0;i<assigment.size();i++){

	}
}
*/

double joint_probability(const vector<varible>& bay,const vector<int>& ass);


double probabilita_marginale(const vector<varible>& bayes,int topo[],const vector<int> cardi,string name,string valore,)
{
	vector<int> assing;
	int contatore;
	for(contatore =0;top[contatre] != name_to_id[name]; contatore++);
	assing.resize(contatore);

	for(int i=0;i<assing.size();i++) assing[i] = 0;

	double risultato = 0;

	do{
		risultato += joint_probability(cardi,assig);

	}while(controllo(cardi,assing);
	
	return risutato;

}

bool controllo(const vector<int>& card,vector<int> assig){

	for(int j=0;j<assig.size();j++){
		if(++assig[j]<card[j]) return true;
		assig[j] = 0;
	}
	return false;
}

