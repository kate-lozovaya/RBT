#include <catch.hpp>

#include "RBT.hpp"

/*           10 B          */
TEST_CASE("insert1", "[root]") 
{
   Tree<int> tree;
   tree.insert(10);
   REQUIRE(tree.left_(10) == nullptr);
   REQUIRE(tree.right_(10) == nullptr);
   REQUIRE(tree.parent_(10) == nullptr);
   REQUIRE(tree.color_(10) == BLACK);
   REQUIRE(tree.root_() == tree.search(10));
   REQUIRE(tree.count_() == 1);
}

/*        10 B            
        /    \               
      9 R     12 R          
                              */
TEST_CASE("insert2", "[black parent]") 
{
   Tree<int> tree;
   tree.insert(10);
   tree.insert(9);
   tree.insert(12);
   REQUIRE(tree.left_(10) == tree.search(9));
   REQUIRE(tree.right_(10) == tree.search(12));
   REQUIRE(tree.parent_(10) == nullptr);
   REQUIRE(tree.parent_(9) == tree.search(10));
   REQUIRE(tree.parent_(12) == tree.search(10));
   REQUIRE(tree.color_(9) == RED);
   REQUIRE(tree.color_(10) == BLACK);
   REQUIRE(tree.color_(12) == RED);
   REQUIRE(tree.root_() == tree.search(10));
   REQUIRE(tree.count_() == 3);
}

/*        10 B                  10 B
        /    \                /     \
      7 R     12 R   ->     7 B      12 B
        \                     \
          9 R                   9 R          */
TEST_CASE("insert3", "[red parent, red uncle]") 
{
   Tree<int> tree;
   tree.insert(10);
   tree.insert(7);
   tree.insert(12);
   tree.insert(9);
   REQUIRE(tree.left_(7) == nullptr);
   REQUIRE(tree.right_(7) == tree.search(9));
   REQUIRE(tree.left_(10) == tree.search(7));
   REQUIRE(tree.right_(10) == tree.search(12));
   REQUIRE(tree.parent_(10) == nullptr);
   REQUIRE(tree.parent_(7) == tree.search(10));
   REQUIRE(tree.parent_(9) == tree.search(7));
   REQUIRE(tree.parent_(12) == tree.search(10));
   REQUIRE(tree.color_(7) == BLACK);
   REQUIRE(tree.color_(9) == RED);
   REQUIRE(tree.color_(10) == BLACK);
   REQUIRE(tree.color_(12) == BLACK);
   REQUIRE(tree.root_() == tree.search(10));
   REQUIRE(tree.count_() == 4);
}

/*        10 B                  10 B
        /    \                /     \
      7 B     12 B   ->     8 B      12 B
        \                  /   \
          9 R             7 R   9 R
         /                    
        8 R                   
                                              */
TEST_CASE("insert4", "[red parent, black uncle || !uncle (turn right, turn left)]") 
{
   Tree<int> tree;
   tree.insert(10);
   tree.insert(7);
   tree.insert(12);
   tree.insert(9);
   tree.insert(8);
   REQUIRE(tree.left_(8) == tree.search(7));
   REQUIRE(tree.right_(8) == tree.search(9));
   REQUIRE(tree.left_(10) == tree.search(8));
   REQUIRE(tree.right_(10) == tree.search(12));
   REQUIRE(tree.left_(12) == nullptr);
   REQUIRE(tree.right_(12) == nullptr);
   REQUIRE(tree.parent_(10) == nullptr);
   REQUIRE(tree.parent_(7) == tree.search(8));
   REQUIRE(tree.parent_(8) == tree.search(10));
   REQUIRE(tree.parent_(9) == tree.search(8));
   REQUIRE(tree.parent_(12) == tree.search(10));
   REQUIRE(tree.color_(7) == RED);
   REQUIRE(tree.color_(8) == BLACK);
   REQUIRE(tree.color_(9) == RED);
   REQUIRE(tree.color_(10) == BLACK);
   REQUIRE(tree.color_(12) == BLACK);
   REQUIRE(tree.root_() == tree.search(10));
   REQUIRE(tree.count_() == 5);
}

/*        10 B                  10 B
        /    \                /     \
      7 B     12 B   ->     8 B      12 B
        \                  /   \
          8 R             7 R   9 R
            \                   
             9 R                   
                                              */
TEST_CASE("insert5", "[red parent, black uncle || !uncle (turn left)]") 
{
   Tree<int> tree;
   tree.insert(10);
   tree.insert(7);
   tree.insert(12);
   tree.insert(8);
   tree.insert(9);
   REQUIRE(tree.left_(8) == tree.search(7));
   REQUIRE(tree.right_(8) == tree.search(9));
   REQUIRE(tree.left_(10) == tree.search(8));
   REQUIRE(tree.right_(10) == tree.search(12));
   REQUIRE(tree.parent_(10) == nullptr);
   REQUIRE(tree.parent_(7) == tree.search(8));
   REQUIRE(tree.parent_(8) == tree.search(10));
   REQUIRE(tree.parent_(9) == tree.search(8));
   REQUIRE(tree.parent_(12) == tree.search(10));
   REQUIRE(tree.color_(7) == RED);
   REQUIRE(tree.color_(8) == BLACK);
   REQUIRE(tree.color_(9) == RED);
   REQUIRE(tree.color_(10) == BLACK);
   REQUIRE(tree.color_(12) == BLACK);
   REQUIRE(tree.root_() == tree.search(10));
   REQUIRE(tree.count_() == 5);
}

/*        10 B                  10 B
        /    \                /     \
      7 B     13 B   ->     7 B      12 B
             /                      /   \
          11 R                    11 R   13 R
            \                   
             12 R                   
                                              */
TEST_CASE("insert6", "[red parent, black uncle || !uncle (turn left, turn right)]") 
{
   Tree<int> tree;
   tree.insert(10);
   tree.insert(7);
   tree.insert(13);
   tree.insert(11);
   tree.insert(12);
   REQUIRE(tree.left_(10) == tree.search(7));
   REQUIRE(tree.right_(10) == tree.search(12));
   REQUIRE(tree.left_(12) == tree.search(11));
   REQUIRE(tree.right_(12) == tree.search(13));
   REQUIRE(tree.parent_(10) == nullptr);
   REQUIRE(tree.parent_(7) == tree.search(10));
   REQUIRE(tree.parent_(11) == tree.search(12));
   REQUIRE(tree.parent_(12) == tree.search(10));
   REQUIRE(tree.parent_(13) == tree.search(12));
   REQUIRE(tree.color_(7) == BLACK);
   REQUIRE(tree.color_(10) == BLACK);
   REQUIRE(tree.color_(11) == RED);
   REQUIRE(tree.color_(12) == BLACK);
   REQUIRE(tree.color_(13) == RED);
   REQUIRE(tree.root_() == tree.search(10));
   REQUIRE(tree.count_() == 5);
}

/*        10 B                  10 B
        /    \                /     \
      7 B     13 B   ->     7 B      12 B
             /                      /   \
          12 R                    11 R   13 R
         /                     
        11 R                   
                                              */
TEST_CASE("insert7", "[red parent, black uncle || !uncle (turn right)]") 
{
   Tree<int> tree;
   tree.insert(10);
   tree.insert(7);
   tree.insert(13);
   tree.insert(12);
   tree.insert(11);
   REQUIRE(tree.left_(10) == tree.search(7));
   REQUIRE(tree.right_(10) == tree.search(12));
   REQUIRE(tree.left_(12) == tree.search(11));
   REQUIRE(tree.right_(12) == tree.search(13));
   REQUIRE(tree.parent_(10) == nullptr);
   REQUIRE(tree.parent_(7) == tree.search(10));
   REQUIRE(tree.parent_(11) == tree.search(12));
   REQUIRE(tree.parent_(12) == tree.search(10));
   REQUIRE(tree.parent_(13) == tree.search(12));
   REQUIRE(tree.color_(7) == BLACK);
   REQUIRE(tree.color_(10) == BLACK);
   REQUIRE(tree.color_(11) == RED);
   REQUIRE(tree.color_(12) == BLACK);
   REQUIRE(tree.color_(13) == RED);
   REQUIRE(tree.root_() == tree.search(10));
   REQUIRE(tree.count_() == 5);
}

/*           10 B
           /     \
         7 B      12 B
                 /   \
               11 R   13 R      */
/*TEST_CASE("delete1", "[]") 
{
   Tree<int> tree;
   tree.insert(10);
   tree.insert(7);
   tree.insert(13);
   tree.insert(12);
   tree.insert(11);
   tree.deleteEl(15);
   REQUIRE(tree.left_(10) == tree.search(7));
   REQUIRE(tree.right_(10) == tree.search(12));
   REQUIRE(tree.left_(12) == tree.search(11));
   REQUIRE(tree.right_(12) == tree.search(13));
   REQUIRE(tree.parent_(10) == nullptr);
   REQUIRE(tree.parent_(7) == tree.search(10));
   REQUIRE(tree.parent_(11) == tree.search(12));
   REQUIRE(tree.parent_(12) == tree.search(10));
   REQUIRE(tree.parent_(13) == tree.search(12));
   REQUIRE(tree.color_(7) == BLACK);
   REQUIRE(tree.color_(10) == BLACK);
   REQUIRE(tree.color_(11) == RED);
   REQUIRE(tree.color_(12) == BLACK);
   REQUIRE(tree.color_(13) == RED);
   REQUIRE(tree.root_() == tree.search(10));
   REQUIRE(tree.count_() == 5);
}*/

/*           10 B                         11 B
           /     \                      /     \
         7 B      13 R          ->    7 B      13 R 
                 /   \                        /   \
               12 B   14 B                  12 B   14 B 
              /             
            11 R                                              */
/*TEST_CASE("delete2", "[root]") 
{
   Tree<int> tree;
   tree.insert(10);
   tree.insert(7);
   tree.insert(14);
   tree.insert(12);
   tree.insert(13);
   tree.insert(11);
   tree.deleteEl(10);
   REQUIRE(tree.left_(11) == tree.search(7));
   REQUIRE(tree.right_(11) == tree.search(13));
   REQUIRE(tree.left_(13) == tree.search(12));
   REQUIRE(tree.right_(13) == tree.search(14));
   REQUIRE(tree.parent_(11) == nullptr);
   REQUIRE(tree.parent_(7) == tree.search(11));
   REQUIRE(tree.parent_(13) == tree.search(11));
   REQUIRE(tree.parent_(12) == tree.search(13));
   REQUIRE(tree.parent_(14) == tree.search(13));
   REQUIRE(tree.color_(7) == BLACK);
   REQUIRE(tree.color_(11) == BLACK);
   REQUIRE(tree.color_(12) == BLACK);
   REQUIRE(tree.color_(13) == RED);
   REQUIRE(tree.color_(14) == BLACK);
   REQUIRE(tree.root_() == tree.search(11));
   REQUIRE(tree.count_() == 5);
}*/
