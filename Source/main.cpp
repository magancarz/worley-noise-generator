#include "WorleyNoiseGenerator.h"
#include "WorleyNoiseTextureWriter.h"

int main()
{
    wng::WorleyNoiseSettings worley_noise_settings{};
    worley_noise_settings.width = 512;
    worley_noise_settings.height = 512;
    worley_noise_settings.grid_size = 8;

    wng::WorleyNoiseGenerator worley_noise_generator{worley_noise_settings};
    wng::WorleyNoiseTexture<wng::WorleyNoisePixel> worley_noise_texture = worley_noise_generator.generate();
    std::filesystem::path file_path{"worley_noise_512x512.png"};
    wng::WorleyNoiseTextureWriter::saveToPNG(worley_noise_texture, file_path);

    return 0;
}
