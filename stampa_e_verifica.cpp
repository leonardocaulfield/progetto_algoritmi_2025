//FUNZIONI CHE MI STAMPANO COSE CHE ALLA FINE NON SI VEDONO MA MI ASIUTANO A CAPIRE PASSO PASSO COSA è GIUSTO E COSA NO
using namespace std;

const char* token_name(tipotoken t) {
    switch (t) {
    case KEYWORDS:      return "KEYWORD";
    case NUMBER:        return "NUMBER";
    case IDEN:          return "IDEN";
    case PUNTEGGIATURA: return "PUNTEGGIATURA";
    case PARENTESI:     return "PARENTESI";
    case NUMERITABELLE: return "NUMERITABELLE";
    }
    return "?";
}

void stampa_i_token(const vector<token>& toks){
    for (const auto& t : toks) {
        cout << token_name(t.TYPE) << " : " << t.valorestesso << '\n';
    }
}

void stampa_la_rete(const vector<variabile>& rete1){
    // STAMPA DI VERIFICA
    for (const auto& var : rete1) {
        cout << "Variabile: " << var.name << "\n";

        cout << "  Tipi: ";
        for (const auto& t : var.tipi) {
            cout << t << " ";
        }
        cout << "\n";

        cout << "  Genitori: ";
        for (const auto& g : var.genitori) {
            cout << g << " ";
        }
        cout << "\n";

        cout << "  CPT: \n";
        for (size_t i=0; i<var.cpt.size(); i++) {
            cout << "    Riga " << i << ": ";
            for (double val : var.cpt[i]) {
                cout << val << " ";
            }
            cout << "\n";
        }
        cout << "-----------------------------\n";
    }
}

void stampa_ordinamento_causale(const vector<int>& vet){

	cout << endl;
	cout << "[";

	for(auto i : vet){
		cout << i << " , ";
	}

	cout << "]";
	cout << endl;

}
