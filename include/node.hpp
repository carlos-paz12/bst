#ifndef NODE_HPP
#define NODE_HPP

namespace ds
{
template<typename T>
struct Node
{
  T m_value{};
  Node<T>* m_left{};
  Node<T>* m_right{};

  explicit Node(const T& value = T(), Node<T>* left = nullptr, Node<T>* right = nullptr)
  : m_value(value), m_left(left), m_right(right) { }
};
} // namespace ds

#endif