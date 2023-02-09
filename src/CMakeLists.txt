set(PROJECT_NAME CustomWidgets)

project(${PROJECT_NAME})

set(SOURCES
    ChooseList/chooselist.cpp
    ChooseList/chooselist.h 
    ChooseList/chooselist.ui
    ChooseList/priv/customlistwidgetitem.h 
    ClipRectangle/ClipRectangle.cpp 
    ClipRectangle/ClipRectangle.h 
    ClipRectangle/rectgrabber.cpp 
    ClipRectangle/rectgrabber.h 
    ConsoleEditor/consoleeditor.cpp 
    ConsoleEditor/consoleeditor.h 
    ConsoleEditor/consoleeditor.ui 
    ConsoleEditor/priv/customtexteditor.cpp 
    ConsoleEditor/priv/customtexteditor.h 
    CustomWidgets_images.qrc
    Dropdown/dropdown.cpp 
    Dropdown/dropdown.h 
    Dropdown/dropdown.ui
    Dropdown/priv/dropdownp.cpp 
    Dropdown/priv/dropdownp.h 
    ExtComboEdit/extcomboedit.cpp 
    ExtComboEdit/extcomboedit.h 
    ExtComboEdit/extcombotype.h 
    GroupComboBox/groupcombobox.cpp 
    GroupComboBox/groupcombobox.h 
    HistoryTextEdit/customlistwidget.cpp 
    HistoryTextEdit/customlistwidget.h 
    HistoryTextEdit/historytextedit.cpp 
    HistoryTextEdit/historytextedit.h 
    HistoryTextEdit/historytextedit.ui 
    HistoryTextEdit/priv/combodelegate.cpp 
    HistoryTextEdit/priv/combodelegate.h 
    HistoryTextEdit/priv/listitem.cpp 
    HistoryTextEdit/priv/listitem.h 
    HistoryTextEdit/priv/listitem.ui 
    HtmlEditor/HtmlEditor.cpp 
    HtmlEditor/HtmlEditor.h 
    HtmlEditor/HtmlEditorDialog.cpp 
    HtmlEditor/HtmlEditorDialog.h 
    HtmlEditor/HtmlEditorDialog.ui 
    HtmlEditor/htmleditor.ui 
    LastProjectsMenu/lastprojectsmenu.cpp 
    LastProjectsMenu/lastprojectsmenu.h 
    LogWindow2/logwindow2.cpp 
    LogWindow2/logwindow2.h 
    LogWindow2/logwindow2.ui 
    LogWindow2/priv/delegate.cpp
    LogWindow2/priv/delegate.h
    LogWindow2/priv/imagelistview.cpp 
    LogWindow2/priv/imagelistview.h 
    LogWindow2/priv/itemsettings.cpp 
    LogWindow2/priv/itemsettings.h 
    LogWindow2/priv/itemsettingseditor.cpp 
    LogWindow2/priv/itemsettingseditor.h 
    LogWindow2/priv/itemsettingseditor.ui 
    LogWindow2/priv/itemsettingsmapeditor.cpp 
    LogWindow2/priv/itemsettingsmapeditor.h 
    LogWindow2/priv/itemsettingsmapeditor.ui 
    LogWindow2/priv/listviewmodel.cpp 
    LogWindow2/priv/listviewmodel.h 
    LogWindow2/priv/logwindow2p.cpp 
    LogWindow2/priv/logwindow2p.h 
    ManageProjects/manageprojects.cpp 
    ManageProjects/manageprojects.h 
    ManageProjects/manageprojects.ui 
    MyComboBox/mycombobox.cpp 
    MyComboBox/mycombobox.h 
    MyComboBox/mycombobox.ui 
    MyLineEdit/mylineedit.cpp 
    MyLineEdit/mylineedit.h 
    ProgressDialog/progressdialog.cpp 
    ProgressDialog/progressdialog.h 
    ProgressDialog/progressdialog.ui 
    ResizableView/resizableview.cpp 
    ResizableView/resizableview.h 
    ResizableView/resizableviewdialog.cpp   
    ResizableView/resizableviewdialog.h 
    ResizableView/resizableviewdialog.ui 
    RichLabel/richlabel.cpp 
    RichLabel/richlabel.h 
    XmlProjectEditor/varianmapeditor.cpp 
    XmlProjectEditor/varianmapeditor.h 
    XmlProjectEditor/varianmapeditor.ui 
    XmlProjectEditor/xmlitemdelegate.cpp 
    XmlProjectEditor/xmlitemdelegate.h 
    XmlProjectEditor/xmlprojecteditor.cpp 
    XmlProjectEditor/xmlprojecteditor.h 
    XmlProjectEditor/xmlprojecteditor.ui 
    exceptions.cpp 
    exceptions.h 
    export.h 
    project_pch.h 
)

set(CMAKE_AUTOUIC_SEARCH_PATHS
    LogWindow2
)

if(${PROJECT_NAME}_BUILD_STATIC)
    set(LIB_TYPE STATIC)
else()
    set(LIB_TYPE SHARED)
endif()


add_library(${PROJECT_NAME} ${LIB_TYPE} ${SOURCES})

target_link_libraries(${PROJECT_NAME}
    PRIVATE
    Qt5::Widgets
    Qt5::Xml
    Qt5::PrintSupport
    HelperLibrary
)

target_include_directories(${PROJECT_NAME}
    INTERFACE ${CMAKE_BINARY_DIR}/include/${PROJECT_NAME}
    PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/priv
)
target_precompile_headers(${PROJECT_NAME} PRIVATE project_pch.h)
target_compile_definitions(${PROJECT_NAME} PRIVATE "CUSTOM_WIDGETS_PLUGIN")

if(NOT ${PROJECT_NAME}_BUILD_STATIC)
    install(TARGETS ${PROJECT_NAME} RUNTIME DESTINATION ".")
else()
    target_compile_definitions(${PROJECT_NAME} PUBLIC "${PROJECT_NAME}_BUILD_STATIC")
endif()

moveHeaders()
deployTr()
aviaNames()
makeAI()
