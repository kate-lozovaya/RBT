#include <catch.hpp>

#include "AVL-tree.hpp"

/*           10            */
TEST_CASE("insert", "[root]") 
{
   AVL_tree<int> tree;
   tree.insert(10);
   Node<int> * node = tree.search(10);
   REQUIRE(tree.left_(node) == nullptr);
   REQUIRE(tree.right_(node) == nullptr);
   REQUIRE(tree.parent_(node) == nullptr);
   REQUIRE(tree.key_(node) == 10);
   REQUIRE(tree.height_(node) == 1);
   REQUIRE(tree.count_() == 1);
}

/*        10             9
         /             /   \       
        9      ->     8     10        
      /
     8                           */
TEST_CASE("insert", "[rotate_right]") 
{
   AVL_tree<int> tree;
   tree.insert(10);
   tree.insert(9);
   tree.insert(8);
   Node<int> * node = tree.search(9);
   REQUIRE(tree.left_(node) == tree.search(8));
   REQUIRE(tree.right_(node) == tree.search(10));
   REQUIRE(tree.parent_(node) == nullptr);
   REQUIRE(tree.key_(node) == 9);
   REQUIRE(tree.height_(node) == 2);
   REQUIRE(tree.parent_(tree.search(8)) == node);
   REQUIRE(tree.parent_(tree.search(10)) == node);
   REQUIRE(tree.height_(tree.search(8)) == 1);
   REQUIRE(tree.height_(tree.search(10)) == 1);
   REQUIRE(tree.count_() == 3);
}
