#include "MainWindow.hpp"
#include "ui_MainWindow.h"

#include <QPainter>
#include <QLinearGradient>
#include <QThread>

//*****************************************************************************
//*****************************************************************************
MainWindow::MainWindow(QWidget *parent) :
   QMainWindow(parent),
   disp_(),
   imgBuf_(nullptr),
   ui(new Ui::MainWindow)

{
   ui->setupUi(this);

   // connect buttons
   connect( ui->clearBtn, SIGNAL(clicked()), SLOT(handleClear()) );
   connect( ui->drawBtn, SIGNAL(clicked()), SLOT(handleDraw()) );
   connect( ui->draw2Btn, SIGNAL(clicked()), SLOT(handleDraw2()) );
   connect( ui->gradientBtn, SIGNAL(clicked()), SLOT(handleGradient() ));
   connect( ui->imageBtn, SIGNAL(clicked()), SLOT(handleImage()));

   // setup at start
   handleSetup();
}

//*****************************************************************************
//*****************************************************************************
MainWindow::~MainWindow()
{
   delete ui;
}

//*****************************************************************************
//*****************************************************************************
void MainWindow::handleSetup()
{
   ui->textEdit->append( "Setup..." );

   // set up display
   if ( disp_.setDevice( WaveshareLCD::WS_LCD_1IN28 ) )
   {
      ui->textEdit->append("  display initialized ");
   }
}

//*****************************************************************************
//*****************************************************************************
void MainWindow::handleClear()
{
   ui->textEdit->append( "Clear..." );

   QPainter p(disp_.defaultBuffer());

   p.fillRect( disp_.defaultBuffer()->rect(), Qt::black );

   disp_.updateDisplay();
}

//*****************************************************************************
//*****************************************************************************
void MainWindow::handleDraw()
{
   ui->textEdit->append( "Draw..." );

   QPainter p(disp_.defaultBuffer());

   p.save();

   p.setPen( Qt::red );
   p.drawLine( 120, 120, 180, 180 );

   disp_.updateDisplay();

   p.restore();
}

//*****************************************************************************
//*****************************************************************************
void MainWindow::handleDraw2()
{
   ui->textEdit->append( "Draw 2..." );

   // create background image in buffer
   QPainter p(disp_.defaultBuffer());

   p.setPen(Qt::blue);
   p.setBrush(Qt::NoBrush);

   // center in display
   quint16 center = disp_.getWidth() / 2;

   quint16 diff = 5;

   // bounding rectangle
   QRect r( center-diff, center-diff, diff*2, diff*2 );

   // draw concentric boxes
   for (int i=0; i<15; i++ )
   {
      p.drawRoundedRect( r, diff, diff );

      r.adjust( -diff, -diff, diff, diff );
   }

   // display background
   disp_.updateDisplay();

   // finish with painter
   p.end();

   QThread::msleep( 1000 );

   // pointer to image buffer
   WsBuffer* buf = disp_.defaultBuffer();

   // pointer to buffer that background will be saved in
   WsBuffer* bgBuf = disp_.createNewBuffer();

   // save created image to background buffer
   *bgBuf = *buf;

   // rotation value ( 270 = straight up)
   double rotateVal = 270;

   // draw line in all 'second' positions
   for ( int i=0; i<61; i++ )
   {
      // start with image in background buffer
      *buf = *bgBuf;

      // need painter for current buffer
      QPainter p2( buf );

      // line color
      p2.setPen(Qt::yellow);

      // make center of display the center of the coordinate system
      p2.translate(center,center);

      // set to the current rotation value
      p2.rotate(rotateVal);

      // draw the line
      p2.drawLine( 0, 0, 100, 0 );

      // display it
      disp_.updateDisplay();

      // move to next 'second hand' position
      rotateVal += 6;

      // can't use this painter with buffer after image is copied to it next time
      p2.end();

      // wait a bit
      QThread::msleep( 10 );
   }
}

//*****************************************************************************
//*****************************************************************************
void MainWindow::handleGradient()
{
   ui->textEdit->append( "Draw Gradient..." );

   QPainter p(disp_.defaultBuffer());

   QLinearGradient shade(0, 0, disp_.getWidth()-1, disp_.getHeight()-1);

   shade.setSpread( QGradient::PadSpread );

   shade.setColorAt( 0, Qt::red );
   shade.setColorAt( 1, Qt::blue );

   QRect r = disp_.defaultBuffer()->rect();

   // add text

   p.setPen(Qt::white);

   auto font = p.font();
   font.setPointSize( font.pointSize() + 6 );
   p.setFont( font );

   qreal rotateVal = 0;

   for ( int i=0; i<61; i++ )
   {
      p.fillRect( r, shade );

      p.save();

      p.translate( r.center() );
      p.rotate( rotateVal );
      p.translate( -r.center() );


      p.drawText( r, Qt::AlignCenter, "Hello world!" );

      p.restore();

      disp_.updateDisplay();

      rotateVal += 6.0;

      // wait a bit
      QThread::msleep( 10 );
   }

//   p.translate( r.center() );
//   p.rotate( 90 );
//   p.translate( -r.center() );


//   p.drawText( r, Qt::AlignCenter, "Hello world!" );

//   disp_.updateDisplay();

}

//*****************************************************************************
//*****************************************************************************
void MainWindow::handleImage()
{
   ui->textEdit->append( "Draw image..." );

   auto buf = disp_.createBufferFromImageFile( "LucyCloseUp.jpg", false );

   if ( buf )
      {
      ui->textEdit->append("File read OK");
      disp_.updateDisplay( *buf );
      delete buf;
      }
   else
      ui->textEdit->append("Error reading file");
}

