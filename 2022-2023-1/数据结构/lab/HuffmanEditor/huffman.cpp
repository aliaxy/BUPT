//
// Created by aruve on 2022/11/13.
//

#include "huffman.h"

huffman::huffman() : root(nullptr) {}

huffman::~huffman() {
  this->keys.clear();
  std::queue<TNode *> qu;
  qu.push(root);
  while (!qu.empty()) {
    TNode *curr = qu.front();
    qu.pop();
    if (curr->left) {
      qu.push(curr->left);
    }
    if (curr->right) {
      qu.push(curr->right);
    }
    delete curr;
  }
  this->root = nullptr;
}

void huffman::createTree(const std::unordered_map<unsigned char, int> &src) {
  std::priority_queue<TNode *, std::vector<TNode *>, cmp> qu;
  for (auto &[ch, w] : src) {
    TNode *curr = new TNode(w, ch);
    qu.push(curr);
  }
  while (qu.size() > 1) {
    TNode *x = qu.top();
    qu.pop();
    TNode *y = qu.top();
    qu.pop();
    TNode *z = new TNode(x, y);
    qu.push(z);
  }
  this->root = qu.top();
}

void huffman::createCode() {
  _createCode(this->root, "");
}

void huffman::_createCode(TNode *root, std::string key) {
  if (root->left == nullptr && root->right == nullptr) {
    this->keys[root->ch] = key;
    return;
  }
  _createCode(root->left, key + "0");
  _createCode(root->right, key + "1");
}

void huffman::saveCodeChar(std::string dest) {
  std::ofstream fout;
  fout.open(dest, std::ios::out);
  for (auto &[ch, key] : keys) {
    fout << ch << ": " << key << '\n';
  }
  fout.close();
}

void huffman::saveCodeHex(std::string dest) {
  std::ofstream fout;
  fout.open(dest, std::ios::out);
  for (auto &[ch, key] : keys) {
    fout << std::hex << std::setfill('0') << std::setw(2) << (unsigned int) ch << ": " << key << '\n';
  }
  fout.close();
}

void huffman::encodeBmp(std::string src, std::string dest) {
  std::ifstream fin;
  std::ofstream fout;
  fin.open(src, std::ios::binary), fout.open(dest, std::ios::binary);

  if (!fin.is_open()) {
    std::cerr << "cannot open the file\n";
  }
  unsigned char buf[16];
  for (int i = 0; i < 0x43; i++) {
    fin.read((char *) buf, sizeof(buf));
    for (int j = 0; j < 0x10; j++) {
      fout << std::hex << std::setfill('0') << std::setw(2) << (unsigned int) buf[j] << ' ';
    }
    fout << '\n';
  }
  fin.read((char *) buf, sizeof(buf));
  for (int i = 0; i < 6; i++) {
    fout << std::hex << std::setfill('0') << std::setw(2) << (unsigned int) buf[i] << ' ';
  }
  for (int i = 6; i < 0x10; i++) {
    fout << this->keys[buf[i]] << ' ';
  }
  fout << '\n';

  while (fin.read((char *) buf, sizeof(buf))) {
    for (int i = 0; i < 0x10; i++) {
      fout << this->keys[buf[i]] << ' ';
    }
    fout << '\n';
  }
  fin.close(), fout.close();
}

void huffman::encodeText(std::string src, std::string dest) {
  std::ifstream fin;
  std::ofstream fout;
  fin.open(src, std::ios::in), fout.open(dest, std::ios::out);

  if (!fin.is_open()) {
    std::cerr << "cannot open the file\n";
  }
  char buf[1021] = {0};
  while (fin.getline(buf, sizeof(buf))) {
    int i = 0;
    while (buf[i] != '\n' && buf[i] != '\0') {
      fout << this->keys[buf[i]];
      i++;
    }
    fout << '\n';
  }

  fin.close(), fout.close();
}

void huffman::decode(std::string src, std::string dest) {
  std::ifstream fin;
  std::ofstream fout;
  fin.open(src, std::ios::in), fout.open(dest, std::ios::out);

  if (!fin.is_open()) {
    std::cout << "cannot open the file\n";
  }
  char buf[1021] = {0};
  while (fin.getline(buf, sizeof(buf))) {
    int i = 0;
    while (buf[i] != '\n' && buf[i] != '\0') {
      TNode *cur = this->root;
      while (cur->left && cur->right) {
        if (buf[i] == '0') {
          cur = cur->left;
        } else {
          cur = cur->right;
        }
        i++;
      }
      fout << cur->ch;
    }
    fout << '\n';
  }

  fin.close(), fout.close();
}

void huffman::showTree() {
  _showTree(this->root, 0);
}

void huffman::_showTree(TNode *root, int n) {
  if (root == nullptr) {
    return;
  }

  _showTree(root->right, n + 1);

  for (int i = 0; i < n; i++) {
    std::cout << '\t';
  }

  if (root->left == nullptr && root->right == nullptr) {
    std::printf("%03d(%c)\n", root->w, root->ch);
  } else {
    std::printf("%03d\n", root->w);
  }

  _showTree(root->left, n + 1);
}