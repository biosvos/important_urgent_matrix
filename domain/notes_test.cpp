//
// Created by biosvos on 12/1/22.
//

#include <gtest/gtest.h>
#include "notes.h"

TEST(indices, EraseIndex) {
    Indices idx;
    idx.AddIndex();
    idx.AddIndex();
    idx.AddIndex();

    idx.EraseIndex(0);

    ASSERT_EQ(idx.Get(0), 0);
    ASSERT_EQ(idx.Get(1), 1);
}

TEST(indices, EraseIndexException) {
    Indices idx;

    ASSERT_ANY_THROW(idx.EraseIndex(0));
}

TEST(notes, add) {
    Notes notes;
    notes.AddNote(Note("abc"));
    notes.AddNote(Note("def"));
    notes.AddNote(Note("ghi"));

    notes.EraseNote(Note("def"));

    notes.AddNote(Note("jkl"));
}
