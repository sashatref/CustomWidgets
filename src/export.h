#pragma once

#include <QtCore/qglobal.h>

#ifdef CustomWidgets_BUILD_STATIC
    #define WIDGET_EXPORT
#else
    #if defined(CUSTOM_WIDGETS_PLUGIN)
        #define WIDGET_EXPORT Q_DECL_EXPORT
    #else
        #define WIDGET_EXPORT Q_DECL_IMPORT
    #endif
#endif
