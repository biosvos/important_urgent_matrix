//
// Created by biosvos on 12/12/22.
//

#ifndef IMPORTANT_URGENT_MATRIX_I_SEQUENCE_H
#define IMPORTANT_URGENT_MATRIX_I_SEQUENCE_H

#include <string>
#include <vector>

class ISequence {
public:
    virtual ~ISequence() = default;

public:
    virtual void Add(std::string text) = 0;

    virtual void Erase(std::string text) = 0;

    virtual std::vector<std::string> List() = 0;

    virtual void ChangeOrder(std::string text, std::string dst) = 0;
};

#endif //IMPORTANT_URGENT_MATRIX_I_SEQUENCE_H
