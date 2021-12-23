#include <iostream>

using namespace std;

int n;
int heap_size;

class Node{

    public:
        Node* left;
        Node* right;
        int frequency;
        char c;
};

void min_heapify(Node ** Q, int i){

    int l = 2*i;
    int r = 2*i+1;

    int smallest;

    if(l<=heap_size && Q[l]->frequency < Q[i]->frequency) smallest = l;
    else smallest = i;

    if(r<=heap_size && Q[r]->frequency < Q[smallest]->frequency) smallest = r;

    if(smallest != i){

        Node * tmp = Q[i];
        Q[i] = Q[smallest];
        Q[smallest] = tmp;

        min_heapify(Q, smallest);

    }

}

void build_min_heap(Node ** Q){

    heap_size = n;
    for(int i=n/2;i>=1;i--){
        min_heapify(Q, i);
    }
}

Node* extract_min(Node ** Q){

    Node * min = Q[1];
    Q[1] = Q[heap_size];
    heap_size--;

    min_heapify(Q, 1);
    return min;

}

void insert(Node ** Q, Node * z){

    heap_size++;
    Q[heap_size] = z;

    int i = heap_size;

    while(i>1 && Q[i/2]->frequency > Q[i]->frequency){
        Node *tmp = Q[i];
        Q[i] = Q[i/2];
        Q[i/2] = tmp;

        i = i/2;
    }

}

Node* huffman(int * C){

    Node ** min_pq = new Node *[2*n];

    for(int i=1;i<=n;i++){

        Node * tmp = new Node;
        tmp->frequency = C[i-1];
        tmp->c = 'a'+i-1;

        min_pq[i] = tmp;

    }
    
    build_min_heap(min_pq);

    for(int i=1;i<n;i++){

        Node * z = new Node;
        Node * x = extract_min(min_pq);
        Node * y = extract_min(min_pq);
        z->left = x;
        z->right = y;

        z->frequency = x->frequency + y->frequency;
        insert(min_pq, z);

    }

    Node * ret = extract_min(min_pq);

    return ret;
}

void make_code(Node * root, std::string c, std::string * code_list){

    if(root->left){
        c = c + "0";
        make_code(root->left, c, code_list);
        c = c.substr(0, c.length() - 1);
    }

    if(root->right){
        c = c + "1";
        make_code(root->right, c, code_list);
        c = c.substr(0, c.length() - 1);
    }

    if(!(root->left) && !(root->right)){
        int idx = ((int) root->c) - 'a';
        code_list[idx] = c;
    }
}

int main(){

    cin >> n;

    if(n==0) return 0;

    int * C = new int[n];

    for(int i=0;i<n;i++){
        cin >> C[i];
    }

    if(n==1){
        cout << 0 << endl;
        return 0;
    }

    Node * huffman_root = huffman(C);
    std::string code = "";

    std::string *code_list = new std::string[n];

    make_code(huffman_root, code, code_list);

    for(int i=0;i<n;i++){
        cout << code_list[i] << '\n';
    }

    delete[] C;
    delete[] code_list;

    delete[] huffman_root;

    return 0;

}