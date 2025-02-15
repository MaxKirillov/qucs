/***************************************************************************
                               module.h
                              ----------
    begin                : Thu Nov 5 2009
    copyright            : (C) 2009 by Stefan Jahn
    email                : stefan@lkcc.org
 ***************************************************************************/

/***************************************************************************
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 ***************************************************************************/

#ifndef MODULE_H
#define MODULE_H

#include <QList>
#include <QHash>
#include <QMap>

#include <memory>

class Element;

// function typedefs for circuits and analyses
typedef Element * (* pInfoFunc) (QString&, char * &, bool);
typedef Element * (* pInfoVAFunc) (QString&, QString&, bool, QString);
typedef Component * (* pCreatorFunc) ();

class Module
{
 public:
  Module ();
  ~Module ();
  static void registerModule (QString, pInfoFunc);
  static void registerComponent (QString, pInfoFunc);
  static void intoCategory (Module *);
  static std::shared_ptr<Component> getComponent(QString);
  static void registerDynamicComponents(void);

 public:
  static QHash<QString, Module *> Modules;
  static QMap<QString, QString> vaComponents;

 public:
  static void registerModules (void);
  static void unregisterModules (void);

 public:
  pInfoFunc info = 0;
  pInfoVAFunc infoVA = 0;
  QString category;
};

class Category
{
 public:
  Category ();
  Category (const QString);
  ~Category ();

 public:
  static QList<Category *> Categories;

 public:
  static QStringList getCategories (void);
  static QList<Module *> getModules (QString);
  static int getModulesNr (QString);

 public:
  QString Name;
  QList<Module *> Content;
};

#endif /* __MODULE_H__ */
