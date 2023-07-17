//This is the code which implements graph by reading a file (here file.txt). This also has DFX and BFS implementation

#include<iostream>
#include<bits/stdc++.h>
#include<vector>
#include<string>
#include<fstream>
#include<sstream>
#include<queue>
#include<stack>
#include<map>

class NodeComparator {
    public:
        bool operator()(std::pair<int, int>& a, std::pair<int, int>& b) const {
        return a.second > b.second;
        }
};

class Edge{
    private:
        int m_d_id;
        int m_weight;
    public:
        Edge(int d_id, int weight): m_d_id(d_id), m_weight(weight) {}
        Edge():m_d_id(0), m_weight(0) {}
        int get_D_id(){
            return m_d_id;
        }
        int get_weight(){
            return m_weight;
        }
        void set_D_d(int i){
            m_d_id = i;
        }
        void set_weight(int i){
            m_weight = i;
        }
};

class Node{
    private:
        int node_id;
        std::vector<Edge*> listofEdgeConnecting;
    public:
        Node(): node_id(0){}
        Node(int node_id): node_id(node_id) {}
        int get_node_id(){
            return node_id;
        }
        void set_node_id(int i){
            node_id= i;
        }

        void set_listofEdge(Edge* e){
            listofEdgeConnecting.push_back(e);
        }
        std::vector<Edge*>& get_listofEdge() {
            return listofEdgeConnecting;
        }
        
};
        
class Graph{
    private:
        std::string m_file;
        std::vector<Node*> VertexWithEdges;
    public:
        Graph(std::string file_name) {
            std::ifstream inf{ file_name };
            std::string line;
    
            int count{}, nodes{}, edges{};
            while( getline(inf, line)){
                    std::istringstream is (line);
                    if(count == 0){
                        int num;
                        is>>num;
                        VertexWithEdges.resize(num+1);
                        std::cout<<num<<'\n';
                    }
                    else if(count == 1){
                        int num;
                        is>>num;
                        edges = num;
                        std::cout<<num<<'\n';
                    }
                    else{
                        int k{}, s_id{}, w{}, d_id{}, num{};
                        while( is >> num ) {
                            if( k ==0){
                                s_id = num;
                                Node* n = new Node(num);
                                add_node(n);

                            }
                            else if (k == 1){
                                d_id = num;
                                Node* n = new Node(num);
                                add_node(n);
                            }
                            else {
                                w = num;
                            }
                            k++;
                        }
                        add_edge(s_id, d_id, w);
                }
                count++;
            }
        }
        
        int size(){
            return VertexWithEdges.size();
        }

        void add_edge(int s, int d, int w){
            Edge* e = new Edge(d, w);
            Edge* f = new Edge(s, w);
            std::cout<<e->get_D_id()<<" "<<e->get_weight()<<'\n';

            if(VertexWithEdges[s] != 0 && VertexWithEdges[d] != 0){
                VertexWithEdges[s]->set_listofEdge(e);
                VertexWithEdges[d]->set_listofEdge(f);
            }
        }

        void add_node(Node* n) {
            if(VertexWithEdges[n->get_node_id()] == 0){
                VertexWithEdges[n->get_node_id()] = n;
            }
        }

        void print(){
            for(int i=1; i< VertexWithEdges.size(); i++){
                std::cout<<"Printing node vector\n";
                std::cout<<VertexWithEdges[i]->get_node_id()<<'\n';
                std::cout<<"Size of list "<<VertexWithEdges[i]->get_listofEdge().size()<<std::endl;
                if (VertexWithEdges[i]->get_listofEdge().size()){
                    for(int j=0; j<VertexWithEdges[i]->get_listofEdge().size(); j++){
                        std::cout<<"Edges connected to node "<<VertexWithEdges[i]->get_node_id()<<": ";
                        std::cout<<VertexWithEdges[i]->get_listofEdge()[j]->get_D_id()<<'\n';
                    }
                    std::cout<<'\n';
                }
                else{
                    std::cout<<"No edges found\n";
                    //std::cout<<"[]"<<std::endl;
                }
            }
        }

        friend std::ostream& operator<<(std::ostream& out, const Graph& c){
            for(int i=1; i<= c.VertexWithEdges.size(); i++){
                out<<"Printing node vector\n";
                out<<c.VertexWithEdges[i]->get_node_id()<<'\n';
                std::cout<<c.VertexWithEdges[i]->get_listofEdge().size()<<'\n';
                if (c.VertexWithEdges[i]->get_listofEdge().size()){
                    for(int j=0; j<c.VertexWithEdges[i]->get_listofEdge().size(); j++){
                        out<<"Edges connected to node "<<c.VertexWithEdges[i]->get_node_id()<<": ";
                        out<<c.VertexWithEdges[i]->get_listofEdge()[j]->get_D_id()<<std::endl;
                        out<<c.VertexWithEdges[i]->get_listofEdge()[i]->get_weight()<<std::endl;
                    }
                }
                else{
                    out<<"No edges found\n";
                    //out<<"[]"<<std::endl;
                }
            }
            return out;
        }

        void BFS();
        void DFS();
        bool check_ifNodeExists(int s);
        //void Dijkstra(int source, int dest);
};

void Graph::BFS(){
    std::vector<bool> v(VertexWithEdges.size()+1);
    std::queue<int> q;
    q.push(VertexWithEdges[1]->get_node_id());
        v[VertexWithEdges[1]->get_node_id()] = true;
        int i{0};
        while(!q.empty()){
            int front = q.front();
            q.pop();
            std::cout<<"Node_id in front of the queue :"<<front<<std::endl;
            for(int j=0; j<VertexWithEdges[front]->get_listofEdge().size(); j++){
                //std::cout<<"gives edges of this node: "<<VertexWithEdges[front]->get_listofEdge()[j]->get_D_id()<<std::endl;
                if(v[VertexWithEdges[front]->get_listofEdge()[j]->get_D_id()] == false){
                    q.push(VertexWithEdges[front]->get_listofEdge()[j]->get_D_id());
                    v[VertexWithEdges[front]->get_listofEdge()[j]->get_D_id()] = true;
                    std::cout<<VertexWithEdges[front]->get_listofEdge()[j]->get_D_id()<<" ";
                }
            }
             std::cout<<'\n';
            i++;
        }
}

void Graph::DFS(){
    std::vector<bool> v(VertexWithEdges.size()+1);
    std::stack<int> st;
    std::cout<<'\n';
    st.push(VertexWithEdges[1]->get_node_id());
        v[VertexWithEdges[1]->get_node_id()] = true;
        int i{0};
        while(!st.empty()){
            int top = st.top();
            st.pop();
            std::cout<<"Node_id on the top of stack :"<<top<<std::endl;
            for(int j=0; j<VertexWithEdges[top]->get_listofEdge().size(); j++){
                //std::cout<<"gives edges of this node: "<<VertexWithEdges[front].get_listofEdge()[j].get_EdgeConnectedToNode().get_node_id()<<std::endl;
                if(v[VertexWithEdges[top]->get_listofEdge()[j]->get_D_id()] == false){
                    st.push(VertexWithEdges[top]->get_listofEdge()[j]->get_D_id());
                    v[VertexWithEdges[top]->get_listofEdge()[j]->get_D_id()] = true;
                    std::cout<<VertexWithEdges[top]->get_listofEdge()[j]->get_D_id()<<" ";
                }
            }
            std::cout<<'\n';
            i++;
        }
}

/*void Graph::Dijkstra(int source, int dest){
    int numofnodes = size();
    int weight{};
    std::vector<int> v(VertexWithEdges.size()+1, std::numeric_limits<int>::max()); //This is close set which keeps track on the visited nodes
    std::stack<int> st;  //This is the stack where the weight of visited nodes are stored
    std::vector<bool> pr_q(VertexWithEdges.size()+1);
    std::priority_queue<std::pair<int, int>, std::vector<std::pair<int, int>>, NodeComparator> pq; // comparator function to compare with the 2nd element of the pair(which is weight)
    v[VertexWithEdges[source]->get_node_id()] = 0;
    st.push(0);

    int top = VertexWithEdges[source]->get_node_id();
    do{
        pq.pop();
        for(int i=0; i<VertexWithEdges[top]->get_listofEdge().size(); i++){
            if(v[VertexWithEdges[top]->get_listofEdge()[i]->get_D_id()] == 0 && top != source) //Find the node value in m_stack. if not exists then proceed further
            {
                //v[VertexWithEdges[top]->get_listofEdge()[i]->get_D_id()] = VertexWithEdges[top]->get_listofEdge()[i]->get_weight();
                int distance = weight + st.top();
                if (pr_q[VertexWithEdges[top]->get_listofEdge()[i]->get_D_id()] != false && distance < v[VertexWithEdges[top]->get_listofEdge()[i]->get_weight()]) 
                {
                    v[VertexWithEdges[top]->get_listofEdge()[i]->get_D_id()] = VertexWithEdges[top]->get_listofEdge()[i]->get_weight();
                } 
                //else push the new key in priority queue
                   //v[VertexWithEdges[top]->get_listofEdge()[i]->get_D_id()] = VertexWithEdges[top]->get_listofEdge()[i]->get_weight() ;
                //top = pq.top.first()
                //st.push(pq.top.second())
                //pq.pop()
            }
            else{
                pq.push({VertexWithEdges[top]->get_listofEdge()[i]->get_D_id(), VertexWithEdges[top]->get_listofEdge()[i]->get_weight()});
                pr_q[VertexWithEdges[top]->get_listofEdge()[i]->get_D_id()] = true;
                //v[VertexWithEdges[top]->get_listofEdge()[i]->get_D_id()] = VertexWithEdges[top]->get_listofEdge()[i]->get_weight() ;
            }
        }
        std::pair<int, int> pq_top = pq.top();
        top = pq_top.first;
        weight = pr_q[pq_top.first];
        pr_q[pq_top.first] = 0;
        //st.push(pq_top.second);
    }
    while(!pq.empty());
}*/

bool Graph::check_ifNodeExists(int s){
    if(VertexWithEdges[s]->get_node_id() == 1){
            return true;
        }
    return false;
}

int main() {
    Graph obj("file.txt");
    obj.print();
    obj.DFS();
    
    return 0;  
}
