#include <iostream>
#define INT_MAX 2147483647

using namespace std;

int number_v;
int number_e;
int heap_size;

class Vertex{

    public:
        string name;
        int d;
        string p;

};

class Edge{

    public:
        string u;
        string v;
        int weight;

};

void min_heapify(Vertex ** Q, int i){

    int l = 2*i;
    int r = 2*i+1;

    int smallest;

    if(l<=heap_size && Q[l]->d < Q[i]->d) smallest = l;
    else smallest = i;

    if(r<=heap_size && Q[r]->d < Q[smallest]->d) smallest = r;

    if(smallest != i){

        Vertex * tmp = Q[i];
        Q[i] = Q[smallest];
        Q[smallest] = tmp;

        min_heapify(Q, smallest);

    }

}

void build_min_heap(Vertex ** Q){

    heap_size = number_v;
    for(int i=number_v/2;i>=1;i--){
        min_heapify(Q, i);
    }
}

Vertex * extract_min(Vertex ** Q){

    Vertex * min = Q[1];
    Q[1] = Q[heap_size];
    heap_size--;

    min_heapify(Q, 1);
    return min;

}

void decrease_key(Vertex ** Q, int i, int key){

    Q[i]->d = key;

    while(i>1 && Q[i/2]->d > Q[i]->d){

        Vertex * tmp = Q[i];
        Q[i] = Q[i/2];
        Q[i/2] = tmp;

        i = i/2;
    }
}


Vertex ** Dijkstra(Vertex ** G, Edge * w){

    Vertex ** S = new Vertex *[number_v];
    int s_idx = 0;

    build_min_heap(G);

    while(heap_size){

        Vertex * u = extract_min(G);
        S[s_idx++] = u;

        for(int i=0;i<number_e;++i){

            if(w[i].u == u->name){

                Vertex * v;
                int idx = 0;

                for(int j=1;j<=heap_size;j++){
                    if(w[i].v == G[j]->name){
                        v = G[j];
                        idx = j;
                        break;
                    }
                }
                if(idx == 0) continue;

                if((v->d == INT_MAX) || v->d > u->d + w[i].weight){
                    decrease_key(G, idx, u->d + w[i].weight);
                    v->p = u->name;

                }
            }
        }
    }

    return S;

}

void Print(Vertex ** S){

    int * print_list = new int[number_v];

    for(int i=0;i<number_v;i++){
        string n = S[i]->name;

        int idx = n.at(0) - 'A';
        print_list[idx] = S[i]->d;
    }

    for(int i=0;i<number_v;i++){
        cout << print_list[i] << '\n';
    }

    delete[] print_list;

}

int main(){

    string vertexes;

    getline(cin, vertexes);
    if(vertexes.empty()) return 0;

    number_v = (vertexes.length()) / 2 + 1;

    Vertex ** G = new Vertex *[number_v+1];

    int idx = 1;

    while(idx<=number_v){

        G[idx] = new Vertex;
        
        char c = 'A'+idx-1;
        string s;
        s += c;
        G[idx]->name = s;
        G[idx]->p = " ";
        if(idx == 1) G[idx]->d = 0;
        else G[idx]->d = INT_MAX;

        idx++;
    }

    cin >> number_e;

    Edge * w = new Edge[number_e];

    string e;
    for(int i=0;i<number_e;i++){

        cin >> e;
        string buffer;

        int comma;
        
        for(int j=0;j<e.length();j++){

            if(e.at(j) == ','){
                w[i].u = buffer;
                buffer.clear();
                comma = j;
                break;
            }

            buffer += e.at(j);
        }

        for(int j=comma+1;j<e.length();j++){

            if(e.at(j) == ','){
                w[i].v = buffer;
                buffer.clear();
                comma = j;
                break;
            }
            
            buffer += e.at(j);
        }

        for(int j=comma+1;j<e.length();j++){
            buffer += e.at(j);
        }
        w[i].weight = stoi(buffer);

    } 

    Vertex ** S = Dijkstra(G, w);

    Print(S);

    delete[] w;
    delete[] G;
    delete[] S;

    return 0;

}