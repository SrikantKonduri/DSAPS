#include <iostream>
#include <bits/stdc++.h>

using namespace std;

struct Node{
    int val;
    struct Node *prev,*next;
};

class DLL{
public:
    Node *head,*tail;
    int size;
    
    DLL(){
        head = new Node;
        size = 0;
        head->val = -1;
        tail = new Node;
        tail->val = -1;
        head->next = tail;
        head->prev = NULL;
        tail->prev = head;
        tail->next = NULL;
    }

    bool isEmpty(){
        return head->next == tail;
    }

    struct Node* insert(int val){
        struct Node *new_node = new Node;
        new_node->val = val;
        new_node->next = head->next;
        new_node->prev = head;
        head->next->prev = new_node;
        head->next = new_node;
        size++;
        return new_node;
    }

    void removeNode(struct Node *node){
        if(isEmpty()){
            return ;
        }
        if(node != NULL){
            size--;
            Node *node_prev = node->prev;
            Node *node_next = node->next;
            node_prev->next = node_next;
            node_next->prev = node_prev;
            delete node;
        }
    }

    int removeFromEnd(){
        if(isEmpty()){
            return -1;
        }
        size--;
        struct Node *temp = tail->prev;
        temp->prev->next = tail;
        tail->prev = temp->prev;
        int to_return = temp->val;
        delete temp;
        return to_return;
    }

    void printList(){
        struct Node *cur = head;
        while(cur != NULL && cur->next != tail){
            cur = cur->next;
            cout << cur->val << " ";
        }
        cout << endl << "size: " << size << endl;
    }
};

class Block{
public:
    int key,value,freq_element;
    struct Node *node;

    Block(){}

    Block(int _key,int _value,int _freq_element,struct Node *_node){
        key = _key;
        value = _value;
        freq_element = _freq_element;
        node = _node;
    }

};


class LFUCache {
public:
    int capacity,size,min_freq;
    map<int,DLL> freq_table;
    map<int,Block> key_table;
    
    LFUCache(int _capacity) {
        DLL list;
        freq_table[1] = list;
        capacity = _capacity;
        min_freq = 1;
        size = 0;
    }
    
    
    bool isFull(){
        return capacity == size;
    }

    bool containsKey(int key){
        return key_table.find(key) != key_table.end() && key_table[key].value != -1;
    }

    bool containsList(int freq){
        return freq_table.find(freq) != freq_table.end();
    }

    bool containsInKeyTable(int key){
        return key_table.find(key) != key_table.end();
    }

    int get(int key) {
        if(capacity == 0){
            return -1;
        }
        if(containsKey(key)){
            int old_list_number = key_table[key].freq_element;
            freq_table[old_list_number].removeNode(key_table[key].node);
            if(min_freq == old_list_number && freq_table[old_list_number].isEmpty()){
                min_freq++;
            }
            key_table[key].freq_element = old_list_number + 1;
            if(containsList(old_list_number + 1)){
                DLL new_list = freq_table[old_list_number + 1];
                key_table[key].node = new_list.insert(key);
            }
            else{
                DLL new_list;
                key_table[key].node = new_list.insert(key);
                freq_table[old_list_number+1] = new_list;
            }
            return key_table[key].value;
        }
        return -1;
    }
    
    void set(int key, int val) {
        if(capacity == 0){
            return ;
        }
        if(containsKey(key)){
            int list_number = key_table[key].freq_element;
            DLL list = freq_table[list_number];
            list.removeNode(key_table[key].node);
            if(list.isEmpty() && list_number == min_freq){
                min_freq++;
            }
            int new_list_number = list_number + 1;
            key_table[key].freq_element = new_list_number;
            key_table[key].value = val;
            if(containsList(new_list_number)){
                DLL prom_list = freq_table[new_list_number];
                key_table[key].node  = prom_list.insert(key);
            }
            else{
                DLL new_list;
                key_table[key].node  = new_list.insert(key);
                freq_table[new_list_number] = new_list;
            }
        }
        else if(isFull()){
            int removed_key = freq_table[min_freq].removeFromEnd();
            key_table.erase(removed_key);
            min_freq = 1;
            struct Node *new_node = freq_table[min_freq].insert(key);
            if(containsInKeyTable(key)){
                Block old_block = key_table[key];
                old_block.freq_element = 1;
                old_block.key = key;
                old_block.value = val;
                old_block.node = new_node;
            }
            else{
                Block new_block(key,val,1,new_node);
                key_table[key] = new_block;
            }
        }
        else{
            size++;
            min_freq = 1;
            struct Node *new_node = freq_table[min_freq].insert(key);
            if(containsInKeyTable(key)){
                Block old_block = key_table[key];
                old_block.freq_element = 1;
                old_block.key = key;
                old_block.value = val;
                old_block.node = new_node;
            }
            else{
                Block new_block(key,val,1,new_node);
                key_table[key] = new_block;
            }
        }
    }
};

int main(){
    int cap,q;
    cin >> cap >> q;
    LFU cache(cap);
    while(q-- != 0){
        int op;
        cin >> op;
        if(op == 1){
            int key;
            cin >> key;
            cout << cache.get(key) << endl;
        }
        else if(op == 2){
            int key,val;
            cin >> key >> val;
            cache.set(key,val);
        }
    }
}