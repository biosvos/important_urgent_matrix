//
// Created by biosvos on 12/12/22.
//

#ifndef IMPORTANT_URGENT_MATRIX_FTX_H
#define IMPORTANT_URGENT_MATRIX_FTX_H

#include "../usecase/i_usecase.h"

class Ftx {
public:
    explicit Ftx(const std::shared_ptr<IUsecase> &usecase);

    void Run();

private:
    std::shared_ptr<IUsecase> usecase_;
};


#endif //IMPORTANT_URGENT_MATRIX_FTX_H
