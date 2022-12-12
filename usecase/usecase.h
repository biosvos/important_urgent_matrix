//
// Created by biosvos on 12/12/22.
//

#ifndef IMPORTANT_URGENT_MATRIX_USECASE_H
#define IMPORTANT_URGENT_MATRIX_USECASE_H

#include <memory>

#include "i_usecase.h"
#include "../domain/i_sequence.h"

class Usecase : public IUsecase {
public:
    Usecase(std::shared_ptr<ISequence> important_sequence, std::shared_ptr<ISequence> urgent_sequence);

    void CreateNote(std::string text) override;

    void DeleteNote(std::string text) override;

    std::vector<std::string> ListImportantNotes() override;

    std::vector<std::string> ListUrgentNotes() override;

    void ChangeImportantOrder(std::string text, size_t pos) override;

    void ChangeUrgentOrder(std::string text, size_t pos) override;

private:
    std::shared_ptr<ISequence> important_sequence_, urgent_sequence_;
};


#endif //IMPORTANT_URGENT_MATRIX_USECASE_H
