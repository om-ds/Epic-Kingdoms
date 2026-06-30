#pragma once
#include <SFML/Graphics.hpp>
#include <map>
#include <vector>

namespace Collision {

    class TextureMaskManager {
    private:
        std::map<const sf::Texture*, std::vector<sf::Uint8>> m_TextureMasks;
    public:
        ~TextureMaskManager() { m_TextureMasks.clear(); }

        sf::Uint8 GetPixel(const std::vector<sf::Uint8>& mask, const sf::Texture* tex, unsigned int x, unsigned int y) {
            if (x >= tex->getSize().x || y >= tex->getSize().y) return 0;
            return mask[x + y * tex->getSize().x];
        }

        const std::vector<sf::Uint8>& GetMask(const sf::Texture* texture) {
            auto pair = m_TextureMasks.find(texture);
            if (pair != m_TextureMasks.end()) {
                return pair->second;
            } else {
                sf::Image image = texture->copyToImage();
                std::vector<sf::Uint8> mask(image.getSize().x * image.getSize().y);

                for (unsigned int y = 0; y < image.getSize().y; y++) {
                    for (unsigned int x = 0; x < image.getSize().x; x++) {
                        mask[x + y * image.getSize().x] = image.getPixel(x, y).a;
                    }
                }
                m_TextureMasks[texture] = mask;
                return m_TextureMasks[texture];
            }
        }
    };

    inline TextureMaskManager& GetBitmapsManager() {
        static TextureMaskManager instance;
        return instance;
    }

    inline bool SingleSpritePixelTest(const sf::Sprite& Object, const sf::Vector2f& MousePosition, sf::Uint8 AlphaLimit = 0) {
        if (!Object.getGlobalBounds().contains(MousePosition)) return false;

        const sf::Texture* texture = Object.getTexture();
        if (!texture) return false;

        TextureMaskManager& manager = GetBitmapsManager();
        const std::vector<sf::Uint8>& mask = manager.GetMask(texture);

        sf::Vector2f localPos = Object.getInverseTransform().transformPoint(MousePosition);
        sf::IntRect texRect = Object.getTextureRect();

        int pixelX = static_cast<int>(localPos.x) + texRect.left;
        int pixelY = static_cast<int>(localPos.y) + texRect.top;

        if (pixelX < 0 || pixelY < 0 || pixelX >= (int)texture->getSize().x || pixelY >= (int)texture->getSize().y) {
            return false;
        }

        return (manager.GetPixel(mask, texture, pixelX, pixelY) > AlphaLimit);
    }
}
