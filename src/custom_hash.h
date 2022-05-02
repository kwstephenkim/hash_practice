// started at 11:13 am

#pragma once

#include <memory>
#include <string>

class HashTable {
public:
  using Value = std::string;
  struct Node {
    Node(const int k, const Value& v)
      : key_(k), value_(v) {}
    int key_;
    Value value_;
    std::shared_ptr<Node> next_;
  };
  using NodePtr = std::shared_ptr<struct Node>;

  HashTable(const int bucket_size = 30);
  ~HashTable();

  void Insert(const int k, const Value& v);
  bool Remove(const int k);
  NodePtr Find(const int key);
  const auto Size() const {
    return size_;
  }


private:
  int size_;
  int bucket_size_;
  std::shared_ptr<NodePtr[]> buckets_;

  const int HashCode(const int key) const {
    return key % bucket_size_;
  }
  NodePtr FindImpl(NodePtr node, const int k);
  void DeepDisconnect(NodePtr node);
  // delete node from the list starting at "head"
  // then, returns the new head of the list
  // the new head could be still "head" or
  // head->next if head == node
  NodePtr RemoveImpl(NodePtr head, NodePtr node);
};


