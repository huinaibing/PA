#ifndef FILTERED_DRAW_GRAPH_H
#define FILTERED_DRAW_GRAPH_H

#include "BaseDrawGraph.h"
#include "BaseFilter.h"

class FilteredDrawGraph : public BaseDrawGraph
{
public:
    FilteredDrawGraph(BaseFilter *filter);
    ~FilteredDrawGraph();

private:
    BaseFilter *filter;
};

#endif
