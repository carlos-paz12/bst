#include <chrono>
#include <cstdlib>
#include <iostream>
#include <string_view>
#include <thread>
#include <vector>

#include "tree.hpp"

#ifdef _WIN32
#define CLEAR_COMMAND "cls"
#else
#define CLEAR_COMMAND "clear"
#endif

template<typename T>
void info(const ds::BinarySearchTree<T>& tree, const std::string_view& msg = "", unsigned long wait_seconds = 0)
{
  if (not msg.empty()) std::cout << msg << "\n\n";

  std::cout << "Tree:\n";
  std::cout << "Size (# nodes) -> " << tree.size() << '\n';
  std::cout << "Height -> " << tree.height() << '\n';
  std::cout << tree.to_string();

  std::this_thread::sleep_for(std::chrono::seconds(wait_seconds));
  system(CLEAR_COMMAND); // std::cout << "\033[2J\033[1;1H";
}

int main()
{
  ds::BinarySearchTree<int> tree;

  info(tree, "Initial tree structure:", 2);

  std::vector<int> values_to_insert{ 50, 25, 75, 15, 30, 60, 80, 10, 20, 26, 34, 55, 70, 79, 92 };
  for (const auto& val : values_to_insert)
  {
    if (not tree.insert(val)) break;
    info(tree, "Inserted \033[31m" + std::to_string(val) + "\033[0m...", 4);
  }

  info(tree, "Tree structure before removals:", 5);

  std::vector<int> values_to_remove{ 10, 15, 80, 50 };
  for (const auto& val : values_to_remove)
  {
    (void)tree.remove(val);
    info(tree, "Removed \033[31m" + std::to_string(val) + "\033[0m...", 4);
  }

  info(tree, "Final tree structure:", 8);

  return EXIT_SUCCESS;
}
