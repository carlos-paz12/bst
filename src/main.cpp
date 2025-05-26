#include <chrono>   // chrono::seconds()
#include <cstdlib>  // system()
#include <iostream> // cout
#include <thread>   // this_thread
#include <vector>   // vector

#include "tree.hpp"

using namespace std;
using namespace ds;

template<typename T>
void info(const Tree<T>& tree, const string_view& msg = "", const time_t& time = 0)
{
  if (not msg.empty())
    cout << msg << "\n\n";
  cout << "[NODES] " << tree.count() << " [HEIGHT] " << tree.height() << '\n';
  cout << tree.to_string();
  this_thread::sleep_for(chrono::seconds(time));
  system("clear");
}

int main()
{
  Tree<int> tree;

  // [!] Display initial state of tree.
  info(tree, "Initial tree structure:", 2);

  // [!] Insertion step-by-step with visualization.
  vector<int> values_to_insert{ 50, 25, 75, 15, 30, 60, 80, 10, 20, 26, 34, 55, 70, 79, 92 };
  for (const auto& val : values_to_insert)
  {
    tree.insert(val);
    info(tree, "Inserted \033[31m" + to_string(val) + "\033[0m...", 4);
  }

  // [!] Display intermediary state of tree.
  info(tree, "Tree structure before insertions:", 5);

  // [!] Removal step-by-step with visualization.
  std::vector<int> values_to_remove{ 10, 15, 80, 50 };
  for (const auto& val : values_to_remove)
  {
    tree.remove(val);
    info(tree, "Removed \033[31m" + to_string(val) + "\033[0m...", 4);
  }

  // [!] Display final state of tree.
  info(tree, "Final tree structure:", 8);

  return EXIT_SUCCESS;
}
