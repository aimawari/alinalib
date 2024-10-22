#include <alinalib.h>
#include <stdlib.h>
#include <string.h>

#include "SDL_surface.h"
#include "SDL_ttf.h"

struct alinalib_TTFFont
{
    TTF_Font* data;
};

alinalib_TTFFont* alinalib__loadDefuaultFont()
{
    alinalib_TTFFont* defaultFont = alinalib_loadFont(
        "assets/Roboto-Regular.ttf", ALINALIB_DEFAULT_FONT_SIZE);

    return defaultFont;
}

alinalib_TTFFont* alinalib_loadFont(const char* filePath, int size)
{
    alinalib_TTFFont* font = malloc(sizeof(alinalib_TTFFont));
    if (font == NULL)
    {
        free(font);
        return NULL;
    }
    else
    {
        font->data = TTF_OpenFont(filePath, size);
        if (font->data == NULL)
        {
            printf("Failed to load font! TTF_Error: %s\n", TTF_GetError());
            return NULL;
        }
        return font;
    }
}

void alinalib_disposeFont(alinalib_TTFFont* font)
{
    if (!font->data)
    {
        TTF_CloseFont(font->data);
    }

    free(font);
}

alinalib_Vector2 alinalib_measureText(const char* text, alinalib_TTFFont* font)
{
    int w, h;
    TTF_SizeText(font->data, text, &w, &h);

    alinalib_Vector2 size = {(float)w, (float)h};

    return size;
}

void alinalib_setFontSize(alinalib_TTFFont* font, int ptsize)
{
    TTF_SetFontSize(font->data, ptsize);
}

void alinalib_drawText(alinalib_Context* ctx,
                       const char* text,
                       const alinalib_Vector2 position,
                       const alinalib_Color color)
{
    SDL_Surface* textSurface =
        TTF_RenderText_Blended(ctx->defaultFont->data,
                               text,
                               (SDL_Color){color.r, color.g, color.b, color.a});
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
        position.x, position.y, textSurface->w, textSurface->h};

    SDL_RenderCopy(ctx->renderer, texture, NULL, &textRect);

    // Clean up
    SDL_DestroyTexture(texture);
    SDL_FreeSurface(textSurface);
}

void alinalib_drawCustomText(alinalib_Context* ctx,
                             alinalib_TTFFont* font,
                             const char* text,
                             const alinalib_Vector2 position,
                             const alinalib_Vector2 origin,
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
                    TTF_RenderText_Blended(font->data,
                                           text,
                                           (SDL_Color){outlineColor.r,
                                                       outlineColor.g,
                                                       outlineColor.b,
                                                       outlineColor.a});
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

                SDL_Rect outlineRect = {position.x + offsets[i],
                                        position.y + offsets[j],
                                        outlineSurface->w,
                                        outlineSurface->h};

                SDL_RenderCopyEx(ctx->renderer,
                                 outlineTexture,
                                 NULL,
                                 &outlineRect,
                                 angle,
                                 (SDL_Point*)&origin,
                                 SDL_FLIP_NONE);

                // Clean up
                SDL_FreeSurface(outlineSurface);
                SDL_DestroyTexture(outlineTexture);
            }
        }
    }

    // Render the filled text
    SDL_Surface* textSurface = TTF_RenderText_Blended(
        font->data, text, (SDL_Color){color.r, color.g, color.b, color.a});
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
        position.x, position.y, textSurface->w, textSurface->h};

    SDL_RenderCopyEx(ctx->renderer,
                     textTexture,
                     NULL,
                     &textRect,
                     angle,
                     (SDL_Point*)&origin,
                     SDL_FLIP_NONE);

    // Clean up
    SDL_FreeSurface(textSurface);
    SDL_DestroyTexture(textTexture);
}
