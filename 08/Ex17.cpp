#include <iostream>
#include <vector>
#include <unordered_map>
#include <cstring>
#include <algorithm>
#include <stdexcept>


using std::string;
using std::vector;

struct Node
{  
    int parent;
    char in;   
    int length_ = 0;
    int pat_id = -1;
    int suffix = -1;
    int term_link = -1;
    int go[128];
    Node(int parent_, char in_) : parent(parent_), in(in_) { std::memset(go, -1, sizeof(go));}
};

class AhoKar{

private:
    vector<Node> nodes;
    int known_patterns = 0;
    int go_to(int cur, char s);
    int suffix(int cur);
    int TermLink(int cur);
    template<typename T>
    void process_results(int pos, int cur, T func);

public:
    AhoKar();
    int Add(const string&);
    template<typename T>
    void FindIn(const string&, T func);
};

AhoKar::AhoKar() {
    nodes.emplace_back(0, 0);
};

int AhoKar::Add(const string& str){
    int cur = 0;
    for (auto s : str){
        if (nodes[cur].go[s] < 0){
            nodes.emplace_back(cur, s);
            nodes[cur].go[s] = nodes.size() - 1;
        }
        cur = nodes[cur].go[s];
    }

    if (nodes[cur].length_)
        return nodes[cur].pat_id;
    nodes[cur].length_ = str.length();
    nodes[cur].pat_id = known_patterns;
    return known_patterns++;
}

template<typename T>
void AhoKar::FindIn(const string& str, T func){
    int cur = 0;
    for (int i=0; i < str.length(); i++){
        char c = str[i];
        cur = go_to(cur, c);
        process_results(i, cur, func);
    }
}

int AhoKar::go_to(int cur, char s){
    int next = nodes[cur].go[s];
    if (next >= 0){
        return next;
    }
    else if (cur == 0){
        return cur;
    }
    else {
        return nodes[cur].go[s] = go_to(suffix(cur), s);
    }
}

int AhoKar::suffix(int cur){
    Node &node = nodes[cur];
    if (node.suffix == -1){
        if (cur == 0 || node.parent == 0)
            node.suffix = 0;
        else 
            node.suffix = go_to(suffix(node.parent), node.in);
    }
    return node.suffix;
}

int AhoKar::TermLink(int cur){
    if (cur == 0)
        return 0;
    if (nodes[cur].term_link == -1){
        int linked = suffix(cur);
        if (linked == 0 || nodes[linked].length_){
            nodes[cur].term_link = linked;
        }
        else {
            nodes[cur].term_link = TermLink(linked);
        }
    }
    return nodes[cur].term_link;
}

template<typename T>
void AhoKar::process_results(int pos, int cur, T func){
    if (!nodes[cur].length_){
        cur = TermLink(cur);
    }
    while (cur != 0){
        func(nodes[cur].pat_id, pos - nodes[cur].length_ + 1);
        cur = TermLink(cur);
    }
}


vector<int> Find(const string &pattern, const string &text){
    vector<int> result;
    int cur = 0;

    while (cur < pattern.length() && pattern[cur] == '?'){
        cur++;
    }
    if (cur == pattern.length()){
        for (int i = 0; i < static_cast<int>(text.length()) - cur + 1; i++)
            result.push_back(i);
        return result;
    }

    AhoKar MyTrie;
    std::unordered_map<int, vector<int>> offset;
    int total_parts=0;

    while (cur < pattern.length()){
        int start = cur;

        while (cur < pattern.length() && pattern[cur] != '?')
            cur++;

        int pattern_id = MyTrie.Add(pattern.substr(start, cur - start));
        offset[pattern_id].push_back(start);
        total_parts++;
        while (cur < pattern.length() && pattern[cur] == '?')
            cur++;
    }

    std::vector<int> pos(text.length());

    MyTrie.FindIn(text, [&pos, &offset](int id, int o){  // id - parent id, o - offset
        for (int i : offset[id]){
            if (o - i >= 0 && o - i < pos.size())
                pos[o - i]++;
        }
    });

    for (int i=0; i+pattern.size() <= pos.size(); i++){
        if (pos[i] == total_parts)
            result.push_back(i);
    }
    return result;
}

int main(){
    string pattern;
    string text;
    std::cin >> pattern;
    std::cin >> text;
    const std::vector<int> res = Find(pattern, text);
    for (auto i:res)
        std::cout << i << " ";
    std::cout << std::endl;
}
