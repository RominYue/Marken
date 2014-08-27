#ifndef PARSE_LINE_DATA_H_INCLUDED
#define PARSE_LINE_DATA_H_INCLUDED

#include <set>
#include <vector>
#include <string>
#include <memory>

class ParseElem;

class ParseLineData {
public:
    ParseLineData();
    ParseLineData(const ParseLineData&) = default;
    ParseLineData& operator=(const ParseLineData&) = default;
    virtual ~ParseLineData();

    ParseLineData* prev() const;
    ParseLineData* next() const;
    void setNeighbor(ParseLineData *prev, ParseLineData *next);
    void removeFromList();

    std::set<std::shared_ptr<ParseElem>>* future();
    void insertToFuture(std::shared_ptr<ParseElem> elem);

    std::vector<std::shared_ptr<ParseElem>>& elems();
    std::shared_ptr<ParseElem> operator [](const int index) const;
    std::string generateHtml() const;

    bool isChanged() const;
    void saveStruct();

private:
    ParseLineData* _prev;
    ParseLineData* _next;
    std::set<std::shared_ptr<ParseElem>> _future;

    std::vector<std::shared_ptr<ParseElem>> _elems;
    std::vector<std::shared_ptr<ParseElem>> _olds;
};

#endif // PARSE_LINE_DATA_H_INCLUDED
