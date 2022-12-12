//
// Created by biosvos on 12/12/22.
//

#ifndef IMPORTANT_URGENT_MATRIX_I_USECASE_H
#define IMPORTANT_URGENT_MATRIX_I_USECASE_H

#include <string>
#include <vector>

class IUsecase {
public:
    virtual ~IUsecase() = default;

public:
    virtual void CreateNote(std::string text) = 0;

    virtual void DeleteNote(std::string text) = 0;

    virtual std::vector<std::string> ListImportantNotes() = 0;

    virtual std::vector<std::string> ListUrgentNotes() = 0;

    virtual void ChangeImportantOrder(std::string text, size_t pos) = 0;

    virtual void ChangeUrgentOrder(std::string text, size_t pos) = 0;
};

#endif //IMPORTANT_URGENT_MATRIX_I_USECASE_H
