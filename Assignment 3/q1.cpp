#include <iostream>
#include <bits/stdc++.h>

using namespace std;

struct Node{
    struct Node *alphabets[27];
    bool endofword;
    Node(){
        for(int i=0;i<27;i++){
            alphabets[0] = NULL;
        }
        endofword = false;
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

    bool spellcheck(string input){
        int length = input.length();
        struct Node *cur = root;
        for(int i=0;i<length;i++){
            char ch = input[i];
            if(cur->alphabets[ch-96] == NULL){
                return false;
            }
            cur = cur->alphabets[ch-96];
        }
        return cur->endofword;
    }

    void getWords(struct Node *ptr,string word,vector<string> &result){
        if(ptr != NULL){
            if(ptr->endofword){
                result.push_back(word);
            }
            for(int i=1;i<=26;i++){
                if(ptr->alphabets[i] != NULL){
                    word.push_back(i+96);
                    getWords(ptr->alphabets[i],word,result);
                    word.pop_back();
                }
            }

        }
    }

    void autocomplete(string input,vector<string> &result){
        int length = input.length();
        struct Node *cur = root;
        for(int i=0;i<length;i++){
            cur = cur->alphabets[input[i]-96];
            if(cur == NULL){
                break;
            }
        }
        if(cur != NULL){
            getWords(cur,input,result);
        }
    }

    int findEditDistance(string word,string target,int i,int j,vector<vector<int> > &dp){
        if(i < 0){
            return j+1;
        }
        if(j < 0){
            return i+1;
        }
        if(dp[i][j] != -1){ 
            return dp[i][j];
        }
        if(word[i] == target[j]){
            dp[i][j] = findEditDistance(word,target,i-1,j-1,dp);
            return dp[i][j];
        }
        int insert = findEditDistance(word,target,i,j-1,dp);
        int replace = findEditDistance(word,target,i-1,j-1,dp);
        int delete_char = findEditDistance(word,target,i-1,j,dp);
        dp[i][j] = min(min(insert,replace),delete_char) + 1;
        return dp[i][j];
    }

    void autocorrect(struct Node *root,string word,string target,vector<string> &result){
        if(root != NULL){
            if(root->endofword){
                int word_len = word.length();
                int target_len = target.length();
                if(abs(word_len-target_len) > 3){
                    return;
                }
                vector<vector<int> > dp(word_len,vector<int>(target_len,-1));
                int distance = findEditDistance(word,target,word_len-1,target_len-1,dp);
                if(distance <= 3){
                    result.push_back(word);
                }
            }
            for(int i=1;i<=26;i++){
                if(root->alphabets[i] != NULL){
                    char ch = i + 96;
                    word.push_back(ch);
                    autocorrect(root->alphabets[i],word,target,result);
                    word.pop_back();
                }
            }
        }
    }

    void print(struct Node *root,string word){
        if(root != NULL){
            if(root->endofword){
                cout << word << endl;
            }
            for(int i=1;i<=26;i++){
                if(root->alphabets[i] != NULL){
                    char ch = i + 96;
                    word.push_back(ch);
                    print(root->alphabets[i],word);
                    word.pop_back();
                }
            }
        }
    }

};
// consider filters filers entitled tilers litter dames filling grasses fitter

void printResultVector(vector<string> &result){
    cout << result.size() << endl;
    for(string str : result){
        cout << str << endl;
    }
}

int main(){
    Trie mytrie;
    int n,q;
    cin >> n >> q;
    while(n-- != 0){
        string str;
        cin >> str;
        mytrie.insert(str);
    }
    while(q-- != 0){
        int operation;
        cin >> operation;
        string target;
        cin >> target;
        vector<string> result;
        switch(operation){
            case 1:
                cout << mytrie.spellcheck(target) << endl;
                break;
            case 2:
                mytrie.autocomplete(target,result);
                printResultVector(result);
                break;
            case 3:
                mytrie.autocorrect(mytrie.root,"",target,result);
                printResultVector(result);
                break;
        }
    }
}