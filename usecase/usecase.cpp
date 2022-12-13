//
// Created by biosvos on 12/12/22.
//

#include "usecase.h"

#include <utility>

Usecase::Usecase(std::shared_ptr<ISequence> important_sequence,
                 std::shared_ptr<ISequence> urgent_sequence) :
        important_sequence_(std::move(important_sequence)),
        urgent_sequence_(std::move(urgent_sequence)) {}

void Usecase::CreateNote(std::string text) {
    important_sequence_->Add(text);
    urgent_sequence_->Add(text);
}

void Usecase::DeleteNote(std::string text) {
    important_sequence_->Erase(text);
    urgent_sequence_->Erase(text);
}

std::vector<std::string> Usecase::ListImportantNotes() {
    return important_sequence_->List();
}

std::vector<std::string> Usecase::ListUrgentNotes() {
    return urgent_sequence_->List();
}

void Usecase::ChangeImportantOrder(std::string text, std::string dst) {
    important_sequence_->ChangeOrder(text, dst);
}

void Usecase::ChangeUrgentOrder(std::string text, std::string dst) {
    urgent_sequence_->ChangeOrder(text, dst);
}
