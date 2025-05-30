#ifndef TREE_HPP
#define TREE_HPP

#include "degree.hpp"
#include "node.hpp"

#include <iostream>
#include <ostream>
#include <sstream>
#include <string>

namespace ds
{
template<typename T>
class BinarySearchTree
{
public:
  using value_type = T;
  using size_type = long long;
  using node = Node<value_type>;
  using node_ptr = node*;

private:
  node_ptr m_root; //!< Pointer to the root node of the tree.

public:
  /// @brief Default constructor.
  BinarySearchTree() : m_root(nullptr) { }

  /// @brief Copy constructor.
  BinarySearchTree(const BinarySearchTree& other) : m_root(copy(other.m_root)) { }

  /// @brief Move constructor.
  BinarySearchTree(const BinarySearchTree&& other) noexcept : m_root(other.m_root) { other.m_root = nullptr; }

  /// @brief Copy assignment operator.
  BinarySearchTree& operator=(const BinarySearchTree& other)
  {
    if (this != &other)
    {
      destroy(m_root);
      m_root = copy(other.m_root);
    }
    return *this;
  }

  /// @brief Move assignment operator.
  BinarySearchTree& operator=(BinarySearchTree&& other) noexcept
  {
    if (this != &other)
    {
      destroy(m_root);
      m_root = other.m_root;
      other.m_root = nullptr;
    }
    return *this;
  }

  /// @brief Destructor.
  ~BinarySearchTree() { destroy(m_root); }

  /**
   * @brief Searches for a node containing the given value.
   *
   * Traverses the binary search tree to locate the node whose value matches `_target_`.
   *
   * @param _target_ The value to search for.
   *
   * @return A reference to the pointer to the node containing the target value,
   *         or a null pointer reference if the value is not found.
   */
  [[nodiscard]] node_ptr& find(const value_type& _target_) { return find(m_root, _target_); }

  /**
   * @brief Inserts a value into the tree.
   *
   * Attempts to insert `_target_` into the binary search tree. If the value already
   * exists in the tree, the insertion is not performed.
   *
   * @param _target_ The value to insert.
   *
   * @return `true` if the value was inserted successfully, `false` if it already exists.
   */
  [[nodiscard]] bool insert(const value_type _target_) { return insert(m_root, _target_); }

  /**
   * @brief Removes a value from the tree.
   *
   * Attempts to remove the node with the value `_target_` from the binary search tree.
   *
   * @param _target_ The value to remove.
   *
   * @return `true` if the value was found and removed, `false` otherwise.
   */
  [[nodiscard]] bool remove(const value_type& _target_, const bool recursively = false)
  {
    if (recursively) return kill(m_root, _target_);
    return remove(m_root, _target_);
  }

  /**
   * @brief Checks whether the tree is empty.
   *
   * @return `true` if the container is empty, `false` otherwise.
   */
  [[nodiscard]] bool empty() const { return (not m_root); }

  /**
   * @brief Calculate the height of tree (0-indexed).
   *
   * @return The height of the tree (0-indexed) or `-1` if the tree is empty.
   */
  [[nodiscard]] size_type height() const { return height(m_root); }

  /**
   * @brief Calculate the number of nodes in the tree.
   *
   * @return The number of nodes in the tree or `0` if the tree is empty.
   */
  [[nodiscard]] size_type size() const { return size(m_root); }

  /**
   * @brief Displays the tree using pre-order traversal (left-to-right).
   *
   * Visits the root node first, followed by the left subtree, then the right subtree.
   * The values are printed to the standard output.
   */
  void pre_order_lr() { display_pre_order_lr(m_root); }

  /**
   * @brief Displays the tree using pre-order traversal (right-to-left).
   *
   * Visits the root node first, followed by the right subtree, then the left subtree.
   * The values are printed to the standard output.
   */
  void pre_order_rl() { display_pre_order_rl(m_root); }

  /**
   * @brief Displays the tree using in-order traversal (left-to-right).
   *
   * Visits the left subtree first, followed by the root node, then the right subtree.
   * The values are printed to the standard output in ascending order if the tree is a valid BST.
   */
  void in_order_lr() { display_in_order_lr(m_root); }

  /**
   * @brief Displays the tree using in-order traversal (right-to-left).
   *
   * Visits the right subtree first, followed by the root node, then the left subtree.
   * The values are printed to the standard output in descending order if the tree is a valid BST.
   */
  void in_order_rl() { display_in_order_rl(m_root); }

  /**
   * @brief Displays the tree using post-order traversal (left-to-right).
   *
   * Visits the left subtree first, then the right subtree, and finally the root node.
   * The values are printed to the standard output.
   */
  void post_order_lr() { display_post_order_lr(m_root); }

  /**
   * @brief Displays the tree using post-order traversal (right-to-left).
   *
   * Visits the right subtree first, then the left subtree, and finally the root node.
   * The values are printed to the standard output.
   */
  void post_order_rl() { display_post_order_rl(m_root); }

  /**
   * @brief Returns a string representation of the tree structure.
   *
   * Produces a visual layout of the tree using Unicode characters to illustrate the hierarchy.
   *
   * @return A formatted string representing the tree's structure.
   */
  [[nodiscard]] std::string to_string() const { return to_string(m_root, "", false, true); }

private:
  /// @brief Creates a deep copy of the subtree rooted at _node_.
  node_ptr copy(const node_ptr& _node_)
  {
    if (not _node_) return nullptr;

    // [!] Allocates and builds a new node with the same value.
    node_ptr new_root = new node(_node_->m_value);

    // [!] Recursively copies the left and right children
    new_root->m_left = copy(_node_->m_left);
    new_root->m_right = copy(_node_->m_right);

    return new_root;
  }

  /// @brief Recursively destroy the subtree rooted at _node_.
  void destroy(node_ptr& _node_)
  {
    if (not _node_) return;

    destroy(_node_->m_left);
    destroy(_node_->m_right);

    // [!] Destroys the value stored in the node and frees the allocated memory.
    delete _node_;

    _node_ = nullptr;
  }

  [[nodiscard]] node_ptr& find(node_ptr& _node_, const value_type& _target_)
  {
    if (not _node_) return _node_;

    if (_target_ == _node_->m_value)
      return _node_;
    else if (_target_ < _node_->m_value)
      return find(_node_->m_left, _target_);
    else
      return find(_node_->m_right, _target_);
  }

  [[nodiscard]] bool insert(node_ptr& _node_, const value_type _target_)
  {
    if (not _node_)
    {
      _node_ = new node(_target_);
      return true;
    }
    else if (_target_ < _node_->m_value)
    {
      return insert(_node_->m_left, _target_);
    }
    else if (_target_ > _node_->m_value)
    {
      return insert(_node_->m_right, _target_);
    }
    else
    {
      return false;
    }
  }

  [[nodiscard]] bool remove(node_ptr& _node_, const value_type& _target_)
  {
    if (not _node_) return false;

    if (_target_ < _node_->m_value)
    {
      return remove(_node_->m_left, _target_);
    }
    else if (_target_ > _node_->m_value)
    {
      return remove(_node_->m_right, _target_);
    }
    else
    {
      if (degree(_node_) == Degree::LEAF)
      {
        delete _node_;
        _node_ = nullptr;
      }
      else if (degree(_node_) == Degree::UNARY)
      {
        node_ptr child{ _node_->m_left ? _node_->m_left : _node_->m_right };
        delete _node_;
        _node_ = child;
      }
      else
      {
        node_ptr min_in_right{ _node_->m_right };
        while (min_in_right->m_left) min_in_right = min_in_right->m_left;
        _node_->m_value = min_in_right->m_value;
        return remove(_node_->m_right, min_in_right->m_value);
      }
    }
    return true;
  }

  [[nodiscard]] bool kill(node_ptr& _node_, const value_type& _target_)
  {
    if (not _node_) return false;
    if (_node_->m_value == _target_)
    {
      if (_node_->m_left) kill(_node_->m_left, _node_->m_left->m_value);
      if (_node_->m_right) kill(_node_->m_right, _node_->m_right->m_value);
      remove(_node_, _target_);
      return true;
    }
    return (kill(_node_->m_left, _node_->m_left->m_value) or kill(_node_->m_right, _node_->m_right->m_value));
  }

  Degree degree(const node_ptr& _node_) const
  {
    if (not _node_->m_left and not _node_->m_right)
      return Degree::LEAF;
    else if (_node_->m_left and _node_->m_right)
      return Degree::BINARY;
    else
      return Degree::UNARY;
  }

  [[nodiscard]] size_type height(const node_ptr& _node_) const
  {
    if (not _node_) return -1;

    const size_type height_left{ height(_node_->m_left) };
    const size_type height_right{ height(_node_->m_right) };

    return 1 + std::max(height_left, height_right);
  }

  [[nodiscard]] size_type size(const node_ptr& _node_) const
  {
    if (not _node_) return 0;
    return (1 + size(_node_->m_left) + size(_node_->m_right));
  }

  void display_pre_order_lr(const node_ptr& _node_)
  {
    if (_node_)
    {
      std::cout << _node_->m_value << " ";
      display_pre_order_lr(_node_->m_left);
      display_pre_order_lr(_node_->m_right);
    }
  }

  void display_pre_order_rl(const node_ptr& _node_)
  {
    if (_node_)
    {
      std::cout << _node_->m_value << " ";
      display_pre_order_rl(_node_->m_right);
      display_pre_order_rl(_node_->m_left);
    }
  }

  void display_in_order_lr(const node_ptr& _node_)
  {
    if (_node_)
    {
      display_in_order_lr(_node_->m_left);
      std::cout << _node_->m_value << " ";
      display_in_order_lr(_node_->m_right);
    }
  }

  void display_in_order_rl(const node_ptr& _node_)
  {
    if (_node_)
    {
      display_in_order_rl(_node_->m_right);
      std::cout << _node_->m_value << " ";
      display_in_order_rl(_node_->m_left);
    }
  }

  void display_post_order_lr(const node_ptr& _node_)
  {
    if (_node_)
    {
      display_post_order_lr(_node_->m_left);
      display_post_order_lr(_node_->m_right);
      std::cout << _node_->m_value << " ";
    }
  }

  void display_post_order_rl(const node_ptr& _node_)
  {
    if (_node_)
    {
      display_post_order_rl(_node_->m_right);
      display_post_order_rl(_node_->m_left);
      std::cout << _node_->m_value << " ";
    }
  }

  [[nodiscard]] std::string to_string(const node_ptr& _node_, std::string prefix, bool is_left, bool is_root) const
  {
    /*
     * The following function have been provided by:
     * <https://stackoverflow.com/questions/36802354/print-binary-tree-in-a-pretty-way-using-c>
     *
     * And modified as necessary...
     */
    std::ostringstream oss{};

    oss << prefix;
    oss << (is_root ? ".\n└──" : (is_left ? "├──" : "└──"));

    if (_node_)
    {
      oss << "\033[32m◉ " << _node_->m_value << "\033[0m\n";
      oss << to_string(_node_->m_right, prefix + (is_left ? "│  " : "   "), true, false);
      oss << to_string(_node_->m_left, prefix + (is_left ? "│  " : "   "), false, false);
    }
    else
    {
      oss << "\033[31mx\033[0m\n";
    }

    return oss.str();
  }
};
} // namespace ds

#endif
