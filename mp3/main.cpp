#include "List.h"

int main() {
    List<int> list;
    for (int i = 1; i <= 9; i++) {
        list.insertFront(i);
    }
    list.reverse();
    List<int> list2;
    for (int i = 16; i >= 1; i--) {
        list2.insertFront(i);
    }
    list2.waterfall();
    cout << list2 << endl;
    list2.sort();
    cout << list2 << endl;
  return 0;
}
