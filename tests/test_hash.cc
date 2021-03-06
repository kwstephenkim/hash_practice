#include <gtest/gtest.h>

#include "custom_hash.h"

TEST(HashTable, ConsAndDestructors) {
  {
    HashTable table(10);
  }
  EXPECT_TRUE(true) << "HashTable(10) failed";
  {
    HashTable table(1);
  }
  EXPECT_TRUE(true) << "HashTable(1) failed";
  {
    HashTable table(1000000);
  }
  EXPECT_TRUE(true) << "HashTable(1000000) failed";

}

TEST(HashTable, Insert) {
  {
    HashTable table;
    EXPECT_EQ(table.Size(), 0);
    table.Insert(5, "Apple");
    EXPECT_EQ(table.Size(), 1);
    table.Insert(44, "Orange");
    EXPECT_EQ(table.Size(), 2);
    table.Insert(32, "Pineapple");
    EXPECT_EQ(table.Size(), 3);
  }
  EXPECT_TRUE(true);
}

TEST(HashTable, Find) {
    HashTable table(10);
    EXPECT_EQ(table.Size(), 0);
    table.Insert(5, "Apple");
    EXPECT_EQ(table.Size(), 1);
    table.Insert(45, "Orange");
    EXPECT_EQ(table.Size(), 2);
    table.Insert(35, "Pineapple");
    EXPECT_EQ(table.Size(), 3);
    auto n = table.Find(35);
    EXPECT_TRUE(n);
    if (n) {
      EXPECT_EQ(n->key_, 35);
      EXPECT_EQ(n->value_, "Pineapple");
    }
    EXPECT_FALSE(table.Find(55));
    EXPECT_FALSE(table.Find(12));
}

#define InsertConflictTest() \
HashTable table(10);                            \
EXPECT_EQ(table.Size(), 0);                     \
table.Insert(5, "Apple");                       \
EXPECT_EQ(table.Size(), 1);                     \
table.Insert(45, "Orange");                     \
EXPECT_EQ(table.Size(), 2);                     \
table.Insert(35, "Pineapple");                  \
EXPECT_EQ(table.Size(), 3);                     \
table.Insert(35, "Dragon Fruit");               \
EXPECT_EQ(table.Size(), 3);                     \
table.Insert(22, "Cantalope");                  \
EXPECT_EQ(table.Size(), 4);                     \
table.Insert(25, "Cantalope");                  \
EXPECT_EQ(table.Size(), 5);                     \
table.Insert(75, "Cantalope");                  \
EXPECT_EQ(table.Size(), 6);                     \


TEST(HashTable, InsertConflict) {
  {
    InsertConflictTest();
  }
  EXPECT_TRUE(true);
}

TEST(HashTable, Remove) {
  InsertConflictTest();
  EXPECT_TRUE(table.Find(5));
  table.Remove(5);
  EXPECT_FALSE(table.Find(5));

  EXPECT_FALSE(table.Find(85));
  EXPECT_FALSE(table.Remove(85));
  EXPECT_FALSE(table.Find(85));

  EXPECT_TRUE(table.Find(35));
  table.Remove(35);
  EXPECT_FALSE(table.Find(35));

  EXPECT_TRUE(table.Find(75));
  table.Remove(75);
  EXPECT_FALSE(table.Find(75));

  EXPECT_EQ(table.Size(), 3);
}
