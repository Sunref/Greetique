//
// gif.h
// by Charlie Tangora
// Public domain.
// Email me : ctangora -at- gmail -dot- com
//
// This file offers a simple, very limited way to create animated GIFs directly in code.
//
// Those looking for particular cleverness are likely to be disappointed; it's pretty
// much a straight-ahead implementation of the GIF format with optional Floyd-Steinberg
// dithering. (It does at least use delta encoding - only the changed portions of each
// frame are saved.)
//
// So resulting files are often quite large. The hope is that it will be handy nonetheless
// as a quick and easily-integrated way for programs to spit out animations.
//
// Only RGBA8 is currently supported as an input format. (The alpha is ignored.)
//
// If capturing a buffer with a bottom-left origin (such as OpenGL), define GIF_FLIP_VERT
// to automatically flip the buffer data when writing the image (the buffer itself is
// unchanged.
//
// USAGE:
// Create a GifWriter struct. Pass it to GifBegin() to initialize and write the header.
// Pass subsequent frames to GifWriteFrame().
// Finally, call GifEnd() to close the file handle and free memory.
//

#ifndef gif_h
#define gif_h

#include <stdio.h>   // for FILE*
#include <string.h>  // for memcpy and bzero
#include <stdint.h>  // for integer typedefs
#include <stdbool.h> // for bool macros

// Define these macros to hook into a custom memory allocator.
// TEMP_MALLOC and TEMP_FREE will only be called in stack fashion - frees in the reverse order of mallocs
// and any temp memory allocated by a function will be freed before it exits.
// MALLOC and FREE are used only by GifBegin and GifEnd respectively (to allocate a buffer the size of the image, which
// is used to find changed pixels for delta-encoding.)

#ifndef GIF_TEMP_MALLOC
#include <stdlib.h>
#define GIF_TEMP_MALLOC malloc
#endif

#ifndef GIF_TEMP_FREE
#include <stdlib.h>
#define GIF_TEMP_FREE free
#endif

#ifndef GIF_MALLOC
#include <stdlib.h>
#define GIF_MALLOC malloc
#endif

#ifndef GIF_FREE
#include <stdlib.h>
#define GIF_FREE free
#endif

typedef struct
{
    int bitDepth;

    uint8_t r[256];
    uint8_t g[256];
    uint8_t b[256];

    // k-d tree over RGB space, organized in heap fashion
    // i.e. left child of node i is node i*2, right child is node i*2+1
    // nodes 256-511 are implicitly the leaves, containing a color
    uint8_t treeSplitElt[256];
    uint8_t treeSplit[256];
} GifPalette;

// Simple structure to write out the LZW-compressed portion of the image
// one bit at a time
typedef struct
{
    uint32_t chunkIndex;
    uint8_t chunk[256];   // bytes are written in here until we have 256 of them, then written to the file
    uint8_t bitIndex;     // how many bits in the partial byte written so far
    uint8_t byte;         // current partial byte
    uint8_t padding[2];   // make padding explicit
} GifBitStatus;

// The LZW dictionary is a 256-ary tree constructed as the file is encoded,
// this is one node
typedef struct
{
    uint16_t m_next[256];
} GifLzwNode;

typedef struct
{
    FILE* f;
    uint8_t* oldImage;
    bool firstFrame;
    uint8_t padding[7];    // make padding explicit
} GifWriter;

// Creates a gif file.
// The input GIFWriter is assumed to be uninitialized.
// The delay value is the time between frames in hundredths of a second - note that not all viewers pay much attention to this value.
bool GifBegin(GifWriter* writer, const char* filename, uint32_t width, uint32_t height, uint32_t delay, int32_t bitDepth, bool dither);

// Writes out a new frame to a GIF in progress.
// The GIFWriter should have been created by GifBegin.
// AFAIK, it is legal to use different bit depths for different frames of an image -
// this may be handy to save bits in animations that don't change much.
bool GifWriteFrame(GifWriter* writer, const uint8_t* image, uint32_t width, uint32_t height, uint32_t delay, int bitDepth, bool dither);

// Writes the EOF code, closes the file handle, and frees temp memory used by a GIF.
// Many if not most viewers will still display a GIF properly if the EOF code is missing,
// but it's still a good idea to write it out.
bool GifEnd(GifWriter* writer);

#endif // gif_h