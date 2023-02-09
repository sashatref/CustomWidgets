#include "../project_pch.h"

#include "HtmlEditor.h"
#include "ui_htmleditor.h"

#include "../ResizableView/resizableviewdialog.h"

namespace CustomWidgetsQt
{

const QString rsrcPath = ":/CustomWidgets/Images/HtmlEditor";

HtmlEditor::HtmlEditor(QWidget *parent)
    : QMainWindow(),
      ui(new Ui::HtmlEditor()),
      m_isReadOnly(false)
{
    ui->setupUi(this);

    setWindowTitle(QCoreApplication::applicationName());

    connect(parent, &QWidget::destroyed, this, &HtmlEditor::deleteLater);
    connect(ui->textEdit, &QTextEdit::currentCharFormatChanged,
            this, &HtmlEditor::currentCharFormatChanged);
    connect(ui->textEdit, &QTextEdit::cursorPositionChanged,
            this, &HtmlEditor::cursorPositionChanged);

    setToolButtonStyle(Qt::ToolButtonFollowStyle);
    setupFileActions();
    setupEditActions();
    setupTextActions();

    QFont textFont("Helvetica");
    textFont.setStyleHint(QFont::SansSerif);
    ui->textEdit->setFont(textFont);
    fontChanged(ui->textEdit->font());
    colorChanged(ui->textEdit->textColor());
    alignmentChanged(ui->textEdit->alignment());

    connect(ui->textEdit->document(), &QTextDocument::modificationChanged,
            ui->actionSave, &QAction::setEnabled);
    connect(ui->textEdit->document(), &QTextDocument::modificationChanged,
            this, &QWidget::setWindowModified);
    connect(ui->textEdit->document(), &QTextDocument::undoAvailable,
            ui->actionUndo, &QAction::setEnabled);
    connect(ui->textEdit->document(), &QTextDocument::redoAvailable,
            ui->actionRedo, &QAction::setEnabled);

    connect(ui->textEdit, &QTextEdit::copyAvailable, this, [this](bool _isAvalaible)
    {
        ui->actionCopy->setEnabled(_isAvalaible);
        ui->actionCut->setEnabled(_isAvalaible);
    });

    setWindowModified(ui->textEdit->document()->isModified());
    ui->actionSave->setEnabled(ui->textEdit->document()->isModified());
    ui->actionUndo->setEnabled(ui->textEdit->document()->isUndoAvailable());
    ui->actionRedo->setEnabled(ui->textEdit->document()->isRedoAvailable());

#ifndef QT_NO_CLIPBOARD
    ui->actionCut->setEnabled(false);
    ui->actionCopy->setEnabled(false);

    connect(QApplication::clipboard(), &QClipboard::dataChanged, this, &HtmlEditor::clipboardDataChanged);
#endif

    ui->textEdit->setFocus();
    setCurrentFileName(QString());

    ui->textEdit->zoomIn(3);
}

void HtmlEditor::closeEvent(QCloseEvent *e)
{
    if (maybeSave())
        e->accept();
    else
        e->ignore();
}

void HtmlEditor::setupFileActions()
{
    ui->actionNew->setPriority(QAction::LowPriority);
    ui->actionNew->setShortcut(QKeySequence::New);
    connect(ui->actionNew, &QAction::triggered, this, &HtmlEditor::fileNew);

    ui->actionOpen->setShortcut(QKeySequence::Open);
    connect(ui->actionOpen, &QAction::triggered, this, &HtmlEditor::fileOpen);

    ui->actionSave->setShortcut(QKeySequence::Save);
    ui->actionSave->setEnabled(false);
    connect(ui->actionSave, &QAction::triggered, this, &HtmlEditor::fileSave);

    ui->actionSave_as->setPriority(QAction::LowPriority);
    connect(ui->actionSave_as, &QAction::triggered, this, &HtmlEditor::fileSaveAs);

#ifndef QT_NO_PRINTER
    ui->actionPrint->setPriority(QAction::LowPriority);
    ui->actionPrint->setShortcut(QKeySequence::Print);
    connect(ui->actionPrint, &QAction::triggered, this, &HtmlEditor::filePrint);

    connect(ui->actionPrint_preview, &QAction::triggered, this, &HtmlEditor::filePrintPreview);

    ui->actionExportPDF->setPriority(QAction::LowPriority);
    ui->actionExportPDF->setShortcut(Qt::CTRL + Qt::Key_D);
    connect(ui->actionExportPDF, &QAction::triggered, this, &HtmlEditor::filePrintPdf);
#endif
}

void HtmlEditor::setupEditActions()
{
    ui->actionUndo->setShortcut(QKeySequence::Undo);
    connect(ui->actionUndo, &QAction::triggered, ui->textEdit, &QTextEdit::undo);

    ui->actionRedo->setPriority(QAction::LowPriority);
    ui->actionRedo->setShortcut(QKeySequence::Redo);
    connect(ui->actionRedo, &QAction::triggered, ui->textEdit, &QTextEdit::redo);


#ifndef QT_NO_CLIPBOARD
    ui->actionCut->setPriority(QAction::LowPriority);
    ui->actionCut->setShortcut(QKeySequence::Cut);
    connect(ui->actionCut, &QAction::triggered, ui->textEdit, &QTextEdit::cut);


    ui->actionCopy->setPriority(QAction::LowPriority);
    ui->actionCopy->setShortcut(QKeySequence::Copy);
    connect(ui->actionCopy, &QAction::triggered, ui->textEdit, &QTextEdit::copy);

    ui->actionPaste->setPriority(QAction::LowPriority);
    ui->actionPaste->setShortcut(QKeySequence::Paste);
    connect(ui->actionPaste, &QAction::triggered, ui->textEdit, &QTextEdit::paste);

    if (const QMimeData *md = QApplication::clipboard()->mimeData())
        ui->actionPaste->setEnabled(md->hasText());
#endif
}

void HtmlEditor::setupTextActions()
{
    ui->actionTextBold->setShortcut(Qt::CTRL + Qt::Key_B);
    ui->actionTextBold->setPriority(QAction::LowPriority);
    connect(ui->actionTextBold, &QAction::triggered, this, &HtmlEditor::textBold);

    QFont bold;
    bold.setBold(true);
    ui->actionTextBold->setFont(bold);
    ui->actionTextBold->setCheckable(true);

    ui->actionTextItalic->setPriority(QAction::LowPriority);
    ui->actionTextItalic->setShortcut(Qt::CTRL + Qt::Key_I);
    connect(ui->actionTextItalic, &QAction::triggered, this, &HtmlEditor::textItalic);

    QFont italic;
    italic.setItalic(true);
    ui->actionTextItalic->setFont(italic);
    ui->actionTextItalic->setCheckable(true);

    ui->actionTextUnderline->setShortcut(Qt::CTRL + Qt::Key_U);
    ui->actionTextUnderline->setPriority(QAction::LowPriority);
    connect(ui->actionTextUnderline, &QAction::triggered, this, &HtmlEditor::textUnderline);

    QFont underline;
    underline.setUnderline(true);
    ui->actionTextUnderline->setFont(underline);
    ui->actionTextUnderline->setCheckable(true);



    ui->actionAlignLeft->setShortcut(Qt::CTRL + Qt::Key_L);
    ui->actionAlignLeft->setCheckable(true);
    ui->actionAlignLeft->setPriority(QAction::LowPriority);

    ui->actionAlignCenter->setShortcut(Qt::CTRL + Qt::Key_E);
    ui->actionAlignCenter->setCheckable(true);
    ui->actionAlignCenter->setPriority(QAction::LowPriority);

    ui->actionAlignRight->setShortcut(Qt::CTRL + Qt::Key_R);
    ui->actionAlignRight->setCheckable(true);
    ui->actionAlignRight->setPriority(QAction::LowPriority);

    ui->actionAlignJustify->setShortcut(Qt::CTRL + Qt::Key_J);
    ui->actionAlignJustify->setCheckable(true);
    ui->actionAlignJustify->setPriority(QAction::LowPriority);

    // Make sure the alignLeft  is always left of the alignRight
    QActionGroup *alignGroup = new QActionGroup(this);
    connect(alignGroup, &QActionGroup::triggered, this, &HtmlEditor::textAlign);

    if (QApplication::isLeftToRight()) {
        alignGroup->addAction(ui->actionAlignLeft);
        alignGroup->addAction(ui->actionAlignCenter);
        alignGroup->addAction(ui->actionAlignRight);
    } else {
        alignGroup->addAction(ui->actionAlignRight);
        alignGroup->addAction(ui->actionAlignCenter);
        alignGroup->addAction(ui->actionAlignLeft);
    }
    alignGroup->addAction(ui->actionAlignJustify);

    ui->formatToolbar->addActions(alignGroup->actions());
    ui->menuFormat->addActions(alignGroup->actions());

    QPixmap pix(16, 16);
    pix.fill(Qt::black);
    ui->actionTextColor->setIcon(pix);
    connect(ui->actionTextColor, &QAction::triggered, this, &HtmlEditor::textColor);


//    tb = addToolBar(tr("Format Actions"));
//    tb->setAllowedAreas(Qt::TopToolBarArea | Qt::BottomToolBarArea);
//    addToolBarBreak(Qt::TopToolBarArea);
//    addToolBar(tb);

    comboStyle = new QComboBox(ui->styleToolBar);
    ui->styleToolBar->addWidget(comboStyle);
    comboStyle->addItem("Standard");
    comboStyle->addItem("Bullet List (Disc)");
    comboStyle->addItem("Bullet List (Circle)");
    comboStyle->addItem("Bullet List (Square)");
    comboStyle->addItem("Ordered List (Decimal)");
    comboStyle->addItem("Ordered List (Alpha lower)");
    comboStyle->addItem("Ordered List (Alpha upper)");
    comboStyle->addItem("Ordered List (Roman lower)");
    comboStyle->addItem("Ordered List (Roman upper)");

    typedef void (QComboBox::*QComboIntSignal)(int);
    connect(comboStyle, static_cast<QComboIntSignal>(&QComboBox::activated), this, &HtmlEditor::textStyle);

    typedef void (QComboBox::*QComboStringSignal)(const QString &);
    comboFont = new QFontComboBox(ui->styleToolBar);
    ui->styleToolBar->addWidget(comboFont);
    connect(comboFont, static_cast<QComboStringSignal>(&QComboBox::activated), this, &HtmlEditor::textFamily);

    comboSize = new QComboBox(ui->styleToolBar);
    comboSize->setObjectName("comboSize");
    ui->styleToolBar->addWidget(comboSize);
    comboSize->setEditable(true);

    const QList<int> standardSizes = QFontDatabase::standardSizes();
    foreach (int size, standardSizes)
        comboSize->addItem(QString::number(size));
    comboSize->setCurrentIndex(standardSizes.indexOf(QApplication::font().pointSize()));

    connect(comboSize, static_cast<QComboStringSignal>(&QComboBox::activated), this, &HtmlEditor::textSize);
}

bool HtmlEditor::load(const QString &f)
{
    if (!QFile::exists(f))
        return false;
    QFile file(f);
    if (!file.open(QFile::ReadOnly))
        return false;

    QByteArray data = file.readAll();
    QTextCodec *codec = Qt::codecForHtml(data);
    QString str = codec->toUnicode(data);
    if (Qt::mightBeRichText(str)) {
        ui->textEdit->setHtml(str);
    } else {
        str = QString::fromLocal8Bit(data);
        ui->textEdit->setPlainText(str);
    }

    setCurrentFileName(f);
    return true;
}

void HtmlEditor::loadHtml(const QString &_html)
{
    ui->textEdit->setHtml(_html);
}

QString HtmlEditor::saveHtml() const
{
    return ui->textEdit->toHtml();
}

QString HtmlEditor::savePlaintText() const
{
    return ui->textEdit->toPlainText();
}

bool HtmlEditor::getReadOnly() const
{
    return m_isReadOnly;
}

void HtmlEditor::setReadOnly(bool _isReadOnly)
{
    m_isReadOnly = _isReadOnly;

    ui->textEdit->setReadOnly(m_isReadOnly);
    ui->actionAddImage->setEnabled(!m_isReadOnly);
    ui->actionAlignCenter->setEnabled(!m_isReadOnly);
    ui->actionAlignJustify->setEnabled(!m_isReadOnly);
    ui->actionAlignLeft->setEnabled(!m_isReadOnly);
    ui->actionAlignRight->setEnabled(!m_isReadOnly);
    ui->actionCopy->setEnabled(!m_isReadOnly);
    ui->actionCut->setEnabled(!m_isReadOnly);
    ui->actionExportPDF->setEnabled(!m_isReadOnly);
    ui->actionNew->setEnabled(!m_isReadOnly);
    ui->actionOpen->setEnabled(!m_isReadOnly);
    ui->actionPaste->setEnabled(!m_isReadOnly);
    ui->actionPrint->setEnabled(!m_isReadOnly);
    ui->actionPrint_preview->setEnabled(!m_isReadOnly);
    ui->actionRedo->setEnabled(!m_isReadOnly);
    ui->actionSave->setEnabled(!m_isReadOnly);
    ui->actionSave_as->setEnabled(!m_isReadOnly);
    ui->actionTextBold->setEnabled(!m_isReadOnly);
    ui->actionTextColor->setEnabled(!m_isReadOnly);
    ui->actionTextItalic->setEnabled(!m_isReadOnly);
    ui->actionTextUnderline->setEnabled(!m_isReadOnly);
    ui->actionUndo->setEnabled(!m_isReadOnly);

    comboFont->setEnabled(!m_isReadOnly);
    comboSize->setEnabled(!m_isReadOnly);
    comboStyle->setEnabled(!m_isReadOnly);
}

bool HtmlEditor::maybeSave()
{
    if (!ui->textEdit->document()->isModified())
        return true;

    const QMessageBox::StandardButton ret =
        QMessageBox::warning(this, QCoreApplication::applicationName(),
                             tr("The document has been modified.\n"
                                "Do you want to save your changes?"),
                             QMessageBox::Save | QMessageBox::Discard | QMessageBox::Cancel);
    if (ret == QMessageBox::Save)
        return fileSave();
    else if (ret == QMessageBox::Cancel)
        return false;
    return true;
}

void HtmlEditor::setCurrentFileName(const QString &fileName)
{
    this->fileName = fileName;
    ui->textEdit->document()->setModified(false);

    QString shownName;
    if (fileName.isEmpty())
        shownName = "untitled.txt";
    else
        shownName = QFileInfo(fileName).fileName();

    setWindowTitle(tr("%1[*] - %2").arg(shownName, QCoreApplication::applicationName()));
    setWindowModified(false);
}

void HtmlEditor::fileNew()
{
    if (maybeSave()) {
        ui->textEdit->clear();
        setCurrentFileName(QString());
    }
}


void HtmlEditor::fileOpen()
{
    QFileDialog fileDialog(this, tr("Open File..."));
    fileDialog.setAcceptMode(QFileDialog::AcceptOpen);
    fileDialog.setFileMode(QFileDialog::ExistingFile);
    fileDialog.setMimeTypeFilters(QStringList() << "text/html" << "text/plain");
    if (fileDialog.exec() != QDialog::Accepted)
        return;
    const QString fn = fileDialog.selectedFiles().first();
    if (load(fn))
        statusBar()->showMessage(tr("Opened \"%1\"").arg(QDir::toNativeSeparators(fn)));
    else
        statusBar()->showMessage(tr("Could not open \"%1\"").arg(QDir::toNativeSeparators(fn)));
}

bool HtmlEditor::fileSave()
{
    if (fileName.isEmpty())
        return fileSaveAs();
    if (fileName.startsWith(QStringLiteral(":/")))
        return fileSaveAs();

    QTextDocumentWriter writer(fileName);
    bool success = writer.write(ui->textEdit->document());
    if (success) {
        ui->textEdit->document()->setModified(false);
        statusBar()->showMessage(tr("Wrote \"%1\"").arg(QDir::toNativeSeparators(fileName)));
    } else {
        statusBar()->showMessage(tr("Could not write to file \"%1\"")
                                 .arg(QDir::toNativeSeparators(fileName)));
    }
    return success;
}

bool HtmlEditor::fileSaveAs()
{
    QFileDialog fileDialog(this, tr("Save as..."));
    fileDialog.setAcceptMode(QFileDialog::AcceptSave);
    QStringList mimeTypes;
    mimeTypes << "application/vnd.oasis.opendocument.text" << "text/html" << "text/plain";
    fileDialog.setMimeTypeFilters(mimeTypes);
    fileDialog.setDefaultSuffix("odt");
    if (fileDialog.exec() != QDialog::Accepted)
        return false;
    const QString fn = fileDialog.selectedFiles().first();
    setCurrentFileName(fn);
    return fileSave();
}

void HtmlEditor::filePrint()
{
#if !defined(QT_NO_PRINTER) && !defined(QT_NO_PRINTDIALOG)
    QPrinter printer(QPrinter::HighResolution);
    QPrintDialog *dlg = new QPrintDialog(&printer, this);
    if (ui->textEdit->textCursor().hasSelection())
        dlg->addEnabledOption(QAbstractPrintDialog::PrintSelection);
    dlg->setWindowTitle(tr("Print Document"));
    if (dlg->exec() == QDialog::Accepted)
        ui->textEdit->print(&printer);
    delete dlg;
#endif
}

void HtmlEditor::filePrintPreview()
{
#if !defined(QT_NO_PRINTER) && !defined(QT_NO_PRINTDIALOG)
    QPrinter printer(QPrinter::HighResolution);
    QPrintPreviewDialog preview(&printer, this);
    connect(&preview, &QPrintPreviewDialog::paintRequested, this, &HtmlEditor::printPreview);
    preview.exec();
#endif
}

void HtmlEditor::printPreview(QPrinter *printer)
{
#ifdef QT_NO_PRINTER
    Q_UNUSED(printer);
#else
    ui->textEdit->print(printer);
#endif
}


void HtmlEditor::filePrintPdf()
{
#ifndef QT_NO_PRINTER
//! [0]
    QFileDialog fileDialog(this, tr("Export PDF"));
    fileDialog.setAcceptMode(QFileDialog::AcceptSave);
    fileDialog.setMimeTypeFilters(QStringList("application/pdf"));
    fileDialog.setDefaultSuffix("pdf");
    if (fileDialog.exec() != QDialog::Accepted)
        return;
    QString fileName = fileDialog.selectedFiles().first();
    QPrinter printer(QPrinter::HighResolution);
    printer.setOutputFormat(QPrinter::PdfFormat);
    printer.setOutputFileName(fileName);
    ui->textEdit->document()->print(&printer);
    statusBar()->showMessage(tr("Exported \"%1\"")
                             .arg(QDir::toNativeSeparators(fileName)));
//! [0]
#endif
}

void HtmlEditor::textBold()
{
    QTextCharFormat fmt;
    fmt.setFontWeight(ui->actionTextBold->isChecked() ? QFont::Bold : QFont::Normal);
    mergeFormatOnWordOrSelection(fmt);
}

void HtmlEditor::textUnderline()
{
    QTextCharFormat fmt;
    fmt.setFontUnderline(ui->actionTextUnderline->isChecked());
    mergeFormatOnWordOrSelection(fmt);
}

void HtmlEditor::textItalic()
{
    QTextCharFormat fmt;
    fmt.setFontItalic(ui->actionTextItalic->isChecked());
    mergeFormatOnWordOrSelection(fmt);
}

void HtmlEditor::textFamily(const QString &f)
{
    QTextCharFormat fmt;
    fmt.setFontFamily(f);
    mergeFormatOnWordOrSelection(fmt);
}

void HtmlEditor::textSize(const QString &p)
{
    qreal pointSize = p.toFloat();
    if (p.toFloat() > 0) {
        QTextCharFormat fmt;
        fmt.setFontPointSize(pointSize);
        mergeFormatOnWordOrSelection(fmt);
    }
}

void HtmlEditor::textStyle(int styleIndex)
{
    QTextCursor cursor = ui->textEdit->textCursor();

    if (styleIndex != 0) {
        QTextListFormat::Style style = QTextListFormat::ListDisc;

        switch (styleIndex) {
            default:
            case 1:
                style = QTextListFormat::ListDisc;
                break;
            case 2:
                style = QTextListFormat::ListCircle;
                break;
            case 3:
                style = QTextListFormat::ListSquare;
                break;
            case 4:
                style = QTextListFormat::ListDecimal;
                break;
            case 5:
                style = QTextListFormat::ListLowerAlpha;
                break;
            case 6:
                style = QTextListFormat::ListUpperAlpha;
                break;
            case 7:
                style = QTextListFormat::ListLowerRoman;
                break;
            case 8:
                style = QTextListFormat::ListUpperRoman;
                break;
        }

        cursor.beginEditBlock();

        QTextBlockFormat blockFmt = cursor.blockFormat();

        QTextListFormat listFmt;

        if (cursor.currentList()) {
            listFmt = cursor.currentList()->format();
        } else {
            listFmt.setIndent(blockFmt.indent() + 1);
            blockFmt.setIndent(0);
            cursor.setBlockFormat(blockFmt);
        }

        listFmt.setStyle(style);

        cursor.createList(listFmt);

        cursor.endEditBlock();
    } else {
        // ####
        QTextBlockFormat bfmt;
        bfmt.setObjectIndex(-1);
        cursor.mergeBlockFormat(bfmt);
    }
}

void HtmlEditor::textColor()
{
    QColor col = QColorDialog::getColor(ui->textEdit->textColor(), this);
    if (!col.isValid())
        return;
    QTextCharFormat fmt;
    fmt.setForeground(col);
    mergeFormatOnWordOrSelection(fmt);
    colorChanged(col);
}

void HtmlEditor::textAlign(QAction *a)
{
    if (a == ui->actionAlignLeft)
        ui->textEdit->setAlignment(Qt::AlignLeft | Qt::AlignAbsolute);
    else if (a == ui->actionAlignCenter)
        ui->textEdit->setAlignment(Qt::AlignHCenter);
    else if (a == ui->actionAlignRight)
        ui->textEdit->setAlignment(Qt::AlignRight | Qt::AlignAbsolute);
    else if (a == ui->actionAlignJustify)
        ui->textEdit->setAlignment(Qt::AlignJustify);
}

void HtmlEditor::currentCharFormatChanged(const QTextCharFormat &format)
{
    fontChanged(format.font());
    colorChanged(format.foreground().color());
}

void HtmlEditor::cursorPositionChanged()
{
    alignmentChanged(ui->textEdit->alignment());
}

void HtmlEditor::clipboardDataChanged()
{
#ifndef QT_NO_CLIPBOARD
    if (const QMimeData *md = QApplication::clipboard()->mimeData())
        ui->actionPaste->setEnabled(md->hasText());
#endif
}

void HtmlEditor::mergeFormatOnWordOrSelection(const QTextCharFormat &format)
{
    QTextCursor cursor = ui->textEdit->textCursor();
    if (!cursor.hasSelection())
        cursor.select(QTextCursor::WordUnderCursor);
    cursor.mergeCharFormat(format);
    ui->textEdit->mergeCurrentCharFormat(format);
}

void HtmlEditor::fontChanged(const QFont &f)
{
    comboFont->setCurrentIndex(comboFont->findText(QFontInfo(f).family()));
    comboSize->setCurrentIndex(comboSize->findText(QString::number(f.pointSize())));
    ui->actionTextBold->setChecked(f.bold());
    ui->actionTextItalic->setChecked(f.italic());
    ui->actionTextUnderline->setChecked(f.underline());
}

void HtmlEditor::colorChanged(const QColor &c)
{
    QPixmap pix(16, 16);
    pix.fill(c);
    ui->actionTextColor->setIcon(pix);
}

void HtmlEditor::alignmentChanged(Qt::Alignment a)
{
    if (a & Qt::AlignLeft)
        ui->actionAlignLeft->setChecked(true);
    else if (a & Qt::AlignHCenter)
        ui->actionAlignCenter->setChecked(true);
    else if (a & Qt::AlignRight)
        ui->actionAlignRight->setChecked(true);
    else if (a & Qt::AlignJustify)
        ui->actionAlignJustify->setChecked(true);
}


void HtmlEditor::on_actionAddImage_triggered()
{
    ResizableViewDialog dialog(this);
    if(dialog.exec())
    {
        QPixmap pix = dialog.getPixmap();
        QByteArray ba = ImageUtils::imageToByteArray(pix, "PNG");

        ui->textEdit->insertHtml(QString("<img src=\"data:image/png;base64,%1\" width=\"%2\""
                                         " height=\"%3\" alt=\"Image\"/>")
                                 .arg(QString(ba.toBase64()))
                                 .arg(pix.width())
                                 .arg(pix.height()));
    }
}

}
