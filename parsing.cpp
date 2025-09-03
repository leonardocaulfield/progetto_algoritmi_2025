using namespace std;

enum tipotoken { KEYWORDS, NUMBER, IDEN, PUNTEGGIATURA, PARENTESI, NUMERITABELLE };

struct token{
    tipotoken TYPE;
    string valorestesso;
};

struct variabile{
	string name;
	vector<string> genitori;
	vector<string> tipi;
	vector<vector<double>> cpt;
};

vector<variabile> rete;
unordered_map<string,int> name_id;

//bool iskey(tipotoken tp,string valorestes){if(tp == KEYWORDS  &&  valo

void op_variabile(int *ind_tok,int *ind_map,const vector<token>& tok,unordered_map<string,int>& map){

	rete.emplace_back();
	rete[(*ind_map)].name = tok[(*ind_tok)].valorestesso;
	map[tok[(*ind_tok)].valorestesso] = int {(*ind_map)};
//	while(tok[(*ind_tok)].TYPE != NUMBER){(*ind_tok)++;}
//	rete[(*ind_map)].tipi.resize(stoi(tok[(*ind_tok)].valorestesso));

	(*ind_tok)++;
	int r=0;
	while(((*ind_tok)<tok.size()) && tok[(*ind_tok)].valorestesso != ";"){
		if(tok[(*ind_tok)].TYPE == IDEN){
//			rete[(*ind_map)].tipi.resize(r+1);
			rete[(*ind_map)].tipi.push_back(tok[(*ind_tok)].valorestesso);
		}(*ind_tok)++;
	}
	(*ind_map)++;
}

void op_probabilita(int *ind_tok,int *ind_map,const vector<token>& tok,unordered_map<string,int>& map){

	(*ind_map) = map[tok[(*ind_tok)].valorestesso];

	int r=0;

	(*ind_tok)++;
	if(tok[(*ind_tok)].valorestesso == "|"){
		while(((*ind_tok)<tok.size()) && tok[(*ind_tok)].valorestesso != ")"){
			if(tok[(*ind_tok)].TYPE == IDEN){
//				rete[(*ind_map)].genitori.resize(r+1);
				rete[(*ind_map)].genitori.emplace_back(tok[(*ind_tok)].valorestesso);
			}(*ind_tok)++;
			r++;
		}
	}
	int k=0;
	r=0;
	while(((*ind_tok)<tok.size()) && tok[(*ind_tok)].valorestesso != "}"){
		if(tok[(*ind_tok)].TYPE == NUMERITABELLE){
			rete[(*ind_map)].cpt.resize(r+1);
			rete[(*ind_map)].cpt[k].push_back(stod(tok[(*ind_tok)].valorestesso));
		}
		if(tok[(*ind_tok)].valorestesso == ";"){
			r++;
			k++;
		}
		(*ind_tok)++;
	}
}

vector<variabile> parsingpt1(const vector<token>& tok){
	int i=0,k=0;
	while(i<tok.size()){
		if(tok[i].valorestesso == "variable"){
			i++;
			op_variabile(&i,&k,tok,name_id);
		}
		if(tok[i].valorestesso == "probability"){
			i+=2;
			op_probabilita(&i,&k,tok,name_id);
		}
		i++;
	}
	return rete;
}
