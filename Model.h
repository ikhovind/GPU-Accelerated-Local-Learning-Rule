#ifndef FILTER_FINDER_MODEL_H
#define FILTER_FINDER_MODEL_H


#include <memory>
#include <string>
#include "Arrays.h"
#include <filesystem>
#include <boost/compute/system.hpp>
#include <boost/compute/utility/source.hpp>

#include <boost/program_options.hpp>
#include <boost/compute/algorithm/copy.hpp>
#include <boost/compute/container/vector.hpp>

namespace compute = boost::compute;
namespace po = boost::program_options;

template <typename T>
class Model {
public:
    double sigma;
    double lambda;
    size_t filters;
    size_t resolution;
    size_t batch_size;
    std::vector<T> results = std::vector<T>();
    std::string kernel_options;
    compute::vector<double> mugpu;
    compute::vector<double> batch_data;
    compute::context context;
    compute::command_queue queue;
    compute::program program;
    explicit Model(double sigma_, double lambda_, size_t grid_size_, size_t image_res_, size_t batch_size_, double learning_rate = 0.1) :  sigma(sigma_), lambda(lambda_), filters(grid_size_ * grid_size_), resolution(image_res_), batch_size(batch_size_) {
        results.resize(filters * resolution * resolution);
        for(auto &a : results) {
            a = get_rand();
        }

        kernel_options = std::string("-Dfilters=");
        kernel_options.append(std::to_string(filters));
        kernel_options.append(" -Dresolution=");
        kernel_options.append(std::to_string(resolution));
        kernel_options.append(" -Dlambda=");
        kernel_options.append(std::to_string(lambda));
        kernel_options.append(" -Dsigma=");
        kernel_options.append(std::to_string(sigma));
        kernel_options.append(" -Dbatch_size=");
        kernel_options.append(std::to_string(batch_size));
        kernel_options.append(" -Dlearning_rate=");
        kernel_options.append(std::to_string(learning_rate));
        kernel_options.append(" -Dlower_res=");
        int lower_res = resolution / 2;
        kernel_options.append(std::to_string(lower_res));
        kernel_options.append(" -Dupper_res=");
        kernel_options.append(std::to_string(resolution - lower_res));

        context = compute::context(device);
        program = make_sma_program(context);
        mugpu = compute::vector<double>(results.size(),context);
        batch_data = compute::vector<double>(batch_size_ * image_res_ * image_res_, context);
        queue = compute::command_queue(context, device);
        compute::copy(results.begin(), results.end(), mugpu.begin(), queue);
        kernel = compute::kernel(program, "SMA");

        kernel.set_arg(0,mugpu.get_buffer());
        kernel.set_arg(1,batch_data.get_buffer());
    };

    void update(int j);

    void save(const char &subfigure);
    bool load(const char &subfigure);

private:
    compute::kernel kernel;
    compute::program make_sma_program(const compute::context& context);
    compute::device device = compute::system::default_device();
    double f(int i, SquareArray<T> const &x);
};


#endif //FILTER_FINDER_MODEL_H
