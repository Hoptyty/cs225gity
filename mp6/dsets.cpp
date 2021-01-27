/* Your code here! */
#include "dsets.h"
#include <stdlib.h>

void DisjointSets::addelements(int num) {
    up_trees.insert(up_trees.end(), num, -1);
}

int DisjointSets::find(int elem) {
    if (up_trees[elem] < 0)
        return elem;
    up_trees[elem] = find(up_trees[elem]);
    return up_trees[elem];
    //return find(up_trees[elem]);
}

void DisjointSets::setunion(int a, int b) {
    int a_root = find(a);
    int b_root = find(b);
    int new_size = up_trees[a_root] + up_trees[b_root]; 

    if (up_trees[a_root] > up_trees[b_root]) {
        up_trees[a_root] = b_root;
        up_trees[b_root] = new_size;
    }
    else {
        up_trees[b_root] = a_root;
        up_trees[a_root] = new_size;
    }
}

int DisjointSets::size(int elem) {
    return abs(up_trees[find(elem)]);
}
