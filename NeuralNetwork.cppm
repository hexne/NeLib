/*******************************************************************************
 * @Author : yongheng
 * @Data   : 2024/12/06 22:51
*******************************************************************************/

module;
#include <array>
#include <iostream>
#include <ostream>
#include <tuple>
#include <complex>
#include <memory>

#include "tools.h"
export module NeuralNetwork;


template <std::size_t... N>
struct NeuralNetworkHelper;

template <std::size_t Row, std::size_t Col, std::size_t... Args>
struct NeuralNetworkHelper<Row, Col, Args...> {
    using type = std::remove_cvref_t<decltype(std::tuple_cat(
                        std::declval<std::tuple<std::array<std::array<double,Col>, Row>>>(),
                        std::declval<typename NeuralNetworkHelper<Col, Args...>::type>()
                    ))>;
};

template <std::size_t Last>
struct NeuralNetworkHelper<Last> {
    using type = std::tuple<>;
};

struct Activate {
    virtual double activate(const double) = 0;
};
struct Sigmoid : Activate {
    double activate(const double x) override {
        return 1.0 / (1 + exp(-x));
    }
};
struct Tanh : Activate {
    double activate(const double) override {
        // @TODO
        return 0.0;
    }
};


export
NAMESPACE_BEGIN(nl)

template <std::size_t... N>
class NeuralNetwork {
    typename NeuralNetworkHelper<N ...>::type weights_;
    std::tuple<std::array<double, N> ...> inputs_;
    std::tuple<std::array<double, N> ...> outputs_;
    std::size_t layout_count_ = sizeof ... (N);
    enum class ActivateType {
        Sigmoid,
        Tanh,
    };
    std::shared_ptr<Activate> activate_function_{new Sigmoid};
public:
    NeuralNetwork() = default;

    template <size_t index = 0>
    void forward() {
        if constexpr (index < std::tuple_size_v<typename NeuralNetworkHelper<N ...>::type>) {
            auto &weight = std::get<index>(weights_);
            auto &input = std::get<index + 1>(inputs_);
            auto &output = std::get<index>(outputs_);

            for (int i = 0;i < input.size(); ++i) {
                input[i] = 0;
                for (int j = 0;j < output.size(); ++j) {
                    input[i] += weight[j][i] * output[j];
                }
            }

            for (int i = 0;i < input.size(); ++i) {
                input[i] = activate_function_->activate(input[i]);
            }

            forward<index + 1>();
        }
    }

};

NAMESPACE_END(nl)

