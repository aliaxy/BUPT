#include "hash_table.h"

int main() {
  std::ifstream fin("../in.txt", std::ios::in);
  if (!fin.is_open()) {
    std::cerr << "open file failed\n";
    return 0;
  }
  hash_table<int, int, std::hash<int>, std::identity, std::equal_to<int>> ht(50, std::hash<int>(),
                                                                             std::equal_to<int>());

  int n;
  fin >> n;
  for (int i = 0, x; i < n; i++) {
    fin >> x;
    ht.insert(x);
  }
  fin.close();
  /* 控制台输入 */
  int x;
  while (std::cin >> x, x != -1) {
    auto starttime = std::chrono::system_clock::now();
    auto curr = ht.find(x);
    std::chrono::duration<double> diff = std::chrono::system_clock::now() - starttime;
    if (curr.first != nullptr) {
      std::cout << x << " exists.\n";
    } else {
      std::cout << x << " not exists.\n";
    }
    std::cout << "Compare times: " << curr.second << '\n';
    std::cout << "Use time: " << std::fixed << std::setprecision(8) << diff.count() << "s\n\n";
  }
  ht.clear();
  return 0;
}
