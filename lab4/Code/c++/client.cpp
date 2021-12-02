#include<iostream>
#include <list>
#include <chrono>
#include<emscripten/emscripten.h>
#include<emscripten/websocket.h>

using namespace std;
using namespace std::chrono;


// Program to print BFS traversal from a given
// source vertex. BFS(int s) traverses vertices
// reachable from s.
 
 
// This class represents a directed graph using
// adjacency list representation
class Graph
{
    int V;    // No. of vertices
 
    // Pointer to an array containing adjacency
    // lists
    list<int> *adj;  
public:
    Graph(int V);  // Constructor
 
    // function to add an edge to graph
    void addEdge(int v, int w);
 
    // prints BFS traversal from a given source s
    void BFS(int s,  const EmscriptenWebSocketOpenEvent *websocketEvent); 
};
 
Graph::Graph(int V)
{
    this->V = V;
    adj = new list<int>[V];
}
 
void Graph::addEdge(int v, int w)
{
    adj[v].push_back(w); // Add w to v’s list.
}
 
void Graph::BFS(int s, const EmscriptenWebSocketOpenEvent *websocketEvent)
{
    milliseconds start = duration_cast< milliseconds >(
        system_clock::now().time_since_epoch()
    );
    // Mark all the vertices as not visited
    bool *visited = new bool[V];
    for(int i = 0; i < V; i++)
        visited[i] = false;
 
    // Create a queue for BFS
    list<int> queue;
 
    // Mark the current node as visited and enqueue it
    visited[s] = true;
    queue.push_back(s);
 
    // 'i' will be used to get all adjacent
    // vertices of a vertex
    list<int>::iterator i;
 
    while(!queue.empty())
    {
        // Dequeue a vertex from queue and print it
        s = queue.front();
        //cout << s << " ";
        // send to server
        EMSCRIPTEN_RESULT result;
        string msg = to_string(s);
        result = emscripten_websocket_send_utf8_text(websocketEvent->socket, msg.c_str());
        if (result) {
            printf("Failed to emscripten_websocket_send_utf8_text(): %d\n", result);
        }

        queue.pop_front();
 
        // Get all adjacent vertices of the dequeued
        // vertex s. If a adjacent has not been visited,
        // then mark it visited and enqueue it
        for (i = adj[s].begin(); i != adj[s].end(); ++i)
        {
            if (!visited[*i])
            {
                visited[*i] = true;
                queue.push_back(*i);
            }
        }
    }
    
    milliseconds end = duration_cast< milliseconds >(
        system_clock::now().time_since_epoch()
    );

    auto spend = end - start;
    EMSCRIPTEN_RESULT result;
    string msg = "Spend: " + to_string(spend.count()) + " ms";
    result = emscripten_websocket_send_utf8_text(websocketEvent->socket, msg.c_str());
    if (result) {
        printf("Failed to emscripten_websocket_send_utf8_text(): %d\n", result);
    }
}


EM_BOOL onopen(int eventType, const EmscriptenWebSocketOpenEvent *websocketEvent, void *userData) {
    puts("onopen");
    
    Graph g(4);
    g.addEdge(0, 1);
    g.addEdge(0, 2);
    g.addEdge(1, 2);
    g.addEdge(2, 0);
    g.addEdge(2, 3);
    g.addEdge(3, 3);
 
    cout << "Following is Breadth First Traversal "
         << "(starting from vertex 2) \n";
    g.BFS(2, websocketEvent);
    
    return EM_TRUE;
}

EM_BOOL onerror(int eventType, const EmscriptenWebSocketErrorEvent *websocketEvent, void *userData) {
    puts("onerror happened");

    return EM_TRUE;
}

EM_BOOL onclose(int eventType, const EmscriptenWebSocketCloseEvent *websocketEvent, void *userData) {
    puts("onclose happened");

    return EM_TRUE;
}

EM_BOOL onmessage(int eventType, const EmscriptenWebSocketMessageEvent *websocketEvent, void *userData) {
    //puts("onmessage");
    if (websocketEvent->isText) {
        // For only ascii chars.
        printf("message: %s\n", websocketEvent->data);
    }

    /*
    EMSCRIPTEN_RESULT result;
    result = emscripten_websocket_close(websocketEvent->socket, 1000, "no reason");
    if (result) {
        printf("Failed to emscripten_websocket_close(): %d\n", result);
    }
    */
    return EM_TRUE;
}




int main() {
    if (!emscripten_websocket_is_supported()) {
        return 0;
    }
    EmscriptenWebSocketCreateAttributes ws_attrs = {
        "ws://localhost:8765/ws",
        NULL,
        EM_TRUE
    };

    EMSCRIPTEN_WEBSOCKET_T ws = emscripten_websocket_new(&ws_attrs);
    emscripten_websocket_set_onopen_callback(ws, NULL, onopen);
    emscripten_websocket_set_onerror_callback(ws, NULL, onerror);
    emscripten_websocket_set_onclose_callback(ws, NULL, onclose);
    emscripten_websocket_set_onmessage_callback(ws, NULL, onmessage);

    return 1;
}
