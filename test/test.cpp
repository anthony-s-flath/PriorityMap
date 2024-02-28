#include <iostream>
#include <vector>
#include <cstring>
#include "PriorityMap.h"

using namespace std;

class Instance {
public:
    vector<string> label;
    string element;
};

string label1 = "one";
string label2 = "two";
string label3 = "three";
vector<Instance> test = {
    {{label1, label2, label3}, "1 2 3"}, // 0
    {{label1, label3, label2}, "1 3 2"}, // 1
    {{label3, label2, label1}, "3 2 1"}, // 2
    {{label3, label1, label2}, "3 1 2"}, // 3
    {{label2, label3, label1}, "2 3 1"}, // 4
    {{label2, label1, label3}, "2 1 3"}, // 5
    {{label1, label2}, "1 2"}, // 6
    {{label1, label3}, "1 3"}, // 7
    {{label2, label1}, "2 1"}, // 8
    {{label2, label3}, "2 3"}, // 9
    {{label3, label1}, "3 1"}, // 10
    {{label3, label2}, "3 2"}, // 11
    {{label1}, "1"},  // 12
    {{label2}, "2"}, // 13
    {{label3}, "3"}, // 14
    {{label1, label1}, "1 1"}, // 15
    {{label2, label2}, "2 2"}, // 16
    {{label3, label3}, "3 3"}, // 17
    {{label1, label2, label3}, "1 2 1"}, // 18
    {{label1, label2, label3}, "1 2 2"}, // 19
};

void print(bool verbose, string message) {
    if (verbose) {
        cout << message << endl;
    }
}
void print(bool verbose, string message, int expected, int actual) {
    if (expected != actual) {
        cout << "FAIL ";
        cout << message << endl;
        cout << "\tExpected: " << expected << endl;
        cout << "\tActual:   " << actual << endl;
    } else if (verbose) {
        cout << "SUCCESS: ";
        cout << message << endl;
        cout << "\tExpected: " << expected << endl;
        cout << "\tActual:   " << actual << endl;
    }
}
void print(bool verbose, string message, string expected, string actual) {
    if (expected != actual) {
        cout << "FAIL ";
        cout << message << endl;
        cout << "\tExpected: " << expected << endl;
        cout << "\tActual:   " << actual << endl;
    } else if (verbose) {
        cout << "SUCCESS: ";
        cout << message << endl;
        cout << "\tExpected: " << expected << endl;
        cout << "\tActual:   " << actual << endl;
    }
}
string to_print(vector<string> message) {
    string to_return = "{ ";
    for (size_t i = 0; i != message.size(); ++i) {
        to_return += message[i];

        if (i != message.size() - 1)
            to_return += ", ";
    }
    to_return += " }";
    return to_return;
}
void print(bool verbose, string message, vector<string> expected, vector<string> actual) {
    if (expected != actual) {
        cout << "FAIL ";
        cout << message << endl;
        cout << "\tExpected: " << to_print(expected) << endl;
        cout << "\tActual:   " << to_print(actual) << endl;
    } else if (verbose) {
        cout << "SUCCESS: ";
        cout << message << endl;
        cout << "\tExpected: " << to_print(expected) << endl;
        cout << "\tActual:   " << to_print(actual) << endl;
    }
}
void print(bool verbose, string message, bool expected, bool actual) {
    if (expected != actual) {
        cout << "FAIL ";
        cout << message << endl;
        cout << "\tExpected: " << expected << endl;
        cout << "\tActual:   " << actual << endl;
    } else if (verbose) {
        cout << "SUCCESS: ";
        cout << message << endl;
        cout << "\tExpected: " << expected << endl;
        cout << "\tActual:   " << actual << endl;
    }
}


void push(bool v) {
    vector<Instance> push_test = {
        {{"1", "2", "3"}, "dup"}, // same
        {{"1", "2", "3"}, "dup"}, // same
        {{"1", "2", "5"}, "different label"},
        {{"1", "2", "3"}, "different elmt"},
        {{"1", "2", "3"}, "a"},
    };

    Instance empty_label = {{}, "empty"};
    Instance empty_elmt = {{"not", "empty"}, ""};
    Instance empty_instance = {{}, ""};

    PriorityMap<string, string> pmap;
    
    pmap.push(push_test[0].label, push_test[0].element);
    pmap.push(push_test[0].label, push_test[0].element);
    print(v, "1: push(): duplicate pushes", 2, pmap.size());
    pmap.clear();
    
    pmap.push(push_test[2].label, push_test[2].element);
    pmap.push(push_test[3].label, push_test[3].element);
    print(v, "2: push(): different pushes", 2, pmap.size());
    pmap.clear();
    
    pmap.push(empty_label.label, empty_label.element);
    print(v, "3: push(): empty label", 0, pmap.size());
    pmap.clear();
    
    pmap.push(empty_elmt.label, empty_elmt.element);
    print(v, "4: push(): empty element", 1, pmap.size());
    pmap.clear();

    pmap.push(empty_instance.label, empty_instance.element);
    print(v, "5: push(): empty instance", 0, pmap.size());
    pmap.clear();
}

void clear(bool v) {
    vector<Instance> clear_test = {
        {{"1", "2", "3"}, "dup"}, 
        {{"1", "2", "3"}, "dup"}, 
        {{"1", "2", "5"}, "different label"},
        {{"1", "2", "3"}, "different elmt"},
        {{"as", "2", "3"}, "a"}, // 4
    };

    Instance empty_label = {{}, "empty"};
    Instance empty_elmt = {{"not", "empty"}, ""};
    Instance empty_instance = {{}, ""};

    PriorityMap<string, string> pmap;
    
    pmap.push(clear_test[0].label, clear_test[0].element);
    pmap.push(clear_test[0].label, clear_test[0].element);
    pmap.clear();
    print(v, "1: clear(): duplicate pushes", 0, pmap.size());
    
    pmap.push(clear_test[0].label, clear_test[0].element);
    pmap.push(clear_test[0].label, clear_test[0].element);
    pmap.push(clear_test[4].label, clear_test[4].element);
    pmap.clear();
    pmap.clear();
    print(v, "2: clear(): double clear", 0, pmap.size());

    
    pmap.clear();
    pmap.push(clear_test[0].label, clear_test[0].element);
    print(v, "3: clear(): clear before push", 1, pmap.size());
    pmap.clear();

    
    pmap.clear();
    print(v, "1: clear(): empty clear", 0, pmap.size());
}

void contains(bool v) {
    PriorityMap<string, string> pmap;
    
    pmap.push(test[0].label, test[0].element);
    print(v, "1: contains(): same label", true, pmap.contains(test[0].label));
    pmap.clear();
    
    pmap.push(test[0].label, test[0].element);
    print(v, "2: contains(): smaller label", true, pmap.contains(test[6].label));
    pmap.clear();

    pmap.push(test[6].label, test[6].element);
    print(v, "3: contains(): bigger label", false, pmap.contains(test[0].label));
    pmap.clear();

    pmap.push(test[0].label, test[0].element);
    print(v, "4: contains(): mixed label", false, pmap.contains(test[1].label));
    pmap.clear();

    pmap.push(test[12].label, test[12].element);
    print(v, "5: contains(): duplicate label", false, pmap.contains(test[15].label));
    pmap.clear();

    pmap.push(test[6].label, test[6].element);
    print(v, "6: contains(): reversed label", false, pmap.contains(test[8].label));
    pmap.clear();

    pmap.push(test[17].label, test[17].element);
    print(v, "7: contains(): wrong earlier label", false, pmap.contains(test[7].label));
    pmap.clear();

    pmap.push(test[8].label, test[8].element);
    print(v, "8: contains(): wrong earlier label different size", false, pmap.contains(test[12].label));
    pmap.clear();
    
    pmap.push(test[0].label, test[0].element);
    pmap.push(test[6].label, test[6].element);
    print(v, "9: contains(): same label after shorter push", true, pmap.contains(test[0].label));
    pmap.clear();
}

void iterator_memory(bool v) {
    PriorityMap<string, string> pmap;
    
    auto itr1 = pmap.begin();
    print(v, "1: iterator_memory(): not saving begin()", true, pmap.begin() == pmap.begin());
    
    itr1 = pmap.begin();
    print(v, "SUCCESS: 2. iterator_memory(): itr reassigned");

    pmap.push(test[3].label, test[3].element);
    pmap.push(test[10].label, test[10].element);
    pmap.push(test[12].label, test[12].element);
    pmap.push(test[0].label, test[0].element);
    print(v, "SUCCESS: 3. iterator_memory(): push after itr reassigned");
    itr1 = pmap.begin();
    print(v, "SUCCESS: 4. iterator_memory(): itr reassigned after push");

    auto itr2 = itr1;
    print(v, "SUCCESS: 5. iterator_memory(): assigning itr to itr");


    pmap.clear();
    print(v, "SUCCESS: 6. iterator_memory(): clear");

    pmap.push(test[12].label, test[12].element);
    ++itr1;
    print(v, "SUCCESS: 7. iterator_memory(): itr++");

    itr2 = itr1;
    print(v, "SUCCESS: 8. iterator_memory(): itr = itr after operation++");

    ++itr1;
    print(v, "SUCCESS: 9. iterator_memory():  operation++ after itr = itr");

    print(v, "10: iterator_memory(): itr != ++itr", true, itr1 != itr2);
}

void iterator_functs(bool v) {
    PriorityMap<string, string> pmap;
    
    auto itr = pmap.begin();
    print(v, "1: iterator_functs(): itr == itr", true, itr == itr);
    print(v, "2: iterator_functs(): itr != itr", false, itr != itr);
    print(v, "3: iterator_functs(): begin() == begin()", true, pmap.begin() == pmap.begin());
    print(v, "4: iterator_functs(): begin() != begin()", false, pmap.begin() != pmap.begin());
    print(v, "5: iterator_functs(): end() == end()", true, pmap.end() == pmap.end());
    print(v, "6: iterator_functs(): end() != end()", false, pmap.end() != pmap.end());
    print(v, "7: iterator_functs(): empty, begin() == end()", true, pmap.begin() == pmap.end());
    print(v, "8: iterator_functs(): empty, end() == begin()", true, pmap.end() == pmap.begin());
    print(v, "9: iterator_functs(): empty, begin() != end()", false, pmap.begin() != pmap.end());
    print(v, "10: iterator_functs(): empty, end() != begin()", false, pmap.end() != pmap.begin());



    pmap.push(test[0].label, test[0].element);
    itr = pmap.begin();
    print(v, "11: iterator_functs(): one element, begin() == end()", false, pmap.begin() == pmap.end());
    print(v, "12: iterator_functs(): one element, itr == end()", false, itr == pmap.end());
    print(v, "13: iterator_functs(): one element, itr == begin()", true, itr == pmap.begin());
    print(v, "14: iterator_functs(): one element, itr == itr", true, itr == itr);

    print(v, "15: iterator_functs(): element == *itr", test[0].element, *itr);
}

void iterator_loops(bool v) {
    PriorityMap<string, string> pmap;

    int actual = 0;
    int expected = 1;

    pmap.push(test[12].label, test[12].element);
    auto itr = pmap.begin();
    auto end = pmap.end();
    ++itr;
    bool equal = itr == end;
    print(v, "1: iterator_loops(): ++itr == end", true, equal);
    
    actual = 0;
    expected = 1;
    for (auto it = pmap.begin(); it != pmap.end(); ++it) {
        ++actual;
    }
    print(v, "2: iterator_loops(): one elmt for loop", expected, actual);
    pmap.clear();

    pmap.push(test[12].label, test[12].element);
    pmap.push(test[12].label, test[12].element);
    pmap.push(test[3].label, test[3].element);
    pmap.push(test[10].label, test[10].element);
    pmap.push(test[3].label, test[3].element);
    actual = 0;
    expected = 5;
    for (auto it = pmap.begin(); it != pmap.end(); ++it) {
        ++actual;
    }
    print(v, "3: iterator_loops(): five elmt for loop", expected, actual);
    pmap.clear();

    

    pmap.push(test[12].label, test[12].element);
    pmap.push(test[18].label, test[18].element);
    pmap.push(test[3].label, test[3].element);
    pmap.push(test[10].label, test[10].element);
    pmap.push(test[3].label, test[3].element);
    pmap.push(test[13].label, test[13].element);
    pmap.push(test[13].label, test[13].element);
    actual = 0;
    expected = 7;
    for (auto it = pmap.begin(); it != pmap.end(); ++it) {
        ++actual;
    }
    print(v, "4: iterator_loops(): 7 elmt for loop", expected, actual);
    pmap.clear();

    

    vector<int> actual_v(test.size(), 1); // going to push one duplicate
    size_t dup_index = 9;
    ++actual_v[dup_index];
    for (size_t i = 0; i < test.size(); ++i) {
        pmap.push(test[i].label, test[i].element);
    }
    pmap.push(test[dup_index].label, test[dup_index].element);   
    for (auto it = pmap.begin(); it != pmap.end(); ++it) {
        for (size_t i = 0; i < test.size(); ++i) {
            if (*it == test[i].element) {
                --actual_v[i];
            }
        }
    }
    bool good = true;
    for (size_t i = 0; i < actual_v.size(); ++i) {
        if (actual_v[i] != 0) {
            good = false;
            break;
        }
    }
    print(v, "5: iterator_loops(): expected counts by operator*", true, good);
    pmap.clear();


    vector<int> actual_v2(test.size(), 0); // going to push one duplicate
    for (size_t i = 0; i < test.size(); ++i) {
        for (size_t j = 0; j < i % 3; ++j) {
            pmap.push(test[i].label, test[i].element);
            ++actual_v[i];
        }
    }  
    for (auto it = pmap.begin(); it != pmap.end(); ++it) {
        for (size_t i = 0; i < test.size(); ++i) {
            if (*it == test[i].element) {
                --actual_v[i];
            }
        }
    }
    good = true;
    for (size_t i = 0; i < actual_v.size(); ++i) {
        if (actual_v[i] != 0) {
            good = false;
            break;
        }
    }
    print(v, "6: iterator_loops(): random(ish) expected counts by operator*", true, good);
    pmap.clear();

    
    // label1
    vector<string> vlabel1 = {label1};
    pmap.push(test[12].label, test[12].element);
    pmap.push(test[1].label, test[1].element);
    pmap.push(test[14].label, test[14].element);
    pmap.push(test[0].label, test[0].element);
    pmap.push(test[9].label, test[9].element);
    pmap.push(test[1].label, test[1].element);
    pmap.push(test[6].label, test[6].element);
    actual = 0;
    expected = 5;
    for (auto it = pmap.begin(vlabel1); it != pmap.end(vlabel1); ++it) {
        ++actual;
    }
    print(v, "7: iterator_loops(): begin(vector)", expected, actual);
    pmap.clear();

    
    vector<string> vlabel2 = {label3};
    pmap.push(test[12].label, test[12].element); // 1
    pmap.push(test[1].label, test[1].element); // 1 3 2
    pmap.push(test[0].label, test[0].element); // 1 2 3
    pmap.push(test[9].label, test[9].element); // 2 3
    pmap.push(test[1].label, test[1].element); // 1 3 2
    pmap.push(test[6].label, test[6].element); // 1 2
    actual = 0;
    expected = 0;
    for (auto it = pmap.begin(vlabel2); it != pmap.end(vlabel2); ++it) {
        ++actual;
    }
    print(v, "8: iterator_loops(): begin(vector) no actual", expected, actual);
    pmap.clear();

    
    vector<string> vlabel3 = {label1, label2};
    pmap.push(test[12].label, test[12].element); // 1
    pmap.push(test[1].label, test[1].element); // 1 3 2
    pmap.push(test[0].label, test[0].element); // 1 2 3
    pmap.push(test[9].label, test[9].element); // 2 3
    pmap.push(test[1].label, test[1].element); // 1 3 2
    pmap.push(test[6].label, test[6].element); // 1 2
    pmap.push(test[10].label, test[10].element); // 3 1
    pmap.push(test[8].label, test[8].element); // 2 1
    pmap.push(test[18].label, test[18].element); // 1 2 1
    actual = 0;
    expected = 3;
    for (auto it = pmap.begin(vlabel3); it != pmap.end(vlabel3); ++it) {
        ++actual;
    }
    print(v, "9: iterator_loops(): begin(vector), vector.size() == 2", expected, actual);
    pmap.clear();
}

void iterator_assignment(bool v) {
    PriorityMap<string, string> pmap;

    pmap.push(test[12].label, test[12].element);
    pmap.push(test[12].label, test[12].element);
    pmap.push(test[3].label, test[3].element);
    pmap.push(test[10].label, test[10].element);
    pmap.push(test[3].label, test[3].element);
    int actual = 0;
    int expected = 3;
    auto itr = pmap.begin();
    for (size_t i = 0; i < 2; ++i)
        ++itr;
    auto itr2 = itr;
    bool same = true;
    for (; itr2 != pmap.end() && itr != pmap.end(); ++itr, ++itr2) {
        if (*itr != *itr2)
            same = false;
        ++actual;
    }
    print(v, "1: iterator_assignment(): same itr amount", expected, actual);
    print(v, "2: iterator_assignment(): same itr element", true, same);
    pmap.clear();
}

void iterator_gets(bool v) {
    PriorityMap<string, string> pmap;

    
    pmap.push(test[0].label, test[0].element);
    print(v, "1: iterator_gets(): same label", test[0].label, pmap.begin().get_key());
    pmap.clear();
    
    vector<string> vlabel = {label1, label2};
    pmap.push(test[12].label, test[12].element); // 1
    pmap.push(test[1].label, test[1].element); // 1 3 2
    pmap.push(test[6].label, test[6].element); // 1 2
    pmap.push(test[0].label, test[0].element); // 1 2 3
    pmap.push(test[9].label, test[9].element); // 2 3
    pmap.push(test[1].label, test[1].element); // 1 3 2
    pmap.push(test[6].label, test[6].element); // 1 2
    pmap.push(test[10].label, test[10].element); // 3 1
    pmap.push(test[8].label, test[8].element); // 2 1
    pmap.push(test[18].label, test[18].element); // 1 2 1
    int actual = 0;
    int expected = 2;
    for (auto it = pmap.begin(); it != pmap.end(); ++it) {
        if (it.get_key() == vlabel)
            ++actual;
    }
    print(v, "2: iterator_gets(): vector.size() == 2", expected, actual);
    pmap.clear();
}


int main(int argc, char** argv) {
    bool verbose = false;
    if (argc == 2 && (strcmp(argv[1], "-v") == 0 || strcmp(argv[1], "--verbose") == 0)) {
        verbose = true;
    }

    clear(verbose);
    contains(verbose);
    iterator_memory(verbose);
    iterator_functs(verbose);
    iterator_loops(verbose);
    iterator_gets(verbose);
    return 0;
}