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

namespace wng
{
    WorleyNoiseTexture WorleyNoiseDataConverter::convert(const WorleyNoiseData& worley_noise_data)
    {
        WorleyNoiseTexture worley_noise_texture{};
        worley_noise_texture.width = worley_noise_data.width;
        worley_noise_texture.height = worley_noise_data.height;
        worley_noise_texture.data = std::vector<WorleyNoisePixel>(worley_noise_data.width * worley_noise_data.height);

        for (std::size_t index = 0; index < worley_noise_texture.data.size(); ++index)
        {
            worley_noise_texture.data[index] = convertDataToPixel(worley_noise_data.data[index]);
        }

        return worley_noise_texture;
    }

    WorleyNoisePixel WorleyNoiseDataConverter::convertDataToPixel(float worley_noise_data)
    {
        WorleyNoisePixel worley_noise_pixel{};
        worley_noise_pixel.data[0] = static_cast<unsigned char>(worley_noise_data * 255.0f);
        worley_noise_pixel.data[1] = static_cast<unsigned char>(worley_noise_data * 255.0f);
        worley_noise_pixel.data[2] = static_cast<unsigned char>(worley_noise_data * 255.0f);
        worley_noise_pixel.data[3] = 255;

        return worley_noise_pixel;
    }
}
