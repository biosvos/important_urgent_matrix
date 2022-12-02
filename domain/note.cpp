//
// Created by biosvos on 11/29/22.
//

#include "note.h"

Note::Note(std::string_view contents) :
        contents_(contents) {}

std::string Note::GetString() {
    return contents_;
}

bool Note::operator==(const Note &other) {
    return contents_ == other.contents_;
}
