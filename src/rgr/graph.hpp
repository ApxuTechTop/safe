#pragma once

#include <vector>
#include <unordered_map>
#include <iostream>
#include <fstream>
#include <sstream>

class Graph {
    public:
    int vertices_count;
    int edges_count;
    enum class Colors {Red, Green, Blue};
    std::vector<std::pair<int, int>> edges;
    std::vector<Colors> vertices;
    void set_vertices(int _vertices_count) {
        vertices_count = _vertices_count;
        vertices.resize(vertices_count);
    }
    void set_edges(int _edges_count) {
        edges_count = _edges_count;
        edges.resize(edges_count);
    }
    Graph(int _vertices_count = 5) {
        set_vertices(_vertices_count);
    }
};

void generate_good_graph(Graph& graph, float density) {
    for (int i = 0; i < graph.vertices_count; ++i) {
        int color = std::rand() % 3;
        graph.vertices[i] = static_cast<Graph::Colors>(color);
    }
    for (int i = 0; i < graph.vertices_count; ++i) {
        for (int j = 0; j < graph.vertices_count; ++j) {
            if ((float)std::rand() / RAND_MAX < (1 - (1 - density) / 2)) {
                if (!(graph.vertices[i] == graph.vertices[j]) && (i < j)) {
                    graph.edges.emplace_back(i, j);
                }
            }
        }
    }
    
}

void generate_graph(Graph& graph, float density) {
    for (int i = 0; i < graph.vertices_count; ++i) {
        int color = std::rand() % 3;
        graph.vertices[i] = static_cast<Graph::Colors>(color);
    }
    for (int i = 0; i < graph.vertices_count; ++i) {
        for (int j = 0; j < graph.vertices_count; ++j) {
            if ((float)std::rand() / RAND_MAX < density) {
                if ((i < j)) {
                    graph.edges.emplace_back(i, j);
                }
            }
        }
    }
}

bool check_graph(Graph& graph) {
    for (auto [v1, v2] : graph.edges) {
        if (graph.vertices[v1] == graph.vertices[v2]) {
            return false;
        }
    }
    return true;
}

std::unordered_map<Graph::Colors, std::string> str_colors = {{Graph::Colors::Red, "red"}, {Graph::Colors::Green, "green"}, {Graph::Colors::Blue, "blue"}};

std::string graph_to_dot(Graph& graph) {
    std::stringstream ss;
    ss << "graph G {\n";

    for (int i = 0; i < graph.vertices_count; ++i) {
        ss << i << "[ color=" << str_colors[graph.vertices[i]] << " ]\n";
    }
    for (auto [v1, v2] : graph.edges) {
        ss << v1 << " -- " << v2 << '\n';
    }

    ss << "}";

    return ss.str();
}

std::istream& operator>>(std::istream& is, Graph& graph) {
    int vertices_count;
    int edges_count;
    is >> vertices_count >> edges_count;
    graph.set_vertices(vertices_count);
    graph.set_edges(edges_count);
    for (int i = 0; i < edges_count; ++i) {
        int v1, v2;
        is >> v1 >> v2;
        graph.edges[i] = {v1, v2};
    }
    for (int i = 0; i < vertices_count; ++i) {
        int color;
        is >> color;
        graph.vertices[i] = static_cast<Graph::Colors>(color);
    }
    return is;
}

std::ostream& operator<<(std::ostream& os, Graph& graph) {
    os << graph.vertices_count << ' ' << graph.edges.size() << std::endl;
    for (auto [v1, v2] : graph.edges) {
        os << v1 << ' ' << v2 << std::endl;
    }
    for (auto& c : graph.vertices) {
        os << (int)c << ' ';
    }
    return os;
}