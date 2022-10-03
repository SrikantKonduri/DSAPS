#include <iostream>
#include <cmath>

using namespace std;

class Bag{
public:
    int idx;
    long long val;
    Bag(){}

    Bag(int _idx,long long _val){
        idx = _idx;
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
            return (idx / 2 + 1) - 1;
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
        while(child.val > parent.val || (child.val == parent.val && child.idx < parent.idx)){
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
                if(leftchild.val > rightchild.val){
                    if(parent.val < leftchild.val || (parent.val == leftchild.val && leftchild.idx < parent.idx)){
                        Bag temp = leftchild;
                        priority_queue[2*idx+1] = parent;
                        priority_queue[idx] = temp;
                        idx = 2*idx + 1;
                        continue;
                    }
                }
                else{
                    if(parent.val < rightchild.val || (parent.val == rightchild.val && rightchild.idx < parent.idx)){
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
                if(parent.val < leftchild.val || (parent.val == leftchild.val && leftchild.idx < parent.idx)){
                    Bag temp = leftchild;
                    priority_queue[2*idx+1] = parent;
                    priority_queue[idx] = temp;
                    idx = 2*idx + 1;
                    continue;
                }
            }
            else{
                Bag rightchild = priority_queue[idx*2+2];
                if(parent.val < rightchild.val || (parent.val == rightchild.val && rightchild.idx < parent.idx)){
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
            cout << priority_queue[i].idx << "," << priority_queue[i].val << endl;
        }
        cout << "----" << endl;
    }
};

void heapify(int arr[], int N, int i)
{
    int largest = i,left = 2 * i + 1,right = 2 * i + 2;
 
    if (left < N && arr[left] > arr[largest]){
        largest = left;
    }
    if (right < N && arr[right] > arr[largest]){
        largest = right;
    }
    if (largest != i) {
        int temp = arr[i];
        arr[i] = arr[largest];
        arr[largest] = temp;
        heapify(arr, N, largest);
    }
}

void heapSort(int arr[], int N)
{
    for (int i = N / 2 - 1; i >= 0; i--){
        heapify(arr, N, i);
    }
    for (int i = N - 1; i >= 0; i--) {
        int temp = arr[0];
        arr[0] = arr[i];
        arr[i] = temp;
        heapify(arr, i, 0);
    }
}

long long* getKLargestSum(int arr[],int n,int k){
    long long *result = new long long[k];
    long long max_sum = 0;
    int idx = 0;
    for(int i=0;i<n;i++){
        if(arr[i] >= 0){
            max_sum += arr[i];
        }
        else{
            arr[i] *= -1;
        }
    }
    result[idx++] = max_sum;
    heapSort(arr,n);
    Heap heap(2001);
    Bag b(0,max_sum-arr[0]);
    heap.push(b);
    for(;idx<k;idx++){
        Bag temp = heap.pop();
        result[idx] = temp.val;
        if(temp.idx+1 < n){
            Bag b1(temp.idx+1,temp.val - arr[temp.idx+1] + arr[temp.idx]);
            Bag b2(temp.idx+1,temp.val - arr[temp.idx+1]);
            heap.push(b1);
            heap.push(b2);
        }
    }
    return result;
}   

int main(){
    int n,k;
    cin >> n >> k;
    int arr[n];
    for(int i=0;i<n;i++){
        cin >> arr[i];
    }
    long long *result = getKLargestSum(arr,n,k);
    for(int i=0;i<k;i++){
        cout << result[i]  << " ";
    }
    cout << endl;
    return 0;
}