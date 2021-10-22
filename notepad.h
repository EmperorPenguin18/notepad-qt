#ifndef NOTEPAD_H
#define NOTEPAD_H

#include <QMainWindow>
#include <QFile>
#include <QWidget>
#include <QApplication>
#include <QFileDialog>
#include <QMessageBox>
#include <QTextStream>
#include <QPrinter>
#include <QPrintDialog>
#include <QPainter>
#include <QFontDialog>

QT_BEGIN_NAMESPACE
namespace Ui { class Notepad; }
QT_END_NAMESPACE

class Notepad : public QMainWindow
{
    Q_OBJECT

public:
    Notepad(QWidget *parent = nullptr);
    ~Notepad();

private slots:
    void on_actionNew_triggered();

    void on_actionOpen_triggered();

    void on_actionSave_triggered();

    void on_actionSave_as_triggered();

    void on_actionExit_triggered();

    void on_actionPrint_triggered();

    void on_actionSet_font_triggered();

    void on_actionCopy_triggered();

    void on_actionCut_triggered();

    void on_actionPaste_triggered();

    void on_actionUndo_triggered();

    void on_actionRedo_triggered();

    void on_actionBold_triggered(bool bold);

    void on_actionUnderline_triggered(bool underline);

    void on_actionItalic_triggered(bool italic);

    void on_actionAbout_triggered();

private:
    Ui::Notepad *ui;
    QString currentFile;
};
#endif // NOTEPAD_H
