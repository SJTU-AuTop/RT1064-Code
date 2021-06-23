#include <Eigen/Core>

extern "C" double process(){
    Eigen::Matrix3d x;
    return x(0, 0);
}
