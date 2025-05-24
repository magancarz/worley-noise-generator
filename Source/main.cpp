#include "WorleyNoiseDataConverter.h"
#include "WorleyNoiseGenerator.h"
#include "WorleyNoiseTextureWriter.h"

int main()
{
    wng::WorleyNoiseSettings worley_noise_settings{};
    worley_noise_settings.width = 128;
    worley_noise_settings.height = 128;
    worley_noise_settings.depth = 128;

    wng::WorleyNoiseDataConverterSettings worley_noise_data_converter_settings{};
    worley_noise_data_converter_settings.width = worley_noise_settings.width;
    worley_noise_data_converter_settings.height = worley_noise_settings.height;
    worley_noise_data_converter_settings.depth = worley_noise_settings.depth;

    wng::WorleyNoiseDataConverter worley_noise_data_converter{worley_noise_data_converter_settings};
    {
        worley_noise_settings.num_of_octaves = 2;
        worley_noise_settings.grid_size = 4;
        wng::WorleyNoiseGenerator worley_noise_generator{worley_noise_settings};
        wng::WorleyNoiseData worley_noise_data = worley_noise_generator.generate();
        worley_noise_data_converter.fillRedChannel(worley_noise_data);
    }

    {
        worley_noise_settings.num_of_octaves = 3;
        worley_noise_settings.grid_size = 4;
        wng::WorleyNoiseGenerator worley_noise_generator{worley_noise_settings};
        wng::WorleyNoiseData worley_noise_data = worley_noise_generator.generate();
        worley_noise_data_converter.fillGreenChannel(worley_noise_data);
    }

    {
        worley_noise_settings.num_of_octaves = 4;
        worley_noise_settings.grid_size = 4;
        wng::WorleyNoiseGenerator worley_noise_generator{worley_noise_settings};
        wng::WorleyNoiseData worley_noise_data = worley_noise_generator.generate();
        worley_noise_data_converter.fillBlueChannel(worley_noise_data);
    }

    {
        worley_noise_settings.num_of_octaves = 5;
        worley_noise_settings.grid_size = 4;
        wng::WorleyNoiseGenerator worley_noise_generator{worley_noise_settings};
        wng::WorleyNoiseData worley_noise_data = worley_noise_generator.generate();
        worley_noise_data_converter.fillAlphaChannel(worley_noise_data);
    }

    const wng::WorleyNoiseTexture& worley_noise_texture = worley_noise_data_converter.getWorleyNoiseTexture();
    std::filesystem::path file_path{"worley_noise_128x128x128.png"};
    wng::WorleyNoiseTextureWriter::saveToPNG(worley_noise_texture, file_path);

    return 0;
}
