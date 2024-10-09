#include <alinalib.h>

#include "SDL_ttf.h"

TTF_Font* alinalib__loadDefuaultFont()
{
    TTF_Font* defaultFont = alinalib_loadFont("assets/Roboto-Regular.ttf",
                                              ALINALIB_DEFAULT_FONT_SIZE);

    return defaultFont;
}

TTF_Font* alinalib_loadFont(const char* filePath, int size)
{
    TTF_Font* font = TTF_OpenFont(filePath, size);
    if (font == NULL)
    {
        printf("Failed to load font! TTF_Error: %s\n", TTF_GetError());
    }
    return font;
}

void alinalib_drawText(alinalib_Context* ctx,
                       const char* text,
                       alinalib_Point position,
                       alinalib_Color color)
{
    // Create a surface from the text
    SDL_Surface* surface =
        TTF_RenderText_Blended(ctx->defaultFont, text, color);
    if (!surface)
    {
        SDL_Log("Failed to create surface: %s", TTF_GetError());
        return;
    }

    // Create a texture from the surface
    SDL_Texture* texture = SDL_CreateTextureFromSurface(ctx->renderer, surface);
    if (!texture)
    {
        SDL_Log("Failed to create texture: %s", SDL_GetError());
        SDL_FreeSurface(surface);
        return;
    }

    // Define the destination rectangle
    SDL_Rect destRect = {position.x, position.y, surface->w, surface->h};

    // Copy the texture to the renderer
    SDL_RenderCopy(ctx->renderer, texture, NULL, &destRect);

    // Clean up
    SDL_DestroyTexture(texture);
    SDL_FreeSurface(surface);
}
