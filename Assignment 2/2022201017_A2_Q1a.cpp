#include <iostream>
#include <bits/stdc++.h>
using namespace std;

struct Node{
    int val;
    struct Node *prev,*next;
};

class Bag{
public:
    int key,value;
    struct Node *node;

    Bag(){}

    Bag(int _key,int _value,struct Node *_node){
        key = _key;
        value = _value;
        node = _node;
    }
};

class Queue{
    struct Node *front,*back;
    int size;

public:
    Queue(){
        size = 0;
    }

    bool isEmpty(){
        return size == 0;
    }

    struct Node* enqueue(int _val){
        if(isEmpty()){
            size++;
            front = new Node;
            front->val = _val;
            front->next = NULL;
            back = front;
            return front;
        }
        struct Node *temp = new Node;
        temp->val = _val;
        temp->prev = back;
        temp->next = NULL;
        back->next = temp;
        back = temp;
        size++;
        return temp;
    }

    int dequeue(){
        if(!isEmpty()){
            struct Node *temp = front;
            int val = temp->val;
            if(size == 1){
                front = NULL;
                back = NULL;
            }
            else{
                front->next->prev = NULL;
                front = front->next;
            }
            size--;
            delete temp;
            return val;
        }
        return -1;
    }

    void removeNode(struct Node *node){
        struct Node *left = node->prev;
        struct Node *right = node->next;
        if(size == 1){
            front = NULL;
            back = NULL;
        }
        else{
            if(left == NULL){
                front = right;
                front->prev = NULL;
            }
            else if(right == NULL){
                back = left;
                back->next = NULL;
            }
            else{
                left->next = right;
                right->prev = left;
            }
        }
        delete node;
        size--;
    }
    
    void printQueue(){
        struct Node *ptr = front;
        if(size > 0){
            while(ptr != NULL){
                cout << ptr->val << " ";
                ptr = ptr->next;
            }
            cout << endl << size << "-------" << endl;
        }
        else{
            cout << "Empty Queue" << endl;
        }
    }
};

class LRUCache{
    int capacity,size;
    Queue queue;
    map<int,Bag> table;

public:
    LRUCache(int _capacity){
        capacity = _capacity;
        size = 0;        
    }

    bool isFull(){
        return size == capacity;
    }

    bool existInTable(int key){
        return table.find(key) != table.end();
    }

    bool existInQueue(int key){
        return existInTable(key) && table[key].value != -1;
    }

    void set(int key,int val){
        if(existInQueue(key)){
            struct Node *toremove = table[key].node;
            queue.removeNode(toremove);
            struct Node *toadd = queue.enqueue(key);
            table[key].value = val;
            table[key].node = toadd;
        }
        else{
            if(isFull()){
                int key_toremove = queue.dequeue();
                table[key_toremove].value = -1;
                table[key_toremove].node = NULL;
                size--;
            }
            struct Node *toadd = queue.enqueue(key);
            if(existInTable(key)){
                table[key].value = val;
                table[key].node = toadd;
            }
            else{
                Bag new_bag(key,val,toadd);
                table.insert(pair<int,Bag>(key,new_bag));
            }
            size++;
        }
    }

    int get(int key){
        if(existInQueue(key)){
            struct Node *toremove = table[key].node;
            queue.removeNode(toremove);
            struct Node *toadd = queue.enqueue(key);
            table[key].node = toadd;
            return table[key].value;
        }
        return -1;
    }

};


int main(){
    int cap,q;
    cin >> cap >> q;
    LRUCache cache(cap);
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
    // LRUCache cache(2);
    // cache.set(1,1);    
    // cache.set(2,2);
    // cout << cache.get(1) << endl;    
    // cache.set(3,3);
    // cout << cache.get(2) << endl;    
    // cache.set(4,4);
    // cout << cache.get(1) << endl;
    // cout << cache.get(3) << endl;
    // cout << cache.get(4) << endl;
    return 0;
}