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

#include "WorleyNoiseTextureWriter.h"

#include <fstream>

#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "stb_image_write.h"

namespace wng
{
    void WorleyNoiseTextureWriter::saveToPNG(
        const WorleyNoiseTexture& worley_noise_texture,
        const std::filesystem::path& file_name)
    {
        for (unsigned int current_depth = 0; current_depth < worley_noise_texture.depth; ++current_depth)
        {
            std::string final_file_path = file_name.string().append("_").append(std::to_string(current_depth));
            std::size_t current_starting_index = current_depth * worley_noise_texture.width * worley_noise_texture.height;
            assert(current_starting_index < worley_noise_texture.data.size());
            stbi_write_png(
                final_file_path.c_str(),
                worley_noise_texture.width,
                worley_noise_texture.height,
                sizeof(WorleyNoisePixel),
                worley_noise_texture.data.data() + current_starting_index,
                worley_noise_texture.width * sizeof(WorleyNoisePixel));
        }
    }

    void WorleyNoiseTextureWriter::saveAsRawData(
        const WorleyNoiseTexture& worley_noise_texture,
        const std::filesystem::path& file_name)
    {
        std::ofstream output_file_stream{file_name, std::ios::out};
        if (!output_file_stream.is_open())
        {
            return;
        }

        output_file_stream.write((char*)&worley_noise_texture.width, sizeof(int));
        output_file_stream.write((char*)&worley_noise_texture.height, sizeof(int));
        output_file_stream.write((char*)&worley_noise_texture.depth, sizeof(int));
        for (const auto& pixel : worley_noise_texture.data)
        {
            output_file_stream.write((char*)&pixel, sizeof(WorleyNoisePixel));
        }

        output_file_stream.close();
    }
}
