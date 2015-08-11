#pragma once

#include <string>

class Texture
{
    public:

        Texture();
        ~Texture();

        void Load(std::string path, bool genMipMaps = false);
        void Bind(int textureUnit = 0);

        void SetFiltering(int magnification, int minification);

        int GetMinificationFilter();
        int GetMagnificationFilter();

        void Free();

    private:

        int mWidth, mHeight, mBPP;
        unsigned int mTextureID;
        unsigned int mSampler;

        bool mMipMapsGenerated;

        int mMinification, mMagnification;

        std::string mPath;


};
