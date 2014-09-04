#include <cstdio>
#include <string>
#include <QTextBlock>
#include <QWebFrame>
#include "parse_elem_block.h"
#include "BlockData.h"
#include "Preview.h"
#include "ui_Preview.h"
using namespace std;

Preview::Preview(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Preview) {
    ui->setupUi(this);
}

Preview::~Preview() {
    delete ui;
}

void Preview::scrollToLine(int lineNum) {
    char buffer[16];
    sprintf(buffer, "__line__%d__", lineNum);
    //this->ui->webView->page()->currentFrame()->scrollToAnchor(QString::fromUtf8(buffer));
}

void Preview::showPreview(Editor *editor) {
    string html = "";
    auto block = editor->document()->firstBlock();
    int index = 0;
    bool isCode = false;
    char buffer[16];
    while (block.isValid()) {
        auto data = dynamic_cast<BlockData*>(block.userData())->data();
        if (data->blocks.size() == 0) {
            isCode = false;
        } else if ((*data->blocks.rbegin())->type() != ParseElementType::TYPE_CODE_BLOCK) {
            isCode = false;
        }
        ++index;
        if (!isCode) {
            sprintf(buffer, "__line__%d__", index);
            html += "<a href=\"#\" id=\"" + string(buffer) + "\" style=\"display: none\">Check</a>";
        }
        html += data->generateHtml() + "\n";
        if (data->blocks.size() > 0) {
            if ((*data->blocks.rbegin())->type() == ParseElementType::TYPE_CODE_BLOCK) {
                isCode = true;
            }
        }
        block = block.next();
    }
    this->ui->webView->setHtml(QString::fromUtf8(html.c_str()));
}
