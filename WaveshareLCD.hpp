#pragma once

#include <QtCore>
#include <QDateTime>
#include <QTime>

#include "WsBuffer.hpp"

//*****************************************************************************
//*****************************************************************************
/**
 * @brief The WaveshareLCDLCD class
 */
//*****************************************************************************
class WaveshareLCD
{
public:

   // supported devices
   enum WS_DEVICES { NO_DEVICE, WS_LCD_1IN28 };

   //*****************************************************************************
   //*****************************************************************************
   /**
    * @brief WaveshareLCD constructor
    * @param device - constant indicating device to be used
    */
   //*****************************************************************************
   WaveshareLCD();

   //*****************************************************************************
   //*****************************************************************************
   /**
    * @brief WaveshareLCD destructor
    * @param device - constant indicating device to be used
    */
   //*****************************************************************************
   ~WaveshareLCD();

   //*****************************************************************************
   //*****************************************************************************
   /**
    * @brief setDevice - sets the type of display being used. The 'deviceInitialized()'
    *             signal will be emitted after initialization is complete (or error)
    * @param device - enum that defines the device being used
    * @param scanDir - scan direction ( HORIZONTAL or VERTICAL )
    * @return TRUE if device name is accepted and initialization has started.
   */
   //*****************************************************************************
   bool setDevice( WS_DEVICES device );

   //*****************************************************************************
   //*****************************************************************************
   /**
    * @brief isValid - determines if the indicated device is supported and available
    * @return TRUE if valid
    */
   //*****************************************************************************
   bool isValid() { return isValid_; }

   //*****************************************************************************
   //*****************************************************************************
   /**
    * @brief defaultBuffer - gets the initial buffer (QImage) that is created for a device
    * @return pointer to the initial buffer
    */
   //*****************************************************************************
   WsBuffer* defaultBuffer();

   //*****************************************************************************
   //*****************************************************************************
   /**
    * @brief generateBuffer - creates and returns a pointer to a buffer (QImage) object
    * @return - pointer to new output buffer object
    */
   //*****************************************************************************
   WsBuffer* createNewBuffer();

   //*****************************************************************************
   //*****************************************************************************
   /**
    * @brief createBufferFromImageFile
    * @param fileName
    * @return
    */
   //*****************************************************************************
   WsBuffer* createBufferFromImageFile( const QString& fileName, bool deleteLater = true );

   //*****************************************************************************
   //*****************************************************************************
   /**
    * @brief getWidth
    * @return
    */
   //*****************************************************************************
   quint16 getWidth() { return deviceWidth_; }

   //*****************************************************************************
   //*****************************************************************************
   /**
    * @brief getHeight
    * @return
    */
   //*****************************************************************************
   quint16 getHeight() { return deviceHeight_; }

   //*****************************************************************************
   //*****************************************************************************
   /**
    * @brief getFormat
    * @return
    */
   //*****************************************************************************
   QImage::Format getFormat() { return imageFormat_; }

   //*****************************************************************************
   //*****************************************************************************
   /**
    * @brief updateDisplayWithImage
    * @param imageBuffer
    */
   //*****************************************************************************
   void updateDisplay( WsBuffer& imageBuffer );

   //*****************************************************************************
   //*****************************************************************************
   /**
    * @brief updateDisplayWithImage
    * @param imageBuffer
    */
   //*****************************************************************************
   void updateDisplay();

protected:

   //*****************************************************************************
   //*****************************************************************************
   /**
    * @brief setupDevice - sets up the function pointers for the specified device
    * @param device - enum indicating device
    */
   //*****************************************************************************
   bool setupDevice(WS_DEVICES device);

   // device name
   WS_DEVICES deviceName_;

   // device size
   quint16 deviceWidth_;
   quint16 deviceHeight_;
   quint16 deviceDepth_;
   QImage::Format imageFormat_;

   // validity flag
   bool isValid_;

   // initial image buffer
   WsBuffer* imgBuffer_;

   // WsBuffer returned when requested buffer is invalid
   WsBuffer invalidBuffer_;

   // list of output buffer objects
   QList<WsBuffer*> bufferList_;

   // function pointers
   void (*deviceInit)(quint8 scanDir);
   void (*deviceDisplay)(quint16* image);
   void (*deviceClear)(quint16 color);
};
