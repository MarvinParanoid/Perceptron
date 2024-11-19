#pragma once

#include <vector>
#include <cstdint>
#include <fstream>
#include <string_view>

using std::string_view;

class DatasetReader {
    std::ifstream mImage;
    std::ifstream mLabel;

public:
    // MNIST database config
    static constexpr uint32_t IMG_WIDTH = 28;
    static constexpr uint32_t IMG_HEIGHT = 28;
    static constexpr uint32_t IMG_SIZE = IMG_WIDTH * IMG_HEIGHT;
    static constexpr uint32_t SAMPLES_COUNT = 60000;

    DatasetReader(string_view imagePath, string_view labelPath);
    ~DatasetReader();

    void ReadNext(std::vector<double> &data, uint32_t &expected);
};
