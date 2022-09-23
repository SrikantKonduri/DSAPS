#include <iostream>

using namespace std;

struct Node{
    int row,col,data;
    struct Node *next;
};


void printList(struct Node *node){
    while(node != NULL){
        cout << node->row << "," << node->col << "," << node->data << endl;
        node = node->next;
    }
    cout << "-----------" << endl;
}

void printMatrix(struct Node *matrix,int m,int n){
    struct Node *cur = matrix;
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


void addition(struct Node *m1,struct Node *m2,int m,int n){
    struct Node *result = NULL,*ptr = NULL;
    while(m1 != NULL && m2 != NULL){
        struct Node *new_node = new Node;
        if(m1->row == m2->row){
            if(m1->col == m2->col){
                int sum = m1->data + m2->data;
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
        struct Node *new_node = new Node;
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
        struct Node *new_node = new Node;
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

struct Node* takeInput(int m,int n){
    struct Node *matrix = NULL,*ptr = NULL;
    for(int i=0;i<m;i++){
        for(int j=0;j<n;j++){
            int val;
            cin >> val;
            if(val != 0){
                struct Node *new_node = new Node;
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


void sortList(Node* head)
{
    struct Node *i = head;
    while(i != NULL){
        struct Node *j = i->next;
        struct Node *temp = i;
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

        t = i->data;
        i->data = temp->data;
        temp->data = t;

        i = i->next;
    }

}

void transpose(struct Node *matrix,int m,int n){
    struct Node *ptr = matrix;
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

void multiply(struct Node *m1,struct Node *m2,int x1,int y1,int x2,int y2){
    struct Node *result = NULL;
    struct Node *i = m1,*cur = NULL;
    transpose(m2,x2,y2);
    while(i != NULL){
        struct Node *j = m2;
        while(j != NULL){
            if(j->col == i->col){
                struct Node *ptr = result;
                int temp_val = i->data * j->data;
                while(ptr != NULL && (ptr->row != i->row || ptr->col != j->row)){
                    ptr = ptr->next;
                }
                if(ptr != NULL){
                    ptr->data = ptr->data + temp_val;
                }
                else{
                    struct Node *new_node = new Node;
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

// int** resize(int **arr){
//     int old_size = capacity;
//     capacity = capacity * 2;
//     int **new_arr = new int *[capacity];
//     for(int i=0;i<capacity;i++){
//         new_arr[i] = new int[3];
//     }
//     for(int i=0;i<old_size;i++){
//         new_arr[i][0] = arr[i][0];
//         new_arr[i][1] = arr[i][1];
//         new_arr[i][2] = arr[i][2];
//     }
//     return new_arr;
// }

int** takeInputUsingArray(int m,int n,int &matrix_size){
    struct Node *temp_list = NULL;
    struct Node *cur = NULL;
    for(int i=0;i<m;i++){
        for(int j=0;j<n;j++){
            int val = 0;
            cin >> val;
            if(val != 0){
                struct Node *new_node = new Node;
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
    int **matrix = new int*[matrix_size];
    for(int i=0;i<matrix_size;i++){
        matrix[i] = new int[3];
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

void additionUsingArray(int **matrix1,int **matrix2,int m,int n,int nonzero_count1,int nonzero_count2){
    int i=0,j=0;
    struct Node *result = NULL,*cur = NULL;
    while(i < nonzero_count1 && j < nonzero_count2){
        struct Node *new_node = new Node;
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
        struct Node *new_node = new Node;
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
        struct Node *new_node = new Node;
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

int** transposeUsingArray(int **matrix,int m,int n,int nonzero_count){
    int total_arr[n],index_arr[n+1];
    for(int i=0;i<n;i++){
        total_arr[i] = 0;
        index_arr[i] = 0;
    }
    // for(int i=1;i<=nonzero_count;i++){
    //     cout << temp_matrix[i][0] << "," << temp_matrix[i][1] << "," << temp_matrix[i][2] << endl;
    // }
    int **transpose = new int*[nonzero_count];
    for(int i=0;i<nonzero_count;i++){
        transpose[i] = new int[3];
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

void multiplyUsingArray(int **matrix1,int **matrix2,int m1,int n1,int m2,int n2,int nonzero_count1,int nonzero_count2){
    matrix2 = transposeUsingArray(matrix2,m2,n2,nonzero_count2);
    int result[m1][n2];
    for(int i=0;i<m1;i++){
        for(int j=0;j<n2;j++){
            result[i][j] = 0;
        }
    }

    for(int i=0;i<nonzero_count1;i++){
        int row1 = matrix1[i][0],col1 = matrix1[i][1];
        for(int j=0;j<nonzero_count2;j++){
            int row2 = matrix2[j][0],col2 = matrix2[j][1];
            if(col1 == col2){
                int temp_val = matrix1[i][2] * matrix2[j][2];
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
    string datastructure;
    cin >> datastructure;
    string operation;
    cin >> operation;
    if(datastructure == "Array"){
        if(operation == "Transpose"){
            int m,n;
            cin >> m >> n;
            int nonzero_count = 0;
            int **matrix = takeInputUsingArray(m,n,nonzero_count);
            int **result = transposeUsingArray(matrix,m,n,nonzero_count);
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
            int **matrix1 = takeInputUsingArray(m1,n1,nonzero_count1);
            int m2,n2;
            cin >> m2 >> n2;
            int nonzero_count2 = 0;
            int **matrix2 = takeInputUsingArray(m2,n2,nonzero_count2);
            if(operation == "Addition"){
                additionUsingArray(matrix1,matrix2,m1,n1,nonzero_count1,nonzero_count2);
            }
            else if(operation == "Multiplication"){
                multiplyUsingArray(matrix1,matrix2,m1,n1,m2,n2,nonzero_count1,nonzero_count2);
            }

        }
    }
    else if(datastructure == "LinkedList"){
        if(operation == "Transpose"){
            int m,n;
            cin >> m >> n;
            struct Node *matrix = takeInput(m,n);
            transpose(matrix,m,n);
            printMatrix(matrix,n,m);
        }
        else{
            int m1,n1;
            cin >> m1 >> n1;
            struct Node *matrix1 = takeInput(m1,n1);
            int m2,n2;
            cin >> m2 >> n2;
            struct Node *matrix2 = takeInput(m2,n2);
            if(operation == "Addition"){
                addition(matrix1,matrix2,m1,n1);
            }
            else if(operation == "Multiplication"){
                multiply(matrix1,matrix2,m1,n1,m2,n2);
            }
        }
    }
}

    // int m1 = 0,n1 = 0;
    // cin >> m1;
    // cin >> n1;
    // int size1 = 0,size2 = 0;
    // int **matrix1 = takeInputUsingArray(m1,n1,size1);
    // int m2 = 0,n2 = 0;
    // cin >> m2;
    // cin >> n2;
    // int **matrix2 = takeInputUsingArray(m2,n2,size2);
    // multiplyUsingArray(matrix1,matrix2,m1,n1,m2,n2,size1,size2);

    // int **matrix1 = takeInputUsingArray(m,n,size1);
    // for(int i=0;i<size1;i++){
    //     cout << matrix1[i][0] << "," << matrix1[i][1] << "," << matrix1[i][2] << endl;
    // }
    // int **transpose = transposeUsingArray(matrix1,m,n,size1);

    // for(int i=0;i<size1;i++){
    //     cout << matrix1[i][0] << "," << matrix1[i][1] << "," << matrix1[i][2] << endl;
    // }
    // cin >> m;
    // cin >> n;
    // int size2 = 0;
    // int **matrix2 = takeInputUsingArray(m,n,size2);
    // for(int i=0;i<size2;i++){
    //     cout << matrix2[i][0] << "," << matrix2[i][1] << "," << matrix2[i][2] << endl;
    // }
    // additionUsingArray(matrix1,matrix2,m,n,size1,size2);



    // int m1,n1;
    // cin >> m1 >> n1;
    // struct Node *matrix1 = takeInput(m1,n1);
    // int m2,n2;
    // cin >> m2 >> n2;
    // struct Node *matrix2 = takeInput(m2,n2);
    // struct Node *matrix2 = takeInput(m,n);
    // addition(matrix1,matrix2);
    // printMatrix(matrix1,m1,n1);
    // printList(matrix1);
    // multiply(matrix1,matrix2,m1,n1,m2,n2);
