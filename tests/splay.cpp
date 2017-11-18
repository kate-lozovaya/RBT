#include <catch.hpp>

#include "splay.h"

TEST_CASE("insert_root", "[root]") {
   SplayTree<int> testSplayTree;
   testSplayTree.insert(10);
   REQUIRE(testSplayTree.search(10) == 1);
}



