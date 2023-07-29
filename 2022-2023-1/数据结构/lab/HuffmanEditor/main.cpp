#include "common.h"
#include "huffman.h"
#include "bitmap.h"

int main() {
  {
    int n = 27;
    std::unordered_map<unsigned char, int> mp;

    // 优先处理空格的数量
    mp[' '] = 0;
    std::cin >> mp[' '];
    for (int i = 1; i < n; i++) {
      char ch;
      int w;
      std::cin >> ch >> w;
      mp[ch] = w;
    }

    huffman tree;

    tree.createTree(mp);
    tree.createCode();
    tree.saveCodeChar("../testCase/hfmTree");

    tree.encodeText("../testCase/ToBeTran", "../testCase/CodeFile");
    tree.decode("../testCase/CodeFile", "../testCase/TextFile");

    tree.showTree();
  }
  {
    bitmap bmp;
    bmp.loadBmp("../asset/lena.bmp");
    bmp.savePixel();

    huffman tree;

    tree.createTree(bmp.getPixelCnt());
    tree.createCode();
    tree.saveCodeHex("../testCase/bmpHuffmCode");
    tree.encodeBmp("../asset/lena.bmp", "../testCase/bmpCodeFile");
  }

  return 0;
}
