#pragma once

#ifdef _DEBUG
    #ifdef USE_VLD
        #include <vld.h>
    #endif
#endif

#include <QComboBox>
#include <QToolButton>
#include <QHBoxLayout>
#include <QPainter>
#include <QScrollBar>
#include <QAction>
#include <QtConcurrent/QtConcurrent>
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QGraphicsPixmapItem>
#include <QMenu>
#include <QFileDialog>
#include <QContextMenuEvent>
#include <QClipboard>
#include <QCheckBox>
#include <QMessageBox>
#include <QLabel>
#include <QStandardItemModel>
#include <QMainWindow>
#include <QLineEdit>
#include <QTextEdit>
#include <QWidgetAction>
#include <QStylePainter>
#include <QMouseEvent>
#include <QRect>
#include <QTextDocumentWriter>
#include <QPrinter>
#include <QPrintPreviewDialog>
#include <QColorDialog>
#include <QApplication>
#include <QTextList>
#include <QMenuBar>
#include <QToolBar>
#include <QFontComboBox>
#include <QStatusBar>
#include <QPrintDialog>
#include <QAbstractPrintDialog>
#include <QSpacerItem>
#include <QDesktopWidget>
#include <QScreen>
#include <QFileSystemWatcher>
#include <QTextEdit>
#include <QItemDelegate>
#include <QCompleter>
#include <QFontDialog>
#include <QListView>
#include <QStyledItemDelegate>
#include <QInputDialog>

#include <QJsonArray>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonValue>

#ifdef Q_OS_WIN
    #include <Windows.h>
#endif


#include <HelperLibrary/converterfunctions.h>
#include <HelperLibrary/iobject.h>
#include <HelperLibrary/functions.h>
#include <HelperLibrary/Widgets/infowindow.h>
#include <HelperLibrary/Widgets/widgethelper.h>
#include <HelperLibrary/Widgets/myprogressdialog.h>
#include <HelperLibrary/LanguageHelper/languagehelper.h>
#include <HelperLibrary/Styles/iconsenum.h>
#include <HelperLibrary/Widgets/layoutsaver.h>
#include <HelperLibrary/Widgets/extendeddialog.h>
#include <HelperLibrary/Widgets/extendedwidget.h>
#include <HelperLibrary/ExtendApp/uilanginfo.h>
#include <HelperLibrary/anymacro.h>
#include <HelperLibrary/scopetimer.h>
#include <HelperLibrary/ivariant.h>
