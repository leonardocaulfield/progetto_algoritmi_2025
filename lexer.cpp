using namespace std;

//enum tipotoken { KEYWORDS, NUMBER, IDEN, PUNTEGGIATURA, PARENTESI, NUMERITABELLE };
/*
struct token{
    tipotoken TYPE;
    string valorestesso;
};
*/

bool carattere(unsigned char a){
    return isalpha(a);
}
bool numero_o_punto(unsigned char a){
    return isdigit(a) || a=='.';
}

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

vector<token> tokenizer(istream &in){
    vector<token> tokens;
    char c;

    while (in.get(c)) {
        unsigned char uc = static_cast<unsigned char>(c);

        // ignora spazi
        if (isspace(uc)) continue;

        // parentesi
        if (c=='(' || c=='[' || c=='{' || c==')' || c==']' || c=='}') {
            tokens.push_back({ PARENTESI, string(1,c) });
            continue;
        }

        // punteggiatura semplice
        if (c==';' || c==',' || c=='|') {
            tokens.push_back({ PUNTEGGIATURA, string(1,c) });
            continue;
        }

        // --- NUMERI ---
        if (isdigit(uc)) {
            // Caso speciale: NUMERITABELLE = "0." seguito da >=1 cifre
            if (c=='0' && in.peek()=='.') {
                string num = "0.";
                in.get(); // consuma il punto
                // deve esserci almeno una cifra dopo il punto
                if (in.peek()!=EOF && isdigit(static_cast<unsigned char>(in.peek()))) {
                    while (in.peek()!=EOF && isdigit(static_cast<unsigned char>(in.peek()))) {
                        num += static_cast<char>(in.get());
                    }
                    tokens.push_back({ NUMERITABELLE, num });
                    continue;
                } else {
                    // gestiamo "0." come 0 + '.' (punteggiatura)
                    tokens.push_back({ NUMBER, "0" });
                    tokens.push_back({ PUNTEGGIATURA, "." });
                    continue;
                }
            }

            // Intero normale: [1-9][0-9]* oppure singolo 0
            string num(1, c);
            while (in.peek()!=EOF && isdigit(static_cast<unsigned char>(in.peek()))) {
                num += static_cast<char>(in.get());
            }
            tokens.push_back({ NUMBER, num });
            continue;
        }

        // --- IDENTIFICATORI / KEYWORD ---
        if (carattere(uc)) {
            string parola(1, c);
            // usa peek per non consumare il char "di troppo"
            while (in.peek()!=EOF) {
                unsigned char p = static_cast<unsigned char>(in.peek());
                if (isalnum(p) || p=='_') {
                    parola += static_cast<char>(in.get());
                } else break;
            }

            if (!parola.empty() && (
                parola=="variable"   || parola=="table"   || parola=="probability" ||
                parola=="unknown"    || parola=="type"    || parola=="discrete"    ||
                parola=="network"
            )) {
                tokens.push_back({ KEYWORDS, parola });
            } else {
                tokens.push_back({ IDEN, parola });
            }
            continue;
        }

        // altri caratteri: ignora oppure aggiungi gestione se ti serve
    }

    return tokens;
}
