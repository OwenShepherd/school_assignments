#include "matplotlibcpp.h"
#include <vector>
#include <cmath>

namespace plt = matplotlibcpp;

int main() {
    plt::plot({1,2,3,4});
    plt::show();
}
