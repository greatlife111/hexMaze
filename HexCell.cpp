#include "HexCell.h"

#include <iostream>
#include <cmath>

HexCell::HexCell(int Q, int R) {
    path_dist_from_start = 0;
    q = Q;
    r = R;

    for (int i = 0; i < 6; i ++) {
        neighbours[i] = nullptr;
        links[i] = nullptr;
    }
}

void HexCell::link(HexCell* cell) {

    if (cell == nullptr) return;
    if (is_linked(cell)) return;

    if (distance(cell) != 1) return;

    int side = get_neighbour_side(cell);
    links[side] = cell;
    cell->links[(side+3)%6] = this;


}


int HexCell::get_neighbour_side(const HexCell* cell) const {
 
        if (cell != nullptr) {
        int this_s = -q-r;
        int cell_s = -cell->q - cell->r;

        if (cell->q == q) {            
            if (cell->r < r) {
                return N;
            } else {
                return S;
            }
        } else if (cell->r == r) {
            if (cell->q < q) {
                return NW;
            } else {
                return SE;
            }
        } else if (this_s == cell_s) {
            if (cell->q < q) {
                return SW;
            } else {
                return NE;
            }
        }
    }
}



bool HexCell::is_linked(const HexCell* cell) const {
    if (cell != nullptr) {
        if (distance(cell) == 1) {
    
            for (int i = 0; i<6; i++) {
                if (links[i] == cell) return true;
            }
        }
    }
    return false;

}

int HexCell::distance(const HexCell* cell) const {
    if (cell == nullptr) return -1;

    int thisS = -q - r;
    int cellS = -(cell->q) - cell->r;
    
    int max1 = fmax(abs(this->q - cell->q), abs(this->r - cell->r));
    return fmax(max1, abs(thisS - cellS));
}

bool HexCell::is_edge() const {
    for (HexCell* hc : neighbours) {
        if (hc == nullptr) return true;
    }
    return false;
}