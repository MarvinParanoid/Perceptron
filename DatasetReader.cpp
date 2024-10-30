#include "DatasetReader.h"
#include <iostream>

DatasetReader::DatasetReader(string_view imagePath, string_view labelPath) {
    mImage.open(imagePath.data(), std::ios::in | std::ios::binary);
    mLabel.open(labelPath.data(), std::ios::in | std::ios::binary);
    if (!mImage.is_open() || !mLabel.is_open()) {
        throw std::runtime_error("Dataset is not found\n");
    }

    // skip headers
    char number;
    for (int i = 0; i < 16; ++i) {
        mImage.read(&number, sizeof(char));
    }
    for (int i = 0; i < 8; ++i) {
        mLabel.read(&number, sizeof(char));
    }
}

DatasetReader::~DatasetReader() {
    mImage.close();
    mLabel.close();
}

void DatasetReader::ReadNext(std::vector<double> &data, uint32_t &expected) {
    if (mImage.eof() || mLabel.eof() || data.size() != IMG_SIZE) {
        throw std::runtime_error("Error during reading dataset");
    }
    char tmp;
    for (u_int32_t i = 0; i < IMG_SIZE; i++) {
        mImage.read(&tmp, sizeof(char));
        data[i] = tmp ? 1 : 0;
    }
    mLabel.read(&tmp, sizeof(char));
    expected = tmp;
}
