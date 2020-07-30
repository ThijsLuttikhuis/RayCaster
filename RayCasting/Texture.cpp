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
      int topPixel, int bottomPixel, const double &wallXPosition, const double &wallHeight,
                          std::vector<std::pair<int, int>> &ignorePixels) {

    // get window y-pixels
    int yPixels = window::Window::getYPixels(windowName);

    // limit drawing to the size of the screen
    int realBottom = bottomPixel;
    int realTop = topPixel;
    bottomPixel = bottomPixel < 0 ? 0 : bottomPixel;
    topPixel = topPixel > yPixels ? yPixels : topPixel;

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
    int i = bottomPixel - realBottom;
    const int finalTopPixel = std::min(realYPixels, yPixels - realBottom);
    for (; i < finalTopPixel; i++) {
        // get pixel from texture
        int textureYPixel = static_cast<int>(repeats * std::fmod(
              (double)i / realYPixels, 1.0/repeats) * texture.rows);
        auto &pixelColor = texture.at<cv::Vec3b>(textureYPixel, textureXPixel);

        // set pixel in 3D view
        int yPixel = i + realBottom;
        window::Drawer::drawPixel(windowName, xPixel, yPixel, pixelColor);
    }
}


} //window