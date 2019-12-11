#include "huffman.h"
#include <vector>
#include <iostream>
#include <queue>
#include <unordered_map>


using std::vector;

struct HeapNode {
    byte data; 
    long freq; 
    HeapNode *left;
    HeapNode *right;
    byte leafsize = 0; 

    HeapNode(byte data_ = 0, long freq_ = 0, byte leafsize_ = 0, HeapNode *left_ = nullptr, HeapNode *right_ = nullptr)
            : data(data_), freq(freq_), leafsize(leafsize_), left(left_), right(right_) {}
};

void Delete_Tree(HeapNode *tree) {
    if (!tree) return;
    Delete_Tree(tree->left);
    Delete_Tree(tree->right);
    delete tree;
}

struct Compar {
    bool operator()(const HeapNode *left, const HeapNode *right) const {
        return left->freq > right->freq;
    }
};

class BitsWriter {
public:
    void WriteBit(bool bit);
    void WriteByte(byte val);
    vector<byte> GetResult();

private:
    vector<byte> buffer;
    byte accum = 0;
    int bits_count = 0; 
};

void BitsWriter::WriteBit(bool bit) {
    accum |= static_cast<byte>(bit) << (7 - bits_count);
    bits_count++;
    if (bits_count == 8) {
        buffer.push_back(accum);
        bits_count = 0;
        accum = 0;
    }
}

void BitsWriter::WriteByte(byte val) {
    if (bits_count == 0) {
        buffer.push_back(val);
    } 
    else {
        accum |= val >> bits_count;
        buffer.push_back(accum);
        accum = val << (8 - bits_count);
    }
}

vector<byte> BitsWriter::GetResult() {
    if (bits_count != 0) {
        buffer.push_back(accum);
    }
    buffer.push_back(static_cast<byte>(bits_count));
    return buffer;
}

class BitsReader {
public:
    BitsReader(const vector<byte> &buffer_) : buffer(buffer_) {}
    bool ReadBit();
    byte ReadByte();
    long bits_processed() const; 
private:
    const vector<byte> &buffer;
    int bytes_count = 0; 
    int bits_count = 0; 
};

bool BitsReader::ReadBit() {
    bool bit = (buffer[bytes_count] >> (7 - bits_count)) & 1;
    bits_count++;

    if (bits_count == 8) {

        bits_count = 0;
        bytes_count++;
    }
    return bit;
}

byte BitsReader::ReadByte() {
    if (bits_count == 0) {
        return buffer[bytes_count++];
    } 
    else {
        byte accum = 0;
        for (auto i = 0; i < 8; i++) {
            auto bit = ReadBit();
            accum |= static_cast<byte>(bit) << (7 - i);
        }
        return accum;
    }
}

long BitsReader::bits_processed() const {
    return bytes_count * 8 + bits_count;
}

std::pair<HeapNode *, vector<byte> > create_tree(IInputStream &original) {
    //read from file
    //and write to vector
    std::unordered_map<byte, long> counter{};
    vector<byte> file;
    byte val = 0;
    while (original.Read(val)) {
        file.push_back(val);
        counter[val]++;
    }

    std::priority_queue<HeapNode *, vector<HeapNode *>, Compar> heap;
    for (auto &data: counter) {
        auto node = new HeapNode(data.first, data.second, 1);
        heap.push(node);
    }
    if (heap.size() == 1) {
        HeapNode *node1 = heap.top();
        heap.pop();
        auto node = new HeapNode(0, node1->freq, node1->leafsize, node1, nullptr);
        heap.push(node);
    } 
    else {
        while (heap.size() != 1) {
            HeapNode *node1 = heap.top();
            heap.pop();
            HeapNode *node2 = heap.top();
            heap.pop();
            auto node = new HeapNode(0, node1->freq + node2->freq, node1->leafsize + node2->leafsize, node1, node2);
            heap.push(node);
        }
    }

    return std::make_pair(heap.top(), file);
}

void compress(const vector<byte> &input, const vector<byte> &compressed_tree, byte leafsize,
              const std::unordered_map<byte, vector<bool> > &table, IOutputStream &output) {
    BitsWriter bits_writer;

    bits_writer.WriteByte(leafsize); 
    for (size_t i = 1;
         i < compressed_tree.size(); i++) { 
        if (compressed_tree[i] == '0') {
            bits_writer.WriteBit(false);
        } 
        else if (compressed_tree[i] == '1') {
            bits_writer.WriteBit(true);
            i++;
            bits_writer.WriteByte(compressed_tree[i]);
        }
    }

    vector<bool> bits;
    for (auto val: input) {
        bits = table.at(val);
        for (auto bit: bits) {
            bits_writer.WriteBit(bit);
        }
    }
    vector<byte> compressed = bits_writer.GetResult();
    for (auto &data: compressed) {
        output.Write(data);
    }
}

void compress_tree(HeapNode* tree, vector<bool> &route, std::unordered_map<byte, vector<bool> > &table,
                   vector<byte> &compressed_tree) {
    if (!tree->left && !tree->right) {
        table[tree->data] = route;
        compressed_tree.push_back('1');
        compressed_tree.push_back(tree->data);
    } 
    else {
        compressed_tree.push_back('0');
    }
    if (tree->left) {
        route.push_back(false);
        compress_tree(tree->left, route, table, compressed_tree);
    }
    if (tree->right) {
        route.push_back(true);
        compress_tree(tree->right, route, table, compressed_tree);
    }
    route.pop_back();
}

std::pair<std::unordered_map<byte, vector<bool> >, vector<byte> > build_table(HeapNode *tree) {
    vector<bool> route;
    vector<byte> compressed_tree;
    std::unordered_map<byte, vector<bool> > table;
    compress_tree(tree, route, table, compressed_tree);
    return make_pair(table, compressed_tree);
}

vector<byte> read_compressed(IInputStream &compressed) {
    // считываем сжатый файл
    vector<byte> file;
    byte val = 0;
    while (compressed.Read(val)) {
        file.push_back(val);
    }
    return file;
}

vector<byte> decompress(const vector<byte> &file) {
    //decode
    BitsReader bits_reader(file);
    int leafsize = bits_reader.ReadByte();
    leafsize = (leafsize == 0) ? 256 : leafsize;
    int symbols_decoded = 0;
    byte data = 0;
    auto tree = new HeapNode();
    auto node = tree;
    std::stack<HeapNode *> nodes;
    nodes.push(node);
    while (symbols_decoded < leafsize) {
        auto bit = bits_reader.ReadBit();
        HeapNode *new_node;
        if (bit) {
            data = bits_reader.ReadByte();
            symbols_decoded++;
            new_node = new HeapNode(data);
        } 
        else {
            new_node = new HeapNode(0);
            nodes.push(new_node);
        }
        if (!node->left) {
            node->left = new_node;
        } 
        else {
            node->right = new_node;
        }
        if (!bit) {
            node = new_node;
        }
        while ((symbols_decoded < leafsize) && (node->left && node->right)) {
            node = nodes.top();
            nodes.pop();
        }
    }

    vector<byte> decoded;
    node = tree;
    auto last_bits = (file[file.size() - 1] == 0) ? 8 : file[file.size() - 1]; 
    auto bits_to_read = (file.size() - 2) * 8 + last_bits;
    while (bits_reader.bits_processed() < bits_to_read) {
        auto bit = bits_reader.ReadBit();
        node = bit ? node->right : node->left;

        if (!node->left && !node->right) {
            decoded.push_back(node->data);
            node = tree;
        }
    }

    Delete_Tree(tree);
    return decoded;
}

void Encode(IInputStream& original, IOutputStream& compressed) {
    vector<byte> file;
    HeapNode *tree;
    std::tie(tree, file) = create_tree(original);
    vector<byte> compressed_tree;
    std::unordered_map<byte, vector<bool> > table{};
    std::tie(table, compressed_tree) = build_table(tree);
    compress(file, compressed_tree, tree->leafsize, table, compressed);

    Delete_Tree(tree);
}

void Decode(IInputStream& compressed, IOutputStream& original) {
    auto file = read_compressed(compressed);
    auto decoded = decompress(file);
    for (auto val: decoded) {
        original.Write(val);
    }
}


int main() {
    //read and compress
    std::ifstream in_("input/test.txt");
    std::ofstream compress_("input/compressed.txt");

    IInputStream input(in_);
    IOutputStream compr_output(compress_);
    Encode(input, compr_output);

    in_.close();
    compress_.close();

    //decompress and write to output.txt
    std::ifstream compress_out("input/compressed.txt");
    std::ofstream out_("input/output.txt");

    IInputStream compr_input(compress_out);
    IOutputStream output(out_);
    Decode(compr_input, output);

    compress_out.close();
    out_.close();
    return 0;
}
