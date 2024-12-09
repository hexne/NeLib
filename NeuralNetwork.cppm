/*******************************************************************************
 * @Author : yongheng
 * @Data   : 2024/12/06 22:51
*******************************************************************************/

module;
#include <vector>

#include "tools.h"
export module NeuralNetwork;

export
NAMESPACE_BEGIN(nl)

template <typename ... Args>
class NeuralNetwork {
    std::vector<std::vector<double>> weights_;


    template <size_t ... index>
    void neural_network_impl(auto &&tuple, std::index_sequence<index...>) {
        (weights_[index].resize(std::get<index>(tuple)), ...);
    }

public:
    NeuralNetwork(std::vector<size_t> weights) {
        weights_.resize(weights.size());
        for (int i = 0; i < weights.size(); i++) {
            weights_[i].resize(weights[i]);
        }
    }
    NeuralNetwork(Args && ... args) {
        weights_.resize(sizeof...(args));
        auto tuple = std::forward_as_tuple(args...);
        auto callback = std::get<sizeof ...(args) - 1>(tuple);
        neural_network_impl(tuple, std::make_index_sequence<sizeof...(args) - 1>());

    }
};
/*******************************************************************************

NeuralNetwork nn({1,2,3,4})

*******************************************************************************/



NAMESPACE_END(nl)

