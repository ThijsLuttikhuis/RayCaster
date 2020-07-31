//
// Created by thijs on 16-07-20.
//

#ifndef RAYCASTER_TEXTURE_H
#define RAYCASTER_TEXTURE_H


#include <opencv2/core/mat.hpp>
#include <list>

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
    static bool addTexture(const std::string &filePath);
    static bool addTexture(const std::string &filePath, const std::string &name);
    static bool addTexture(const std::string &filePath, const double &width, const double &height);
    static bool addTexture(const std::string &filePath, const std::string& name, const double &width, const double &height);

    [[nodiscard]] static const cv::Mat &getTexture(const std::string &name);
    [[nodiscard]] static double getWidth(const std::string &name);
    [[nodiscard]] static double getHeight(const std::string &name);

    static void drawTexture(const std::string &windowName, const std::string &textureName, const int &xPixel,
          int topPixel, int bottomPixel, const double &wallXPosition, const double &wallBot, const double &wallTop,
                            std::list<std::pair<int, int>> &ignorePixels);
};
//name, xLeft, topDrawHeight,
//          width, bottomDrawHeight - topDrawHeight, {255,255,255}
}//window

#endif //RAYCASTER_TEXTURE_H
