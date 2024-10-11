#include <alinalib.h>
#include <stdlib.h>
#include <string.h>

#include "SDL_surface.h"
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

void alinalib_disposeFont(TTF_Font* font)
{
    TTF_CloseFont(font);
}

alinalib_Point alinalib_measureText(const char* text, TTF_Font* font)
{
    alinalib_Point size;
    TTF_SizeText(font, text, &size.x, &size.y);

    return size;
}

void alinalib_setFontSize(TTF_Font* font, int ptsize)
{
    TTF_SetFontSize(font, ptsize);
}

void alinalib_drawText(alinalib_Context* ctx,
                       const char* text,
                       const alinalib_Point* position,
                       const alinalib_Color color)
{
    SDL_Surface* textSurface =
        TTF_RenderText_Blended(ctx->defaultFont, text, color);
    if (!textSurface)
    {
        SDL_Log("Failed to create surface: %s", TTF_GetError());
        return;
    }

    SDL_Texture* texture =
        SDL_CreateTextureFromSurface(ctx->renderer, textSurface);
    if (!texture)
    {
        SDL_Log("Failed to create texture: %s", SDL_GetError());
        SDL_FreeSurface(textSurface);
        return;
    }

    SDL_Rect textRect = {
        position->x, position->y, textSurface->w, textSurface->h};

    SDL_RenderCopy(ctx->renderer, texture, NULL, &textRect);

    // Clean up
    SDL_DestroyTexture(texture);
    SDL_FreeSurface(textSurface);
}

void alinalib_drawCustomText(alinalib_Context* ctx,
                             TTF_Font* font,
                             const char* text,
                             const alinalib_Point* position,
                             const alinalib_Point* origin,
                             const alinalib_Color color,
                             double angle,
                             int outlineWidth,
                             const alinalib_Color outlineColor)
{
    // Check if the outline color is effectively "empty"
    if (outlineWidth > 0 &&
        memcmp(&outlineColor, &(SDL_Color){0, 0, 0, 0}, sizeof(SDL_Color)) != 0)
    {
        int offsets[] = {-outlineWidth, 0, outlineWidth};

        // Render the outline in multiple directions
        for (int i = 0; i < 3; ++i)
        {
            for (int j = 0; j < 3; ++j)
            {
                // Skip the center position
                if (i == 1 && j == 1) continue;

                SDL_Surface* outlineSurface =
                    TTF_RenderText_Blended(font, text, outlineColor);
                if (!outlineSurface)
                {
                    SDL_Log("Failed to create outline surface: %s",
                            TTF_GetError());
                    return;
                }
                SDL_Texture* outlineTexture =
                    SDL_CreateTextureFromSurface(ctx->renderer, outlineSurface);
                if (!outlineTexture)
                {
                    SDL_Log("Failed to create outline texture: %s",
                            SDL_GetError());
                    SDL_FreeSurface(outlineSurface);
                    return;
                }

                SDL_Rect outlineRect = {position->x + offsets[i],
                                        position->y + offsets[j],
                                        outlineSurface->w,
                                        outlineSurface->h};

                SDL_RenderCopyEx(ctx->renderer,
                                 outlineTexture,
                                 NULL,
                                 &outlineRect,
                                 angle,
                                 origin,
                                 SDL_FLIP_NONE);

                // Clean up
                SDL_FreeSurface(outlineSurface);
                SDL_DestroyTexture(outlineTexture);
            }
        }
    }

    // Render the filled text
    SDL_Surface* textSurface = TTF_RenderText_Blended(font, text, color);
    if (!textSurface)
    {
        SDL_Log("Failed to create text surface: %s", TTF_GetError());
        return;
    }

    SDL_Texture* textTexture =
        SDL_CreateTextureFromSurface(ctx->renderer, textSurface);
    if (!textTexture)
    {
        SDL_Log("Failed to create text texture: %s", SDL_GetError());
        SDL_FreeSurface(textSurface);
        return;
    }

    SDL_Rect textRect = {
        position->x, position->y, textSurface->w, textSurface->h};

    SDL_RenderCopyEx(ctx->renderer,
                     textTexture,
                     NULL,
                     &textRect,
                     angle,
                     origin,
                     SDL_FLIP_NONE);

    // Clean up
    SDL_FreeSurface(textSurface);
    SDL_DestroyTexture(textTexture);
}
