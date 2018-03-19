#include "maincontroller.h"

MainController::MainController()
{
    this->newImage = 0;
    this->oldImage = 0;
}

MainController::~MainController()
{
   delete newImage;
   newImage = 0;

   delete oldImage;

   oldImage = 0

}
