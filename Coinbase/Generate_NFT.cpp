#include <bits/stdc++.h>
using namespace std;

struct TraitValue {
    string name;
    double weight;
};

struct Trait {
    string name;
    vector<TraitValue> values;
    vector<double> cdf;
};

class NFTGenerator {
private:
    vector<Trait> traits;
    vector<double> randoms;
    int randIdx = 0;

    double nextRandom() {
        if (randIdx >= randoms.size())
            throw runtime_error("Ran out of random numbers");
        return randoms[randIdx++];
    }

    void buildCDF(Trait &trait) {
        double sum = 0.0;
        for (auto &v : trait.values) sum += v.weight;

        double cumulative = 0.0;
        for (auto &v : trait.values) {
            cumulative += v.weight / sum;
            trait.cdf.push_back(cumulative);
        }
    }

    string selectValue(const Trait &trait) {
        double r = nextRandom();
        auto it = lower_bound(trait.cdf.begin(), trait.cdf.end(), r);
        int idx = it - trait.cdf.begin();
        return trait.values[idx].name;
    }

public:
    NFTGenerator(const vector<Trait> &traits,
                 const vector<double> &randoms)
        : traits(traits), randoms(randoms) {}

    vector<map<string, string>> generate(int n) {
        set<string> seen;
        vector<map<string, string>> result;

        long long maxComb = 1;
        for (auto &t : traits)
            maxComb *= t.values.size();

        int attempts = 0;
        int maxAttempts = min((long long)randoms.size(), maxComb * 2);

        while (result.size() < n && attempts < maxAttempts) {
            attempts++;
            map<string, string> nft;
            string signature;

            try {
                for (auto &trait : traits) {
                    string val = selectValue(trait);
                    nft[trait.name] = val;
                    signature += trait.name + ":" + val + "|";
                }
            } catch (...) {
                break;
            }

            if (seen.insert(signature).second) {
                result.push_back(nft);
            }
        }

        return result;
    }
};

vector<map<string, string>>
generate_nfts(
    unordered_map<string, vector<pair<string, int>>> &configTraits,
    int n,
    vector<double> &random_numbers
) {
    vector<Trait> traits;

    for (auto &entry : configTraits) {
        Trait t;
        t.name = entry.first;

        for (auto &p : entry.second) {
            t.values.push_back({p.first, (double)p.second});
        }

        traits.push_back(t);
    }

    // Ensure deterministic order
    sort(traits.begin(), traits.end(),
         [](const Trait &a, const Trait &b) {
             return a.name < b.name;
         });

    for (auto &t : traits) {
        NFTGenerator dummy({}, {});
        double sum = 0;
        for (auto &v : t.values) sum += v.weight;
        double c = 0;
        for (auto &v : t.values) {
            c += v.weight / sum;
            t.cdf.push_back(c);
        }
    }

    NFTGenerator generator(traits, random_numbers);
    return generator.generate(n);
};

int main() {
    unordered_map<string, vector<pair<string, int>>> configTraits = {
        {"color", {{"red", 160}, {"blue", 12}}},
        {"background", {{"sky", 54}, {"forest", 20}}}
    };

    int n = 7;

    vector<double> random_numbers = {
        0.10, 0.20,   // NFT 1
        0.95, 0.90,   // NFT 2
        0.10, 0.90,   // NFT 3 (may collide or not)
        0.80, 0.10,    // fallback if needed
        0.995, 0.90
    };

    auto nfts = generate_nfts(configTraits, n, random_numbers);

    for (int i = 0; i < nfts.size(); i++) {
        cout << "NFT " << i + 1 << ": ";
        for (auto &kv : nfts[i]) {
            cout << kv.first << "=" << kv.second << " ";
        }
        cout << endl;
    }

    return 0;
}
