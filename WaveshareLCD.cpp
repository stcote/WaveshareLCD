#include "WaveshareLCD.hpp"
#include <QImage>
#include "DEV_Config.hpp"
#include "LCD_1in28.hpp"

//*****************************************************************************
//*****************************************************************************
WaveshareLCD::WaveshareLCD()
    : deviceName_(NO_DEVICE)
    , deviceWidth_(0)
    , deviceHeight_(0)
    , deviceDepth_(16)
    , imageFormat_(QImage::Format_RGB16)
    , isValid_(false)
    , imgBuffer_(nullptr)
    , invalidBuffer_(1, 1, QImage::Format_Invalid)
    , bufferList_()
    , deviceInit(nullptr)
    , deviceDisplay(nullptr)
    , deviceClear(nullptr)
{
}

//*****************************************************************************
//*****************************************************************************
WaveshareLCD::~WaveshareLCD()
{
   // free all buffers
   qDeleteAll( bufferList_ );
   bufferList_.clear();

   // de-initialize
   DEV_ModuleExit();
}

//*****************************************************************************
//*****************************************************************************
bool WaveshareLCD::setDevice(WS_DEVICES device)
{
   // save the device type
   deviceName_ = device;

   // initialize the module
   if ( DEV_ModuleInit() != 0 )
   {
      // error
      DEV_ModuleExit();
      return false;
   }

   // set up for the particular device
   return setupDevice( device );
}

//*****************************************************************************
//*****************************************************************************
bool WaveshareLCD::setupDevice(WS_DEVICES device)
{
   bool deviceFound = false;

   // iterate through devices
   if ( device == WS_LCD_1IN28 )
   {
      deviceInit           = LCD_1IN28_Init;
      deviceClear          = LCD_1IN28_Clear;
      deviceDisplay        = LCD_1IN28_Display;

      // dimensions
      deviceWidth_= LCD_1IN28_WIDTH;
      deviceHeight_= LCD_1IN28_HEIGHT;
      deviceDepth_ = 16;
      imageFormat_ = QImage::Format_RGB16;

      // indicate that we have found the device
      deviceFound = true;
   }

   isValid_ = deviceFound;

   // more setup
   if ( isValid_ )
   {
      // initialize
      deviceInit(HORIZONTAL);

      // clear the display and st the backlighting
      deviceClear(0);
      LCD_SetBacklight(1023);

      // create the initial buffer
      imgBuffer_ = createNewBuffer();
   }

   // ensure that we found the device
   return deviceFound;
}

//*****************************************************************************
//*****************************************************************************
WsBuffer* WaveshareLCD::createNewBuffer()
{
   if ( isValid_ )
   {
      WsBuffer* buf = new WsBuffer( deviceWidth_, deviceHeight_, imageFormat_ );

      bufferList_ << buf;

      return buf;
   }

   // not set up yet
   return nullptr;
}

//*****************************************************************************
//*****************************************************************************
WsBuffer* WaveshareLCD::createBufferFromImageFile(const QString& fileName, bool deleteLater)
{
   if ( isValid_ )
   {
      QImage img;
      bool resp = false;

      resp = img.load( fileName );

      if ( resp )
      {
         WsBuffer* buf = new WsBuffer( deviceWidth_, deviceHeight_, imageFormat_ );

         dynamic_cast<QImage&>(*buf) = img.scaled( deviceWidth_, deviceHeight_ ).convertToFormat( imageFormat_ );

         if ( deleteLater )
            bufferList_ << buf;

         return buf;
      }
   }

   // not set up yet
   return nullptr;
}

//*****************************************************************************
//*****************************************************************************
WsBuffer* WaveshareLCD::defaultBuffer()
{
   if ( isValid_ && imgBuffer_ )
   {
      return imgBuffer_;
   }

   // invalid buffer
   return &invalidBuffer_;
}

//*****************************************************************************
//*****************************************************************************
void WaveshareLCD::updateDisplay(WsBuffer& imageBuffer)
{
   if ( !isValid_ ) return;

   auto numWords = imageBuffer.dataSize();

   // use output buffer from this image buffer
   quint16* outBuf = imageBuffer.outBuf();

   // get input buffer from the source buffer
   const quint16* inBuf = (const quint16*)imageBuffer.constBits();

   // populate output buffer with byte swapped version of input buffer
   for ( quint32 i=0; i<numWords; i++ )
   {
      outBuf[i] = __builtin_bswap16(inBuf[i]);
   }

   // update the display
   deviceDisplay( outBuf );
}

//*****************************************************************************
//*****************************************************************************
void WaveshareLCD::updateDisplay()
{
   // default to initial buffer
   if ( isValid_ && imgBuffer_ )
   {
      updateDisplay( *imgBuffer_ );
   }
}
