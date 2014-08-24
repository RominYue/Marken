#include <QFile>
#include <QTextStream>
#include "MarkdownBlockData.h"
#include "MarkdownDebug.h"

MarkdownDebug::MarkdownDebug() {
}

void MarkdownDebug::saveBlockData(QTextDocument *document) const {
    QTextBlock block = document->firstBlock();
    QFile file("block.data");
    if (!file.open(QIODevice::WriteOnly | QIODevice::Text)) {
        return;
    }
    QTextStream out(&file);
    out.setCodec("UTF-8");
    while (block.isValid()) {
        out << "Line: " << block.firstLineNumber() + 1 << endl;
        out << block.text() << endl;
        MarkdownBlockData* data = dynamic_cast<MarkdownBlockData*>(block.userData());
        if (data != nullptr) {
            for (int i = 0; i < data->types()->size(); ++i) {
                out << "    " << data->indent(i) << "\t" << getDataTypeString(data->type(i)) << endl;
            }
        }
        out << endl;
        block = block.next();
    }
    file.close();
}

QString MarkdownDebug::getDataTypeString(MarkdownBlockData::LineType type) const {
    switch (type) {
    case MarkdownBlockData::LINE_DEFAULT:
        return "Paragraph";
    case MarkdownBlockData::LINE_EMPTY:
        return "Empty";
    case MarkdownBlockData::LINE_BLOCK_HTML:
        return "Block HTML";
    case MarkdownBlockData::LINE_BLOCK_HTML_END:
        return "Block HTML End";
    case MarkdownBlockData::LINE_ATX_HEADER_1:
        return "Atx Header 1";
    case MarkdownBlockData::LINE_ATX_HEADER_2:
        return "Atx Header 2";
    case MarkdownBlockData::LINE_ATX_HEADER_3:
        return "Atx Header 3";
    case MarkdownBlockData::LINE_ATX_HEADER_4:
        return "Atx Header 4";
    case MarkdownBlockData::LINE_ATX_HEADER_5:
        return "Atx Header 5";
    case MarkdownBlockData::LINE_ATX_HEADER_6:
        return "Atx Header 6";
    case MarkdownBlockData::LINE_SETEXT_HEADER_1:
        return "Setext Header 1";
    case MarkdownBlockData::LINE_SETEXT_HEADER_2:
        return "Setext Header 2";
    case MarkdownBlockData::LINE_CODE_BLOCK:
        return "Code Block";
    case MarkdownBlockData::LINE_HORIZONTAL:
        return "Horizontal";
    case MarkdownBlockData::LINE_LINK_LABEL:
        return "Link Label";
    case MarkdownBlockData::LINE_BLOCK_QUOTE:
        return "Block Quote";
    case MarkdownBlockData::LINE_ORDERED_LIST:
        return "Ordered List";
    case MarkdownBlockData::LINE_UNORDERED_LIST:
        return "Unordered List";
    case MarkdownBlockData::LINE_INVALID:
        return "Invalid";
    }
    return "";
}
