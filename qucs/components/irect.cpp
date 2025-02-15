/***************************************************************************
                                 irect.cpp
                                -----------
    begin                : Sat Sep 18 2004
    copyright            : (C) 2004 by Michael Margraf
    email                : michael.margraf@alumni.tu-berlin.de
 ***************************************************************************/

/***************************************************************************
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 ***************************************************************************/

#include "irect.h"


iRect::iRect()
{
  Description = QObject::tr("ideal rectangle current source");

  Arcs.push_back(qucs::Arc(-12,-12, 24, 24,  0, 16*360,QPen(Qt::darkBlue,2)));
  Lines.push_back(qucs::Line(-30,  0,-12,  0,QPen(Qt::darkBlue,2)));
  Lines.push_back(qucs::Line( 30,  0, 12,  0,QPen(Qt::darkBlue,2)));
  Lines.push_back(qucs::Line( -7,  0,  7,  0,QPen(Qt::darkBlue,3)));
  Lines.push_back(qucs::Line(  6,  0,  0, -4,QPen(Qt::darkBlue,3)));
  Lines.push_back(qucs::Line(  6,  0,  0,  4,QPen(Qt::darkBlue,3)));

  // little rectangle symbol
  Lines.push_back(qucs::Line( 19,  5, 19,  7,QPen(Qt::darkBlue,2)));
  Lines.push_back(qucs::Line( 13,  7, 19,  7,QPen(Qt::darkBlue,2)));
  Lines.push_back(qucs::Line( 13,  7, 13, 11,QPen(Qt::darkBlue,2)));
  Lines.push_back(qucs::Line( 13, 11, 19, 11,QPen(Qt::darkBlue,2)));
  Lines.push_back(qucs::Line( 19, 11, 19, 15,QPen(Qt::darkBlue,2)));
  Lines.push_back(qucs::Line( 13, 15, 19, 15,QPen(Qt::darkBlue,2)));
  Lines.push_back(qucs::Line( 13, 15, 13, 17,QPen(Qt::darkBlue,2)));

  Ports.push_back(qucs::Port( 30,  0));
  Ports.push_back(qucs::Port(-30,  0));

  x1 = -30; y1 = -14;
  x2 =  30; y2 =  20;

  tx = x1+4;
  ty = y2+4;
  Model = "Irect";
  Name  = "I";

  Props.push_back(qucs::Property("I", "1 mA", true,
		QObject::tr("current at high pulse")));
  Props.push_back(qucs::Property("TH", "1 ms", true,
		QObject::tr("duration of high pulses")));
  Props.push_back(qucs::Property("TL", "1 ms", true,
		QObject::tr("duration of low pulses")));
  Props.push_back(qucs::Property("Tr", "1 ns", false,
		QObject::tr("rise time of the leading edge")));
  Props.push_back(qucs::Property("Tf", "1 ns", false,
		QObject::tr("fall time of the trailing edge")));
  Props.push_back(qucs::Property("Td", "0 ns", false,
		QObject::tr("initial delay time")));

  rotate();  // fix historical flaw
}

iRect::~iRect()
{
}

Component* iRect::newOne()
{
  return new iRect();
}

Element* iRect::info(QString& Name, char* &BitmapFile, bool getNewOne)
{
  Name = QObject::tr("Rectangle Current");
  BitmapFile = (char *) "irect";

  if(getNewOne)  return new iRect();
  return 0;
}
