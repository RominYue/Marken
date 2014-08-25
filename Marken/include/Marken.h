#ifndef MARKEN_H
#define MARKEN_H

#include <QMainWindow>
#include <QDropEvent>
#include <QDragEnterEvent>
#include <QCloseEvent>

namespace Ui {
class Marken;
}

class Marken : public QMainWindow
{
    Q_OBJECT

public:
    explicit Marken(QWidget *parent = 0);
    ~Marken();

    void closeEvent(QCloseEvent *event) override final;

private:
    void initToolbar();

    bool trySave();
    bool tryCloseAll();

private slots:
    bool tryOpen(QString path);
    void updateTabTitle(bool);

    void on_actionNew_triggered();
    void on_actionOpen_triggered();
    void on_actionSave_triggered();
    void on_actionSave_As_triggered();
    void on_actionClose_triggered();
    void on_actionClose_All_triggered();
    void on_actionQuit_triggered();
    void on_tabWidget_tabCloseRequested(int index);

    void on_actionSave_All_triggered();
    void on_actionUndo_triggered();
    void on_actionRedo_triggered();
    void on_actionCut_triggered();
    void on_actionCopy_triggered();
    void on_actionPaste_triggered();
    void on_actionDelete_triggered();
    void on_actionSelect_All_triggered();
    void on_actionPreference_triggered();

    void on_actionAtx_Header_1_triggered();
    void on_actionAtx_Header_2_triggered();
    void on_actionAtx_Header_3_triggered();
    void on_actionAtx_Header_4_triggered();
    void on_actionAtx_Header_5_triggered();
    void on_actionAtx_Header_6_triggered();
    void on_actionSetext_Header_1_triggered();
    void on_actionSetext_Header_2_triggered();
    void on_actionHorizon_Line_triggered();
    void on_actionInline_Link_triggered();
    void on_actionInline_Code_triggered();
    void on_actionImage_triggered();
    void on_actionReference_Link_triggered();
    void on_actionOrdered_List_triggered();
    void on_actionUnordered_List_triggered();
    void on_actionQuote_triggered();
    void on_actionUnquote_triggered();
    void on_actionLink_Label_triggered();
    void on_actionEmphasis_triggered();
    void on_actionBold_triggered();

    void on_actionPreview_triggered();

    void on_actionSyntax_Document_triggered();

private:
    Ui::Marken *ui;
};

#endif // MARKEN_H
