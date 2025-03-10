/*******************************************************************************
 * @Author : yongheng
 * @Data   : 2025/03/09 11:08
*******************************************************************************/


module;
#include <mdspan>
#include <random>
#include "tools.h"
export module CNN;

import Matrix;

// 卷积层
class ConvLayer {
    static constexpr size_t kernel_row{3}, kernel_col{3}, kernel_count{5};
    static constexpr size_t image_weight_{255}, image_height_{255};

    std::array<nl::Matrix<double, kernel_row, kernel_col>, kernel_count> kernels_{};
    std::mdspan<unsigned char, std::extents<size_t, image_height_, image_weight_>> image_;

    void init_kernels() {
        // kernels_ = {
        //     {
        //         0.f, 1.f, 0.f,
        //         0.f, 1.f, 0.f,
        //         0.f, 1.f, 0.f,
        //     },
        // };

        static std::random_device rd;
        std::mt19937 gen(rd());
        std::uniform_real_distribution dis(-1.0, 1.0);

        for (int count = 0; count < kernel_count; count ++) {
            for (int i = 0; i < kernel_row; i++) {
                for (int j = 0; j < kernel_col; j++) {
                    kernels_[count][i, j] = dis(gen);
                }
            }
        }


    }
public:
    explicit ConvLayer(unsigned char *image_data) :
        image_(std::mdspan<unsigned char, std::extents<size_t, image_height_, image_weight_>>(image_data))
    {
        init_kernels();
    }
    void conv() {

    }


};

class NonLinearLayer {  };
class PoolLayer {  };
class FullyConnLayer {  };



export
NAMESPACE_BEGIN(nl)





class CNN {

};

NAMESPACE_END(nl)


