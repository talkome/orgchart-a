/**
 * Created by talko on 5/12/22.
 */

#pragma once
#include <vector>
#include <string>
#include <queue>
#include <deque>
#include <algorithm>
#include <iterator>
#include "Node.hpp"

using namespace std;

namespace ariel {

    class OrgChart {

    public:
        Node* root;
        deque<string> tree_traversal;

        // Constructor
        OrgChart(){
            this->root = nullptr;
        }

        // Destructor
        ~OrgChart()= default;

        // Print Operator
        friend ostream& operator<<(ostream &out, OrgChart &oc);

        // addition
        OrgChart& add_root(string const &);
        OrgChart& add_sub(string const &, string const &);

        // searching using bfs algorithm
        Node* find_node(string const &) const;

        // Tree Scanner
        void scan_level_order(Node*);
        void scan_reverse_order(Node*);
        void scan_preorder(Node*);

        // Iterator Method
        deque<string>::iterator begin_level_order();
        deque<string>::iterator end_level_order();

        deque<string>::iterator begin_reverse_order();
        deque<string>::iterator reverse_order();

        deque<string>::iterator begin_preorder();
        deque<string>::iterator end_preorder();

    };
}




