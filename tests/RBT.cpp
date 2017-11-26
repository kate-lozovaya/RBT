#include <catch.hpp>

#include "RBT.hpp"

/*           10            */
TEST_CASE("insert1", "[root]") 
{
   Tree<int> tree;
   tree.insert(10);
   Node<int> * node = tree.search(10);
   REQUIRE(tree.left_(node) == nullptr);
   REQUIRE(tree.right_(node) == nullptr);
   REQUIRE(tree.parent_(node) == nullptr);
   REQUIRE(tree.value_(node) == 10);
   REQUIRE(tree.color_(node) == BLACK);
   REQUIRE(tree.count_() == 1);
}

/*        10             9
         /             /   \       
        9      ->     8     10        
      /
     8                           */


/*  8                        9
      \                    /   \       
        9           ->    8     10        
          \
           10                     */


/*        9                9
        /   \     ->     /
       8     10         8        */


/*        9                9
        /   \     ->     /   \
       8     10         7     10    
      /                          
     7                            */


/*        9                10
        /   \     ->     /
       8     10         8        */

