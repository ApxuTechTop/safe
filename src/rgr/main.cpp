#include <Safe.hpp>
#include "graph.hpp"
#include <array>
#include <algorithm>
#include <random>

int main()
{
    Safe::long_num a = 10; // кол-во этапов проверок
    srand(time(NULL));
    Graph graph(10);
    generate_good_graph(graph, 0.4);
    if (check_graph(graph)) {
        std::cout << "Graph is good\n";
    } else {
        std::cout << "Graph is bad\n";
    }
    std::ofstream dotfile("graph.dot");
    dotfile << graph_to_dot(graph);
    std::ofstream os("graph.txt");
    os << graph;
    std::vector<Safe::long_num> R;
    std::vector<Safe::long_num> N;
    std::vector<Safe::long_num> C;
    std::vector<Safe::long_num> D;
    std::vector<Safe::long_num> Z;
    R.resize(graph.vertices_count);
    N.resize(graph.vertices_count);
    C.resize(graph.vertices_count);
    D.resize(graph.vertices_count);
    Z.resize(graph.vertices_count);
    for (int step = 0; step < a; ++step)
    {
        // Шаг 1
        std::array<Graph::Colors, 3> shuffled_colors = {Graph::Colors::Red, Graph::Colors::Green, Graph::Colors::Blue};
        auto rd = std::random_device{};
        auto rng = std::default_random_engine{rd()};
        std::shuffle(shuffled_colors.begin(), shuffled_colors.end(), rng);
        std::unordered_map<Graph::Colors, Graph::Colors> transmuted_color = {
            {Graph::Colors::Red, shuffled_colors[0]},
            {Graph::Colors::Green, shuffled_colors[1]},
            {Graph::Colors::Blue, shuffled_colors[2]}};

        for (int i = 0; i < graph.vertices_count; ++i)
        {
            // Шаг 2
            Safe::Encryption::RSA rsa;
            auto [d, n] = rsa.get_open_key();
            auto c = rsa.get_close_key();
            Safe::long_num r = Safe::Math::get_num(1, n);
            r = (r >> 2) << 2;
            int bc = static_cast<int>(transmuted_color[graph.vertices[i]]);
            R[i] = r + bc;
            // Шаг 3

            N[i] = n;
            D[i] = d;
            C[i] = c;
            // Шаг 4
            Z[i] = Safe::Math::pow_mod(R[i], d, n);
        }
        // Шаг 5
        auto edge = graph.edges[std::rand() % graph.edges.size()];
        auto [v1, v2] = edge;
        Safe::long_num z1, z2;
        z1 = Safe::Math::pow_mod(Z[v1], C[v1], N[v1]);
        z2 = Safe::Math::pow_mod(Z[v2], C[v2], N[v2]);
        int r1 = (z1 % 4).to_int();
        int r2 = (z2 % 4).to_int();
        std::cout << v1 << "(" << r1 << ") -- " << v2 << "(" << r2 << ")" << std::endl;
        if ((r1) == (r2))
        {
            
            std::cout << (step + 1) << " этап - Не верно\n";
            std::cout << "Алиса не знает раскраску\n";
            return 0;
        }
        else
        {
            std::cout << (step + 1) << " этап - Верно\n";
        }
    }
    std::cout << "Алисе знает раскраску\n";
}