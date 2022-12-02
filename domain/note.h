//
// Created by biosvos on 11/29/22.
//

#ifndef IMPORTANT_URGENT_MATRIX_NOTE_H
#define IMPORTANT_URGENT_MATRIX_NOTE_H

#include <string>

class Note {
public:
    explicit Note(std::string_view contents);

    std::string GetString();

    bool operator==(const Note &other);

private:
    std::string contents_;
};

#endif //IMPORTANT_URGENT_MATRIX_NOTE_H
