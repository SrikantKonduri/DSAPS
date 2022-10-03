#include <iostream>

using namespace std;

template <class TYPE>
class Node{
public:
    TYPE data;
    Node *left,*right;
    int freq,count,height;
    Node(){}
    Node(TYPE _data,Node *_left,Node *_right){
        data = _data;
        left = _left;
        right = _right;
        freq = 1;
        height = 1;
        count = 1;
    }
};

template <class TYPE>
class AVL{
public:
    Node<TYPE> *root;

    AVL(){
        root = NULL;
    }

    int getHeight(Node<TYPE> *root){
        if(root == NULL){
            return 0;
        }
        return root->height;
    }
    
    Node<TYPE>* search(Node<TYPE> *root,TYPE data){
        if(root != NULL){
            if(root->data == data){
                return root;
            }
            if(data < root->data){
                return search(root->left,data);
            }
            return search(root->right,data);
        }
        return NULL;
    }

    bool search(TYPE data){
        Node<TYPE> *result = search(root,data);
        if(result != NULL){
            return true;
        }
        return false;
    }

    int getNodeCount(Node<TYPE> *node){
        if(node == NULL){
            return 0;
        }
        return node->count;
    }

    int getBalanceFactor(Node<TYPE> *node){
        return getHeight(node->left) - getHeight(node->right);
    }

    Node<TYPE>* rotateLeft(Node<TYPE> *cur){
        Node<TYPE> *cur_right = cur->right;
        cur->right = cur_right->left;
        cur_right->left = cur;
        cur->height = 1 + max(getHeight(cur->left),getHeight(cur->right));
        cur->count = cur->freq + getNodeCount(cur->left) + getNodeCount(cur->right);
        cur_right->height = 1 + max(getHeight(cur_right->left),getHeight(cur_right->right));
        cur_right->count = cur_right->freq + getNodeCount(cur_right->left) + getNodeCount(cur_right->right);
        return cur_right;
    }

    Node<TYPE>* rotateRight(Node<TYPE> *cur){
        Node<TYPE> *cur_left = cur->left;
        cur->left = cur_left->right;
        cur_left->right = cur;
        cur->height = 1 + max(getHeight(cur->left),getHeight(cur->right));
        cur->count = cur->freq + getNodeCount(cur->left) + getNodeCount(cur->right);
        cur_left->height = 1 + max(getHeight(cur_left->left),getHeight(cur_left->right));
        cur_left->count = cur_left->freq + getNodeCount(cur_left->left) + getNodeCount(cur_left->right);
        return cur_left;
    }

    
    Node<TYPE>* insertAndBalance(Node<TYPE> *master,TYPE data){
        int balance_factor = 0;
        if(master == NULL){
            Node<TYPE> *new_node = new Node<TYPE>(data,NULL,NULL);
            master = new_node;
            return new_node;
        }
        if(data < master->data){
            if(master->left == NULL){
                Node<TYPE> *new_node = new Node<TYPE>(data,NULL,NULL);
                master->left = new_node;
            }
            else{
                Node<TYPE> *left = insertAndBalance(master->left,data);
                master->left = left;
            }
        }
        else{
            if(master->right == NULL){
                Node<TYPE> *new_node = new Node<TYPE>(data,NULL,NULL);
                master->right = new_node;
            }
            else{
                Node<TYPE> *right = insertAndBalance(master->right,data);
                master->right = right;
            }
        }
        master->height = 1 + max(getHeight(master->left),getHeight(master->right));
        master->count = master->freq + getNodeCount(master->left) + getNodeCount(master->right);
        balance_factor = getBalanceFactor(master);

        // cout << "Data: " << data << endl;

        // LL Imbalance
        if (balance_factor > 1 && data < master->left->data){
            return rotateRight(master);
        }
 
        // RR Imbalance
        if (balance_factor < -1 && data > master->right->data){
            return rotateLeft(master);
        }
    
        // LR Imbalance
        if (balance_factor > 1 && data > master->left->data){
            master->left = rotateLeft(master->left);
            return rotateRight(master);
        }
    
        // RL Imabalance
        if (balance_factor < -1 && data < master->right->data){
            master->right = rotateRight(master->right);
            return rotateLeft(master);
        }

        return master;

    }

    void upDateCount(Node<TYPE> *master,TYPE data){
        if(master != NULL){
            if(data == master->data){
                master->freq++;
                master->count++;
            }
            else if(data < master->data){
                master->count++;
                upDateCount(master->left,data);
            }
            else{
                master->count++;
                upDateCount(master->right,data);
            }
        }
    }

    void insert(TYPE data){
        Node<TYPE> *search_result = search(root,data);
        if(search_result != NULL){
            upDateCount(root,data);
            return;
        }
        // int h;
        // cin >> h;
        root = insertAndBalance(root,data);
    }

    void printTree(Node<TYPE> *root,int depth){
        if(root == NULL) {
            cout << "X" << endl;
            return;
        }

        Node<TYPE> *temp = root;

        // cout << "[" << temp -> data << ":" << temp -> freq << "| " << getNodeCount(temp->left) << ", " << getNodeCount(temp->right) << " | {" << temp -> height << "}" "]" << endl;
        cout << "[" << temp -> data << "," << temp->freq << "," << temp->count << "," << temp->height <<  "]" << endl;
        for(int i = 0; i < depth; ++i) {
            cout << "     ";
        }
        cout << "├──";
        printTree(root -> right, depth + 1);
        
        for(int i = 0; i < depth; ++i) {
            cout << "     ";
        }
        cout << "└──";
        printTree(root -> left, depth + 1);
    }

    int countOccurance(TYPE data){
        Node<TYPE> *result = search(root,data);
        if(result != NULL){
            return result->freq;
        }
        return 0;
    }

    Node<TYPE>* getLowerBound(Node<TYPE> *root,TYPE data){
        if(root != NULL){
            if(root->data == data){
                return root;
            }
            if(data < root->data){
                Node<TYPE> *left = getLowerBound(root->left,data);
                if(left == NULL){
                    return root;
                }
                return left;
            }
            if(data > root->data){
                Node<TYPE> *right = getLowerBound(root->right,data);
                return right;
            }
        }
        return NULL;
    }

    TYPE lower_bound(TYPE element){
        Node<TYPE> *result = getLowerBound(root,element);
        if(result == NULL){
            return TYPE();
        }
        return result->data;
    }

    Node<TYPE>* getUpperBound(Node<TYPE> *root,TYPE data){
        if(root != NULL){
            if(data < root->data){
                Node<TYPE> *left = getUpperBound(root->left,data);
                if(left == NULL){
                    return root;
                }
                return left;
            }
            return getUpperBound(root->right,data);
        }
        return NULL;
    }

    TYPE upper_bound(TYPE element){
        Node<TYPE> *result = getUpperBound(root,element);
        if(result == NULL){
            return TYPE();
        }
        return result->data;
    }

    Node<TYPE>* getClosestLess(Node<TYPE> *root,TYPE data){
        if(root != NULL){
            if(data == root->data){
                return root;
            }
            if(data > root->data){
                return root;
            }
            return getClosestLess(root->left,data);
        }
        return NULL;
    }
    
    TYPE closest_element(TYPE element){
        TYPE greater_equal = lower_bound(element);
        Node<TYPE> *lesser_result = getClosestLess(root,element);
        TYPE lesser_equal = TYPE();
        if(lesser_result == NULL){
            return greater_equal;
        }
        else{
            lesser_equal = lesser_result->data;
        }
        if(abs(element - lesser_equal) <= abs(element - greater_equal)){
            return lesser_equal;
        }
        return greater_equal;
    }

    TYPE findKthLargest(Node<TYPE> *root,int k){
        // if(k == 1){
        //     // find largest
        // }
        int right_count = getNodeCount(root->right);
        if(right_count >= k){
            return findKthLargest(root->right,k);
        }
        k = k - right_count;
        if(root->freq >= k){
            return root->data;
        }
        k = k - root->freq;
        return findKthLargest(root->left,k);
    }

    TYPE Kth_largest(int k){
        if(k > root->count){
            return TYPE();
        }
        return findKthLargest(root,k);
    }

    Node<TYPE> *getLeastFromRST(Node<TYPE> *root){
        if(root != NULL){
            if(root->left == NULL){
                return root;
            }
            return getLeastFromRST(root->left);
        }
        return NULL;
    }

    Node<TYPE>* deleteLeasetFromLST(Node<TYPE> *root){
        
    }
    
    Node<TYPE>* delete_node(Node<TYPE> *root,TYPE data){
        if(root != NULL){
            if(data < root->data){
                return delete_node(root->left,data);
            }
            if(data > root->data){
                return delete_node(root->right,data);
            }
            Node<TYPE> *least_rst = getLeastFromRST(root->left);
            if(least_rst == NULL){

            }
            else{
                
            }
        }
        return NULL;
    }
    
    void deleteNode(TYPE data){
    
    }

};


int main(){
 
 
}
 