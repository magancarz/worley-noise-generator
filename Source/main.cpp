#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "stb_image_write.h"

#include "WorleyNoiseGenerator.h"

int main()
{
    wng::WorleyNoiseSettings worley_noise_settings{};
    worley_noise_settings.width = 512;
    worley_noise_settings.height = 512;
    worley_noise_settings.grid_size = 8;

    wng::WorleyNoiseGenerator worley_noise_generator{worley_noise_settings};
    wng::WorleyNoiseTexture<wng::WorleyNoisePixel> worley_noise_texture = worley_noise_generator.generate();

    stbi_write_png(
        "worley_noise.png",
        worley_noise_settings.width,
        worley_noise_settings.height,
        4,
        worley_noise_texture.data.data(),
        worley_noise_settings.width * 4);

    return 0;
}
