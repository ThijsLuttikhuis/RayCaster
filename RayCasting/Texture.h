//
// Created by thijs on 16-07-20.
//

#ifndef RAYCASTER_TEXTURE_H
#define RAYCASTER_TEXTURE_H


#include <opencv2/core/mat.hpp>

namespace window {

class TextureAttributes {
public:
    cv::Mat texture;
    double width;         //cm
    double height;        //cm
};

class Texture {
private:
    static std::map<std::string, TextureAttributes> textures;

public:
    static void addTexture(const std::string &filePath);
    static void addTexture(const std::string &filePath, const std::string &name);
    static void addTexture(const std::string &filePath, const double &width, const double &height);
    static void addTexture(const std::string &filePath, const std::string& name, const double &width, const double &height);

    [[nodiscard]] static const cv::Mat &getTexture(const std::string &name);
    [[nodiscard]] static double getWidth(const std::string &name);
    [[nodiscard]] static double getHeight(const std::string &name);

    static void drawTexture(const std::string &windowName, const std::string &textureName, const int &xPixel,
          const int &topPixel, const int &bottomPixel, const int &realTop, const int &realBottom,
          const double &wallXPosition, const double &wallHeight);
};
//name, xLeft, topDrawHeight,
//          width, bottomDrawHeight - topDrawHeight, {255,255,255}
}//window

#endif //RAYCASTER_TEXTURE_H
