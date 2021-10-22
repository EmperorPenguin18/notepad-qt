#include "notepad.h"
#include "ui_notepad.h"

Notepad::Notepad(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::Notepad)
{
    ui->setupUi(this);
}

Notepad::~Notepad()
{
    delete ui;
}


void Notepad::on_actionNew_triggered()
{
    currentFile.clear();
    ui->textEdit->setText(QString());
}


void Notepad::on_actionOpen_triggered()
{
    QString fileName = QFileDialog::getOpenFileName(this, "Open the file");
    QFile file(fileName);
    currentFile = fileName;
    if (!file.open(QIODevice::ReadOnly | QFile::Text)) {
        QMessageBox::warning(this, "Warning", "Cannot open file: " + file.errorString());
        return;
    }
    setWindowTitle(fileName);
    QTextStream in(&file);
    QString text = in.readAll();
    ui->textEdit->setText(text);
    file.close();
}


void Notepad::on_actionSave_triggered()
{
    QString fileName;
    // If we don't have a filename from before, get one.
    if (currentFile.isEmpty()) {
        fileName = QFileDialog::getSaveFileName(this, "Save");
        currentFile = fileName;
    } else {
        fileName = currentFile;
    }
    QFile file(fileName);
    if (!file.open(QIODevice::WriteOnly | QFile::Text)) {
        QMessageBox::warning(this, "Warning", "Cannot save file: " + file.errorString());
        return;
    }
    setWindowTitle(fileName);
    QTextStream out(&file);
    QString text = ui->textEdit->toPlainText();
    out << text;
    file.close();
}


void Notepad::on_actionSave_as_triggered()
{
    QString fileName = QFileDialog::getSaveFileName(this, "Save as");
    QFile file(fileName);

    if (!file.open(QFile::WriteOnly | QFile::Text)) {
        QMessageBox::warning(this, "Warning", "Cannot save file: " + file.errorString());
        return;
    }
    currentFile = fileName;
    setWindowTitle(fileName);
    QTextStream out(&file);
    QString text = ui->textEdit->toPlainText();
    out << text;
    file.close();
}


void Notepad::on_actionExit_triggered()
{
    QCoreApplication::quit();
}


void Notepad::on_actionPrint_triggered()
{
    QPrinter printer;

    QPrintDialog dialog(&printer, this);
    dialog.setWindowTitle(tr("Print Document"));
    if (ui->textEdit->textCursor().hasSelection())
        dialog.addEnabledOption(QAbstractPrintDialog::PrintSelection);
    if (dialog.exec() != QDialog::Accepted) {
        return;
    }

    QPainter painter;
    painter.begin(&printer);
    painter.drawText(100, 100, 500, 500, Qt::AlignLeft|Qt::AlignTop, ui->textEdit->toPlainText());
    painter.end();
}


void Notepad::on_actionSet_font_triggered()
{
    bool fontSelected;
    QFont font = QFontDialog::getFont(&fontSelected, this);
    if (fontSelected)
        ui->textEdit->setFont(font);
}

void Notepad::on_actionCopy_triggered()
{
#if QT_CONFIG(clipboard)
    ui->textEdit->copy();
#endif
}


void Notepad::on_actionCut_triggered()
{
#if QT_CONFIG(clipboard)
    ui->textEdit->cut();
#endif
}


void Notepad::on_actionPaste_triggered()
{
#if QT_CONFIG(clipboard)
    ui->textEdit->paste();
#endif
}


void Notepad::on_actionUndo_triggered()
{
    ui->textEdit->undo();
}


void Notepad::on_actionRedo_triggered()
{
    ui->textEdit->redo();
}


void Notepad::on_actionBold_triggered(bool bold)
{
    bold ? ui->textEdit->setFontWeight(QFont::Bold) :
               ui->textEdit->setFontWeight(QFont::Normal);
}


void Notepad::on_actionUnderline_triggered(bool underline)
{
    ui->textEdit->setFontUnderline(underline);
}


void Notepad::on_actionItalic_triggered(bool italic)
{
    ui->textEdit->setFontItalic(italic);
}


void Notepad::on_actionAbout_triggered()
{
    QMessageBox::about(this, tr("About MDI"),
                    tr("The <b>Notepad</b> example demonstrates how to code a basic "
                       "text editor using QtWidgets"));
}

