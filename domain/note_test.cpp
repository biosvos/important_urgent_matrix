//
// Created by biosvos on 11/29/22.
//

#include <gtest/gtest.h>

#include "note.h"

TEST(a, b) {
    auto note = Note("asdf");

    ASSERT_EQ("asdf", note.GetString());
}