#include "ResourceManager.h"

ResourceManager::~ResourceManager() {
    std::for_each(
        m_allTextures.begin(),
        m_allTextures.end(),
        [](const std::pair<String, std::shared_ptr<Texture2D>>& texturePair) {
            UnloadTexture(*texturePair.second);
        });
    m_allTextures.clear();
}

const std::shared_ptr<Texture2D>&
ResourceManager::GetTexture(const String&      textureName,
                            const unsigned int sizeWidth,
                            const unsigned int sizeHeight) {
    if (m_allTextures.count(textureName) == 0) {
        LoadTexture(textureName, sizeWidth, sizeHeight);
    }
    return m_allTextures.at(textureName);
}

void ResourceManager::LoadTexture(const String&      filename,
                                  const unsigned int sizeWidth,
                                  const unsigned int sizeHeight) {
    Image newImage = LoadImage(filename.c_str());
    ImageResizeNN(&newImage, sizeWidth, sizeHeight);

    m_allTextures.insert(
        { filename,
          std::make_shared<Texture2D>(LoadTextureFromImage(newImage)) });

    UnloadImage(newImage);
}
