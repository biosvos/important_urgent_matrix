//
// Created by biosvos on 12/12/22.
//

#ifndef IMPORTANT_URGENT_MATRIX_FILE_SEQUENCE_H
#define IMPORTANT_URGENT_MATRIX_FILE_SEQUENCE_H

#include <unordered_map>
#include "../domain/i_sequence.h"

class FileSequence : public ISequence {
public:
    FileSequence(std::string_view filename);

    void Add(std::string text) override;

    void Erase(std::string text) override;

    std::vector<std::string> List() override;

    void ChangeOrder(std::string text, size_t pos) override;

private:
    std::vector<std::string> MapToStrings();

    std::unordered_map<std::string, size_t> m_;
    std::string filename_;
};


#endif //IMPORTANT_URGENT_MATRIX_FILE_SEQUENCE_H
