//QUI METTO IL MAIN
#include <iostream>
#include <sstream>
#include <string>
#include <cstring>
#include <fstream>
#include <vector>
#include <cctype>
#include <unordered_map>
#include <map>
#include <thread>
#include <chrono>
#include "parsing.cpp"
#include "lexer.cpp"
#include "build.cpp"
#include "topologial_sort.cpp"
#include "prob_marginale.cpp"
#include "stampa_e_verifica.cpp"

using namespace std;

int main(){
    ifstream in("BIF/cancer.bif");
    if (!in) {
        cerr << "Errore: impossibile aprire il file\n";
        return 1;
    }

	vector<token> toks = tokenizer(in);
	vector<variabile> rete1 = parsingpt1(toks);
	stampa_la_rete(rete1);

	this_thread::sleep_for(chrono::seconds(1));

	vector<vector<int>> dag;
	dag = build(rete1,name_id,id_name);
	stampa(dag,id_name);

	this_thread::sleep_for(chrono::seconds(1));

	vector<int> topologico;
	topologico = topo_sort(dag);
	stampa_ordinamento_causale(topologico);

	this_thread::sleep_for(chrono::seconds(1));

	vector<dettagli> parents;
	parents = creo_parenti(rete1,name_id);
	marginale(rete1,topologico,parents);
}
