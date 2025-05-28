#ifndef TREE_HPP
#define TREE_HPP

#include "degree.hpp"
#include "node.hpp"

#include <iostream>
#include <sstream>
#include <string>
#include <sys/types.h>

namespace ds
{
template<typename T>
class Tree
{
public:
  using size_type = int64_t;
  using TreeNode = Node<T>;
  using TreeNodePtr = TreeNode*;

  Tree() : m_root(nullptr) { }

  Tree(const Tree& other) : m_root(copy(other.m_root)) { }

  Tree& operator=(const Tree& other) {
    if (this != &other) {
      destroy(m_root);
      m_root = copy(other.m_root);
    }
    return *this;
  }

  ~Tree() { destroy(m_root); }

  TreeNodePtr search(const T& value) { return search(m_root, value); }

  void insert(const T& value) { insert(m_root, value); }

  void remove(const T& value) { remove(m_root, value); }

  [[nodiscard]] size_type height() const { return height(m_root); }

  [[nodiscard]] size_type count() const { return count(m_root); }

  void pre_order_lr() { pre_order_lr(m_root); }

  void pre_order_rl() { pre_order_rl(m_root); }

  void in_order_lr() { in_order_lr(m_root); }

  void in_order_rl() { in_order_rl(m_root); }

  void post_order_lr() { post_order_lr(m_root); }

  void post_order_rl() { post_order_rl(m_root); }

  [[nodiscard]] std::string to_string() const { return to_string(m_root, "", false, true); }

private:
  TreeNodePtr m_root;

  TreeNodePtr copy(TreeNodePtr other_root) {
    if (not other_root) {
      return nullptr;
    }
    TreeNodePtr new_root{ new TreeNode(other_root->m_value) };
    new_root->m_left = copy(other_root->m_left);
    new_root->m_right = copy(other_root->m_right);
    return new_root;
  }

  void destroy(TreeNodePtr& node) {
    if (not node) {
      return;
    }
    destroy(node->m_left);
    destroy(node->m_right);
    delete node;
    node = nullptr;
  }

  TreeNodePtr search(const TreeNodePtr& node, const T& value) {
    if (not node) {
      return nullptr;
    }
    if (value == node->m_value) {
      return node;
    }
    if (value < node->m_value) {
      return search(node->m_left, value);
    }
    return search(node->m_right, value);
  }

  void insert(TreeNodePtr& node, const T& value) {
    if (not node) {
      node = new TreeNode(value);
    } else if (value < node->m_value) {
      insert(node->m_left, value);
    } else if (value > node->m_value) {
      insert(node->m_right, value);
    }
  }

  void remove(TreeNodePtr& node, const T& value) {
    if (not node) {
      return;
    }

    if (value < node->m_value) {
      remove(node->m_left, value);
    } else if (value > node->m_value) {
      remove(node->m_right, value);
    } else {
      if (degree(node) == Degree::LEAF) {
        delete node;
        node = nullptr;
      } else if (degree(node) == Degree::UNARY) {
        TreeNodePtr child{ node->m_left ? node->m_left : node->m_right };
        delete node;
        node = child;
      } else {
        /// @todo fix: Backward branch (while loop) is ID-dependent due to variable reference to 'min_right' and may
        /// cause performance degradationclang-tidy(altera-id-dependent-backward-branch)
        TreeNodePtr min_right{ node->m_right };
        while (min_right->m_left) min_right = min_right->m_left;
        node->m_value = min_right->m_value;
        remove(node->m_right, min_right->m_value);
      }
    }
  }

  Degree degree(const TreeNodePtr& node) const {
    if (not node->m_left and not node->m_right) {
      return Degree::LEAF;
    }
    if (node->m_left and node->m_right) {
      return Degree::BINARY;
    }
    return Degree::UNARY;
  }

  [[nodiscard]] size_type height(const TreeNodePtr& node) const {
    if (not node) {
      return -1;
    }
    size_type left{ height(node->m_left) };
    size_type right{ height(node->m_right) };
    return 1 + std::max(left, right);
  }

  [[nodiscard]] size_type count(const TreeNodePtr& node) const {
    if (not node) {
      return 0;
    }
    return 1 + count(node->m_left) + count(node->m_right);
  }

  void pre_order_lr(const TreeNodePtr& node) {
    if (node) {
      std::cout << node->m_value << " ";
      pre_order_lr(node->m_left);
      pre_order_lr(node->m_right);
    }
  }

  void pre_order_rl(const TreeNodePtr& node) {
    if (node) {
      std::cout << node->m_value << " ";
      pre_order_rl(node->m_right);
      pre_order_rl(node->m_left);
    }
  }

  void in_order_lr(const TreeNodePtr& node) {
    if (node) {
      in_order_lr(node->m_left);
      std::cout << node->m_value << " ";
      in_order_lr(node->m_right);
    }
  }

  void in_order_rl(const TreeNodePtr& node) {
    if (node) {
      in_order_rl(node->m_right);
      std::cout << node->m_value << " ";
      in_order_rl(node->m_left);
    }
  }

  void post_order_lr(const TreeNodePtr& node) {
    if (node) {
      post_order_lr(node->m_left);
      post_order_lr(node->m_right);
      std::cout << node->m_value << " ";
    }
  }

  void post_order_rl(const TreeNodePtr& node) {
    if (node) {
      post_order_rl(node->m_right);
      post_order_rl(node->m_left);
      std::cout << node->m_value << " ";
    }
  }

  [[nodiscard]] std::string to_string(const TreeNodePtr& node, std::string prefix, bool is_left, bool is_root) const {
    /*
     * The following function have been provided by:
     * <https://stackoverflow.com/questions/36802354/print-binary-tree-in-a-pretty-way-using-c>
     *
     * And modified as necessary...
     */
    std::ostringstream oss{};

    oss << prefix;
    oss << (is_root ? ".\n└──" : (is_left ? "├──" : "└──"));

    if (node) {
      oss << "\033[32m◉ " << node->m_value << "\033[0m\n";
      oss << to_string(node->m_right, prefix + (is_left ? "│  " : "   "), true, false);
      oss << to_string(node->m_left, prefix + (is_left ? "│  " : "   "), false, false);
    } else {
      oss << "\033[31mx\033[0m\n";
    }

    return oss.str();
  }
};
} // namespace ds

#endif