// Must be defined in one file, _before_ #include "clay.h"
#define CLAY_IMPLEMENTATION
#include "head/clay.h"
#include <stdio.h>

const Clay_Color COLOR_LIGHT = (Clay_Color) {224, 215, 210, 255};
const Clay_Color COLOR_RED = (Clay_Color) {168, 66, 28, 255};
const Clay_Color COLOR_ORANGE = (Clay_Color) {225, 138, 50, 255};

void HandleClayErrors(Clay_ErrorData errorData)
{
    // See the Clay_ErrorData struct for more information
    printf("%s", errorData.errorText.chars);
    switch(errorData.errorType)
    {
        case CLAY_ERROR_TYPE_TEXT_MEASUREMENT_FUNCTION_NOT_PROVIDED: {break;}
        case CLAY_ERROR_TYPE_ARENA_CAPACITY_EXCEEDED: {break;}
        case CLAY_ERROR_TYPE_ELEMENTS_CAPACITY_EXCEEDED: {break;}
        case CLAY_ERROR_TYPE_TEXT_MEASUREMENT_CAPACITY_EXCEEDED: {break;}
        case CLAY_ERROR_TYPE_DUPLICATE_ID: {break;}
        case CLAY_ERROR_TYPE_FLOATING_CONTAINER_PARENT_NOT_FOUND: {break;}
        case CLAY_ERROR_TYPE_PERCENTAGE_OVER_1: {break;}
        case CLAY_ERROR_TYPE_INTERNAL_ERROR: {break;}
    }
}

// Example measure text function
static inline Clay_Dimensions MeasureText(Clay_StringSlice text, Clay_TextElementConfig *config, uintptr_t userData)
{
    // Clay_TextElementConfig contains members such as fontId, fontSize, letterSpacing etc
    // Note: Clay_String->chars is not guaranteed to be null terminated
    return (Clay_Dimensions)
    {
            .width = text.length * config->fontSize, // <- this will only work for monospace fonts, see the renderers/ directory for more advanced text measurement
            .height = config->fontSize
    };
}

// Layout config is just a struct that can be declared statically, or inline
Clay_ElementDeclaration sidebarItemConfig = (Clay_ElementDeclaration)
{
    .layout =
    {
        .sizing = { .width = CLAY_SIZING_GROW(0), .height = CLAY_SIZING_FIXED(50) }
    },
    .backgroundColor = COLOR_ORANGE
};

// Re-useable components are just normal functions
void SidebarItemComponent()
{
    CLAY(sidebarItemConfig)
    {
        // children go here...
    }
}

int main()
{
    bool temp_loop = true;
    
    // Note: malloc is only used here as an example, any allocator that provides
    // a pointer to addressable memory of at least totalMemorySize will work
    uint64_t totalMemorySize = Clay_MinMemorySize();
    Clay_Arena arena = Clay_CreateArenaWithCapacityAndMemory(totalMemorySize, malloc(totalMemorySize));

    //TODO:
    float screenWidth = 1024;
    float screenHeight = 800;
    // Note: screenWidth and screenHeight will need to come from your environment, Clay doesn't handle window related tasks
    Clay_Initialize(arena, (Clay_Dimensions) { screenWidth, screenHeight }, (Clay_ErrorHandler) { HandleClayErrors });

    //TODO: replace bool with renderLoop() function, so we only exit when renderer calls it
    while(temp_loop)
    { 
        // Will be different for each renderer / environment
        // Optional: Update internal layout dimensions to support resizing
        Clay_SetLayoutDimensions((Clay_Dimensions) { screenWidth, screenHeight });

        //TODO:
        float mousePositionX = 100;
        float mousePositionY = 100;
        bool isMouseDown = false;
        // Optional: Update internal pointer position for handling mouseover / click / touch events - needed for scrolling & debug tools
        Clay_SetPointerState((Clay_Vector2) { mousePositionX, mousePositionY }, isMouseDown);

        //TODO:
        float mouseWheelX = 1;
        float mouseWheelY = 1;
        float deltaTime = 1000;
        // Optional: Update internal pointer position for handling mouseover / click / touch events - needed for scrolling and debug tools
        Clay_UpdateScrollContainers(true, (Clay_Vector2) { mouseWheelX, mouseWheelY }, deltaTime);

        // All clay layouts are declared between Clay_BeginLayout and Clay_EndLayout
        Clay_BeginLayout();

        //TODO:
        void* profilePicture = malloc(256);
        // An example of laying out a UI with a fixed width sidebar and flexible width main content
        CLAY({ .id = CLAY_ID("OuterContainer"), .layout = { .sizing = {CLAY_SIZING_GROW(0), CLAY_SIZING_GROW(0)}, .padding = CLAY_PADDING_ALL(16), .childGap = 16 }, .backgroundColor = {250,250,255,255} })
        {
            CLAY({
                .id = CLAY_ID("SideBar"),
                .layout = { .layoutDirection = CLAY_TOP_TO_BOTTOM, .sizing = { .width = CLAY_SIZING_FIXED(300), .height = CLAY_SIZING_GROW(0) }, .padding = CLAY_PADDING_ALL(16), .childGap = 16 },
                .backgroundColor = COLOR_LIGHT }) {}
        }
            
        CLAY({ .id = CLAY_ID("ProfilePictureOuter"), .layout = { .sizing = { .width = CLAY_SIZING_GROW(0) }, .padding = CLAY_PADDING_ALL(16), .childGap = 16, .childAlignment = { .y = CLAY_ALIGN_Y_CENTER } }, .backgroundColor = COLOR_RED })
        {
            CLAY({ .id = CLAY_ID("ProfilePicture"), .layout = { .sizing = { .width = CLAY_SIZING_FIXED(60), .height = CLAY_SIZING_FIXED(60) }}, .image = { .imageData = &profilePicture, .sourceDimensions = {60, 60} } }) {}
            CLAY_TEXT(CLAY_STRING("Clay - UI Library"), CLAY_TEXT_CONFIG({ .fontSize = 24, .textColor = {255, 255, 255, 255} }));
        }

        // Standard C code like loops etc work inside components
        for (int i = 0; i < 5; i++)
        {
            SidebarItemComponent();
        }
        CLAY({ .id = CLAY_ID("MainContent"), .layout = { .sizing = { .width = CLAY_SIZING_GROW(0), .height = CLAY_SIZING_GROW(0) } }, .backgroundColor = COLOR_LIGHT }) {}
    

        temp_loop = false;
    }

    // All clay layouts are declared between Clay_BeginLayout and Clay_EndLayout
    Clay_RenderCommandArray renderCommands = Clay_EndLayout();

    // More comprehensive rendering examples can be found in the renderers/ directory
    for (int i = 0; i < renderCommands.length; i++)
    {
        Clay_RenderCommand *renderCommand = &renderCommands.internalArray[i];

        switch (renderCommand->commandType)
        {
            case CLAY_RENDER_COMMAND_TYPE_RECTANGLE:
            {
                //TODO:
                //DrawRectangle( renderCommand->boundingBox, renderCommand->renderData.rectangle.backgroundColor);
            }
            case CLAY_RENDER_COMMAND_TYPE_NONE: {break;}
            case CLAY_RENDER_COMMAND_TYPE_BORDER: {break;}
            case CLAY_RENDER_COMMAND_TYPE_TEXT: {break;}
            case CLAY_RENDER_COMMAND_TYPE_IMAGE: {break;}
            case CLAY_RENDER_COMMAND_TYPE_SCISSOR_START: {break;}
            case CLAY_RENDER_COMMAND_TYPE_SCISSOR_END: {break;}
            case CLAY_RENDER_COMMAND_TYPE_CUSTOM: {break;}
        }
    }
}