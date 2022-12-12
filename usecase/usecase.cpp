//
// Created by biosvos on 12/12/22.
//

#include "usecase.h"

#include <utility>

void Usecase::CreateNote(std::string text) {
    important_sequence_->Add(text);
    urgent_sequence_->Add(text);
}

void Usecase::DeleteNote(std::string text) {
    important_sequence_->Erase(text);
    urgent_sequence_->Erase(text);
}

std::vector<std::string> Usecase::ListImportantNotes() {
    return std::vector<std::string>();
}

std::vector<std::string> Usecase::ListUrgentNotes() {
    return std::vector<std::string>();
}

void Usecase::ChangeImportantOrder(std::string text, size_t pos) {

}

void Usecase::ChangeUrgentOrder(std::string text, size_t pos) {

}

Usecase::Usecase(std::shared_ptr<ISequence> important_sequence,
                 std::shared_ptr<ISequence> urgent_sequence) :
        important_sequence_(std::move(important_sequence)),
        urgent_sequence_(std::move(urgent_sequence)) {}
