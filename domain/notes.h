//
// Created by biosvos on 11/29/22.
//

#ifndef IMPORTANT_URGENT_MATRIX_NOTES_H
#define IMPORTANT_URGENT_MATRIX_NOTES_H

#include <vector>
#include "note.h"

class Indices {
public:
    void AddIndex();

    void EraseIndex(int idx);

    void Move(int old_idx, int new_idx);

    int Get(int idx);

    size_t Size();

private:
    std::vector<int> arr_;
};

class Notes {
public:
    Notes();

    Notes(std::initializer_list<Note> notes);

    void AddNote(const Note &note);

    void EraseNote(const Note &note);

    void ChangeUrgentPritority(int old_index, int new_index);

    void ChangeImportantPritority(int old_index, int new_index);

    std::vector<Note>::iterator begin();

    std::vector<Note>::iterator end();

private:
    std::vector<Note> notes_; // 순서에 변동이 없어야 한다.
    Indices importants_;
    Indices urgents_;
};


#endif //IMPORTANT_URGENT_MATRIX_NOTES_H
