#pragma once
#ifndef ANDRES_COMPLETE_GRAPH_HXX
#define ANDRES_COMPLETE_GRAPH_HXX

#include <cmath>

#include "graph.hxx"

namespace andres {
namespace graph {

template<typename VISITOR = IdleGraphVisitor>
class CompleteGraph {
public:
    typedef VISITOR Visitor;

    class AdjacencyIterator {
    public:
        typedef CompleteGraph<Visitor> GraphType;
        typedef typename std::random_access_iterator_tag iterator_category;
        typedef Adjacency<> value_type;
        typedef typename std::ptrdiff_t difference_type;

        AdjacencyIterator();
        AdjacencyIterator(const GraphType&);
        AdjacencyIterator(const GraphType&, const std::size_t);
        AdjacencyIterator(const GraphType&, const std::size_t, const std::size_t);

        // increment and decrement
        AdjacencyIterator& operator+=(const difference_type);
        AdjacencyIterator& operator-=(const difference_type);
        AdjacencyIterator& operator++(); // prefix
        AdjacencyIterator& operator--(); // prefix
        AdjacencyIterator operator++(int); // postfix
        AdjacencyIterator operator--(int); // postfix
        AdjacencyIterator operator+(const difference_type) const;
        AdjacencyIterator operator-(const difference_type) const;

        // comparison
        bool operator==(const AdjacencyIterator&) const;
        bool operator!=(const AdjacencyIterator&) const;
        bool operator<(const AdjacencyIterator&) const;
        bool operator<=(const AdjacencyIterator&) const;
        bool operator>(const AdjacencyIterator&) const;
        bool operator>=(const AdjacencyIterator&) const;

        // access
        Adjacency<> operator*() const;
        Adjacency<> operator[](const std::size_t) const;

    protected:
        const GraphType* graph_;
        std::size_t vertex_;
        std::size_t adjacencyIndex_;
    };

    class VertexIterator
    :   public AdjacencyIterator {
    public:
        typedef CompleteGraph<Visitor> GraphType;
        typedef AdjacencyIterator Base;
        typedef typename Base::iterator_category iterator_category;
        typedef typename Base::value_type value_type;
        typedef typename Base::difference_type difference_type;

        VertexIterator();
        VertexIterator(const VertexIterator&);
        VertexIterator(const AdjacencyIterator&);
        VertexIterator(const GraphType&);
        VertexIterator(const GraphType&, const std::size_t);
        VertexIterator(const GraphType&, const std::size_t, const std::size_t);

        // access
        std::size_t operator*() const;
        std::size_t operator[](const std::size_t) const;
    };

    class EdgeIterator
    :   public AdjacencyIterator {
    public:
        typedef CompleteGraph<Visitor> GraphType;
        typedef AdjacencyIterator Base;
        typedef typename Base::iterator_category iterator_category;
        typedef typename Base::value_type value_type;
        typedef typename Base::difference_type difference_type;

        EdgeIterator();
        EdgeIterator(const EdgeIterator&);
        EdgeIterator(const AdjacencyIterator&);
        EdgeIterator(const GraphType&);
        EdgeIterator(const GraphType&, const std::size_t);
        EdgeIterator(const GraphType&, const std::size_t, const std::size_t);

        // access
        std::size_t operator*() const;
        std::size_t operator[](const std::size_t) const;
    };

    // construction
    CompleteGraph(const Visitor& = Visitor());
    CompleteGraph(const std::size_t, const Visitor& = Visitor());
    void assign(const Visitor& = Visitor());
    void assign(const std::size_t, const Visitor& = Visitor());

    // iterator access (compatible with Digraph)
    VertexIterator verticesFromVertexBegin(const std::size_t) const;
    VertexIterator verticesFromVertexEnd(const std::size_t) const;
    VertexIterator verticesToVertexBegin(const std::size_t) const;
    VertexIterator verticesToVertexEnd(const std::size_t) const;
    EdgeIterator edgesFromVertexBegin(const std::size_t) const;
    EdgeIterator edgesFromVertexEnd(const std::size_t) const;
    EdgeIterator edgesToVertexBegin(const std::size_t) const;
    EdgeIterator edgesToVertexEnd(const std::size_t) const;
    AdjacencyIterator adjacenciesFromVertexBegin(const std::size_t) const;
    AdjacencyIterator adjacenciesFromVertexEnd(const std::size_t) const;
    AdjacencyIterator adjacenciesToVertexBegin(const std::size_t) const;
    AdjacencyIterator adjacenciesToVertexEnd(const std::size_t) const;

    // access (compatible with Digraph)
    std::size_t numberOfVertices() const;
    std::size_t numberOfEdges() const;
    std::size_t numberOfEdgesFromVertex(const std::size_t) const;
    std::size_t numberOfEdgesToVertex(const std::size_t) const;
    std::size_t vertexOfEdge(const std::size_t, const std::size_t) const;
    std::size_t edgeFromVertex(const std::size_t, const std::size_t) const;
    std::size_t edgeToVertex(const std::size_t, const std::size_t) const;
    std::size_t vertexFromVertex(const std::size_t, const std::size_t) const;
    std::size_t vertexToVertex(const std::size_t, const std::size_t) const;
    Adjacency<> adjacencyFromVertex(const std::size_t, const std::size_t) const;
    Adjacency<> adjacencyToVertex(const std::size_t, const std::size_t) const;
    std::pair<bool, std::size_t> findEdge(const std::size_t, const std::size_t) const;
    bool multipleEdgesEnabled() const;

private:
    std::size_t edgeOfStrictlyIncreasingPairOfVertices(const std::size_t, const std::size_t) const;

    std::size_t numberOfVertices_;
    Visitor visitor_;
};

template<typename VISITOR>
inline
CompleteGraph<VISITOR>::CompleteGraph(
    const Visitor& visitor
)
:   numberOfVertices_(0),
    visitor_(visitor)
{}

template<typename VISITOR>
inline
CompleteGraph<VISITOR>::CompleteGraph(
    const std::size_t numberOfVertices,
    const Visitor& visitor
)
:   numberOfVertices_(numberOfVertices),
    visitor_(visitor)
{}

template<typename VISITOR>
inline void
CompleteGraph<VISITOR>::assign(
    const Visitor& visitor
) {
    numberOfVertices_ = 0;
    visitor_ = visitor;
}

template<typename VISITOR>
inline void
CompleteGraph<VISITOR>::assign(
    const std::size_t numberOfVertices,
    const Visitor& visitor
) {
    numberOfVertices_ = numberOfVertices;
    visitor_ = visitor;
}

template<typename VISITOR>
inline typename CompleteGraph<VISITOR>::VertexIterator
CompleteGraph<VISITOR>::verticesFromVertexBegin(
    const std::size_t vertex
) const {
    return VertexIterator(*this, vertex, 0);
}

template<typename VISITOR>
inline typename CompleteGraph<VISITOR>::VertexIterator
CompleteGraph<VISITOR>::verticesFromVertexEnd(
    const std::size_t vertex
) const {
    return VertexIterator(*this, vertex, numberOfEdgesFromVertex(vertex));
}

template<typename VISITOR>
inline typename CompleteGraph<VISITOR>::VertexIterator
CompleteGraph<VISITOR>::verticesToVertexBegin(
    const std::size_t vertex
) const {
    return VertexIterator(*this, vertex, 0);
}

template<typename VISITOR>
inline typename CompleteGraph<VISITOR>::VertexIterator
CompleteGraph<VISITOR>::verticesToVertexEnd(
    const std::size_t vertex
) const {
    return VertexIterator(*this, vertex, numberOfEdgesFromVertex(vertex));
}

template<typename VISITOR>
inline typename CompleteGraph<VISITOR>::EdgeIterator
CompleteGraph<VISITOR>::edgesFromVertexBegin(
    const std::size_t vertex
) const {
    return EdgeIterator(*this, vertex, 0);
}

template<typename VISITOR>
inline typename CompleteGraph<VISITOR>::EdgeIterator
CompleteGraph<VISITOR>::edgesFromVertexEnd(
    const std::size_t vertex
) const {
    return EdgeIterator(*this, vertex, numberOfEdgesFromVertex(vertex));
}

template<typename VISITOR>
inline typename CompleteGraph<VISITOR>::EdgeIterator
CompleteGraph<VISITOR>::edgesToVertexBegin(
    const std::size_t vertex
) const {
    return EdgeIterator(*this, vertex, 0);
}

template<typename VISITOR>
inline typename CompleteGraph<VISITOR>::EdgeIterator
CompleteGraph<VISITOR>::edgesToVertexEnd(
    const std::size_t vertex
) const {
    return EdgeIterator(*this, vertex, numberOfEdgesFromVertex(vertex));
}

template<typename VISITOR>
inline typename CompleteGraph<VISITOR>::AdjacencyIterator
CompleteGraph<VISITOR>::adjacenciesFromVertexBegin(
    const std::size_t vertex
) const {
    return AdjacencyIterator(*this, vertex, 0);
}

template<typename VISITOR>
inline typename CompleteGraph<VISITOR>::AdjacencyIterator
CompleteGraph<VISITOR>::adjacenciesFromVertexEnd(
    const std::size_t vertex
) const {
    return AdjacencyIterator(*this, vertex, numberOfEdgesFromVertex(vertex));
}

template<typename VISITOR>
inline typename CompleteGraph<VISITOR>::AdjacencyIterator
CompleteGraph<VISITOR>::adjacenciesToVertexBegin(
    const std::size_t vertex
) const {
    return AdjacencyIterator(*this, vertex, 0);
}

template<typename VISITOR>
inline typename CompleteGraph<VISITOR>::AdjacencyIterator
CompleteGraph<VISITOR>::adjacenciesToVertexEnd(
    const std::size_t vertex
) const {
    return AdjacencyIterator(*this, vertex, numberOfEdgesFromVertex(vertex));
}

template<typename VISITOR>
inline std::size_t
CompleteGraph<VISITOR>::numberOfVertices() const {
    return numberOfVertices_;
}

template<typename VISITOR>
inline std::size_t
CompleteGraph<VISITOR>::numberOfEdges() const {
    return numberOfVertices() * (numberOfVertices() - 1) / 2;
}

template<typename VISITOR>
inline std::size_t
CompleteGraph<VISITOR>::numberOfEdgesFromVertex(
    const std::size_t vertex
) const {
    assert(vertex < numberOfVertices());
    return numberOfVertices() - 1;
}

template<typename VISITOR>
inline std::size_t
CompleteGraph<VISITOR>::numberOfEdgesToVertex(
    const std::size_t vertex
) const {
    assert(vertex < numberOfVertices());
    return numberOfVertices() - 1;
}

template<typename VISITOR>
inline std::size_t
CompleteGraph<VISITOR>::vertexOfEdge(
    const std::size_t edgeIndex,
    const std::size_t j
) const {
    assert(edgeIndex < numberOfEdges());
    assert(j < 2);
    const float p = static_cast<float>(numberOfVertices() * 2 - 1) / 2;
    const float q = static_cast<float>(edgeIndex) * 2;
    const std::size_t vertex0 = static_cast<std::size_t>(p - std::sqrt(p * p - q));
    if(j == 0) {
        return vertex0;
    }
    else {
        return edgeIndex + vertex0 * (vertex0 + 1) / 2 - (numberOfVertices() - 1) * vertex0 + 1;
    }
}

template<typename VISITOR>
inline std::size_t
CompleteGraph<VISITOR>::edgeFromVertex(
    const std::size_t vertex,
    const std::size_t j
) const {
    assert(j < numberOfEdgesFromVertex(vertex));
    if(j < vertex) {
        const std::size_t vertexAdjacent = j;
        const std::size_t edgeAdjacent = edgeOfStrictlyIncreasingPairOfVertices(vertexAdjacent, vertex);
        return edgeAdjacent;
    }
    else {
        const std::size_t vertexAdjacent = j + 1;
        const std::size_t edgeAdjacent = edgeOfStrictlyIncreasingPairOfVertices(vertex, vertexAdjacent);
        return edgeAdjacent;
    }
}

template<typename VISITOR>
inline std::size_t
CompleteGraph<VISITOR>::edgeToVertex(
    const std::size_t vertex,
    const std::size_t j
) const {
    assert(j < numberOfEdgesToVertex(vertex));
    return edgeFromVertex(vertex, j);
}

template<typename VISITOR>
inline std::size_t
CompleteGraph<VISITOR>::vertexFromVertex(
    const std::size_t vertex,
    const std::size_t j
) const {
    assert(j < numberOfEdgesFromVertex(vertex));
    if(j < vertex) {
        return j;
    }
    else {
        return j + 1;
    }
}

template<typename VISITOR>
inline std::size_t
CompleteGraph<VISITOR>::vertexToVertex(
    const std::size_t vertex,
    const std::size_t j
) const {
    assert(j < numberOfEdgesToVertex(vertex));
    return vertexFromVertex(vertex, j);
}

template<typename VISITOR>
inline Adjacency<>
CompleteGraph<VISITOR>::adjacencyFromVertex(
    const std::size_t vertex,
    const std::size_t j
) const {
    assert(j < numberOfEdgesToVertex(vertex));
    if(j < vertex) {
        const std::size_t vertexAdjacent = j;
        const std::size_t edgeAdjacent = edgeOfStrictlyIncreasingPairOfVertices(vertexAdjacent, vertex);
        return Adjacency<>(vertexAdjacent, edgeAdjacent);
    }
    else {
        const std::size_t vertexAdjacent = j + 1;
        const std::size_t edgeAdjacent = edgeOfStrictlyIncreasingPairOfVertices(vertex, vertexAdjacent);
        return Adjacency<>(vertexAdjacent, edgeAdjacent);
    }
}

template<typename VISITOR>
inline Adjacency<>
CompleteGraph<VISITOR>::adjacencyToVertex(
    const std::size_t vertex,
    const std::size_t j
) const {
    return adjacencyFromVertex(vertex, j);
}

/// findEdge(vertex0, vertex1)
///    - 0 1 2
///    0 - 3 4
///    1 3 - 5
///    2 4 5 -
template<typename VISITOR>
inline std::pair<bool, std::size_t>
CompleteGraph<VISITOR>::findEdge(
    const std::size_t vertex0,
    const std::size_t vertex1
) const {
    assert(vertex0 < numberOfVertices());
    assert(vertex1 < numberOfVertices());
    if(vertex0 == vertex1) {
        return std::pair<bool, std::size_t>(false, 0);
    }
    else if(vertex0 < vertex1) {
        return std::pair<bool, std::size_t>(true, edgeOfStrictlyIncreasingPairOfVertices(vertex0, vertex1));
    }
    else {
        return std::pair<bool, std::size_t>(true, edgeOfStrictlyIncreasingPairOfVertices(vertex1, vertex0));
    }
}

template<typename VISITOR>
inline bool
CompleteGraph<VISITOR>::multipleEdgesEnabled() const {
    return false;
}

template<typename VISITOR>
inline std::size_t
CompleteGraph<VISITOR>::edgeOfStrictlyIncreasingPairOfVertices(
    const std::size_t vertex0,
    const std::size_t vertex1
) const {
    assert(vertex1 < numberOfVertices());
    assert(vertex0 < vertex1);
    return (numberOfVertices() - 1) * vertex0 - vertex0 * (vertex0 + 1) / 2 + vertex1 - 1;
}

// implementation of AdjacencyIterator

template<typename VISITOR>
inline
CompleteGraph<VISITOR>::AdjacencyIterator::AdjacencyIterator()
:   graph_(0),
    vertex_(0),
    adjacencyIndex_(0)
{}

template<typename VISITOR>
inline
CompleteGraph<VISITOR>::AdjacencyIterator::AdjacencyIterator(
    const GraphType& graph
)
:   graph_(&graph),
    vertex_(0),
    adjacencyIndex_(0)
{}

template<typename VISITOR>
inline
CompleteGraph<VISITOR>::AdjacencyIterator::AdjacencyIterator(
    const GraphType& graph,
    const std::size_t vertex
)
:   graph_(&graph),
    vertex_(vertex),
    adjacencyIndex_(0)
{
    assert(vertex < graph.numberOfVertices());
}

template<typename VISITOR>
inline
CompleteGraph<VISITOR>::AdjacencyIterator::AdjacencyIterator(
    const GraphType& graph,
    const std::size_t vertex,
    const std::size_t adjacencyIndex
)
:   graph_(&graph),
    vertex_(vertex),
    adjacencyIndex_(adjacencyIndex)
{
    assert(vertex < graph.numberOfVertices());
    assert(adjacencyIndex <= graph.numberOfVertices());
}

template<typename VISITOR>
inline typename CompleteGraph<VISITOR>::AdjacencyIterator&
CompleteGraph<VISITOR>::AdjacencyIterator::operator+=(
    const difference_type d
) {
    adjacencyIndex_ += d;
    return *this;
}

template<typename VISITOR>
inline typename CompleteGraph<VISITOR>::AdjacencyIterator&
CompleteGraph<VISITOR>::AdjacencyIterator::operator-=(
    const difference_type d
) {
    adjacencyIndex_ -= d;
    return *this;
}

template<typename VISITOR>
inline typename CompleteGraph<VISITOR>::AdjacencyIterator&
CompleteGraph<VISITOR>::AdjacencyIterator::operator++() {
    ++adjacencyIndex_;
    return *this;
}

template<typename VISITOR>
inline typename CompleteGraph<VISITOR>::AdjacencyIterator&
CompleteGraph<VISITOR>::AdjacencyIterator::operator--() {
    --adjacencyIndex_;
    return *this;
}

template<typename VISITOR>
inline typename CompleteGraph<VISITOR>::AdjacencyIterator
CompleteGraph<VISITOR>::AdjacencyIterator::operator++(int) {
    AdjacencyIterator copy = *this;
    ++adjacencyIndex_;
    return copy;
}

template<typename VISITOR>
inline typename CompleteGraph<VISITOR>::AdjacencyIterator
CompleteGraph<VISITOR>::AdjacencyIterator::operator--(int) {
    AdjacencyIterator copy = *this;
    --adjacencyIndex_;
    return copy;
}

template<typename VISITOR>
inline typename CompleteGraph<VISITOR>::AdjacencyIterator
CompleteGraph<VISITOR>::AdjacencyIterator::operator+(
    const difference_type d
) const {
    AdjacencyIterator copy = *this;
    copy += d;
    return copy;
}

template<typename VISITOR>
inline typename CompleteGraph<VISITOR>::AdjacencyIterator
CompleteGraph<VISITOR>::AdjacencyIterator::operator-(
    const difference_type d
) const {
    AdjacencyIterator copy = *this;
    copy -= d;
    return copy;
}

template<typename VISITOR>
inline Adjacency<>
CompleteGraph<VISITOR>::AdjacencyIterator::operator*() const {
    return graph_->adjacencyFromVertex(vertex_, adjacencyIndex_);
}

template<typename VISITOR>
inline Adjacency<>
CompleteGraph<VISITOR>::AdjacencyIterator::operator[](
    const std::size_t j
) const {
    return graph_->adjacencyFromVertex(vertex_, adjacencyIndex_ + j);
}

template<typename VISITOR>
inline bool
CompleteGraph<VISITOR>::AdjacencyIterator::operator==(
    const AdjacencyIterator& other
) const {
    return adjacencyIndex_ == other.adjacencyIndex_
        && vertex_ == other.vertex_
        && graph_ == other.graph_;
}

template<typename VISITOR>
inline bool
CompleteGraph<VISITOR>::AdjacencyIterator::operator!=(
    const AdjacencyIterator& other
) const {
    return adjacencyIndex_ != other.adjacencyIndex_
        || vertex_ != other.vertex_
        || graph_ != other.graph_;
}

template<typename VISITOR>
inline bool
CompleteGraph<VISITOR>::AdjacencyIterator::operator<(
    const AdjacencyIterator& other
) const {
    return adjacencyIndex_ < other.adjacencyIndex_
        && vertex_ == other.vertex_
        && graph_ == other.graph_;
}

template<typename VISITOR>
inline bool
CompleteGraph<VISITOR>::AdjacencyIterator::operator<=(
    const AdjacencyIterator& other
) const {
    return adjacencyIndex_ <= other.adjacencyIndex_
        && vertex_ == other.vertex_
        && graph_ == other.graph_;
}


template<typename VISITOR>
inline bool
CompleteGraph<VISITOR>::AdjacencyIterator::operator>(
    const AdjacencyIterator& other
) const {
    return adjacencyIndex_ > other.adjacencyIndex_
        && vertex_ == other.vertex_
        && graph_ == other.graph_;
}

template<typename VISITOR>
inline bool
CompleteGraph<VISITOR>::AdjacencyIterator::operator>=(
    const AdjacencyIterator& other
) const {
    return adjacencyIndex_ >= other.adjacencyIndex_
        && vertex_ == other.vertex_
        && graph_ == other.graph_;
}

// implementation of VertexIterator

template<typename VISITOR>
inline
CompleteGraph<VISITOR>::VertexIterator::VertexIterator()
:   Base()
{}

template<typename VISITOR>
inline
CompleteGraph<VISITOR>::VertexIterator::VertexIterator(
    const GraphType& graph
)
:   Base(graph)
{}

template<typename VISITOR>
inline
CompleteGraph<VISITOR>::VertexIterator::VertexIterator(
    const GraphType& graph,
    const std::size_t vertex
)
:   Base(graph, vertex)
{}

template<typename VISITOR>
inline
CompleteGraph<VISITOR>::VertexIterator::VertexIterator(
    const GraphType& graph,
    const std::size_t vertex,
    const std::size_t adjacencyIndex
)
:   Base(graph, vertex, adjacencyIndex)
{}

template<typename VISITOR>
inline
CompleteGraph<VISITOR>::VertexIterator::VertexIterator(
    const VertexIterator& it
)
:   Base(*(it.graph_), it.vertex_, it.adjacencyIndex_)
{}

template<typename VISITOR>
inline
CompleteGraph<VISITOR>::VertexIterator::VertexIterator(
    const AdjacencyIterator& it
)
:   Base(it)
{}

template<typename VISITOR>
inline std::size_t
CompleteGraph<VISITOR>::VertexIterator::operator*() const {
    return Base::graph_->vertexFromVertex(Base::vertex_, Base::adjacencyIndex_);
}

template<typename VISITOR>
inline std::size_t
CompleteGraph<VISITOR>::VertexIterator::operator[](
    const std::size_t j
) const {
    return Base::graph_->vertexFromVertex(Base::vertex_, Base::adjacencyIndex_ + j);
}

// implementation of EdgeIterator

template<typename VISITOR>
inline
CompleteGraph<VISITOR>::EdgeIterator::EdgeIterator()
:   Base()
{}

template<typename VISITOR>
inline
CompleteGraph<VISITOR>::EdgeIterator::EdgeIterator(
    const GraphType& graph
)
:   Base(graph)
{}

template<typename VISITOR>
inline
CompleteGraph<VISITOR>::EdgeIterator::EdgeIterator(
    const GraphType& graph,
    const std::size_t vertex
)
:   Base(graph, vertex)
{}

template<typename VISITOR>
inline
CompleteGraph<VISITOR>::EdgeIterator::EdgeIterator(
    const GraphType& graph,
    const std::size_t vertex,
    const std::size_t adjacencyIndex
)
:   Base(graph, vertex, adjacencyIndex)
{}

template<typename VISITOR>
inline
CompleteGraph<VISITOR>::EdgeIterator::EdgeIterator(
    const EdgeIterator& it
)
:   Base(*(it.graph_), it.vertex_, it.adjacencyIndex_)
{}

template<typename VISITOR>
inline
CompleteGraph<VISITOR>::EdgeIterator::EdgeIterator(
    const AdjacencyIterator& it
)
:   Base(it)
{}

template<typename VISITOR>
inline std::size_t
CompleteGraph<VISITOR>::EdgeIterator::operator*() const {
    return Base::graph_->edgeFromVertex(Base::vertex_, Base::adjacencyIndex_);
}

template<typename VISITOR>
inline std::size_t
CompleteGraph<VISITOR>::EdgeIterator::operator[](
    const std::size_t j
) const {
    return Base::graph_->edgeFromVertex(Base::vertex_, Base::adjacencyIndex_ + j);
}

} // namespace graph
} // namespace andres

#endif // #ifndef ANDRES_COMPLETE_GRAPH_HXX
