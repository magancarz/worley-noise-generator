#include "WorleyNoiseDataConverter.h"
#include "WorleyNoiseGenerator.h"
#include "WorleyNoiseTextureWriter.h"

int main()
{
    wng::WorleyNoiseSettings worley_noise_settings{};
    worley_noise_settings.width = 1024;
    worley_noise_settings.height = 1024;
    worley_noise_settings.num_of_octaves = 5;

    wng::WorleyNoiseDataConverter worley_noise_data_converter{worley_noise_settings.width, worley_noise_settings.height};
    {
        worley_noise_settings.grid_size = 8;
        wng::WorleyNoiseGenerator worley_noise_generator{worley_noise_settings};
        wng::WorleyNoiseData worley_noise_data = worley_noise_generator.generate();
        worley_noise_data_converter.fillRedChannel(worley_noise_data);
    }

    {
        worley_noise_settings.grid_size = 16;
        wng::WorleyNoiseGenerator worley_noise_generator{worley_noise_settings};
        wng::WorleyNoiseData worley_noise_data = worley_noise_generator.generate();
        worley_noise_data_converter.fillGreenChannel(worley_noise_data);
    }

    {
        worley_noise_settings.grid_size = 32;
        wng::WorleyNoiseGenerator worley_noise_generator{worley_noise_settings};
        wng::WorleyNoiseData worley_noise_data = worley_noise_generator.generate();
        worley_noise_data_converter.fillBlueChannel(worley_noise_data);
    }

    worley_noise_data_converter.fillAlphaChannel(255);

    const wng::WorleyNoiseTexture& worley_noise_texture = worley_noise_data_converter.getWorleyNoiseTexture();
    std::filesystem::path file_path{"worley_noise_512x512.png"};
    wng::WorleyNoiseTextureWriter::saveToPNG(worley_noise_texture, file_path);

    return 0;
}
