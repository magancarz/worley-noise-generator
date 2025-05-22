// MIT License

// Copyright (c) 2025 Mateusz Gancarz

// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files (the "Software"), to deal
// in the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
// copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions:

// The above copyright notice and this permission notice shall be included in all
// copies or substantial portions of the Software.

// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
// SOFTWARE.

#include "WorleyNoiseDataConverter.h"

#include <cassert>

namespace wng
{
    WorleyNoiseDataConverter::WorleyNoiseDataConverter(int width, int height)
        : worley_noise_texture{.width = width, .height = height, .data = std::vector<WorleyNoisePixel>(width * height)} {}

    void WorleyNoiseDataConverter::fillAllChannels(const WorleyNoiseData& worley_noise_data)
    {
        assert(worley_noise_data.width == worley_noise_texture.width && worley_noise_data.height == worley_noise_texture.height);

        for (std::size_t index = 0; index < worley_noise_texture.data.size(); ++index)
        {
            unsigned char byte_value = convertDataToByteValue(worley_noise_data.data[index]);
            worley_noise_texture.data[index].data[0] = byte_value;
            worley_noise_texture.data[index].data[1] = byte_value;
            worley_noise_texture.data[index].data[2] = byte_value;
            worley_noise_texture.data[index].data[3] = byte_value;
        }
    }

    unsigned char WorleyNoiseDataConverter::convertDataToByteValue(float worley_noise_data)
    {
        return static_cast<unsigned char>(worley_noise_data * 255.0f);
    }

    void WorleyNoiseDataConverter::fillRedChannel(const WorleyNoiseData& worley_noise_data)
    {
        assert(worley_noise_data.width == worley_noise_texture.width && worley_noise_data.height == worley_noise_texture.height);

        for (std::size_t index = 0; index < worley_noise_texture.data.size(); ++index)
        {
            worley_noise_texture.data[index].data[0] = convertDataToByteValue(worley_noise_data.data[index]);
        }
    }

    void WorleyNoiseDataConverter::fillGreenChannel(const WorleyNoiseData& worley_noise_data)
    {
        assert(worley_noise_data.width == worley_noise_texture.width && worley_noise_data.height == worley_noise_texture.height);

        for (std::size_t index = 0; index < worley_noise_texture.data.size(); ++index)
        {
            worley_noise_texture.data[index].data[1] = convertDataToByteValue(worley_noise_data.data[index]);
        }
    }

    void WorleyNoiseDataConverter::fillBlueChannel(const WorleyNoiseData& worley_noise_data)
    {
        assert(worley_noise_data.width == worley_noise_texture.width && worley_noise_data.height == worley_noise_texture.height);

        for (std::size_t index = 0; index < worley_noise_texture.data.size(); ++index)
        {
            worley_noise_texture.data[index].data[2] = convertDataToByteValue(worley_noise_data.data[index]);
        }
    }

    void WorleyNoiseDataConverter::fillAlphaChannel(const WorleyNoiseData& worley_noise_data)
    {
        assert(worley_noise_data.width == worley_noise_texture.width && worley_noise_data.height == worley_noise_texture.height);

        for (std::size_t index = 0; index < worley_noise_texture.data.size(); ++index)
        {
            worley_noise_texture.data[index].data[3] = convertDataToByteValue(worley_noise_data.data[index]);
        }
    }

    void WorleyNoiseDataConverter::fillAlphaChannel(unsigned char value)
    {
        for (auto& pixel : worley_noise_texture.data)
        {
            pixel.data[3] = value;
        }
    }
}
