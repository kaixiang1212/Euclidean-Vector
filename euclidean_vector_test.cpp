// Copyright [2019] <Kai Xiang Yong>
/*

  == Explanation and rational of testing ==

  I have tested many valid and invalid operation such that my
  program would produce the right behaviour omitting some redundant
  test case.

*/
#define CATCH_CONFIG_MAIN
#include <sstream>

#include "assignments/ev/euclidean_vector.h"
#include "catch.h"

// #include "euclidean_vector.h"

SCENARIO("Creation of unit vectors") {
  WHEN("You have two identical vectors") {
    EuclideanVector a{2};
    a[0] = 1;
    a[1] = 2;
    EuclideanVector b{2};
    b[0] = 1;
    b[1] = 2;
    THEN("Get their unit vectors") {
      EuclideanVector c{a.CreateUnitVector()};
      EuclideanVector d{b.CreateUnitVector()};
      REQUIRE(c == d);
    }
  }
}

SCENARIO("Accessing dimension that doesn't exist") {
  WHEN("You try to split an empty string") {
    EuclideanVector a{2};
    a[0] = 1;
    a[1] = 2;
    THEN("You get a single empty result") {
      std::stringstream ss;
      ss << "Index 2 is not valid for this EuclideanVector object";
      CHECK_THROWS(a.at(2), ss.str());
    }
  }
}

SCENARIO("Operation between two vectors with different dimension") {
  GIVEN("You have two vectors with different dimension") {
    EuclideanVector a{2};
    EuclideanVector b{4};
    THEN("You get a exception") {
      CHECK_THROWS(a += b, "Dimensions of LHS(4) and RHS(2) do not match\n");
      CHECK_THROWS(a + b, "Dimensions of LHS(2) and RHS(4) do not match\n");
      CHECK_THROWS(a -= b, "Dimensions of LHS(2) and RHS(4) do not match\n");
      CHECK_THROWS(a - b, "Dimensions of LHS(2) and RHS(4) do not match\n");
    }
  }
}

SCENARIO("Vector divided by 0") {
  GIVEN("You have a vector") {
    EuclideanVector a{4};
    std::stringstream ss;
    ss << "You get a exception when you try to divide by 0";
    THEN(ss.str()) { CHECK_THROWS(a / 0, ""); }
  }
}

SCENARIO("two vectors same dimension") {
  GIVEN("You have two vectors with same dimension") {
    EuclideanVector a{2};
    a[0] = 5;
    a[1] = 4;
    EuclideanVector b{2};
    b[0] = 4;
    b[1] = 5;
    WHEN("They have same length but in different order") {
      THEN("They should not be equal") { REQUIRE(a != b); }
      THEN("They should have the same Euclidean Norm") {
        REQUIRE(a.GetEuclideanNorm() == b.GetEuclideanNorm());
      }
    }
  }
}

TEST_CASE("Default Constructor") {
  EuclideanVector a{4};
  REQUIRE(a.GetNumDimensions() == 4);
  for (int i = 0; i < 4; i++) {
    REQUIRE(a.at(i) == 0);
  }
}

TEST_CASE("Constructor") {
  EuclideanVector a{4, 2};
  REQUIRE(a.GetNumDimensions() == 4);
  for (int i = 0; i < 4; i++) {
    REQUIRE(a.at(i) == 2);
  }
}
