/***************************************************************************
                          msmbend.cpp  -  description
                             -------------------
    begin                : Sat Aug 23 2003
    copyright            : (C) 2003 by Michael Margraf
    email                : margraf@mwt.ee.tu-berlin.de
 ***************************************************************************/

/***************************************************************************
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 ***************************************************************************/

#include "msmbend.h"


MSmbend::MSmbend()
{
  Description = QObject::tr("microstrip mitered bend");

  Lines.append(new Line(-30,  0,-18,  0,QPen(QPen::darkBlue,2)));
  Lines.append(new Line(  0, 18,  0, 30,QPen(QPen::darkBlue,2)));
  Lines.append(new Line(-18, -8, -8, -8,QPen(QPen::darkBlue,2)));
  Lines.append(new Line( -8, -8,  8,  8,QPen(QPen::darkBlue,2)));
  Lines.append(new Line(-18,  8, -8,  8,QPen(QPen::darkBlue,2)));
  Lines.append(new Line(-18, -8,-18,  8,QPen(QPen::darkBlue,2)));
  Lines.append(new Line( -8,  8, -8, 18,QPen(QPen::darkBlue,2)));
  Lines.append(new Line(  8,  8,  8, 18,QPen(QPen::darkBlue,2)));
  Lines.append(new Line( -8, 18,  8, 18,QPen(QPen::darkBlue,2)));

  Lines.append(new Line(-22, -4,-26,  4,QPen(QPen::darkBlue,2)));

  Ports.append(new Port(-30, 0));
  Ports.append(new Port(  0,30));

  x1 = -30; y1 = -9;
  x2 =   9; y2 = 30;

  tx = x1+4;
  ty = y2+4;
  Sign  = "MMBEND";
  Model = "MMBEND";
  Name  = "MS";

  Props.append(new Property("Subst", "Subst1", true, QObject::tr("substrate")));
  Props.append(new Property("W1", "1 mm", true, QObject::tr("width of line 1")));
  Props.append(new Property("W2", "2 mm", true, QObject::tr("width of line 2")));
}

MSmbend::~MSmbend()
{
}

MSmbend* MSmbend::newOne()
{
  return new MSmbend();
}