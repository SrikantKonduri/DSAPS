#include <iostream>
#include <fstream>
#include <chrono>
#include <bits/stdc++.h>

using namespace std;
using namespace std::chrono;

class Bag{
public:
    int fileno;
    long long int val;
    Bag(){}

    Bag(int _fileno,long long int _val){
        fileno = _fileno;
        val = _val;
    }

};

class Heap{
    int capacity,size,cur;
    Bag *priority_queue;
    bool *check;

public:
    Heap(){}
    Heap(int _capacity){
        capacity = _capacity;
        size = 0;
        cur = 0;
        priority_queue = new Bag[capacity];
        check = new bool[capacity];
        for(int i=0;i<capacity;i++){
            check[i] = false;
        }
    }

    int myCeil(int idx){
        if(idx % 2 == 1){
            return idx/2;
        }
        return idx/2-1;
    }

    void push(Bag element){
        priority_queue[cur] = element;
        check[cur] = true;
        cur++;
        size++;
        int child_idx = cur-1,parent_idx = myCeil(cur-1); 
        if(child_idx == 0){
            return ;
        }
        Bag child = priority_queue[child_idx];
        Bag parent = priority_queue[parent_idx];
        while(child.val < parent.val){
            priority_queue[child_idx] = parent;
            priority_queue[parent_idx] = child;
            if(parent_idx == 0){
                break;
            }
            child_idx = parent_idx;
            parent_idx = myCeil(child_idx);
            child = priority_queue[child_idx];
            parent = priority_queue[parent_idx];
        }
    }

    bool inRange(int idx){
        return idx >= 0 && idx < capacity;
    }

    bool hasChild(int idx){
        bool left = inRange(idx*2+1) && check[idx*2+1];
        bool right = inRange(idx*2+2) && check[idx*2+2];
        return left || right;
    }

    bool hasLeftChild(int idx){
        return inRange(idx*2+1) && check[idx*2+1];
    }

    bool hasRightChild(int idx){
        return inRange(idx*2+2) && check[idx*2+2];
    }

    void heapify(int idx){
        while(inRange(idx) && hasChild(idx)){
            Bag parent = priority_queue[idx];

            if(hasLeftChild(idx) && hasRightChild(idx)){
                Bag leftchild = priority_queue[idx*2+1];
                Bag rightchild = priority_queue[idx*2+2];
                if(leftchild.val < rightchild.val){
                    if(parent.val > leftchild.val){
                        Bag temp = leftchild;
                        priority_queue[2*idx+1] = parent;
                        priority_queue[idx] = temp;
                        idx = 2*idx + 1;
                        continue;
                    }
                }
                else{
                    if(parent.val > rightchild.val){
                        Bag temp = rightchild;
                        priority_queue[2*idx+2] = parent;
                        priority_queue[idx] = temp;
                        idx = 2*idx + 2;
                        continue;
                    }
                }
            }
            else if(hasLeftChild(idx)){
                Bag leftchild = priority_queue[idx*2+1];
                if(parent.val > leftchild.val){
                    Bag temp = leftchild;
                    priority_queue[2*idx+1] = parent;
                    priority_queue[idx] = temp;
                    idx = 2*idx + 1;
                    continue;
                }
            }
            else{
                Bag rightchild = priority_queue[idx*2+2];
                if(parent.val > rightchild.val){
                    Bag temp = rightchild;
                    priority_queue[2*idx+2] = parent;
                    priority_queue[idx] = temp;
                    idx = 2*idx + 2;
                }
                continue;
            }
            break;
        }
    }

    Bag pop(){
        if(size == 0){
            Bag b;
            cout << "Empty heap!" << endl;
            return b;
        }
        size--;
        Bag temp = priority_queue[cur-1];
        Bag to_return = temp;
        to_return = priority_queue[0];
        priority_queue[cur-1] = priority_queue[0];
        priority_queue[0] = temp;
        cur--;
        check[cur] = false;
        heapify(0);
        return to_return;
    }

    void printHeap(){
        for(int i=0;i<size;i++){
            cout << priority_queue[i].fileno << "," << priority_queue[i].val << endl;
        }
        cout << "----" << endl;
    }

    bool isEmpty(){
        // cout << "Size: " << size << endl;
        return size == 0;
    }
};

int insertIntoFiles(string src_file){
    ifstream input;
    input.open(src_file);
    if(input.fail()){
        cout << "Cannot open input file!" << endl;
        return 0;
    }
    int chunk = 10000000,filecount = 0;
    int written = 0;
    ofstream output;
    string temp_file = "";
    string str;
    vector<long long int> arr;
    long long int val;
    while(input >> val){
        if(!output.is_open()){
            temp_file = "./tempfiles/temp" + to_string(filecount) + ".txt";
            output.open(temp_file);
        }
        if(output.is_open() && written == chunk){
            sort(arr.begin(),arr.end());
            for(auto num : arr){
                output << num << " ";
            }
            arr.clear();
            output.close();
            filecount++;
            written = 0;
        }
        arr.push_back(val);
        written++;
    }
    if(written > 0){
        sort(arr.begin(),arr.end());
        for(auto num : arr){
            output << num << " ";
        }
        arr.clear();
        filecount++;
    }
    input.close();
    output.close();
    return filecount-1;
}

void insertAndSort(int filecount,string dtn_file){
    Heap min_heap(filecount+1);
    ifstream files[filecount+1];
    ofstream output;
    output.open(dtn_file);
    string file_name = "";
    for(int i=0;i<=filecount;i++){
        file_name = "./tempfiles/temp" + to_string(i) + ".txt";
        files[i].open(file_name);
        if(files[i].fail()){
            cout << "Failed to open temp" << i << ".txt file" << endl;
            return ;
        }
        long long int val;
        files[i] >> val;
        Bag b(i,val);
        min_heap.push(b);
    }
    while(!min_heap.isEmpty()){
        Bag top = min_heap.pop();
        output << top.val << "\n";
        string str;
        long long int val;
        if(files[top.fileno] >> val){
            Bag b(top.fileno,val);
            min_heap.push(b);
        }
        else{
            for(int i=0;i<=filecount;i++){
                if(i == top.fileno || !(files[i] >> val)){
                    continue;
                }
                Bag b(i,val);
                min_heap.push(b);
                break;
            }
        }
    }
    for(int i=0;i<=filecount;i++){
        files[i].close();
    }
    output.close();
}

int main(int argc,char** argv){
    auto start = high_resolution_clock::now();
    string src_file = argv[1];
    string dtn_file = argv[2];
    int filecount = insertIntoFiles(src_file);
    insertAndSort(filecount,dtn_file);
    auto stop = high_resolution_clock::now();
    auto duration = duration_cast<seconds>(stop - start);
    cout << "Number of integers in a temporary file: 10000000" << endl;
    cout << "Number of temporary files created: " << filecount + 1 << endl;
    cout << "Time taken by the program: " << duration.count() << " seconds" << endl;
    return 0;
}
