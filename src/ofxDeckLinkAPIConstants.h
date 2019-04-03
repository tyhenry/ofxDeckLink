#pragma once

#include "ofMain.h"

// platform specific DeckLink include files :P
#ifdef TARGET_OSX
    #include "DeckLinkAPI.h"
    #define OFX_DECKLINK_COM_STR CFStringRef
    #define OFX_DECKLINK_COM_STR_RELEASE(A) CFRelease(A)
    #define OFX_DECKLINK_COM_STR_TO_CSTRING(COM_STR, CSTRING) CFStringGetCString(COM_STR, CSTRING, sizeof(CSTRING), kCFStringEncodingUTF8)
#endif

#ifdef TARGET_WIN32
    #include <objbase.h>        // Necessary for COM
    #include <comdef.h>			// Added

    #include "DeckLinkAPI_h.h"
    #define OFX_DECKLINK_COMSTR BSTR
    #define OFX_DECKLINK_COMSTR_RELEASE(COMSTR) SysFreeString(COMSTR);
    #define OFX_DECKLINK_COMSTR_TO_CSTRING(COMSTR, CSTRING) CSTRING = _com_util::ConvertBSTRToString(COMSTR)
#endif

#define OFX_DECKLINK_API_BEGIN_NAMESPACE namespace ofx { namespace DeckLinkAPI {
#define OFX_DECKLINK_API_END_NAMESPACE } }

OFX_DECKLINK_API_BEGIN_NAMESPACE


inline HRESULT GetDeckLinkIterator( IDeckLinkIterator **deckLinkIterator )
{
    HRESULT result = S_OK;

#ifdef TARGET_OSX
    *deckLinkIterator = CreateDeckLinkIteratorInstance();
    result = ( **deckLinkIterator == NULL ) ? E_FAIL : S_OK;
#endif

#ifdef TARGET_WIN32
    // Create an IDeckLinkIterator object to enumerate all DeckLink cards in the system
    result = CoCreateInstance( CLSID_CDeckLinkIterator, NULL, CLSCTX_ALL, IID_IDeckLinkIterator, ( void** )deckLinkIterator );
#endif

    return result;
}

const char* toString( _BMDDisplayMode mode );
const char* toString( _BMDPixelFormat mode );
const char* toString( _BMDFieldDominance mode );

struct Timecode {
    uint8_t hours;
    uint8_t minutes;
    uint8_t seconds;
    uint8_t frames;
    bool b_drop_frame;
    Timecode();

    int toFrameNum( int timebase ) const;
    string toString() const;

    bool operator==( const Timecode& vec ) const;
    bool operator!=( const Timecode& vec ) const;
};

OFX_DECKLINK_API_END_NAMESPACE

namespace ofxDeckLinkAPI = ofx::DeckLinkAPI;