#include "common.h"
#include "RBTree.h"

int main() {
  std::ifstream fin("../test/in.txt", std::ios::in);
  std::ofstream fout("../test/out.txt", std::ios::out);

  if (!fin.is_open()) {
    std::cerr << "open file failed\n";
    return 0;
  }

  RBTree<int> rb;

  int n, m;
  fin >> n >> m;
  for (int i = 0, x; i < n; i++) {
    fin >> x;
    rb.insert(x);
  }

  while (m--) {
    int x;
    fin >> x;
    auto starttime = std::chrono::system_clock::now();
    std::pair<RBTNode<int>*, int> curr = rb.find(x);
    std::chrono::duration<double> diff = std::chrono::system_clock::now() - starttime;
    if (curr.first != nullptr) {
      fout << x << " exists.\n";
    } else {
      fout << x << " not exists.\n";
    }
    fout << "Compare times: " << curr.second << '\n';
    fout << "Use time: " << std::fixed << std::setprecision(8) << diff.count() << "s\n\n";
  }

  rb.inOrderPrint();
  std::cout << rb.blackNodeNum();

  fin.close();
  fout.close();
  return 0;
}
