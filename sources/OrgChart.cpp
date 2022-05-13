/**
 * Created by talko on 5/12/22.
 */

#include "OrgChart.hpp"

using namespace std;

ariel::OrgChart &ariel::OrgChart::add_root(string const &item) {
    if (nullptr != root) {
        Node *new_head = new Node(item);
        new_head->sons.push_back(*root);
        root = new_head;
    } else {
        this->root = new Node(item);
    }

    return *this;
}

ariel::OrgChart &ariel::OrgChart::add_sub(string const &boss_name, string const &sub_name) {
    Node* boss = find_node(boss_name);
    Node *sub = new Node(sub_name);
    boss->sons.push_back(*sub);
    return *this;

}

Node *ariel::OrgChart::find_node(string const &item) const {
    Node* curr;
    deque<Node*> search_queue;
    search_queue.push_back(this->root);
    while(!search_queue.empty()){
        curr = search_queue.front();
        if (!(curr->name == item)) {
            for (auto &son: curr->sons) {
                search_queue.push_back(&son);
            }
            search_queue.pop_front();
        } else {
            return curr;
        }
    }

    throw invalid_argument("this item is not in the graph");
}

// print operator
ostream& ariel::operator<<(ostream& out, ariel::OrgChart& oc) {
    for (auto it = oc.begin_preorder(); it != oc.end_preorder(); ++it) {
        out << (*it);
    }
   return out;
}

// Tree Scanner
void ariel::OrgChart::scan_level_order(Node *curr) {
    for (auto & son : curr->sons) {
        this->tree_traversal.push_back(son.name);
    }
    for (auto & son : curr->sons) {
        scan_level_order(&son);
    }
}

void ariel::OrgChart::scan_reverse_order(Node *curr) {
    for (int i = curr->sons.size(); i > 0; i--) {
        this->tree_traversal.push_front(curr->sons[i].name);
    }
    for (int i = curr->sons.size(); i > 0; i--) {
        scan_preorder(&curr->sons[i-1]);
    }
}

void ariel::OrgChart::scan_preorder(Node *curr) {
    for (auto & son : curr->sons) {
        this->tree_traversal.push_back(son.name);
        scan_preorder(&son);
    }
}

// iterator
deque<string>::iterator ariel::OrgChart::begin_level_order() {
    this->tree_traversal.clear();
    this->tree_traversal.push_back(this->root->name);
    scan_level_order(this->root);
    return this->tree_traversal.begin();
}

deque<string>::iterator ariel::OrgChart::end_level_order() {
    return this->tree_traversal.end();
}

deque<string>::iterator ariel::OrgChart::begin_reverse_order() {
    this->tree_traversal.clear();
    this->tree_traversal.push_back(this->root->name);
    scan_reverse_order(this->root);
    return this->tree_traversal.begin();
}

deque<string>::iterator ariel::OrgChart::reverse_order() {
    return this->tree_traversal.end();
}

deque<string>::iterator ariel::OrgChart::begin_preorder() {
    this->tree_traversal.clear();
    this->tree_traversal.push_back(this->root->name);
    scan_preorder(this->root);
    return this->tree_traversal.begin();
}

deque<string>::iterator ariel::OrgChart::end_preorder() {
    return this->tree_traversal.end();
}