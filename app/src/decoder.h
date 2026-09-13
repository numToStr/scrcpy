#ifndef SC_DECODER_H
#define SC_DECODER_H

#include "common.h"

#include <libavcodec/avcodec.h>

#include "coords.h"
#include "trait/frame_source.h"
#include "trait/packet_sink.h"

#ifdef HAVE_HWACCEL
struct sc_hwaccel;
#endif

struct sc_decoder {
    struct sc_packet_sink packet_sink; // packet sink trait
    struct sc_frame_source frame_source; // frame source trait

    const char *name; // must be statically allocated (e.g. a string literal)

    AVCodecContext *ctx;
    AVFrame *frame;

#ifdef HAVE_HWACCEL
    struct sc_hwaccel *hwaccel;
    int hwaccel_buffered_frames;
#endif

    struct sc_stream_session session; // only initialized for video stream
    struct sc_size frame_size;
};

// The name must be statically allocated (e.g. a string literal)
void
sc_decoder_init(struct sc_decoder *decoder, const char *name);

#ifdef HAVE_HWACCEL
void
sc_decoder_enable_hardware_decoding(struct sc_decoder *decoder,
                                    struct sc_hwaccel *hwaccel,
                                    int buffered_frames);
#endif

#endif
