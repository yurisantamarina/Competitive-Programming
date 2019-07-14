#include <iostream>
#include <string>
#include <vector>

struct State {
	std::string* mysterious;
	std::string* s;
	std::string* t;
	std::vector<std::vector<int> >* nxt_s;
	std::vector<std::vector<int> >* nxt_t;
	State() {}
	State(std::string* mysterious, std::string* s, std::string* t,
		std::vector<std::vector<int> >* nxt_s, 
		std::vector<std::vector<int> >* nxt_t) {
		this->mysterious = mysterious;
		this->s = s;
		this->t = t;
		this->nxt_s = nxt_s;
		this->nxt_t = nxt_t;
	}
};

std::vector<int> PrefixFunction(const std::string& str) {
	std::vector<int> pref((int)str.size(), 0);
	int curr_pref = 0;
	for (int i = 1; i < (int)str.size(); i++) {
		curr_pref = pref[i - 1];
		while (str[curr_pref] != str[i] && curr_pref > 0) {
			curr_pref = pref[curr_pref - 1];
		}
		if (str[curr_pref] == str[i]) {
			curr_pref++;
		}
		pref[i] = curr_pref;
	}
	return pref;
}

std::vector<std::vector<int> > BuildNext(const std::string& str, 
	const std::vector<int>& pref) {
	std::vector<std::vector<int> > nxt((int)str.size() + 1, 
		std::vector<int>(26, 0));

	for (int i = 0; i < (int)str.size() + 1; i++) {
		for (int j = 0; j < 26; j++) {

			if (i == (int)str.size()) {
				nxt[i][j] = nxt[pref[i - 1]][j];
				continue;
			}

			char c = char(j + 'a');
			int curr_pref = i;
			while (str[curr_pref] != c && curr_pref > 0) {
				curr_pref = pref[curr_pref - 1];
			}
			if (str[curr_pref] == c) {
				curr_pref++;
			}
			nxt[i][j] = curr_pref;
		}
	}

	return nxt;
}

int GetNext(int pos, const std::vector<std::vector<int> >& nxt, int letter) {
	return nxt[pos][letter];
}

int RecoverCode(int pos_mysterious, int pos_s, int pos_t, const State& st, 
				auto& dp) {
	if (pos_mysterious == (st.mysterious)->size()) {
		return (pos_s == (st.s)->size()) - (pos_t == (st.t)->size());
	}

	if (dp[pos_mysterious][pos_s][pos_t] != -1000001) {
		return dp[pos_mysterious][pos_s][pos_t];
	}
	
	int answer = -1000000;
	int new_pos_s = 0, new_pos_t = 0;

	if ((*(st.mysterious))[pos_mysterious] == '*') {
		for (int j = 0; j < 26; j++) {
			answer = std::max(answer, RecoverCode(pos_mysterious + 1, 
												GetNext(pos_s, *st.nxt_s, j), GetNext(pos_t, *st.nxt_t, j), 
													st, dp));
		}
	} else {
		int j = int((*(st.mysterious))[pos_mysterious] - 'a');
		answer = std::max(answer, RecoverCode(pos_mysterious + 1, 
											GetNext(pos_s, *st.nxt_s, j), GetNext(pos_t, *st.nxt_t, j), 
												st, dp));
	}
	
	return dp[pos_mysterious][pos_s][pos_t] = answer + (pos_s == (st.s)->size()) - (pos_t == (st.t)->size());
}

int main() {
	std::ios_base::sync_with_stdio(0);
	std::cin.tie(0);
	std::string mysterious, s, t;
	std::cin >> mysterious;
	std::cin >> s;
	std::cin >> t;

	std::vector<int> pref_s = PrefixFunction(s);
	std::vector<int> pref_t = PrefixFunction(t);

	std::vector<std::vector<int> > nxt_s = BuildNext(s, pref_s);
	std::vector<std::vector<int> > nxt_t = BuildNext(t, pref_t);

	std::vector<std::vector<std::vector<int> > > dp;
	dp.resize((int)mysterious.size() + 1);
	for (int i = 0; i < (int)mysterious.size() + 1; i++) {
		dp[i].resize((int)s.size() + 1);
		for (int j = 0; j < (int)s.size() + 1; j++) {
			dp[i][j].resize((int)t.size() + 1, -1000001);
		}
	}

	int answer = RecoverCode(0, 0, 0, 
							State(&mysterious, &s, &t, &nxt_s, &nxt_t), dp);
	std::cout << answer << std::endl;

	return 0;
}