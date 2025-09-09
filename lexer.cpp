using namespace std;

enum tipotoken { KEYWORDS, NUMBER, IDEN, PUNTEGGIATURA, PARENTESI, NUMERITABELLE };

struct token{
    tipotoken TYPE;
    string valorestesso;
};

bool carattere(char a){
    return isalpha(a);
}

bool numero_o_punto(char a){
    return isdigit(a) || a=='.';
}


vector<token> tokenizer(istream &in){
	vector<token> tokens;
	char c;

	while (in.get(c)) {
		char uc = c;

		if (isspace(uc)) continue;

		if (c=='(' || c=='[' || c=='{' || c==')' || c==']' || c=='}') {
	    	tokens.push_back({ PARENTESI, string(1,c) });
	    	continue;
		}

		if (c==';' || c==',' || c=='|') {
			tokens.push_back({ PUNTEGGIATURA, string(1,c) });
			continue;
		}

		if (isdigit(uc)) {

			if (isdigit(c) && in.peek()=='.') {
			string num= string(1,c);
			num += in.get();

			if (in.peek()!=EOF && isdigit(in.peek())) {
				while (in.peek()!=EOF && isdigit(in.peek())) {
				num += in.get();
				}
				tokens.push_back({ NUMERITABELLE, num });
				continue;
			} else {
				tokens.push_back({ NUMBER, "0" });
				tokens.push_back({ PUNTEGGIATURA, "." });
				continue;
				}
			}

			string num(1, c);
			while (in.peek()!=EOF && isdigit(in.peek())) {
			num += in.get();
			}
			tokens.push_back({ NUMBER, num });
			continue;
		}

		if (carattere(uc)) {
			string parola(1, c);

			while (in.peek()!=EOF) {
				char p = in.peek();
				if (isalnum(p) || p=='_') {
				parola += in.get();
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
	}
	return tokens;
}
