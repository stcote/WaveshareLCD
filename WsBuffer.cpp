#include "WsBuffer.hpp"

//*****************************************************************************
//*****************************************************************************
WsBuffer::WsBuffer(quint16 w, quint16 h, Format fmt) :
   QImage( w, h, fmt ),
   outBufSize_(sizeInBytes()/2),
   outBuffer_(new quint16[outBufSize_]),
   orgWidth_(w),
   orgHeight_(h),
   orgFormat_(fmt)
{

}

//*****************************************************************************
//*****************************************************************************
WsBuffer::~WsBuffer()
{
   delete [] outBuffer_;
}
