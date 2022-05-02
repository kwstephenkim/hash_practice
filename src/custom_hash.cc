#include "custom_hash.h"

HashTable::HashTable(const int bucket_size)
  : size_(0), bucket_size_(bucket_size) {
  buckets_ = std::shared_ptr<std::shared_ptr<Node>[]>(new NodePtr[bucket_size_]);
}

HashTable::~HashTable() {
  for (int i = 0; i < bucket_size_; i++) {
    DeepDisconnect(buckets_[i]);
  }
  size_ = 0;
}

void HashTable::Insert(const int k, const Value& v) {
  NodePtr node = Find(k);
  if (node) {
    node->value_ = v;
    return;
  }
  node = std::make_shared<Node>(k, v);
  auto& bucket = buckets_[HashCode(k)];
  size_++;
  if (!bucket) {
    bucket = node;
    return;
  }
  node->next_ = bucket;
  bucket = node;
  return;
}

HashTable::NodePtr HashTable::Find(const int key) {
  return FindImpl(buckets_[HashCode(key)], key);
}

HashTable::NodePtr HashTable::FindImpl(NodePtr node, const int key) {
  if (!node || node->key_ == key) {
    return node;
  }
  return FindImpl(node->next_, key);
}

void HashTable::DeepDisconnect(NodePtr node) {
  if (!node) return;
  DeepDisconnect(node->next_);
  node->next_ = nullptr;
  return;
}

bool HashTable::Remove(const int k) {
  auto node = Find(k);
  if (!node) return false;
  auto& bucket = buckets_[HashCode(k)];
  bucket = RemoveImpl(bucket, node);
  size_--;
  return true;
}

HashTable::NodePtr HashTable::RemoveImpl(NodePtr head, NodePtr node) {
  if (!node) return head;

  if (head == node) {
    auto new_head = head->next_;
    head->next_ = nullptr;
    return new_head;
  }
  auto new_list = RemoveImpl(head->next_, node);
  head->next_ = new_list;
  return head;
}
