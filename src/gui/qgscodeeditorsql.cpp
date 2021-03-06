/***************************************************************************
    qgscodeeditorsql.cpp - A SQL editor based on QScintilla
     --------------------------------------
    Date                 : 06-Oct-2013
    Copyright            : (C) 2013 by Salvatore Larosa
    Email                : lrssvtml (at) gmail (dot) com
 ***************************************************************************
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 ***************************************************************************/

#include "qgsapplication.h"
#include "qgscodeeditorsql.h"
#include "qgssymbollayerutils.h"

#include <QWidget>
#include <QString>
#include <QFont>


QgsCodeEditorSQL::QgsCodeEditorSQL( QWidget *parent )
  : QgsCodeEditor( parent )
{
  if ( !parent )
  {
    setTitle( tr( "SQL Editor" ) );
  }
  setMarginVisible( false );
  setFoldingVisible( true );
  setAutoCompletionCaseSensitivity( false );
  initializeLexer();
}

void QgsCodeEditorSQL::initializeLexer()
{
  QFont font = getMonospaceFont();
  QColor defaultColor = color( ColorRole::Default );

  mSqlLexer = new QgsCaseInsensitiveLexerSQL( this );
  mSqlLexer->setDefaultFont( font );
  mSqlLexer->setDefaultColor( defaultColor );
  mSqlLexer->setDefaultPaper( color( ColorRole::Background ) );
  mSqlLexer->setFont( font, -1 );
  font.setBold( true );
  mSqlLexer->setFont( font, QsciLexerSQL::Keyword );

  mSqlLexer->setColor( defaultColor, QsciLexerSQL::Default );
  mSqlLexer->setColor( color( ColorRole::Comment ), QsciLexerSQL::Comment );
  mSqlLexer->setColor( color( ColorRole::CommentLine ), QsciLexerSQL::CommentLine );
  mSqlLexer->setColor( color( ColorRole::Number ), QsciLexerSQL::Number );
  mSqlLexer->setColor( color( ColorRole::Keyword ), QsciLexerSQL::Keyword );
  mSqlLexer->setColor( color( ColorRole::SingleQuote ), QsciLexerSQL::SingleQuotedString );
  mSqlLexer->setColor( color( ColorRole::DoubleQuote ), QsciLexerSQL::DoubleQuotedString );
  mSqlLexer->setColor( color( ColorRole::Operator ), QsciLexerSQL::Operator );
  mSqlLexer->setColor( color( ColorRole::Identifier ), QsciLexerSQL::Identifier );
  mSqlLexer->setColor( color( ColorRole::QuotedIdentifier ), QsciLexerSQL::QuotedIdentifier );
  mSqlLexer->setColor( color( ColorRole::QuotedOperator ), QsciLexerSQL::QuotedOperator );

  setLexer( mSqlLexer );
}

void QgsCodeEditorSQL::setFields( const QgsFields &fields )
{
  mFieldNames.clear();

  for ( const QgsField &field : fields )
  {
    mFieldNames << field.name();
  }

  updateApis();
}

void QgsCodeEditorSQL::updateApis()
{
  mApis = new QsciAPIs( mSqlLexer );

  for ( const QString &fieldName : qgis::as_const( mFieldNames ) )
  {
    mApis->add( fieldName );
  }

  mApis->prepare();
  mSqlLexer->setAPIs( mApis );
}
