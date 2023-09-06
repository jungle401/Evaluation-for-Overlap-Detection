#include <iostream>
#include <fstream>
#include <vector>
#include <set>
#include <fmt/format.h>
#include <cassert>
using namespace std;
using vii = vector<pair<int, int>>;
int main() {
  auto fin = ifstream{"./scere_fps.ovl"};
  auto r1s = set<int>();
  auto str = string();
  auto amt_lim = 200;
  auto fout = ofstream{fmt::format("./scere_fp_h{}.ovl", amt_lim)};
  assert(fout.is_open());
  auto amt_inc = 0;
  while (getline(fin, str, ',')) {
    auto r1 = stoi(str);
    if (r1s.contains(r1)) {
      getline(fin, str);
    } else {
      r1s.insert(r1);
      getline(fin, str);
      auto r2 = stoi(str);
      fout << r1 << ',' << r2 << endl;
      if (amt_inc++ > amt_lim) {
        break;
      }
    }
  }
}
