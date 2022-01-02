#include "FileSystem.h"

int p = 101;

class HashTable{
public:
    unsigned int a;
    unsigned int b;
    unsigned int size;
    Folder* folders;
};

int mod = 137;

int HashingString(const string& _string){
    int res = 0;
    int pow = 1, p = 31;
    for (int i = 0; i < _string.size(); i++){
        res += ((int) _string[i] * pow) % mod;
        pow *= (pow * p) % mod;
    }
    return res;
}

int UniversalHashing(const string& _string, int a, int b, int m){
    int hash = HashingString(_string);
    return ((a * hash + b) % p) % m;
}

void PerfectHashing(HashTable* PerfectHash, vector<Folder>& folders){
    vector<vector<Folder>> _HashTable;
    _HashTable.resize(folders.size());
    for (int i = 0; i < folders.size(); i++){
        int hash = UniversalHashing(folders[i].GetFolderName(), 1, 41, folders.size());
        _HashTable[hash].push_back(folders[i]);
    }
    for (int i = 0; i < folders.size(); i++){
        if (!_HashTable[i].empty()){
            PerfectHash[i].folders = new Folder[_HashTable[i].size() * _HashTable[i].size()];
            PerfectHash[i].size = _HashTable[i].size() * _HashTable[i].size();

            if (_HashTable[i].size() == 1){
                PerfectHash[i].folders[0] = _HashTable[i][0];
                PerfectHash[i].a = PerfectHash[i].b = 0;
                continue;
            }
            bool perfectHashed = false, sameHash = false;
            int* usedHash = new int[_HashTable[i].size() * _HashTable[i].size()];
            for (int j = 0; j < _HashTable[i].size() * _HashTable[i].size(); j++)
                usedHash[i] = 0;
            PerfectHash[i].b = PerfectHash[i].a = 1;
            while (!perfectHashed){
                for (int j = 0; j < _HashTable[i].size(); j++) {
                    int hash = UniversalHashing(_HashTable[i][j].GetFolderName(),
                                                PerfectHash[i].a,
                                                PerfectHash[i].b,
                                                PerfectHash[i].size);
                    if (usedHash[hash] != 0)
                        sameHash = true;
                }
                if (sameHash) {
                    sameHash = false;
                    if (PerfectHash[i].a == p - 1) {
                        PerfectHash[i].a = 1;
                        PerfectHash[i].b++;
                    } else {
                        PerfectHash[i].a++;
                    }
                    continue;
                } else {
                    perfectHashed = true;
                    for (int j = 0; j < _HashTable[i].size(); j++) {
                        int hash = UniversalHashing(_HashTable[i][j].GetFolderName(),
                                                    PerfectHash[i].a,
                                                    PerfectHash[i].b,
                                                    PerfectHash[i].size);
                        PerfectHash[i].folders[hash] = _HashTable[i][j];
                    }
                }
            }
        }
    }
}

int main() {
    int m;
    cout << "Input number of values: ";
    cin >> m;
    cout << "\n";
    vector<Folder> folders;
    folders = Folder::FoldersGenerator(m);
    HashTable* PerfectHashTable = new HashTable[m];
    for (int i = 0; i < m; i++) {
        PerfectHashTable[i].a = PerfectHashTable[i].b = PerfectHashTable[i].size = 0;
        PerfectHashTable[i].folders = nullptr;
    }
    PerfectHashing(PerfectHashTable, folders);
    for (int i = 0; i < folders.size(); i++){
        cout << i << ": ";
        if (PerfectHashTable[i].folders == nullptr)
            cout << "\n";
        else{
            for (int j = 0; j < PerfectHashTable[i].size; j++)
                cout << " {" << PerfectHashTable[i].folders[j].GetFolderName() << "} ";
            cout << '\n';
        }
    }

    delete [] PerfectHashTable;

    return 0;
}