#include<iostream>


using namespace std;

template <class TYPE>class Dequeue{
    TYPE *arr;
    int sze,first,last,capacity;


public:
    void dequeue(){ 
        capacity = 2;
        arr = new TYPE[capacity];
        first = 0;
        last = 1;
        sze=0;
        if(arr == NULL){
            cout << "Cannot allocate Memory!" << endl;
        }
    }

    void dequeue(int n,TYPE t){
        capacity = 2 * n;
        arr = new TYPE[capacity];
        first = 0;
        last = capacity - 1;
        sze = n;
        if(arr != NULL){
            for(int i=0;i<n;i++){
                first++;
                arr[i] = t;
            }
        }
        else{
            cout << "Cannot allocate Memory!" << endl;
        }
    }

    void resize(){
        TYPE *new_arr = new TYPE[capacity*2];
        int i=0,f=first,l=last;
        while( (last + 1) % capacity != first){
            last = (last + 1) % capacity;
            new_arr[i++] = arr[last];
        }
        capacity = 2 * capacity;
        first = i;
        last = capacity - 1;
        delete arr;
        arr = new_arr;
    }

    void push_back(TYPE t){
        if(first == last){
            resize();
        }
        sze++;
        arr[last] = t;
        if(last == 0){
            last = capacity - 1;
        }
        else{
            last--;
        }
    }

    void push_front(TYPE t){
        if(first == last){
            resize();
        }
        sze++;
        arr[first] = t;
        first=(first+1)%capacity;
    }

    void pop_back(){
        if((last + 1) % capacity == first){
            // cout << "No elements exist to pop!" << endl;
        }
        else{
            sze--;
            last=(last+1) % capacity;
        }
    }

    void pop_front(){
        if((last + 1) % capacity == first){
            // cout << "No Elements exist to pop!" << endl;
        }
        else{
            sze--;
            if(first == 0){
                first = capacity - 1;
            }
            else{
                first--;
            }
        }
    }

    TYPE front(){
        if((last + 1) % capacity == first){
            // cout << "No elements exist to access!!" << endl;
            return TYPE();
        }
        if(first == 0){
            return arr[capacity - 1];
        }
        return arr[first-1];
    }

    TYPE back(){
        if((last + 1) % capacity == first){
            // cout << "No elements to access!!" << endl;
            return TYPE();
        }
        return arr[(last + 1) % capacity];
    }

    TYPE operator [](int index){
        if(sze == 0 || index >= sze){
            // cout << "No elements exist to access!" << endl;
            return TYPE();
        }
        // else if(index >= sze){
        //     cout << index << ": Index out of Bounds exception!" << endl;
        //     return NULL;
        // }
        int temp = sze - index;
        return arr[(last + temp) % capacity];
    }

    bool empty(){
        return sze == 0;
    }    

    int size(){
        return sze;
    }

    void clear(){
        first = 0;
        last = capacity - 1;
        sze = 0;
    }

    void resize(int n,TYPE data){
        if(n > sze){
            int to_add = n - sze;
            while(to_add-- != 0){
                push_back(data);
            }
        }
        else{
            int to_remove = sze - n;
            while(to_remove-- != 0){
                pop_back();
            }
        }
    }

    void display(){
        if((last + 1) % capacity == first){
            cout << "No elements to display!" << endl;
        }
        else{
            int f = first-1;
            if(first == 0){
                f = capacity-1;
            }
            while(f != last){
                cout << arr[f] << " ";
                if(f == 0){
                    f = capacity - 1;
                }
                else{
                    f--;
                }
            }
            cout << endl;
        }

    }

};  

int main(){
    Dequeue<int> DQ;
    int val;
    int choice,flag = 1,n;

    while(flag){
        cout << "------------\n";
        cout << "Choice: ";
        cin >> choice;
        switch(choice){
            case 0:
                flag = 0;
                break;
            case 1:
                DQ.dequeue();
                break;
            case 2:
                cin >> n >> val;
                DQ.dequeue(n,val);
                break;
            case 3:
                cin >> val;
                DQ.push_back(val);
                break;
            case 4:
                DQ.pop_back();
                break;
            case 5:
                cin >> val;
                DQ.push_front(val);
                break;
            case 6:
                DQ.pop_front();
                break;
            case 7:
                cout << DQ.front() << endl;
                break;
            case 8:
                cout << DQ.back() << endl;
                break;
            case 9:
                cout << ((DQ.empty()) ? "true" : "false") << endl;
                break;
            case 10:
                cout << DQ.size() << endl;
                break;
            case 11:
                cin >> n >> val;
                DQ.resize(n, val);
                break;
            case 12:
                DQ.clear();
                break;
            case 13:
                cin >> n;
                cout << DQ[n] << endl;
                break;
            case 14:
                DQ.display();
                break;
            default:
                cout << "Enter correct choice!" << endl;
        }
    }

    return 0;
}