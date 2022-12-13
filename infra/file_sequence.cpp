//
// Created by biosvos on 12/12/22.
//

#include <fstream>
#include "file_sequence.h"

FileSequence::FileSequence(std::string_view filename) : filename_(filename) {
    std::ifstream ifs(filename_);
    std::string line;
    int i = 0;
    while (std::getline(ifs, line)) {
        m_.emplace(line, i);
        ++i;
    }
    ifs.close();
}

void FileSequence::Add(std::string text) {
    auto size = m_.size();
    m_.emplace(text, size);

    auto arr = MapToStrings();
    std::ofstream ofs(filename_);
    for (const auto &item: arr) {
        ofs << item << std::endl;
    }
    ofs.close();
}

void FileSequence::Erase(std::string text) {
    m_.erase(text);

    auto arr = MapToStrings();
    std::ofstream ofs(filename_);
    for (const auto &item: arr) {
        ofs << item << std::endl;
    }
    ofs.close();
}

std::vector<std::string> FileSequence::List() {
    std::vector<std::string> ret = MapToStrings();
    return ret;
}

std::vector<std::string> FileSequence::MapToStrings() {
    std::vector<std::string> ret(m_.size());
    for (const auto &[key, value]: m_) {
        ret[value] = key;
    }
    return ret;
}

void FileSequence::ChangeOrder(std::string text, size_t pos) {
    if (pos >= m_.size()) {
        throw std::out_of_range("failed to change order");
    }

    if (m_.find(text) == m_.end()) {
        throw std::logic_error("failed to change order, not found text");
    }

    for (auto &[key, value]: m_) {
        if (value >= pos) {
            ++value;
        }
    }

    m_[text] = pos;

    auto arr = MapToStrings();
    std::ofstream ofs(filename_);
    for (const auto &item: arr) {
        ofs << item << std::endl;
    }
    ofs.close();
}
