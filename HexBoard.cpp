#include "HexBoard.h"

#include <iostream>

#include "queue.h"
#include "stack.h"

HexBoard::HexBoard(int radius) {
    this->radius = radius; 
    longest_path_dist = 0;
    start_coord = {0,0};
    create_board();
    configure_cells();


}

void HexBoard::create_board() {   

    HexCell * center = new HexCell(0,0);
    for (int q = -radius+1; q<=radius-1; q++) {
        for (int r = -radius+1; r <=radius-1; r++) {
            // HexCell * newhc = new HexCell(q,r);
            if (HexCell(q,r).distance(center) <= radius - 1) {
                cells[{q,r}] = new HexCell(q,r);
            } 
            // newhc = NULL;   
        }
    }
    delete center;
    center = NULL;
}

void HexBoard::configure_cells() {

    if (radius == 1) return;

    for (auto kv : cells) {               // use auto to avoid writing down the expicit type of the iterator
        pair<int, int> coord = kv.first;  // kv.first gets the key
        HexCell* cell = kv.second;        // kv.second gets the value


        vector<pair<int, int>> neighbour_coords = get_neigh_coords(coord);

        for (int i = 0; i < 6; i++) {
            if (cells.find(neighbour_coords[i]) != cells.end()) {
                cells[coord]->neighbours[i] = cells[neighbour_coords[i]];

            }
        }
    }
}

void HexBoard::generate_maze(pair<int, int> start_coord, double branch_prob) {
    Stack<pair<int,int>> mazeStack;    
    mazeStack.push(start_coord);
    this->start_coord = start_coord;
    map<pair<int, int>, bool> visited;

    visited[start_coord] = true;

    while (!mazeStack.isEmpty()) {
        HexCell * curr_cell = cells[mazeStack.peek()];
        HexCell * neigh_cell = chooseNeighbour(curr_cell, visited, branch_prob);

        if (neigh_cell != nullptr) {
            curr_cell->link(neigh_cell);
            visited[{neigh_cell->q, neigh_cell->r}] = true;
            neigh_cell->path_dist_from_start = curr_cell->path_dist_from_start + 1;

            if (neigh_cell->path_dist_from_start > longest_path_dist) {
                longest_path_dist = neigh_cell->path_dist_from_start;
            }
            if (cells[end_coord]->path_dist_from_start < neigh_cell->path_dist_from_start) {
                if (neigh_cell->is_edge()) {
                    end_coord = {neigh_cell->q, neigh_cell->r}; 
                }          
            }
            mazeStack.push({neigh_cell->q, neigh_cell->r});

        } else {
            mazeStack.pop();
        }
    }    

}

void HexBoard::solve_maze() {
    Quack<pair<int, int>> mazeStack;    // solution
    mazeStack.pushR(start_coord);

    map<pair<int, int>, bool> visited;
    visited[start_coord] = true;

    HexCell * curr_cell = cells[start_coord];

    while (curr_cell != cells[end_coord]) {
        curr_cell = cells[mazeStack.peekR()];
        HexCell * next = chooseNeighbour(curr_cell,visited,0.5);

        if (next != nullptr) {
            if (curr_cell->is_linked(next)) {
                visited[{next->q, next->r}] = true;
                mazeStack.pushR({next->q, next->r});
            }
        } else {
            mazeStack.popR();
        }
    }

    while (!mazeStack.isEmpty()) {
        solution.push_back(mazeStack.popL());
    }

    solution.push_back(end_coord);

}
