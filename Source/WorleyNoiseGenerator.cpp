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

#include "WorleyNoiseGenerator.h"

#include <algorithm>
#include <array>
#include <cassert>
#include <random>

#include "WorleyNoisePixel.h"
#include "WorleyNoisePoint.h"

namespace wng
{
    WorleyNoiseGenerator::WorleyNoiseGenerator(const WorleyNoiseSettings& worley_noise_settings)
        : worley_noise_settings{worley_noise_settings} {}

    WorleyNoiseData WorleyNoiseGenerator::generate() const
    {
        if (!settingsValid(worley_noise_settings))
        {
            return WorleyNoiseData{};
        }

        std::vector<WorleyNoiseData> worley_noise_data_arrays;
        worley_noise_data_arrays.resize(worley_noise_settings.num_of_octaves);

        int last_grid_size = worley_noise_settings.grid_size;
        for (auto& worley_noise_data : worley_noise_data_arrays)
        {
            WorleyNoiseSettings current_worley_noise_settings = worley_noise_settings;
            current_worley_noise_settings.grid_size = last_grid_size;
            worley_noise_data = generateWorleyNoiseData(current_worley_noise_settings);

            last_grid_size *= 2;
        }

        return compositeWorleyNoiseData(worley_noise_data_arrays);
    }

    bool WorleyNoiseGenerator::settingsValid(const WorleyNoiseSettings& worley_noise_settings)
    {
        bool grid_size_valid =
            worley_noise_settings.width % worley_noise_settings.grid_size == 0 &&
            worley_noise_settings.height % worley_noise_settings.grid_size == 0;
        bool valid_num_of_octaves = worley_noise_settings.num_of_octaves > 0;

        return grid_size_valid && valid_num_of_octaves;
    }

    std::vector<WorleyNoisePoint> WorleyNoiseGenerator::generateWorleyNoisePoints(const WorleyNoiseSettings& worley_noise_settings) const
    {
        std::random_device device;
        std::mt19937 generator{device()};
        std::uniform_real_distribution<float> distribution{0.0f, 1.0f};

        const float grid_cell_size = static_cast<float>(worley_noise_settings.width)
            / static_cast<float>(worley_noise_settings.grid_size);

        std::vector<WorleyNoisePoint> worley_noise_points;
        worley_noise_points.resize(worley_noise_settings.grid_size * worley_noise_settings.grid_size);
        for (unsigned int index = 0; index < worley_noise_points.size(); ++index)
        {
            unsigned int grid_x = index % worley_noise_settings.grid_size;
            unsigned int grid_y = index / worley_noise_settings.grid_size;

            worley_noise_points[index].x = (distribution(generator) + static_cast<float>(grid_x)) * grid_cell_size;
            worley_noise_points[index].y = (distribution(generator) + static_cast<float>(grid_y)) * grid_cell_size;
        }

        return worley_noise_points;
    }

    WorleyNoiseData WorleyNoiseGenerator::generateWorleyNoiseData(const WorleyNoiseSettings& worley_noise_settings) const
    {
        WorleyNoiseData worley_noise_data{};
        worley_noise_data.width = worley_noise_settings.width;
        worley_noise_data.height = worley_noise_settings.height;
        worley_noise_data.data = std::vector<float>(worley_noise_settings.width * worley_noise_settings.height);

        const int grid_size = worley_noise_data.width / worley_noise_settings.grid_size;
        const float inv_max_distance = 1.0f / (std::sqrt(2.0f) * static_cast<float>(grid_size));

        std::vector<WorleyNoisePoint> worley_noise_points = generateWorleyNoisePoints(worley_noise_settings);
        for (int pixel_y = 0; pixel_y < worley_noise_data.height; ++pixel_y)
        {
            for (int pixel_x = 0; pixel_x < worley_noise_data.width; ++pixel_x)
            {
                int grid_x = pixel_x / grid_size;
                int grid_y = pixel_y / grid_size;

                WorleyNoisePoint pixel_as_point{};
                pixel_as_point.x = static_cast<float>(pixel_x);
                pixel_as_point.y = static_cast<float>(pixel_y);

                float min_distance = 1.0f;
                for (int point_z = -1; point_z <= 1; ++point_z)
                {
                    for (int point_y = -1; point_y <= 1; ++point_y)
                    {
                        for (int point_x = -1; point_x <= 1; ++point_x)
                        {
                            int final_point_x = (grid_x + point_x + worley_noise_settings.grid_size) % worley_noise_settings.grid_size;
                            int final_point_y = (grid_y + point_y + worley_noise_settings.grid_size) % worley_noise_settings.grid_size;
                            unsigned int point_index =
                                final_point_y * worley_noise_settings.grid_size +
                                final_point_x;
                            WorleyNoisePoint& worley_noise_point = worley_noise_points.at(point_index);
                            float distance = worley_noise_point.distance(pixel_as_point) * inv_max_distance;
                            min_distance = std::min(distance, min_distance);
                        }
                    }
                }

                float inverted_value = 1.0f - min_distance;
                unsigned int pixel_index =
                    + pixel_y * worley_noise_settings.width
                    + pixel_x;
                worley_noise_data.data.at(pixel_index) = inverted_value;
            }
        }

        return worley_noise_data;
    }

    WorleyNoiseData WorleyNoiseGenerator::compositeWorleyNoiseData(
        const std::vector<WorleyNoiseData>& worley_noise_data_arrays) const
    {
        WorleyNoiseData composited_worley_noise_data{};
        composited_worley_noise_data.width = worley_noise_settings.width;
        composited_worley_noise_data.height = worley_noise_settings.height;
        composited_worley_noise_data.data = std::vector<float>(composited_worley_noise_data.width * composited_worley_noise_data.height);

        for (int pixel_y = 0; pixel_y < composited_worley_noise_data.height; ++pixel_y)
        {
            for (int pixel_x = 0; pixel_x < composited_worley_noise_data.width; ++pixel_x)
            {
                unsigned int pixel_index = pixel_y * composited_worley_noise_data.width + pixel_x;

                composited_worley_noise_data.data[pixel_index] = 0.0f;
                for (auto& worley_noise_data : worley_noise_data_arrays)
                {
                    composited_worley_noise_data.data[pixel_index] += worley_noise_data.data[pixel_index];
                }

                composited_worley_noise_data.data[pixel_index] /= static_cast<float>(worley_noise_data_arrays.size());
            }
        }

        return composited_worley_noise_data;
    }
}
