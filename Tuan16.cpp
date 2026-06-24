#include <stdio.h>
#include <string.h>

#define INF_VAL 999999
#define TOTAL_CITIES 11

// Giữ nguyên danh sách các địa điểm như cũ
char city_names[TOTAL_CITIES][20] = {
    "Ha Noi", 
    "Son Tay", 
    "Thai Nguyen", 
    "Bac Ninh", 
    "Bac Giang",
    "Uong Bi", 
    "Hai Phong", 
    "Hai Duong", 
    "Hung Yen", 
    "Phu Ly", 
    "Hoa Binh"
};

typedef struct {
    int num_vertices;
    int adj_matrix[TOTAL_CITIES][TOTAL_CITIES];
} NavigationGraph;

void init_graph(NavigationGraph *g) {
    int r, c;
    g->num_vertices = TOTAL_CITIES;
    for (r = 0; r < g->num_vertices; r++) {
        for (c = 0; c < g->num_vertices; c++) {
            if (r == c) {
                g->adj_matrix[r][c] = 0;
            } else {
                g->adj_matrix[r][c] = INF_VAL;
            }
        }
    }
}

void add_highway(NavigationGraph *g, int node_a, int node_b) {
    g->adj_matrix[node_a][node_b] = 1; // Khoảng cách mặc định là 1 đơn vị
    g->adj_matrix[node_b][node_a] = 1;
}

void execute_dijkstra(NavigationGraph *g, int src, int dest) {
    int min_dist[TOTAL_CITIES];
    int visited[TOTAL_CITIES];
    int path_parent[TOTAL_CITIES];
    int idx, step;

    for (idx = 0; idx < g->num_vertices; idx++) {
        min_dist[idx] = INF_VAL;
        visited[idx] = 0;
        path_parent[idx] = -1;
    }

    min_dist[src] = 0;

    for (step = 0; step < g->num_vertices - 1; step++) {
        int current_min = INF_VAL;
        int active_node = -1;

        for (idx = 0; idx < g->num_vertices; idx++) {
            if (!visited[idx] && min_dist[idx] < current_min) {
                current_min = min_dist[idx];
                active_node = idx;
            }
        }

        if (active_node == -1) break;

        visited[active_node] = 1;

        for (idx = 0; idx < g->num_vertices; idx++) {
            if (!visited[idx] && g->adj_matrix[active_node][idx] != INF_VAL && min_dist[active_node] != INF_VAL) {
                if (min_dist[active_node] + g->adj_matrix[active_node][idx] < min_dist[idx]) {
                    min_dist[idx] = min_dist[active_node] + g->adj_matrix[active_node][idx];
                    path_parent[idx] = active_node;
                }
            }
        }
    }

    if (min_dist[dest] == INF_VAL) {
        printf("Khong tim thay duong di tu %s den %s\n\n", city_names[src], city_names[dest]);
        return;
    }

    int route_stack[TOTAL_CITIES];
    int node_count = 0;
    int curr = dest;

    while (curr != -1) {
        route_stack[node_count++] = curr;
        curr = path_parent[curr];
    }

    printf("Tuyen duong tu %s den %s:\n", city_names[src], city_names[dest]);
    for (idx = node_count - 1; idx >= 0; idx--) {
        printf("%s", city_names[route_stack[idx]]);
        if (idx > 0) printf(" -> ");
    }
    printf("\nTong so chang phai di: %d\n\n", min_dist[dest]);
}

int main() {
    NavigationGraph map_data;
    init_graph(&map_data);
    
    // Giữ nguyên cấu trúc các cạnh nối cũ
    add_highway(&map_data, 0, 1);
    add_highway(&map_data, 0, 2);
    add_highway(&map_data, 0, 3);
    add_highway(&map_data, 0, 7);
    add_highway(&map_data, 0, 9);
    add_highway(&map_data, 0, 10);

    add_highway(&map_data, 3, 4);
    add_highway(&map_data, 3, 5);
    add_highway(&map_data, 4, 5);
    add_highway(&map_data, 5, 6);
    add_highway(&map_data, 6, 7);
    add_highway(&map_data, 7, 8);
    add_highway(&map_data, 8, 9);
        
    // Thực hiện tìm kiếm đúng các cặp điểm cũ
    execute_dijkstra(&map_data, 0, 6); 
    execute_dijkstra(&map_data, 2, 5); 
    execute_dijkstra(&map_data, 4, 9); 

    return 0;
}