//
// Created by samuaz on 3/10/21.
//

#include <wintercpp/winter.h>

#include <cstddef>
#include <set>

#include "gtest/gtest.h"

TEST(winterRandom, dashedUUID) {
  for (uint i = 0; i < 100; i++) {
    auto uuid = winter::random::uuid();
    EXPECT_EQ(uuid.size(), 36);
  }
}

TEST(winterRandom, noDashedUUID) {
  for (uint i = 0; i < 100; i++) {
    auto uuid = winter::random::uuidNoDashed();
    EXPECT_EQ(uuid.size(), 32);
  }
}

TEST(winterRandom, uniqueness) {
  std::set<std::string> uuids;
  for (uint i = 0; i < 10000; i++) {
    uuids.insert(winter::random::uuidNoDashed());
    uuids.insert(winter::random::uuidNoDashed());
    uuids.insert(winter::random::uuidNoDashed());
    uuids.insert(winter::random::uuidNoDashed());
    uuids.insert(winter::random::uuidNoDashed());
  }
  EXPECT_EQ(uuids.size(), 50000);
}