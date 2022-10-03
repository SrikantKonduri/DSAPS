#include <iostream>

using namespace std;

char **grid;
int match_count = 0;
int result_idx = 0;
string result[100000];

struct Node{
    struct Node *alphabets[27];
    bool endofword,present;
    Node(){
        for(int i=0;i<27;i++){
            alphabets[i] = NULL;
        }
        endofword = false;
        present = false;
    }

};

class Trie{
public:
    struct Node *root;

    Trie(){
        root = new Node;
    }

    void insert(string str){
        int length = str.length();
        struct Node *cur = root;
        for(int i=0;i<length;i++){
            char ch = str[i];
            if(cur->alphabets[ch-96] != NULL){
                cur = cur->alphabets[ch-96];
            }
            else{
                struct Node *new_node = new Node();
                cur->alphabets[ch-96] = new_node;
                cur = new_node;
            }
        }
        cur->endofword = true;
    }

    void print(struct Node *master,string word){
        if(master != NULL){
            if(master->endofword){
                cout << word << endl;
            }
            for(int i=1;i<=26;i++){
                if(master->alphabets[i] != NULL){
                    char ch = i + 96;
                    word.push_back(ch);
                    print(master->alphabets[i],word);
                    word.pop_back();
                }
            }
        }
    }

    void getResult(struct Node *master,string word){
        if(master != NULL){
            if(master->present){
                result[result_idx] = word;
                result_idx++;
            }
            for(int i=1;i<=26;i++){
                if(master->alphabets[i] != NULL){
                    char ch = i + 96;
                    word.push_back(ch);
                    getResult(master->alphabets[i],word);
                    word.pop_back();
                }
            }
        }
    }
};

bool inRange(int i,int j,int m,int n){
    return i >= 0 && i < m && j>=0 && j < n;
}

void solve(struct Node *cur,int i,int j,int m,int n,string word){
    char ch = grid[i][j];
    if(cur->endofword){
        cur->present = true;
        match_count++;
        cur->endofword = false;
    }
    if(grid[i][j] == '$' || cur->alphabets[ch-96] == NULL){
        return ;
    }
    if(cur->alphabets[ch-96] != NULL){
        grid[i][j] = '$';
        word.push_back(ch);
        cur = cur->alphabets[ch-96];
        if(inRange(i-1,j,m,n)){
            solve(cur,i-1,j,m,n,word);
        }
        if(inRange(i,j+1,m,n)){
            solve(cur,i,j+1,m,n,word);
        }
        if(inRange(i+1,j,m,n)){
            solve(cur,i+1,j,m,n,word);
        }
        if(inRange(i,j-1,m,n)){
            solve(cur,i,j-1,m,n,word);
        }
        if(cur->endofword){
            cur->endofword = false;
            match_count++;
            cur->present = true;
        }
        grid[i][j] = ch; 
    }
}

int main(){
    int m,n;
    cin >> m >> n;
    Trie mytrie;
    grid = new char*[m];
    for(int i=0;i<m;i++){
        grid[i] = new char[n];
        for(int j=0;j<n;j++){
            cin >> grid[i][j];
        }
    }
    int x;
    cin >> x;
    while(x-- != 0){
        string str;
        cin >> str;
        mytrie.insert(str);
    }
    for(int i=0;i<m;i++){
        for(int j=0;j<n;j++){
            solve(mytrie.root,i,j,m,n,"");
        }
    }
    mytrie.getResult(mytrie.root,"");
    cout << match_count << endl;
    for(int i=0;i<match_count;i++){
        cout << result[i] << endl;
    }
}