//
// Created by j on 2022-10-15.
//

#include "usecase/usecase.h"
#include "infra/file_sequence.h"
#include "infra/ftx.h"

int main() {
    auto important_sequence = std::make_shared<FileSequence>("important");
    auto urgent_sequence = std::make_shared<FileSequence>("urgent");
    auto usecase = std::make_shared<Usecase>(important_sequence, urgent_sequence);
    auto ui = std::make_shared<Ftx>(usecase);
    ui->Run();
    return 0;
}