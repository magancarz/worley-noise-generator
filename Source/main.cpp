#include "WorleyNoiseDataConverter.h"
#include "WorleyNoiseGenerator.h"
#include "WorleyNoiseTextureWriter.h"

int main()
{
    wng::WorleyNoiseSettings worley_noise_settings{};
    worley_noise_settings.width = 1024;
    worley_noise_settings.height = 1024;
    worley_noise_settings.grid_size = 8;
    worley_noise_settings.num_of_octaves = 5;

    wng::WorleyNoiseGenerator worley_noise_generator{worley_noise_settings};
    wng::WorleyNoiseData worley_noise_data = worley_noise_generator.generate();

    wng::WorleyNoiseTexture worley_noise_texture = wng::WorleyNoiseDataConverter::convert(worley_noise_data);
    std::filesystem::path file_path{"worley_noise_512x512.png"};
    wng::WorleyNoiseTextureWriter::saveToPNG(worley_noise_texture, file_path);

    return 0;
}
