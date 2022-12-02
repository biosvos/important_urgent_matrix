//
// Created by biosvos on 11/29/22.
//

#include <algorithm>
#include <stdexcept>
#include "notes.h"

namespace {
    template<typename T>
    void Move(std::vector<T> &v, size_t old_index, size_t new_index) {
        if (old_index > new_index) {
            std::rotate(v.rend() - old_index - 1, v.rend() - old_index, v.rend() - new_index);
        } else {
            std::rotate(v.begin() + old_index, v.begin() + old_index + 1, v.begin() + new_index + 1);
        }
    }
}

Notes::Notes() {}

Notes::Notes(std::initializer_list<Note> notes) :
        notes_(notes) {}

void Notes::AddNote(const Note &note) {
    notes_.emplace_back(note);

    importants_.AddIndex();
    urgents_.AddIndex();
}

void Notes::EraseNote(const Note &note) {
    auto it = std::find(std::begin(notes_), std::end(notes_), note);
    if (it == std::end(notes_)) {
        return;
    }

    int index = static_cast<int>(std::distance(std::begin(notes_), it));
    notes_.erase(it);

    importants_.EraseIndex(index);
    urgents_.EraseIndex(index);
}

void Notes::ChangeUrgentPritority(int old_index, int new_index) {
    urgents_.Move(old_index, new_index);
}

void Notes::ChangeImportantPritority(int old_index, int new_index) {
    importants_.Move(old_index, new_index);
}

void Indices::AddIndex() {
    arr_.push_back(static_cast<int>(arr_.size()));
}

void Indices::EraseIndex(int idx) {
    if (!(0 <= idx and idx < arr_.size())) {
        throw std::out_of_range("범위 넘김");
    }
    arr_.erase(std::remove(arr_.begin(), arr_.end(), idx), std::end(arr_));
    std::for_each(arr_.begin(), arr_.end(), [idx](int &cur_idx) {
        if (cur_idx >= idx) {
            --cur_idx;
        }
    });
}

void Indices::Move(int old_idx, int new_idx) {
    ::Move(arr_, old_idx, new_idx);
}

int Indices::Get(int idx) {
    if (!(0 <= idx and idx < arr_.size())) {
        throw std::out_of_range("범위 넘김");
    }
    return arr_[idx];
}

size_t Indices::Size() {
    return arr_.size();
}
