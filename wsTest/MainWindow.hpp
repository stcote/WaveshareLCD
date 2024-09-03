#pragma once

#include <QMainWindow>

#include <WaveshareLCD.hpp>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
   Q_OBJECT

public:

   //*****************************************************************************
   //*****************************************************************************
   /**
    * @brief MainWindow
    * @param parent
    */
   //*****************************************************************************
   MainWindow(QWidget *parent = nullptr);
   ~MainWindow();

protected slots:

   //*****************************************************************************
   //*****************************************************************************
   /**
    * @brief handleSetup
    */
   //*****************************************************************************
   void handleSetup();

   //*****************************************************************************
   //*****************************************************************************
   /**
    * @brief handleClear
    */
   //*****************************************************************************
   void handleClear();

   //*****************************************************************************
   //*****************************************************************************
   /**
    * @brief handleDraw
    */
   //*****************************************************************************
   void handleDraw();

   //*****************************************************************************
   //*****************************************************************************
   /**
    * @brief handleDraw2
    */
   //*****************************************************************************
   void handleDraw2();

   //*****************************************************************************
   //*****************************************************************************
   /**
    * @brief handleGradient
    */
   //*****************************************************************************
   void handleGradient();

   //*****************************************************************************
   //*****************************************************************************
   /**
    * @brief handleImage
    */
   //*****************************************************************************
   void handleImage();

protected:

   // device
   WaveshareLCD disp_;

   // image buffer for Qt drawing
   WsBuffer* imgBuf_;

private:
   Ui::MainWindow *ui;
};
