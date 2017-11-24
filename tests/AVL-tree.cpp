#include <catch.hpp>

#include "AVL-tree.hpp"

TEST_CASE("insert", "[root]") 
{
   AVL_tree<int> tree;
   tree.insert(10);
   Node<int> * node = search(10);
   REQUIRE(tree.left_(node) == nullptr);
   REQUIRE(tree.right_(node) == nullptr);
   REQUIRE(trre.parent_(node) == nullptr);
   REQUIRE(tree.key_(node) == 10);
   REQUIRE(tree.height_(node) == 1);
   REQUIRE(tree.count_() == 1);
}



