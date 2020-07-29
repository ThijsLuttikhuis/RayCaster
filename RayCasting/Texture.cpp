//
// Created by thijs on 16-07-20.
//

#include <utility>
#include <vector>
#include <opencv2/opencv.hpp>
#include "Texture.h"
#include "../Window/Drawer.h"

namespace window {

std::map<std::string, TextureAttributes> Texture::textures;


bool Texture::addTexture(const std::string &filePath) {
    return addTexture(filePath, 100, 100);
}

bool Texture::addTexture(const std::string &filePath, const std::string &name) {
    return addTexture(filePath, name, 100, 100);
}

bool Texture::addTexture(const std::string &filePath, const std::string &name, const double &width, const double &height) {
    TextureAttributes textureAttributes;
    textureAttributes.width = width;
    textureAttributes.height = height;
    textureAttributes.texture = cv::imread(filePath);
    if (textureAttributes.texture.empty()) {
        std::cout << "texture not loaded! exiting..." << std::endl;
        return false;
    }

    textures[name] = textureAttributes;
    return true;
}

bool Texture::addTexture(const std::string &filePath, const double &width, const double &height) {
    TextureAttributes textureAttributes;
    textureAttributes.width = width;
    textureAttributes.height = height;
    textureAttributes.texture = cv::imread(filePath);
    if (textureAttributes.texture.empty()) {
        std::cout << "texture not loaded! exiting..." << std::endl;
        return false;
    }

    std::string name;
    auto it = filePath.end();
    auto itEnd = filePath.end();
    for (; it != filePath.begin(); it--) {
        const char &c = *it;
        if (c == '.') {
            itEnd = it;
        }
        if (c == '\\' or c == '/') {
            ++it;
            break;
        }
    }
    name.insert(name.begin(), it, itEnd);

    textures[name] = textureAttributes;
    return true;
}

double Texture::getWidth(const std::string &name) {
    return textures[name].width;
}

double Texture::getHeight(const std::string &name) {
    return textures[name].height;
}

const cv::Mat &Texture::getTexture(const std::string &name) {
    return textures[name].texture;
}

void Texture::drawTexture(const std::string &windowName, const std::string &textureName, const int &xPixel,
      const int &topPixel, const int &bottomPixel, const int &realTop, const int &realBottom,
      const double &wallXPosition, const double &wallHeight) {

    // get texture
    auto &textureAttributes = textures[textureName];
    auto &texture = textureAttributes.texture;

    // calculate how many times the texture has to be repeated
    double repeats = wallHeight / textureAttributes.height;
    int realYPixels = realTop - realBottom;

    // calculate the x-pixel of the texture
    double xLocation = std::fmod(wallXPosition, textureAttributes.width) / textureAttributes.width;
    int textureXPixel = static_cast<int>(texture.cols * xLocation);

    // loop over the column and draw
    const int finalTopPixel = std::min(realYPixels, window::Window::getYPixels(windowName)-realBottom);
    for (int i = bottomPixel - realBottom; i < finalTopPixel; i++) {
        int yPixel = i + realBottom;
        int textureYPixel = static_cast<int>(repeats * std::fmod(
              (double)i / realYPixels, 1.0/repeats) * texture.rows);

        // get pixel from texture
        auto &pixelColor = texture.at<cv::Vec3b>(textureYPixel, textureXPixel);

        // set pixel in 3D view
        window::Drawer::drawPixel(windowName, xPixel, yPixel, pixelColor);

    }
}


} //window