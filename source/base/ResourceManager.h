#ifndef BASE_RESOURCEMANAGER_H_
#define BASE_RESOURCEMANAGER_H_

#include <string/String.h>
#include <raylib.h>
#include <memory>
#include <unordered_map>

// Holds all the textures and other resources that were loaded.
// This way the texture needed for a given object will be loaded only once.
class ResourceManager {
 private:
    // Holds all the textures mapped to their names of the files loaded.
    std::unordered_map<String, std::shared_ptr<Texture2D>> m_allTextures;

    // Loads a texture from the path of a png.
    // Uses the size given to resize the image to be the correct size.
    void LoadTexture(const String&      filename,
                     const unsigned int sizeWidth,
                     const unsigned int sizeHeight);

 public:
    ~ResourceManager();

    // Returns a texture that was previosly loaded by the name of the image
    // that uses that texture.
    // Not const so that the texture can be created if it was not already.
    // If the image was already loaded it will not be resized.
    const std::shared_ptr<Texture2D>& GetTexture(const String&      textureName,
                                                 const unsigned int sizeWidth,
                                                 const unsigned int sizeHeight);
};

#endif  // BASE_RESOURCEMANAGER_H_
