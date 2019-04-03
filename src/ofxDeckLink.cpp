#include "ofxDeckLink.h"

OFX_DECKLINK_API_BEGIN_NAMESPACE

vector<Device> listDevice()
{
    vector<Device> devinfo;

    cout << "==== ofxDeckLinkAPI::listDevice() ====" << endl;

    IDeckLink* deckLink = NULL;
    HRESULT result;
    int num_device = 0;

    IDeckLinkIterator* deckLinkIterator;
    result = GetDeckLinkIterator( &deckLinkIterator );

    if( deckLinkIterator == NULL ) {
        ofLogError( "ofxDeckLinkAPI::Monitor" ) << "This application requires the DeckLink drivers installed." << "\n" << "Please install the Blackmagic DeckLink drivers to use the features of this application.";
        return devinfo;
    }

    while( deckLinkIterator->Next( &deckLink ) == S_OK ) {
        Device dev;
        OFX_DECKLINK_COMSTR deviceNameString = NULL;

        result = deckLink->GetModelName( &deviceNameString );

        if( result == S_OK ) {
#ifdef TARGET_WIN32
            char * deviceName = _com_util::ConvertBSTRToString( deviceNameString );
            stringstream deviceNameStream;
            deviceNameStream << deviceName;
            cout << num_device << ": " << deviceNameStream;
            dev.model_name = deviceNameStream.str();
#endif
#ifdef TARGET_OSX
            char deviceName[64];
            CFStringGetCString( deviceNameString, deviceName, sizeof( deviceName ), kCFStringEncodingUTF8 );
            stringstream deviceNameStream;
            deviceNameStream << deviceName;
            cout << num_device << ": " << deviceNameStream;
            dev.model_name = deviceNameStream.str();
#endif
            OFX_DECKLINK_COMSTR_RELEASE( deviceNameString );

        }

        IDeckLinkProfileAttributes*	attr = NULL;
        deckLink->QueryInterface( IID_IDeckLinkProfileAttributes, ( void** )&attr );

        if( attr != NULL ) {
            {
                int64_t v = 0;

                if( attr->GetInt( BMDDeckLinkPersistentID, &v ) == S_OK ) {
                    dev.persistent_id = v;
                    cout << ", pid:" << v;
                }
            }
            {
                int64_t v = 0;

                if( attr->GetInt( BMDDeckLinkTopologicalID, &v ) == S_OK ) {
                    dev.topological_id = v;
                    cout << ", tid:" << v;
                }
            }
        }

        cout << endl;
        devinfo.push_back( dev );

        deckLink->Release();

        num_device++;
    }

    if( num_device == 0 )
    { cout << "device not found" << endl; }

    cout << "======================================" << endl << endl;

    if( deckLinkIterator != NULL ) {
        deckLinkIterator->Release();
        deckLinkIterator = NULL;
    }

    return devinfo;
}

OFX_DECKLINK_API_END_NAMESPACE
