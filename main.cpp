#include <iostream>
#include <string>
#include <vector>

using namespace std;

/* failure function of Knuth-Morris-Pratt's Algorithm
 * failure function gives the lenght of the maximum prefix-suffix match
 * prefix must start from the first character of the string (index 0)
 * suffix start from the index 1 at least.
 * prefix and suffix both could finish at the end of the string
 * algo gives an array of size string
 * arr[0] = 0
 * for string abacab
 *     arr =  001012
 *  arr[3] means leanth of max suffix prefix match for the string abac
 *  prefix-suffix match of 4 characters string
 * */

/* O(m) time
 * i is the end index of the suffix
 * j is the end index of the prefix
 * since prefix must start from the first index size of match is always (j+1)
 */
vector<int> failureFunction(string p){
    vector<int> arr(p.size(), 0);

    int i = 1;
    int j = 0;
    int m = p.size();
    while (i < m){
        if (p.at(i) == p.at(j)){
            arr[i] = j + 1;
            i++;
            j++;
        }
        else if (j > 0){
            j = arr[j - 1];
        }else{
            arr[i] = 0;
            i++;
        }
    }
    return arr;
}

// recursive formula
void ff_rec(string& p, int i, int j, vector<int>& arr){
    if (i < p.size()){
        if (p[i] == p[j]){
            arr[i] = j + 1;
            i++;
            j++;
            ff_rec(p, i, j, arr);
        }else if (j > 0){
            j = arr[j - 1];
            ff_rec(p, i, j, arr);
        }else{
            arr[i] = 0;
            i++;
            ff_rec(p, i, j, arr);
        }
    }
}

/*
 * dynamic kind of algorithm
 * left to right index represents last index of the suffix
 * top to bottom index represents last index of the prefix
 * prefix size must be equal to match size again
 */
vector<int> f_dyn(string p){
    int n = p.size();

    vector< vector<int> > m (n, vector<int>(n));
    vector<int> f (n, 0);

    for (int j = 1; j < n; j++){
        if (p[j] == p[0]){
            m[0][j] = 1;
        }else{
            m[0][j] = 0;
        }
        f[j] = m[0][j];
    }

    for (int i = 1; i < n; ++i) {
        bool is_change = false;

        for (int j = i + 1; j < n; ++j) {
            if (p[i] == p[j]){
                m[i][j] = m[i-1][j-1] + 1;
            }else{
                m[i][j] = 0;
            }
            if (m[i][j] > f[j] && (i+1) == m[i][j]){
                f[j] = m[i][j];
                is_change = true;
            }
        }

        if (!is_change){
            break;
        }
    }

    return f;
}

int main(int argc, char *argv[])
{
    string s1 = "aacbaacaasbaccvvavcbbb", s2 = "abacab", s3 = "aacbaacaasba", s4 = "PATTERNWYZXRGARFIELDTHEBIGCATEDIZGTVWAVENHETBQRPWRNYZHUDHLESSQSXQLTYYNEWYBWXVPIJLGZSKRUUFYVDFODRVTJNWEPGDVMSYBGCNDJJRKATVNWGCGCGCGCGCGCGCGCGCGCGCGCGCGCGCGCGCGGCGCGCGGCGCGESOHSVZIQIJCSSPJCHMNGUUQHYHPLVHBTWTWTSBKAVJHMVFKEYUFXXUEHOIZQHQCAVHLFKVMZJFIRJFKFJASDFAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAASDVASFVADFVEENKICIYEZUBFBRJRDVYKNQAPXDQBMRACCAKYMWPXLKLKAAZDUWAWKAALCCCVGKNJDDSWPYGBYJNEMCVWUYBOOWFECWAFRVMUHUBPKVKZUZTGBJCQADWRCTJVVHLZQEORKJTOTJNXYRBCNAZRIPWCOFTJMSILJTSRHIGLULIHOKNXAOFGZIYPPNHLMFTMUBAFMOIFUNORXWIXMDPHQECZFEXZNPYDYBQTBPJTKRWTKBBRRDGZBWRTDYMMINUCJPICJIIOPPEPZAVHYUQJRAAXNRMWRLOIUUJVCBIRTVJOEURWFJKATXJDXDVANXQBUVTLOPLLDURZEUKREGSDVYBZDBBJLGUJNFYOSLASOWPAQNIGYDHWUBJXKKXXIEMIJHGHTXOUNDIJBPBZNAFNXVPUEPCAZDACDIMUGPUAVBKBGIWLDFGZFYYPGEUYLUVOCPNRQZYGBOSTGLQWBSWCNATXZCVCOVVHCTSBHEBWFRPMFWCZJQERMKWCYYMYZJDKEHKKRHFWEIPMIYRLHBQUCSUXWEMEANNFQZBFSDBXNVTZGJZRZKQYJFEAFQLWPOKRIZPQCDCLFCRUHXZTORHJNJHTWVLANHEREITCOMESWKGFPDXUPMHDEZTEVSQJCUMDDKKACFNNHPKXZDHJMWSJFWBQRLKCRPFNFJSIBXWXABLEXFMOVMZTKDAVHOIQPRLUKDSMQGKPDVXFAFANLNONXLHCZTHMQZNTJKEVXRHQGSZDZJPLKNADYFGKTFORQKJAEYZUUUHBNEAGNUVJROPUZGMPRNWPCOVCBYLRTISCWTYKONNRNZOTRTGPNMEJVPQTESMYYGDWYUMCMISDUKROQPASYAYKONXTRVDKHGSWKAOQKRKLDMBRSAPBUSSTOPMWYYKJPMPQNFAFXTTUKPGMKBUZWKHHWCFHSXZPJQVTNFIEKBLMDKHLTCCCBWBZCYQMTVJEAUDHAIXMDOCPKMLYKHZKZRCAOJDNFUMKRHXDLPDWDTVZFTUZOFFJDOHEVFNFJMDFXGRIQFFPGAPQIVMVRNPLSARUIFJMGYXYHWZCJZDPXVYQOQSWKTJFTIURQDSPYMKKHKRQQWLQXSXCIRUIIHBRFOTSHAECKJOZPTXNQNATAVKJMNNDDNQKAQXCBYODFJFXEWGKFMDMEQEFEKXARNEBWQKYONKLIPRACCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCAAAACCCCCCCCCCCCCCCCCCCCC";

    vector<int> v1 = failureFunction(s4);
    vector<int> v2 = f_dyn(s4);

    vector<int> v3 (s4.size(), 0);
    ff_rec(s4, 1, 0, v3);

    cout << "\n [";
    for (int i = 0; i < v1.size(); i++){
        if (v1[i] != v2[i] || v2[i] != v3[i] || v1[i] != v3[i]){
            cout << "FAIIIIIIIIIIIIIIIIIIIIL";
            return -1;
        }

        cout << " " << v1[i] << ", ";
    }
    cout << "]\n";

    cout << "\n [";
    for (int i = 0; i < v2.size(); i++){
        cout << " " << v2[i] << ", ";
    }
    cout << "]\n";

    cout << "\n [";
    for (int i = 0; i < v3.size(); i++){
        cout << " " << v3[i] << ", ";
    }
    cout << "]\n";

    return 0;
}
