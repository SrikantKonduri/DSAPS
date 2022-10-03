#include <iostream>

using namespace std;

template <class TYPE>
class Node{
public:
    int row,col;
    TYPE data;
    Node *next;
};

template <typename TYPE>
void printList(Node<TYPE> *node){
    while(node != NULL){
        cout << node->row << "," << node->col << "," << node->data << endl;
        node = node->next;
    }
    cout << "-----------" << endl;
}

template <typename TYPE>
void printMatrix(Node<TYPE> *matrix,int m,int n){
    Node<TYPE> *cur = matrix;
    for(int i=0;i<m;i++){
        for(int j=0;j<n;j++){
            if(cur != NULL && i == cur->row && j == cur->col){
                cout << cur->data << " ";
                cur = cur->next;
            }
            else{
                cout << "0 ";
            }
        }
        cout << endl;
    }
}

template <typename TYPE>
void addition(Node<TYPE> *m1,Node<TYPE> *m2,int m,int n){
    Node<TYPE> *result = NULL;
    Node<TYPE> *ptr = NULL;
    while(m1 != NULL && m2 != NULL){
        Node<TYPE> *new_node = new Node<TYPE>;
        if(m1->row == m2->row){
            if(m1->col == m2->col){
                TYPE sum = m1->data + m2->data;
                new_node->row = m1->row;
                new_node->col = m1->col;
                new_node->data = sum;
                m1 = m1->next;
                m2 = m2->next;
            }
            else if(m1->col < m2->col){
                new_node->row = m1->row;
                new_node->col = m1->col;
                new_node->data = m1->data;
                m1 = m1->next;
            }
            else {
                new_node->row = m2->row;
                new_node->col = m2->col;
                new_node->data = m2->data;
                m2 = m2->next;
            }
        }
        else if(m1->row < m2->row){
            new_node->row = m1->row;
            new_node->col = m1->col;
            new_node->data = m1->data;
            m1 = m1->next;
        }
        else{
            new_node->row = m2->row;
            new_node->col = m2->col;
            new_node->data = m2->data;
            m2 = m2->next;
        }
        if(result == NULL){
            result = new_node;
            ptr = new_node;
        }
        else{
            ptr->next = new_node;
            ptr = ptr->next;
        }
    }
    while(m1 != NULL){
        Node<TYPE> *new_node = new Node<TYPE>;
        new_node->row = m1->row;
        new_node->col = m1->col;
        new_node->data = m1->data;
        m1 = m1->next;
        if(result == NULL){
            result = new_node;
            ptr = new_node;
        }
        else{
            ptr->next = new_node;
            ptr = ptr->next;
        }
    }
    while(m2 != NULL){
        Node<TYPE> *new_node = new Node<TYPE>;
        new_node->row = m2->row;
        new_node->col = m2->col;
        new_node->data = m2->data;
        m2 = m2->next;
        if(result == NULL){
            result = new_node;
            ptr = new_node;
        }
        else{
            ptr->next = new_node;
            ptr = ptr->next;
        }
    }
    // printList(result);
    printMatrix(result,m,n);

}

template <typename TYPE>
Node<TYPE>* takeInput(int m,int n){
    Node<TYPE> *matrix = NULL,*ptr = NULL;
    for(int i=0;i<m;i++){
        for(int j=0;j<n;j++){
            TYPE val;
            cin >> val;
            if(val != 0){
                Node<TYPE> *new_node = new Node<TYPE>;
                new_node->data = val;
                new_node->row = i;
                new_node->col = j;
                if(matrix == NULL){
                    matrix = new_node;
                    ptr = new_node;
                }
                else{
                    ptr->next = new_node;
                    ptr = ptr->next;
                }
            }
        }
    }
    return matrix;
}

template <typename TYPE>
void sortList(Node<TYPE> *head)
{
    Node<TYPE> *i = head;
    while(i != NULL){
        Node<TYPE> *j = i->next;
        Node<TYPE> *temp = i;
        while(j != NULL){
            if((temp->row > j->row) || (temp->row == j->row && temp->col > j->col)){
                temp = j;
            }
            j = j->next;
        }
        int t = i->row;
        i->row = temp->row;
        temp->row = t;
        
        t = i->col;
        i->col = temp->col;
        temp->col = t;

        TYPE t_data = i->data;
        i->data = temp->data;
        temp->data = t_data;

        i = i->next;
    }

}

template <typename TYPE>
void transpose(Node<TYPE> *matrix,int m,int n){
    Node<TYPE> *ptr = matrix;
    while(ptr != NULL){
        int temp = ptr->col;
        ptr->col = ptr->row;
        ptr->row = temp;
        ptr = ptr->next;
    };
    sortList(matrix);
    // printList(matrix);
    // printMatrix(matrix,n,m);
}

template <typename TYPE>
void multiply(Node<TYPE> *m1,Node<TYPE> *m2,int x1,int y1,int x2,int y2){
    Node<TYPE> *result = NULL;
    Node<TYPE> *i = m1,*cur = NULL;
    transpose(m2,x2,y2);
    while(i != NULL){
        Node<TYPE> *j = m2;
        while(j != NULL){
            if(j->col == i->col){
                Node<TYPE> *ptr = result;
                TYPE temp_val = i->data * j->data;
                while(ptr != NULL && (ptr->row != i->row || ptr->col != j->row)){
                    ptr = ptr->next;
                }
                if(ptr != NULL){
                    ptr->data = ptr->data + temp_val;
                }
                else{
                    Node<TYPE> *new_node = new Node<TYPE>;
                    new_node->row = i->row;
                    new_node->col = j->row;
                    new_node->data = temp_val;
                    if(result == NULL){
                        result = new_node;
                        cur = new_node;
                    }
                    else{
                        cur->next = new_node;
                        cur = cur->next;
                    }
                }
            }
            j = j->next;
        }
        i = i->next;
    }
    // cout << "Transpose successful" << endl;
    sortList(result);
    printMatrix(result,x1,y2);
}

template <typename TYPE>
TYPE** takeInputUsingArray(int m,int n,int &matrix_size){
    Node<TYPE> *temp_list = NULL;
    Node<TYPE> *cur = NULL;
    for(int i=0;i<m;i++){
        for(int j=0;j<n;j++){
            TYPE val = TYPE();
            cin >> val;
            if(val != 0){
                Node<TYPE> *new_node = new Node<TYPE>;
                new_node->row = i;
                new_node->col = j;
                new_node->data = val;
                if(temp_list == NULL){
                    temp_list = new_node;
                    cur = new_node;
                }
                else{
                    cur->next = new_node;
                    cur = cur->next;
                }
                matrix_size++;
            }
        }
    }
    TYPE **matrix = new TYPE*[matrix_size];
    for(int i=0;i<matrix_size;i++){
        matrix[i] = new TYPE[3];
    }
    cur = temp_list;
    int i=0;
    while(cur != NULL){
        matrix[i][0] = cur->row;
        matrix[i][1] = cur->col;
        matrix[i][2] = cur->data;
        i++;
        cur = cur->next;
    }
    return matrix;
}


template <typename TYPE>
void additionUsingArray(TYPE **matrix1,TYPE **matrix2,int m,int n,int nonzero_count1,int nonzero_count2){
    int i=0,j=0;
    Node<TYPE> *result = NULL,*cur = NULL;
    while(i < nonzero_count1 && j < nonzero_count2){
        Node<TYPE> *new_node = new Node<TYPE>;
        if(matrix1[i][0] == matrix2[j][0]){
            if(matrix1[i][1] == matrix2[j][1]){
                new_node->row = matrix1[i][0];
                new_node->col = matrix1[i][1];
                new_node->data = matrix1[i][2] + matrix2[j][2];
                i++;j++;
            }
            else if(matrix1[i][1] < matrix2[j][1]){
                new_node->row = matrix1[i][0];
                new_node->col = matrix1[i][1];
                new_node->data = matrix1[i][2];
                i++;
            }
            else{
                new_node->row = matrix2[j][0];
                new_node->col = matrix2[j][1];
                new_node->data = matrix2[j][2];
                j++;
            }
        }
        else if(matrix1[i][0] < matrix2[j][0]){
            new_node->row = matrix1[i][0];
            new_node->col = matrix1[i][1];
            new_node->data = matrix1[i][2];
            i++;
        }
        else{
            new_node->row = matrix2[j][0];
            new_node->col = matrix2[j][1];
            new_node->data = matrix2[j][2];
            j++;
        }
        if(result == NULL){
            result = new_node;
            cur = new_node;
        }
        else{
            cur->next = new_node;
            cur = cur->next;
        }
    }
    while(i < nonzero_count1){
        Node<TYPE> *new_node = new Node<TYPE>;
        new_node->row = matrix1[i][0];
        new_node->col = matrix1[i][1];
        new_node->data = matrix1[i][2];
        if(result == NULL){
            result = new_node;
            cur = new_node;
        }
        else{
            cur->next = new_node;
            cur = cur->next;
        }
        i++;
    }
    while(j < nonzero_count2){
        Node<TYPE> *new_node = new Node<TYPE>;
        new_node->row = matrix2[j][0];
        new_node->col = matrix2[j][1];
        new_node->data = matrix2[j][2];
        if(result == NULL){
            result = new_node;
            cur = new_node;
        }
        else{
            cur->next = new_node;
            cur = cur->next;
        }
        j++;
    }
    cur = result;
    for(int i=0;i<m;i++){
        for(int j=0;j<n;j++){
            if(cur != NULL && cur->row == i && cur->col == j){
                cout << cur->data << " ";
                cur = cur->next;
            }
            else{
                cout << "0 ";
            }
        }
        cout << endl;
    }
}

template <typename TYPE>
TYPE** transposeUsingArray(TYPE **matrix,int m,int n,int nonzero_count){
    int total_arr[n],index_arr[n+1];
    for(int i=0;i<n;i++){
        total_arr[i] = 0;
        index_arr[i] = 0;
    }
    // for(int i=1;i<=nonzero_count;i++){
    //     cout << temp_matrix[i][0] << "," << temp_matrix[i][1] << "," << temp_matrix[i][2] << endl;
    // }
    TYPE **transpose = new TYPE*[nonzero_count];
    for(int i=0;i<nonzero_count;i++){
        transpose[i] = new TYPE[3];
    }
    // int transpose[nonzero_count][3];
    
    for(int i=0;i<nonzero_count;i++){
        int col = matrix[i][1];
        total_arr[col]++;
    }
    index_arr[0] = 0;
    for(int i=1;i<=n;i++){
        index_arr[i] = index_arr[i-1] + total_arr[i-1];
    }
    for(int i=0;i<nonzero_count;i++){
        int col = matrix[i][1];
        int location = index_arr[col];
        transpose[location][0] = matrix[i][1];
        transpose[location][1] = matrix[i][0];
        transpose[location][2] = matrix[i][2];
        index_arr[col]++;
    }
    return transpose;
}

template <typename TYPE>
void multiplyUsingArray(TYPE **matrix1,TYPE **matrix2,int m1,int n1,int m2,int n2,int nonzero_count1,int nonzero_count2){
    TYPE **matrix3 = transposeUsingArray<TYPE>(matrix2,m2,n2,nonzero_count2);
    TYPE result[m1][n2];
    for(int i=0;i<m1;i++){
        for(int j=0;j<n2;j++){
            result[i][j] = 0;
        }
    }

    for(int i=0;i<nonzero_count1;i++){
        int row1 = matrix1[i][0],col1 = matrix1[i][1];
        for(int j=0;j<nonzero_count2;j++){
            int row2 = matrix3[j][0],col2 = matrix3[j][1];
            if(col1 == col2){
                TYPE temp_val = matrix1[i][2] * matrix3[j][2];
                result[row1][row2] = result[row1][row2] + temp_val;
            }
        }
    }
    for(int i=0;i<m1;i++){
        for(int j=0;j<n2;j++){
            if(result[i][j] != 0){
                cout << result[i][j] << " ";
            }
            else{
                cout << "0 ";
            }
        }
        cout << endl;
    }
}

int main(){
    cout << "1- Array" << endl;
    cout << "2- Linked List" << endl;
    int ds,op;
    cin >> ds;
    cout << "1- Addition" << endl;
    cout << "2- Transpose" << endl;
    cout << "3- Multiplication" << endl;
    cin >> op;
    switch(ds){
        case 1:
            if(op == 2){
                int m,n;
                cin >> m >> n;
                int nonzero_count = 0;
                int **matrix = takeInputUsingArray<int>(m,n,nonzero_count);
                int **result = transposeUsingArray<int>(matrix,m,n,nonzero_count);
                int k = 0;
                for(int i=0;i<n;i++){
                    for(int j=0;j<m;j++){
                        if(k < nonzero_count && result[k][0] == i && result[k][1] == j){
                            cout << result[k][2] << " ";
                            k++;
                        }
                        else{
                            cout << "0 ";
                        }
                    }
                    cout << endl;
                }
            }
            else{
                int m1,n1;
                cin >> m1 >> n1;
                int nonzero_count1 = 0;
                int **matrix1 = takeInputUsingArray<int>(m1,n1,nonzero_count1);
                int m2,n2;
                cin >> m2 >> n2;
                int nonzero_count2 = 0;
                int **matrix2 = takeInputUsingArray<int>(m2,n2,nonzero_count2);
                if(op == 1){
                    additionUsingArray(matrix1,matrix2,m1,n1,nonzero_count1,nonzero_count2);
                }
                else if(op == 3){
                    multiplyUsingArray(matrix1,matrix2,m1,n1,m2,n2,nonzero_count1,nonzero_count2);
                }
            }
            break;
        case 2:
            if(op == 2){
                int m,n;
                cin >> m >> n;
                Node<int> *matrix = takeInput<int>(m,n);
                transpose(matrix,m,n);
                printMatrix(matrix,n,m);
            }
            else{
                int m1,n1;
                cin >> m1 >> n1;
                Node<int> *matrix1 = takeInput<int>(m1,n1);
                int m2,n2;
                cin >> m2 >> n2;
                Node<int> *matrix2 = takeInput<int>(m2,n2);
                if(op == 1){
                    addition(matrix1,matrix2,m1,n1);
                }
                else if(op == 3){
                    multiply(matrix1,matrix2,m1,n1,m2,n2);
                }
            }
            break;
    }
}
